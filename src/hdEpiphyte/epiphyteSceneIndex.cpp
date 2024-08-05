//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "epiphyteSceneIndex.h"
#include "hdEpiphyteSchema.h"

#include "pxr/imaging/hd/coordSysSchema.h"
#include "pxr/imaging/hd/coordSysBindingSchema.h"
#include "pxr/imaging/hd/dependenciesSchema.h"
#include "pxr/imaging/hd/xformSchema.h"
#include "pxr/imaging/hd/primvarsSchema.h"
#include "pxr/imaging/hd/meshSchema.h"

#include "pxr/imaging/hd/mapContainerDataSource.h"
#include "pxr/imaging/hd/retainedDataSource.h"
#include "pxr/imaging/hd/sceneIndexPrimView.h"
#include "pxr/imaging/hd/tokens.h"

#include "pxr/base/trace/trace.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {

class _XformFromMeshPointDataSource : public HdMatrixDataSource
{
public:
    HD_DECLARE_DATASOURCE(_XformFromMeshPointDataSource);

    bool GetContributingSampleTimesForInterval(
        Time startTime,
        Time endTime,
        std::vector<Time>* outSampleTimes) override
    {
        bool result = true;
        result &= _pointsDs->GetContributingSampleTimesForInterval(
            startTime, endTime, outSampleTimes);
        result &= _pointIndexDs->GetContributingSampleTimesForInterval(
            startTime, endTime, outSampleTimes);
        for (const auto& mat : _matrixDs) {
            result &= mat->GetContributingSampleTimesForInterval(
                startTime, endTime, outSampleTimes);
        }
        return result;
    }

    VtValue GetValue(Time shutterOffset) override
    {
        return VtValue(GetTypedValue(shutterOffset));
    }

    GfMatrix4d GetTypedValue(Time shutterOffset) override
    {
        VtArray<GfVec3f> p =
            _pointsDs->GetValue(shutterOffset).UncheckedGet<VtArray<GfVec3f>>();

        int _index = _pointIndexDs->GetValue(shutterOffset).UncheckedGet<int>();
        if (_index < 0 || _index >= static_cast<int>(p.size())) {
            return GfMatrix4d(1);
        }

        GfMatrix4d m = GfMatrix4d(1).SetTranslateOnly(p[_index]);

        for (const auto& mat : _matrixDs) {
            const GfMatrix4d myMat =
                mat->GetValue(shutterOffset).UncheckedGet<GfMatrix4d>();
            m *= myMat;
        }
        return GfMatrix4d(1) * m;
    }

private:
    _XformFromMeshPointDataSource(
        HdIntDataSourceHandle pointIndexDs,
        HdSampledDataSourceHandle pointsDs,
        std::vector<HdMatrixDataSourceHandle>& matrixDs)
      : _pointIndexDs(pointIndexDs)
      , _pointsDs(pointsDs)
      , _matrixDs(matrixDs)
    {
    }
    HdIntDataSourceHandle _pointIndexDs;
    HdSampledDataSourceHandle _pointsDs;
    std::vector<HdMatrixDataSourceHandle> _matrixDs;
};

class _PrimDataSource : public HdContainerDataSource
{
public:
    HD_DECLARE_DATASOURCE(_PrimDataSource);

    TfTokenVector GetNames() override { return _inputSource->GetNames(); }

