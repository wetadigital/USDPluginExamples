//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//

#include "dataSourceTri.h"
#include "debugCodes.h"

#include <usdpluginexamples/usdTri/tokens.h>
#include <usdpluginexamples/usdTri/triangle.h>

#include "pxr/imaging/hd/meshSchema.h"
#include <pxr/imaging/hd/meshTopologySchema.h>
#include <pxr/imaging/hd/primvarsSchema.h>
#include <pxr/imaging/hd/retainedDataSource.h>
#include <pxr/imaging/hd/overlayContainerDataSource.h>
#include <pxr/usdImaging/usdImaging/dataSourceMesh.h>

PXR_NAMESPACE_OPEN_SCOPE

// a static container-handle for the mesh-topology
HdContainerDataSourceHandle
_meshTopologyDs()
{
    static const VtIntArray faceVertexCounts = { 3 };

    static const VtIntArray faceVertexIndices = { 0, 1, 2 };

    using _IntArrayDs = HdRetainedTypedSampledDataSource<VtIntArray>;

    static const _IntArrayDs::Handle fvcDs = _IntArrayDs::New(faceVertexCounts);

    static const _IntArrayDs::Handle fviDs =
        _IntArrayDs::New(faceVertexIndices);

    static const HdContainerDataSourceHandle meshDs =
        HdMeshSchema::Builder()
            .SetTopology(HdMeshTopologySchema::Builder()
                             .SetFaceVertexCounts(fvcDs)
                             .SetFaceVertexIndices(fviDs)
                             .Build())
            .Build();

    return meshDs;
}

// a DataHandle producing Sampled Vec3fArray data
// to be used as points of the triangle
// it carries a great resemblence and is very much a copy of
// UsdImagingDataSourceAttribute we technically would just need to overwrite
// ::GetTypedValue(...) for our purposes here, but the constructor of
// UsdImagingDataSourceAttribute is private so we need to re-implement
// everything

class _PointsFromSideLengthDataSource
  : public HdTypedSampledDataSource<VtVec3fArray>
{
public:
    HD_DECLARE_DATASOURCE(_PointsFromSideLengthDataSource);

    // copied the code from UsdImagingDataSourceAttribute
    bool GetContributingSampleTimesForInterval(
        Time startTime,
        Time endTime,
        std::vector<Time>* outSampleTimes) override
    {
        UsdTimeCode time = _stageGlobals.GetTime();
        if (!_valueQuery.ValueMightBeTimeVarying() || !time.IsNumeric()) {
            return false;
        }

        GfInterval interval(time.GetValue() + startTime,
                            time.GetValue() + endTime);
        std::vector<double> timeSamples;
        _valueQuery.GetTimeSamplesInInterval(interval, &timeSamples);

        // Add boundary timesamples, if necessary.
        if (timeSamples.empty() || timeSamples[0] > interval.GetMin()) {
            timeSamples.insert(timeSamples.begin(), interval.GetMin());
        }
        if (timeSamples.back() < interval.GetMax()) {
            timeSamples.push_back(interval.GetMax());
        }

        // We need to convert the time array because usd uses double and
        // hydra (and prman) use float :/.
        outSampleTimes->resize(timeSamples.size());
        for (size_t i = 0; i < timeSamples.size(); ++i) {
            (*outSampleTimes)[i] = timeSamples[i] - time.GetValue();
        }

        return true;
    }

    // copied the code from UsdImagingDataSourceAttribute
    VtValue GetValue(Time shutterOffset) override
    {
        return VtValue(GetTypedValue(shutterOffset));
    }

    // here we are calculating the points of the triangle based on the values
    // of our sideLength attribute
    VtArray<GfVec3f> GetTypedValue(Time shutterOffset) override
    {

        double sideLength = 1.0f;
        UsdTimeCode time = _stageGlobals.GetTime();
        if (time.IsNumeric()) {
            time = UsdTimeCode(time.GetValue() + shutterOffset);
        }
        _valueQuery.Get<double>(&sideLength, time);

        VtVec3fArray points{
            GfVec3f(0.0f, 0.57735027f * sideLength, 0.0f),
            GfVec3f(-0.5f * sideLength, -0.28867513f * sideLength, 0.0f),
            GfVec3f(0.5f * sideLength, -0.28867513f * sideLength, 0.0f)
        };
        return points;
    }

private:
    // constructor, which also registeres the points-primvar to be 'time'
    // dependend if our sideLength attribute might be timeVarying
    _PointsFromSideLengthDataSource(
        const SdfPath& sceneIndexPath,
        const UsdImagingDataSourceStageGlobals& stageGlobals,
        UsdPrim myPrim)
      : _stageGlobals(stageGlobals)
      , _valueQuery(myPrim, UsdTriTokens->sideLength)
    {
        if (_valueQuery.ValueMightBeTimeVarying()) {
            _stageGlobals.FlagAsTimeVarying(
                sceneIndexPath, HdPrimvarsSchema::GetPointsLocator());
        }
    }

    const UsdImagingDataSourceStageGlobals& _stageGlobals;
    UsdAttributeQuery _valueQuery;
};
HD_DECLARE_DATASOURCE_HANDLES(_PointsFromSideLengthDataSource);

