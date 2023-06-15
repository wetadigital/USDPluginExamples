//
// Copyright © 2023 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/usdImaging/usdImaging/gprimAdapter.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class UsdTriImagingTriangleAdapter
///
/// PrimAdapter plugin for the "Triangle" prim type.
class UsdTriImagingTriangleAdapter : public UsdImagingGprimAdapter
{
public:
    using BaseAdapter = UsdImagingGprimAdapter;

    // ---------------------------------------------------------------------- //
    /// \name Initialization
    // ---------------------------------------------------------------------- //

    virtual SdfPath Populate(
        const UsdPrim& usdPrim,
        UsdImagingIndexProxy* index,
        const UsdImagingInstancerContext* instancerContext = nullptr) override;

    virtual bool IsSupported(const UsdImagingIndexProxy* index) const override;

    // ---------------------------------------------------------------------- //
    /// \name Parallel Setup and Resolve
    // ---------------------------------------------------------------------- //

    virtual void TrackVariability(
        const UsdPrim& usdPrim,
        const SdfPath& cachePath,
        HdDirtyBits* timeVaryingBits,
        const UsdImagingInstancerContext* i_instancerContext =
            nullptr) const override;

    // ---------------------------------------------------------------------- //
    /// \name Change processing
    // ---------------------------------------------------------------------- //

    virtual HdDirtyBits ProcessPropertyChange(
        const UsdPrim& usdPrim,
        const SdfPath& cachePath,
        const TfToken& propertyName) override;

    // ---------------------------------------------------------------------- //
    /// \name GprimAdapter overrides
    // ---------------------------------------------------------------------- //

    /// Override the implementation in GprimAdapter and provide \em custom
    /// points for a triangle.
    virtual VtValue GetPoints(const UsdPrim& usdPrim,
                              UsdTimeCode timeCode) const override;

    /// Override the implementation in GprimAdapter and provide \em custom
    /// topology for a triangle.
    virtual VtValue GetTopology(const UsdPrim& usdPrim,
                                const SdfPath& cachePath,
                                UsdTimeCode time) const override;
};

PXR_NAMESPACE_CLOSE_SCOPE
