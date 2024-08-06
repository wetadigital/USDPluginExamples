//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//

#include "./triGenerative.h"
#include "./debugCodes.h"
#include <pxr/imaging/hd/retainedDataSource.h>
#include <pxr/imaging/hd/primvarsSchema.h>
#include <pxr/imaging/hd/meshSchema.h>
#include <pxr/imaging/hd/tokens.h>
#include <pxr/imaging/hd/xformSchema.h>
#include <pxr/base/tf/token.h>
#include <pxr/base/tf/stringUtils.h>

PXR_NAMESPACE_USING_DIRECTIVE

namespace {
TF_DEFINE_PRIVATE_TOKENS(_makeSomeStuffTokens, (sideLength)(myTriangle));
}

/// @brief the data-source containing the Point positions for a triangle
/// based on the sideLength
class _PointsFromSideLengthDataSource : public HdVec3fArrayDataSource
{
public:
    HD_DECLARE_DATASOURCE(_PointsFromSideLengthDataSource);

    bool GetContributingSampleTimesForInterval(
        Time startTime,
        Time endTime,
        std::vector<Time>* outSampleTimes) override
    {

        const bool result =
            _sideLengthDs->GetContributingSampleTimesForInterval(
                startTime, endTime, outSampleTimes);

        TF_DEBUG(USDTRI_GENERATIVE)
            .Msg("GetContributingSampleTimesForInterval -  (%f-%f) @ %lu  \n",
                 startTime,
                 endTime,
                 outSampleTimes->size());
        return result;
    }

    VtValue GetValue(Time shutterOffset)
    {
        return VtValue(GetTypedValue(shutterOffset));
    }

    VtArray<GfVec3f> GetTypedValue(Time shutterOffset)
    {

        const double sideLength =
            _sideLengthDs->GetValue(shutterOffset).UncheckedGet<double>();

        VtVec3fArray points{
            GfVec3f(0.0f, 0.57735027f * sideLength, 0.0f),
            GfVec3f(-0.5f * sideLength, -0.28867513f * sideLength, 0.0f),
            GfVec3f(0.5f * sideLength, -0.28867513f * sideLength, 0.0f)
        };
        return points;
    }

private:
    _PointsFromSideLengthDataSource(HdSampledDataSourceHandle sideLengthDs)
      : _sideLengthDs(sideLengthDs)
    {
    }

    HdSampledDataSourceHandle _sideLengthDs;
};

_MakeTriGenerativeProcedural::_MakeTriGenerativeProcedural(
    const SdfPath& i_primPath)
  : HdGpGenerativeProcedural(i_primPath)
{
}

HdGpGenerativeProcedural*
_MakeTriGenerativeProcedural::New(const SdfPath& i_primPath)
{
    return new _MakeTriGenerativeProcedural(i_primPath);
}

HdGpGenerativeProcedural::DependencyMap
_MakeTriGenerativeProcedural::UpdateDependencies(
    const HdSceneIndexBaseRefPtr& i_inputScene)
{
    TF_DEBUG(USDTRI_GENERATIVE)
        .Msg("UpdateDependencies @ Prim - <%s> \n",
             _GetProceduralPrimPath().GetText());

    HdGpGenerativeProcedural::DependencyMap result;
    HdSceneIndexPrim myPrim = i_inputScene->GetPrim(_GetProceduralPrimPath());

    HdPrimvarsSchema primvars =
        HdPrimvarsSchema::GetFromParent(myPrim.dataSource);

    if (HdSampledDataSourceHandle ds =
            primvars.GetPrimvar(_makeSomeStuffTokens->sideLength)
                .GetPrimvarValue()) {
        VtValue v = ds->GetValue(0.0f);
        if (v.IsHolding<double>()) {
            result[_GetProceduralPrimPath().AppendChild(
                _makeSomeStuffTokens->myTriangle)] = {
                HdPrimvarsSchema::GetPointsLocator(),
                HdXformSchema::GetDefaultLocator(),
            };
        }
    }
    return result;
}