/// ---------------------------------------------------------------------
/// ---------------------------------------------------------------------

UsdImagingDataSourceTriPrim::UsdImagingDataSourceTriPrim(
    const SdfPath& sceneIndexPath,
    UsdPrim usdPrim,
    const UsdImagingDataSourceStageGlobals& stageGlobals)
  : UsdImagingDataSourceGprim(sceneIndexPath, usdPrim, stageGlobals)
{
    // Note: DataSourceGprim handles the special PointBased primvars for us.
}

TfTokenVector
UsdImagingDataSourceTriPrim::GetNames()
{
    // using the GPrim - Names
    TfTokenVector result = UsdImagingDataSourceGprim::GetNames();

    // and adding what our specialisation of the GPrim DataSource is providing
    // on top
    // ... We do provide a Mesh
    result.push_back(HdMeshSchemaTokens->mesh);

    // and we're technically also providing primvars
    // however as the GPrimDataSource already does this we dont
    // need to add it here
    // result.push_back(HdPrimvarsSchemaTokens->primvars);

    return result;
}

HdDataSourceBaseHandle
UsdImagingDataSourceTriPrim::Get(const TfToken& i_name)
{
    // providing the data-source for the Mesh
    if (i_name == HdMeshSchemaTokens->mesh) {
        // nothing magic here just a mesh with a static topology
        return _meshTopologyDs();
    }

    // for other requests, we're forwarding them to the
    // DataSourceGPrim
    HdDataSourceBaseHandle result = UsdImagingDataSourceGprim::Get(i_name);

    // while the base GPrimDataSource does deal with primvars in
    // general it does not deal with points-primvars
    // so we are overlaying our Points DataSource
    if (i_name == HdPrimvarsSchemaTokens->primvars) {
        // here it is a bit more tricky
        // we overlaying the Primvars - DataHandle that we get from our
        // BaseClass with our own primvars containing the calculated points
        return HdOverlayContainerDataSource::New(
            // the Primvar data-source from the GPrim
            HdContainerDataSource::Cast(result),
            // and overlaying our own
            HdRetainedContainerDataSource::New(
                HdPrimvarsSchemaTokens->points,
                HdPrimvarSchema::Builder()
                    .SetPrimvarValue(
                        // with our DataSource for the Points calculated from
                        // our sideLength attribute
                        _PointsFromSideLengthDataSource::New(
                            _GetSceneIndexPath(),
                            _GetStageGlobals(),
                            _GetUsdPrim()))
                    .SetInterpolation(
                        HdPrimvarSchema::BuildInterpolationDataSource(
                            HdPrimvarSchemaTokens->vertex))
                    .SetRole(HdPrimvarSchema::BuildRoleDataSource(
                        HdPrimvarSchemaTokens->point))
                    .Build()));
    }
    return result;
}

/*static*/
HdDataSourceLocatorSet
UsdImagingDataSourceTriPrim::Invalidate(
    UsdPrim const& prim,
    const TfToken& subprim,
    const TfTokenVector& properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
    HdDataSourceLocatorSet locators;
    for (const TfToken& propertyName : properties) {
        // if the sideLength property got changed we wanna
        // invalidate/dirty the points primvar, so it gets updated
        if (propertyName == UsdTriTokens->sideLength) {
            locators.insert(HdPrimvarsSchema::GetPointsLocator());
        }
    }

    // Give base classes a chance to invalidate.
    locators.insert(UsdImagingDataSourceGprim::Invalidate(
        prim, subprim, properties, invalidationType));
    return locators;
}

PXR_NAMESPACE_CLOSE_SCOPE