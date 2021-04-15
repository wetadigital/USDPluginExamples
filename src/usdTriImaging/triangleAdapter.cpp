//
// Copyright © 2021 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "triangleAdapter.h"
#include "debugCodes.h"

#include <usdpluginexamples/usdTri/triangle.h>

#include <pxr/imaging/hd/tokens.h>
#include <pxr/usd/usdGeom/tokens.h>
#include <pxr/usdImaging/usdImaging/indexProxy.h>
#include <pxr/usdImaging/usdImaging/tokens.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    typedef UsdTriImagingTriangleAdapter Adapter;
    TfType adapterType =
        TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
    adapterType.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

bool
UsdTriImagingTriangleAdapter::IsSupported(
    const UsdImagingIndexProxy* index) const
{
    return index->IsRprimTypeSupported(HdPrimTypeTokens->mesh);
}

void
UsdTriImagingTriangleAdapter::TrackVariability(
    const UsdPrim& usdPrim,
    const SdfPath& cachePath,
    HdDirtyBits* o_timeVaryingBits,
    const UsdImagingInstancerContext* i_instancerContext) const
{
    BaseAdapter::TrackVariability(
        usdPrim, cachePath, o_timeVaryingBits, i_instancerContext);

    // If sideLength varies over time then points need to be pulled on time
    // change.
    _IsVarying(usdPrim,
               UsdTriTokens->sideLength,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               o_timeVaryingBits,
               /*inherited*/ false);

    TF_DEBUG(USDTRIIMAGING)
        .Msg("[%s] <%s>, <%s>, dirtyBits: %s\n",
             TF_FUNC_NAME().c_str(),
             usdPrim.GetPath().GetText(),
             cachePath.GetText(),
             HdChangeTracker::StringifyDirtyBits(*o_timeVaryingBits).c_str());
}

SdfPath
UsdTriImagingTriangleAdapter::Populate(
    const UsdPrim& usdPrim,
    UsdImagingIndexProxy* index,
    const UsdImagingInstancerContext* instancerContext)
{
    TF_DEBUG(USDTRIIMAGING)
        .Msg(
            "[%s] <%s>\n", TF_FUNC_NAME().c_str(), usdPrim.GetPath().GetText());

    return _AddRprim(HdPrimTypeTokens->mesh,
                     usdPrim,
                     index,
                     GetMaterialUsdPath(usdPrim),
                     instancerContext);
}

HdDirtyBits
UsdTriImagingTriangleAdapter::ProcessPropertyChange(const UsdPrim& usdPrim,
                                                    const SdfPath& cachePath,
                                                    const TfToken& propertyName)
{

    TF_DEBUG(USDTRIIMAGING)
        .Msg("[%s] <%s>, <%s>, propertyName: %s\n",
             TF_FUNC_NAME().c_str(),
             usdPrim.GetPath().GetText(),
             cachePath.GetText(),
             propertyName.GetText());

    // If the sideLength attribute changes, then the points are dirty.
    if (propertyName == UsdTriTokens->sideLength) {
        return HdChangeTracker::DirtyPoints;
    }

    // Allow base class to handle change processing.
    return BaseAdapter::ProcessPropertyChange(usdPrim, cachePath, propertyName);
}

VtValue
UsdTriImagingTriangleAdapter::GetPoints(const UsdPrim& usdPrim,
                                        UsdTimeCode timeCode) const
{
    UsdTriTriangle triangle(usdPrim);
    TF_VERIFY(triangle);

    double sideLength;
    TF_VERIFY(triangle.GetSideLengthAttr().Get(&sideLength, timeCode));

    VtVec3fArray points{
        GfVec3f(0.0f, 0.57735027f * sideLength, 0.0f),
        GfVec3f(-0.5f * sideLength, -0.28867513f * sideLength, 0.0f),
        GfVec3f(0.5f * sideLength, -0.28867513f * sideLength, 0.0f)
    };
    return VtValue(points);
}

VtValue
UsdTriImagingTriangleAdapter::GetTopology(const UsdPrim& usdPrim,
                                          const SdfPath& cachePath,
                                          UsdTimeCode time) const
{
    // A single triangle.
    VtIntArray faceVertexCounts(1, 3);
    VtIntArray faceVertexIndices{ 0, 1, 2 };
    static HdMeshTopology planeTopology(UsdGeomTokens->catmullClark,
                                        HdTokens->rightHanded,
                                        faceVertexCounts,
                                        faceVertexIndices);
    return VtValue(planeTopology);
}

PXR_NAMESPACE_CLOSE_SCOPE
