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

#if PXR_VERSION < 2011
    virtual void UpdateForTime(const UsdPrim& usdPrim,
                               const SdfPath& cachePath,
                               UsdTimeCode timeCode,
                               HdDirtyBits i_requestedBits,
                               const UsdImagingInstancerContext*
                                   instancerContext = nullptr) const override;
#endif

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
#if PXR_VERSION < 2011
                              const SdfPath& cachePath,
#endif
                              UsdTimeCode timeCode) const override;

#if PXR_VERSION >= 2011
    /// Override the implementation in GprimAdapter and provide \em custom
    /// topology for a triangle.
    virtual VtValue GetTopology(const UsdPrim& usdPrim,
                                const SdfPath& cachePath,
                                UsdTimeCode time) const override;
#else
private:
    static VtValue _GetTopology();
#endif
};

PXR_NAMESPACE_CLOSE_SCOPE