    HdDataSourceBaseHandle Get(const TfToken& name) override
    {
        HdDataSourceBaseHandle const ds = _inputSource->Get(name);

        if (name == HdXformSchema::GetSchemaToken()) {

            HdMeshSchema meshSchema =
                HdMeshSchema::GetFromParent(_parentSource);
            HdPrimvarsSchema primvarsSchema =
                HdPrimvarsSchema::GetFromParent(_parentSource);
            HdPrimvarSchema pointPV =
                primvarsSchema.GetPrimvar(HdPrimvarsSchemaTokens->points);
            HdXformSchema xformSchema =
                HdXformSchema::GetFromParent(_parentSource);

            HdEpiphyteSchema epiphyteSchema =
                HdEpiphyteSchema::GetFromParent(_inputSource);

            using _BoolDs = HdRetainedTypedSampledDataSource<bool>;

            std::vector<HdMatrixDataSourceHandle> matrixList;
            matrixList.push_back(xformSchema.GetMatrix());

            return HdXformSchema::Builder()
                .SetMatrix(_XformFromMeshPointDataSource::New(
                    epiphyteSchema.GetPointId(),
                    pointPV.GetPrimvarValue(),
                    matrixList))
                .SetResetXformStack(_BoolDs::New(true))
                .Build();
        }
        return ds;
    }

private:
    _PrimDataSource(const HdContainerDataSourceHandle& inputSource,
                    const HdContainerDataSourceHandle& parentSource,
                    const SdfPath& path)
      : _inputSource(inputSource)
      , _parentSource(parentSource)
      , _path(path)

    {
    }
    SdfPath _path;
    HdContainerDataSourceHandle const _inputSource;
    HdContainerDataSourceHandle const _parentSource;
};

HdSceneIndexObserver::AddedPrimEntries
_ToAddedPrimEntries(const SdfPathSet& paths)
{
    HdSceneIndexObserver::AddedPrimEntries entries;
    entries.reserve(paths.size());
    for (const SdfPath& path : paths) {
        entries.push_back({ path, HdSprimTypeTokens->coordSys });
    }
    return entries;
}

HdSceneIndexObserver::RemovedPrimEntries
_ToRemovedPrimEntries(const SdfPathSet& paths)
{
    HdSceneIndexObserver::RemovedPrimEntries entries;
    entries.reserve(paths.size());
    for (const SdfPath& path : paths) {
        entries.push_back({ path });
    }
    return entries;
}

}

HdEpiphyteSceneIndex::HdEpiphyteSceneIndex(
    HdSceneIndexBaseRefPtr const& inputScene)
  : HdSingleInputFilteringSceneIndexBase(inputScene)
{
    TRACE_FUNCTION();

    for (const SdfPath& primPath : HdSceneIndexPrimView(inputScene)) {
        _AddBindingsForPrim(primPath);
    }
}

HdSceneIndexPrim
HdEpiphyteSceneIndex::GetPrim(const SdfPath& primPath) const
{
    HdSceneIndexPrim prim = _GetInputSceneIndex()->GetPrim(primPath);

    auto findBinding = _primtToEpiphyteBinding.find(primPath);
    if (findBinding == _primtToEpiphyteBinding.cend()) {
        return prim;
    }

    HdSceneIndexPrim parentPrim =
        _GetInputSceneIndex()->GetPrim(findBinding->second.parent);

    if (prim.dataSource && parentPrim.dataSource) {
        prim.dataSource = _PrimDataSource::New(
            prim.dataSource, parentPrim.dataSource, primPath);
    }
    return prim;
}

SdfPathVector
HdEpiphyteSceneIndex::GetChildPrimPaths(const SdfPath& primPath) const
{
    SdfPathVector result = _GetInputSceneIndex()->GetChildPrimPaths(primPath);
    return result;
}

void
HdEpiphyteSceneIndex::_AddBindingsForPrim(const SdfPath& primPath)
{
    HdEpiphyteSchema schema = HdEpiphyteSchema::GetFromParent(
        _GetInputSceneIndex()->GetPrim(primPath).dataSource);
    if (!schema) {
        return;
    }

    _EpiphyteBinding binding;

    HdPathDataSourceHandle targetDs = schema.GetPTarget();
    if (targetDs) {
        binding.parent = targetDs->GetTypedValue(0.0f);
    }
    _primtToEpiphyteBinding.emplace(primPath, std::move(binding));
}

void
HdEpiphyteSceneIndex::_RemoveBindingsForPrim(const SdfPath& primPath)
{
    const auto it = _primtToEpiphyteBinding.find(primPath);
    if (it == _primtToEpiphyteBinding.end()) {
        return;
    }
    _primtToEpiphyteBinding.erase(it);
}

