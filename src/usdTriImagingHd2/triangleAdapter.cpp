//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "triangleAdapter.h"
#include "dataSourceTri.h"
#include "debugCodes.h"

#include <usdpluginexamples/usdTri/triangle.h>

#include <pxr/imaging/hd/tokens.h>
#include <pxr/usd/usdGeom/tokens.h>
#include <pxr/usdImaging/usdImaging/indexProxy.h>
#include <pxr/usdImaging/usdImaging/tokens.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    typedef UsdTriImagingTriangleAdapterHd2 Adapter;
    TfType adapterType =
        TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
    adapterType.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

TfTokenVector
UsdTriImagingTriangleAdapterHd2::GetImagingSubprims(const UsdPrim& prim)
{
    TF_DEBUG(USDTRIIMAGING)
        .Msg("[%s] called on <%s> \n",
             TF_FUNC_NAME().c_str(),
             prim.GetPath().GetText());

    return { TfToken() };
}

TfToken
UsdTriImagingTriangleAdapterHd2::GetImagingSubprimType(const UsdPrim& prim,
                                                       const TfToken& subprim)
{
    TF_DEBUG(USDTRIIMAGING)
        .Msg("[%s] called on <%s> / %s \n",
             TF_FUNC_NAME().c_str(),
             prim.GetPath().GetText(),
             subprim.GetText());

    if (subprim.IsEmpty()) {
        return HdPrimTypeTokens->mesh;
    }
    return TfToken();
}

HdContainerDataSourceHandle
UsdTriImagingTriangleAdapterHd2::GetImagingSubprimData(
    const UsdPrim& prim,
    const TfToken& subprim,
    const UsdImagingDataSourceStageGlobals& stageGlobals)
{
    TF_DEBUG(USDTRIIMAGING)
        .Msg("[%s] called on <%s> / %s \n",
             TF_FUNC_NAME().c_str(),
             prim.GetPath().GetText(),
             subprim.GetText());

    if (subprim.IsEmpty()) {
        return UsdImagingDataSourceTriPrim::New(
            prim.GetPath(), prim, stageGlobals);
    }
    return nullptr;
}

HdDataSourceLocatorSet
UsdTriImagingTriangleAdapterHd2::InvalidateImagingSubprim(
    const UsdPrim& prim,
    const TfToken& subprim,
    const TfTokenVector& properties,
    UsdImagingPropertyInvalidationType invalidationType)
{

    TF_DEBUG(USDTRIIMAGING)
        .Msg("[%s] called on <%s> / %s - %lu properties \n",
             TF_FUNC_NAME().c_str(),
             prim.GetPath().GetText(),
             subprim.GetText(),
             properties.size());

    if (subprim.IsEmpty()) {
        return UsdImagingDataSourceTriPrim::Invalidate(
            prim, subprim, properties, invalidationType);
    }
    return HdDataSourceLocatorSet();
}

SdfPath
UsdTriImagingTriangleAdapterHd2::Populate(
    const UsdPrim& usdPrim,
    UsdImagingIndexProxy* index,
    const UsdImagingInstancerContext* instancerContext)
{
    return SdfPath();
}

PXR_NAMESPACE_CLOSE_SCOPE