HdGpGenerativeProcedural::ChildPrimTypeMap
_MakeTriGenerativeProcedural::Update(
    const HdSceneIndexBaseRefPtr& i_inputScene,
    const HdGpGenerativeProcedural::ChildPrimTypeMap& i_previousResult,
    const HdGpGenerativeProcedural::DependencyMap& i_dirtiedDependencies,
    HdSceneIndexObserver::DirtiedPrimEntries* o_outputDirtiedPrims)
{
    TF_DEBUG(USDTRI_GENERATIVE)
        .Msg("Update @ Prim - <%s> \n", _GetProceduralPrimPath().GetText());

    ChildPrimTypeMap result;
    HdSceneIndexPrim myPrim = i_inputScene->GetPrim(_GetProceduralPrimPath());

    SdfPath primPath = _GetProceduralPrimPath();
    primPath = primPath.AppendChild(_makeSomeStuffTokens->myTriangle);

    // check if any incoming dependencies affect us
    bool lengthChanged = false;
    bool xformChanged = false;
    for (const auto& dd : i_dirtiedDependencies) {

        std::stringstream myStr;
        myStr << dd.second;
        TF_DEBUG(USDTRI_GENERATIVE)
            .Msg("DirtiedDependencies - <%s - %s>\n",
                 dd.first.GetText(),
                 myStr.str().c_str());

        // our length-value likely changed if the sideLength primvar on our
        // procedural prim is dirtied
        lengthChanged |=
            ((dd.first == _GetProceduralPrimPath()) &&
             (dd.second.Contains(HdPrimvarsSchema::GetDefaultLocator().Append(
                 _makeSomeStuffTokens->sideLength))));

        xformChanged |=
            ((dd.first == _GetProceduralPrimPath()) &&
             (dd.second.Contains(HdXformSchema::GetDefaultLocator())));
    }

    // check if any length values have changed
    double sideLength = 1.0f;
    if (HdSampledDataSourceHandle sideLengthDS =
            HdPrimvarsSchema::GetFromParent(myPrim.dataSource)
                .GetPrimvar(_makeSomeStuffTokens->sideLength)
                .GetPrimvarValue()) {
        VtValue v = sideLengthDS->GetValue(0.0f /* timeStamp */);
        // this does not allow animated
        if (v.IsHolding<double>()) {
            sideLength = v.UncheckedGet<double>();

            // our length-value also likely changed if the sideLength value is
            // different than our stored value _sideLength
            lengthChanged |= (sideLength != _sideLength);
            _sideLengthDs = sideLengthDS;
        }
    }

    TF_DEBUG(USDTRI_GENERATIVE)
        .Msg("Update @ Prim - <%s> lengthChanged - %d, xformChanged - %d \n",
             _GetProceduralPrimPath().GetText(),
             lengthChanged,
             xformChanged);

    HdDataSourceLocatorSet dirtySet;
    if (lengthChanged) {
        dirtySet.insert(HdPrimvarsSchema::GetPointsLocator());
    }
    if (xformChanged) {
        dirtySet.insert(HdXformSchema::GetDefaultLocator());
    }
    if (!dirtySet.IsEmpty()) {
        o_outputDirtiedPrims->emplace_back(primPath, dirtySet);
    }

    // new
    result[primPath] = HdPrimTypeTokens->mesh;
    return result;
}

HdContainerDataSourceHandle
_MakeTriGenerativeProcedural::_GetChildPrimvarsDs()
{
    HdContainerDataSourceHandle primvarsDs = HdRetainedContainerDataSource::New(
        HdPrimvarsSchemaTokens->points,
        HdPrimvarSchema::Builder()
            .SetPrimvarValue(
                _PointsFromSideLengthDataSource::New(_sideLengthDs))
            .SetInterpolation(HdPrimvarSchema::BuildInterpolationDataSource(
                HdPrimvarSchemaTokens->vertex))
            .SetRole(HdPrimvarSchema::BuildRoleDataSource(
                HdPrimvarSchemaTokens->point))
            .Build());

    return primvarsDs;
}

HdContainerDataSourceHandle
_MakeTriGenerativeProcedural::_GetChildMeshDs()
{
    // a triangle just has 3 vertices
    static const VtIntArray faceVertexCounts = { 3 };

    // the faceVertex indices
    static const VtIntArray faceVertexIndices = { 0, 1, 2 };

    using _IntArrayDs = HdRetainedTypedSampledDataSource<VtIntArray>;

    // create a data-soure for faceVertexCounts
    static const _IntArrayDs::Handle fvcDs = _IntArrayDs::New(faceVertexCounts);

    // create a data-soure for faceVertexIndices
    static const _IntArrayDs::Handle fviDs =
        _IntArrayDs::New(faceVertexIndices);

    // create a data-soure for our mesh
    static const HdContainerDataSourceHandle meshDs =
        HdMeshSchema::Builder()
            .SetTopology(HdMeshTopologySchema::Builder()
                             .SetFaceVertexCounts(fvcDs)
                             .SetFaceVertexIndices(fviDs)
                             .Build())
            .Build();

    return meshDs;
}

HdSceneIndexPrim
_MakeTriGenerativeProcedural::GetChildPrim(
    const HdSceneIndexBaseRefPtr& i_inputScene,
    const SdfPath& i_childPrimPath)
{
    TF_DEBUG(USDTRI_GENERATIVE)
        .Msg("GetChildPrim @ Prim - <%s> \n", i_childPrimPath.GetText());

    HdSceneIndexPrim result;

    HdSceneIndexPrim parentPrim =
        i_inputScene->GetPrim(_GetProceduralPrimPath());

    HdXformSchema inputXform(
        HdXformSchema::GetFromParent(parentPrim.dataSource));

    static const HdContainerDataSourceHandle identityXform =
        HdXformSchema::Builder()
            .SetMatrix(HdRetainedTypedSampledDataSource<GfMatrix4d>::New(
                GfMatrix4d().SetIdentity()))
            .SetResetXformStack(
                HdRetainedTypedSampledDataSource<bool>::New(true))
            .Build();

    if (i_childPrimPath == _GetProceduralPrimPath().AppendChild(
                               _makeSomeStuffTokens->myTriangle)) {
        result.primType = HdPrimTypeTokens->mesh;
        result.dataSource = HdRetainedContainerDataSource::New(
            HdPrimvarsSchemaTokens->primvars,
            _GetChildPrimvarsDs(),
            HdPrimTypeTokens->mesh,
            _GetChildMeshDs(),
            // use parent xform
            HdXformSchema::GetSchemaToken(),
            inputXform.IsDefined() ? inputXform.GetContainer() : identityXform);
    }
    return result;
}

HdGpGenerativeProcedural*
TriProceduralPlugin::Construct(const SdfPath& i_proceduralPrimPath)
{
    return _MakeTriGenerativeProcedural::New(i_proceduralPrimPath);
}

TF_REGISTRY_FUNCTION(TfType)
{
    HdGpGenerativeProceduralPluginRegistry::
        Define<TriProceduralPlugin, HdGpGenerativeProceduralPlugin>();
}