void
HdEpiphyteSceneIndex::_PrimsAdded(
    const HdSceneIndexBase& sender,
    const HdSceneIndexObserver::AddedPrimEntries& entries)
{
    TRACE_FUNCTION();

    const bool isObserved = _IsObserved();

    for (const HdSceneIndexObserver::AddedPrimEntry& entry : entries) {
        _RemoveBindingsForPrim(entry.primPath);
        _AddBindingsForPrim(entry.primPath);
    }

    if (!isObserved) {
        return;
    }

    _SendPrimsAdded(entries);
}

void
HdEpiphyteSceneIndex::_PrimsDirtied(
    const HdSceneIndexBase& sender,
    const HdSceneIndexObserver::DirtiedPrimEntries& entries)
{
    TRACE_FUNCTION();

    // the only locators we might be interested in our ancestors
    static HdDataSourceLocatorSet kAncestorLocatorSet(
        { HdXformSchema::GetDefaultLocator() });

    // the Locators on the target which we use to trigger update calls
    static HdDataSourceLocatorSet ktargetLocatorSet(
        { HdPrimvarsSchema::GetPointsLocator(),
          HdPrimvarsSchema::GetNormalsLocator(),
          HdMeshSchema::GetTopologyLocator(),
          HdXformSchema::GetDefaultLocator() });

    // the Locators on the driven which we use to trigger update calls
    static HdDataSourceLocatorSet kDriverLocatorSet(
        { HdEpiphyteSchema::GetDefaultLocator(),
          HdEpiphyteSchema::GetTargetLocator() });

    const bool isObserved = _IsObserved();

    SdfPathSet addedDirtyDriven;
    for (const HdSceneIndexObserver::DirtiedPrimEntry& entry : entries) {
        // check if our driver got updated
        if (_primtToEpiphyteBinding.find(entry.primPath) !=
            _primtToEpiphyteBinding.cend()) {
            // and whatever got updated concerns us
            if (entry.dirtyLocators.Intersects(kDriverLocatorSet)) {
                // pull the data from the prim
                _RemoveBindingsForPrim(entry.primPath);
                _AddBindingsForPrim(entry.primPath);
                addedDirtyDriven.insert(entry.primPath);
                // we dont need to add any additional dependencies here
                // as our prim is already dirty
            }
        }

        // now lets see if our driver is dirty
        for (const auto& binding : _primtToEpiphyteBinding) {
            // is whatever updated one of our drivers ?
            if (entry.primPath == binding.second.parent) {

                // todo: ancestor transforms ?
                if (entry.dirtyLocators.Intersects(ktargetLocatorSet)) {
                    addedDirtyDriven.insert(binding.first);
                }

                // \todo: if the entry.PrimPath is a parent of our driver
                // our driver object got an update
            }
        }
    }

    if (!isObserved) {
        return;
    }

    _SendPrimsDirtied(entries);

    //  send our changes
    HdSceneIndexObserver::DirtiedPrimEntries dEntries;
    dEntries.reserve(addedDirtyDriven.size());
    for (const SdfPath& p : addedDirtyDriven) {
        dEntries.push_back({ p, HdXformSchema::GetDefaultLocator() });
    }
    _SendPrimsDirtied(dEntries);
}

void
HdEpiphyteSceneIndex::_PrimsRemoved(
    const HdSceneIndexBase& sender,
    const HdSceneIndexObserver::RemovedPrimEntries& entries)
{
    TRACE_FUNCTION();

    const bool isObserved = _IsObserved();

    // internal housekeeping

    for (const auto& entry : entries) {
        _RemoveBindingsForPrim(entry.primPath);
    }

    if (!isObserved) {
        return;
    }

    // forward whatever happend
    _SendPrimsRemoved(entries);
}

PXR_NAMESPACE_CLOSE_SCOPE