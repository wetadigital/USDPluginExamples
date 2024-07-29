//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include "pxr/usdImaging/usdImaging/dataSourceGprim.h"

PXR_NAMESPACE_OPEN_SCOPE

///
/// \brief The UsdImagingDataSourceTriPrim class - inheriting from a GPrim
/// DataSource as we can use a lot of the existing infrastructure of GPrims e.g.
/// support for Transforms, Primvars etc.
/// We do override the implementations for 'Points' & 'Topology' to return the
/// triangle relevant data.  An other approach could be to override
/// the UsdImagingGprimAdapter::GetPoints() /
/// UsdImagingGprimAdapter::GetTopology functions
///
class UsdImagingDataSourceTriPrim : public UsdImagingDataSourceGprim
{
public:
    HD_DECLARE_DATASOURCE(UsdImagingDataSourceTriPrim);

    // return the names of the data-sources this object can provide
    TfTokenVector GetNames() override;

    // return the data-sources based on the names
    HdDataSourceBaseHandle Get(const TfToken& i_name) override;

    // callbacks to help which DataSource Locations need to be invalidated
    // based on the prim/subPrim/properties
    static HdDataSourceLocatorSet Invalidate(
        UsdPrim const& prim,
        const TfToken& subprim,
        const TfTokenVector& properties,
        UsdImagingPropertyInvalidationType invalidationType);

private:
    UsdImagingDataSourceTriPrim(
        const SdfPath& sceneIndexPath,
        UsdPrim usdPrim,
        const UsdImagingDataSourceStageGlobals& stageGlobals);
};

HD_DECLARE_DATASOURCE_HANDLES(UsdImagingDataSourceTriPrim);

PXR_NAMESPACE_CLOSE_SCOPE