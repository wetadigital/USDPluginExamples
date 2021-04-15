//
// Copyright © 2021 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "./triangle.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"

#include "pxr/usd/sdf/types.h"
#include "pxr/usd/sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<UsdTriTriangle, TfType::Bases<UsdGeomGprim>>();

    // Register the usd prim typename as an alias under UsdSchemaBase. This
    // enables one to call
    // TfType::Find<UsdSchemaBase>().FindDerivedByName("Triangle")
    // to find TfType<UsdTriTriangle>, which is how IsA queries are
    // answered.
    TfType::AddAlias<UsdSchemaBase, UsdTriTriangle>("Triangle");
}

/* virtual */
UsdTriTriangle::~UsdTriTriangle() {}

/* static */
UsdTriTriangle
UsdTriTriangle::Get(const UsdStagePtr& stage, const SdfPath& path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdTriTriangle();
    }
    return UsdTriTriangle(stage->GetPrimAtPath(path));
}

/* static */
UsdTriTriangle
UsdTriTriangle::Define(const UsdStagePtr& stage, const SdfPath& path)
{
    static TfToken usdPrimTypeName("Triangle");
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdTriTriangle();
    }
    return UsdTriTriangle(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind
UsdTriTriangle::_GetSchemaKind() const
{
    return UsdTriTriangle::schemaKind;
}

/* virtual */
UsdSchemaKind
UsdTriTriangle::_GetSchemaType() const
{
    return UsdTriTriangle::schemaType;
}

/* static */
const TfType&
UsdTriTriangle::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdTriTriangle>();
    return tfType;
}

/* static */
bool
UsdTriTriangle::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType&
UsdTriTriangle::_GetTfType() const
{
    return _GetStaticTfType();
}

UsdAttribute
UsdTriTriangle::GetSideLengthAttr() const
{
    return GetPrim().GetAttribute(UsdTriTokens->sideLength);
}

UsdAttribute
UsdTriTriangle::CreateSideLengthAttr(VtValue const& defaultValue,
                                     bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdTriTokens->sideLength,
                                      SdfValueTypeNames->Double,
                                      /* custom = */ false,
                                      SdfVariabilityVarying,
                                      defaultValue,
                                      writeSparsely);
}

UsdAttribute
UsdTriTriangle::GetExtentAttr() const
{
    return GetPrim().GetAttribute(UsdTriTokens->extent);
}

UsdAttribute
UsdTriTriangle::CreateExtentAttr(VtValue const& defaultValue,
                                 bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdTriTokens->extent,
                                      SdfValueTypeNames->Float3Array,
                                      /* custom = */ false,
                                      SdfVariabilityVarying,
                                      defaultValue,
                                      writeSparsely);
}

namespace {
static inline TfTokenVector
_ConcatenateAttributeNames(const TfTokenVector& left,
                           const TfTokenVector& right)
{
    TfTokenVector result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}
}

/*static*/
const TfTokenVector&
UsdTriTriangle::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames = {
        UsdTriTokens->sideLength,
        UsdTriTokens->extent,
    };
    static TfTokenVector allNames = _ConcatenateAttributeNames(
        UsdGeomGprim::GetSchemaAttributeNames(true), localNames);

    if (includeInherited)
        return allNames;
    else
        return localNames;
}

PXR_NAMESPACE_CLOSE_SCOPE

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'PXR_NAMESPACE_OPEN_SCOPE', 'PXR_NAMESPACE_CLOSE_SCOPE'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

#include "pxr/usd/usdGeom/boundableComputeExtent.h"
#include "pxr/base/tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

bool
UsdTriTriangle::ComputeExtent(double sideLength, VtVec3fArray* extent)
{
    extent->resize(2);

    (*extent)[0] = GfVec3f(0.5 * sideLength, -0.28867513 * sideLength, 0.0);
    (*extent)[1] = GfVec3f(0.5 * sideLength, 0.57735027 * sideLength, 0.0);

    return true;
}

bool
UsdTriTriangle::ComputeExtent(double sideLength,
                              const GfMatrix4d& transform,
                              VtVec3fArray* extent)
{
    extent->resize(2);

    GfBBox3d bbox = GfBBox3d(
        GfRange3d(GfVec3d(-0.5 * sideLength, -0.28867513 * sideLength, 0.0),
                  GfVec3d(0.5 * sideLength, 0.57735027 * sideLength, 0.0)),
        transform);
    GfRange3d range = bbox.ComputeAlignedRange();
    (*extent)[0] = GfVec3f(range.GetMin());
    (*extent)[1] = GfVec3f(range.GetMax());

    return true;
}

static bool
_ComputeExtentForTriangle(const UsdGeomBoundable& boundable,
                          const UsdTimeCode& time,
                          const GfMatrix4d* transform,
                          VtVec3fArray* extent)
{
    const UsdTriTriangle triangle(boundable);
    if (!TF_VERIFY(triangle)) {
        return false;
    }

    double sideLength;
    if (!triangle.GetSideLengthAttr().Get(&sideLength, time)) {
        return false;
    }

    if (transform) {
        return UsdTriTriangle::ComputeExtent(sideLength, *transform, extent);
    } else {
        return UsdTriTriangle::ComputeExtent(sideLength, extent);
    }
}

TF_REGISTRY_FUNCTION(UsdGeomBoundable)
{
    UsdGeomRegisterComputeExtentFunction<UsdTriTriangle>(
        _ComputeExtentForTriangle);
}

PXR_NAMESPACE_CLOSE_SCOPE
