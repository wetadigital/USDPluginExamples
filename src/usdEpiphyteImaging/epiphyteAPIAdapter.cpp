//
// Copyright © 2024 Weta Fx Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "epiphyteAPIAdapter.h"
#include <usdpluginexamples/usdEpiphyte/epiphyteAPI.h>
#include <usdpluginexamples/hdEpiphyte/hdEpiphyteSchema.h>

#include <pxr/usdImaging/usdImaging/dataSourceAttribute.h>
#include "pxr/imaging/hd/retainedDataSource.h"
#include "pxr/imaging/hd/xformSchema.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    typedef UsdEpiphyteImagingAPIAdapter Adapter;
    TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
    t.SetFactory<UsdImagingAPISchemaAdapterFactory<Adapter>>();
}

class HdDataSourceEpiphyte : public HdContainerDataSource
{
public:
    HD_DECLARE_DATASOURCE(HdDataSourceEpiphyte);

    TfTokenVector GetNames() override;
    HdDataSourceBaseHandle Get(const TfToken& name) override;

private:
    HdDataSourceEpiphyte(const SdfPath& sceneIndexPath,
                         UsdEpiphyteEpiphyteAPI api,
                         const UsdImagingDataSourceStageGlobals& stageGlobals);

private:
    const SdfPath _sceneIndexPath;
    UsdEpiphyteEpiphyteAPI _api;
    const UsdImagingDataSourceStageGlobals& _stageGlobals;
};

HD_DECLARE_DATASOURCE_HANDLES(HdDataSourceEpiphyte);

// ----------------------------------------------------------------------------
HdDataSourceEpiphyte::HdDataSourceEpiphyte(
    const SdfPath& sceneIndexPath,
    UsdEpiphyteEpiphyteAPI api,
    const UsdImagingDataSourceStageGlobals& stageGlobals)
  : _sceneIndexPath(sceneIndexPath)
  , _api(api)
  , _stageGlobals(stageGlobals)
{
}
TfTokenVector
HdDataSourceEpiphyte::GetNames()
{
    static TfTokenVector names = { HdEpiphyteSchemaTokens->target,
                                   HdEpiphyteSchemaTokens->pointId,
                                   HdEpiphyteSchemaTokens->uv };
    return names;
}
HdDataSourceBaseHandle
HdDataSourceEpiphyte::Get(const TfToken& name)
{
    if (name == HdEpiphyteSchemaTokens->target) {
        using _SdfPathDs = HdRetainedTypedSampledDataSource<SdfPath>;
        SdfPathVector targets;
        _api.GetParentRel().GetForwardedTargets(&targets);
        if (targets.size() == 1) {
            return _SdfPathDs::New(targets[0]);
        }

    } else if (name == HdEpiphyteSchemaTokens->pointId) {
        return UsdImagingDataSourceAttribute<int>::New(
            _api.GetPointIdAttr(),
            _stageGlobals,
            _sceneIndexPath,
            HdEpiphyteSchema::GetPointIdLocator());
    } else if (name == HdEpiphyteSchemaTokens->uv) {
        return UsdImagingDataSourceAttribute<GfVec2f>::New(
            _api.GetUvPositionAttr(),
            _stageGlobals,
            _sceneIndexPath,
            HdEpiphyteSchema::GetUvLocator());
    }
    return HdDataSourceBaseHandle();
}

HdContainerDataSourceHandle
UsdEpiphyteImagingAPIAdapter::GetImagingSubprimData(
    UsdPrim const& prim,
    TfToken const& subprim,
    TfToken const& appliedInstanceName,
    const UsdImagingDataSourceStageGlobals& stageGlobals)
{
    if (subprim.IsEmpty()) {
        UsdEpiphyteEpiphyteAPI epiphyteAPI(prim);
        return HdRetainedContainerDataSource::New(
            HdEpiphyteSchemaTokens->epiphyte,
            HdDataSourceEpiphyte::New(
                prim.GetPath(), epiphyteAPI, stageGlobals));
    }
    return nullptr;
}

HdDataSourceLocatorSet
UsdEpiphyteImagingAPIAdapter::InvalidateImagingSubprim(
    const UsdPrim& prim,
    const TfToken& subprim,
    const TfToken& appliedInstanceName,
    const TfTokenVector& properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{

    if (!subprim.IsEmpty()) {
        return HdDataSourceLocatorSet();
    }
    HdDataSourceLocatorSet result;

    for (const TfToken& propertyName : properties) {

        if (propertyName == UsdEpiphyteTokens->pointId ||
            propertyName == UsdEpiphyteTokens->uvPosition ||
            propertyName == UsdEpiphyteTokens->parent) {
            result.insert(HdEpiphyteSchema::GetDefaultLocator());
        }
    }
    return result;
}

PXR_NAMESPACE_CLOSE_SCOPE