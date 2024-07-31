//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/usdImaging/usdImaging/gprimAdapter.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class UsdTriImagingTriangleAdapterHd2
///
/// PrimAdapter plugin for the "Triangle" prim type.
class UsdTriImagingTriangleAdapterHd2 : public UsdImagingGprimAdapter
{
public:
    using BaseAdapter = UsdImagingGprimAdapter;

    // ---------------------------------------------------------------------- //
    /// \name Scene Index Support
    // ---------------------------------------------------------------------- //

    virtual TfTokenVector GetImagingSubprims(UsdPrim const& prim) override;

    virtual TfToken GetImagingSubprimType(UsdPrim const& prim,
                                          TfToken const& subprim) override;

    virtual HdContainerDataSourceHandle GetImagingSubprimData(
        UsdPrim const& prim,
        TfToken const& subprim,
        const UsdImagingDataSourceStageGlobals& stageGlobals) override;

    virtual HdDataSourceLocatorSet InvalidateImagingSubprim(
        UsdPrim const& prim,
        TfToken const& subprim,
        TfTokenVector const& properties,
        UsdImagingPropertyInvalidationType invalidationType) override;

    // ---------------------------------------------------------------------- //
    /// \name Initialization
    // ---------------------------------------------------------------------- //

    // seems we need this here to ensure we can compile
    virtual SdfPath Populate(
        const UsdPrim& usdPrim,
        UsdImagingIndexProxy* index,
        const UsdImagingInstancerContext* instancerContext = nullptr) override;
};

PXR_NAMESPACE_CLOSE_SCOPE