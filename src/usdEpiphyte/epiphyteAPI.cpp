//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//

#include "./epiphyteAPI.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"

#include "pxr/usd/sdf/types.h"
#include "pxr/usd/sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<UsdEpiphyteEpiphyteAPI, TfType::Bases<UsdAPISchemaBase>>();
}

/* virtual */
UsdEpiphyteEpiphyteAPI::~UsdEpiphyteEpiphyteAPI() {}

/* static */
UsdEpiphyteEpiphyteAPI
UsdEpiphyteEpiphyteAPI::Get(const UsdStagePtr& stage, const SdfPath& path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdEpiphyteEpiphyteAPI();
    }
    return UsdEpiphyteEpiphyteAPI(stage->GetPrimAtPath(path));
}

/* virtual */
UsdSchemaKind
UsdEpiphyteEpiphyteAPI::_GetSchemaKind() const
{
    return UsdEpiphyteEpiphyteAPI::schemaKind;
}

/* static */
bool
UsdEpiphyteEpiphyteAPI::CanApply(const UsdPrim& prim, std::string* whyNot)
{
    return prim.CanApplyAPI<UsdEpiphyteEpiphyteAPI>(whyNot);
}

/* static */
UsdEpiphyteEpiphyteAPI
UsdEpiphyteEpiphyteAPI::Apply(const UsdPrim& prim)
{
    if (prim.ApplyAPI<UsdEpiphyteEpiphyteAPI>()) {
        return UsdEpiphyteEpiphyteAPI(prim);
    }
    return UsdEpiphyteEpiphyteAPI();
}

/* static */
const TfType&
UsdEpiphyteEpiphyteAPI::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdEpiphyteEpiphyteAPI>();
    return tfType;
}

/* static */
bool
UsdEpiphyteEpiphyteAPI::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType&
UsdEpiphyteEpiphyteAPI::_GetTfType() const
{
    return _GetStaticTfType();
}

UsdAttribute
UsdEpiphyteEpiphyteAPI::GetUvPositionAttr() const
{
    return GetPrim().GetAttribute(UsdEpiphyteTokens->uvPosition);
}

UsdAttribute
UsdEpiphyteEpiphyteAPI::CreateUvPositionAttr(VtValue const& defaultValue,
                                             bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdEpiphyteTokens->uvPosition,
                                      SdfValueTypeNames->Float2,
                                      /* custom = */ false,
                                      SdfVariabilityVarying,
                                      defaultValue,
                                      writeSparsely);
}

UsdAttribute
UsdEpiphyteEpiphyteAPI::GetPointIdAttr() const
{
    return GetPrim().GetAttribute(UsdEpiphyteTokens->pointId);
}

UsdAttribute
UsdEpiphyteEpiphyteAPI::CreatePointIdAttr(VtValue const& defaultValue,
                                          bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdEpiphyteTokens->pointId,
                                      SdfValueTypeNames->Int,
                                      /* custom = */ false,
                                      SdfVariabilityVarying,
                                      defaultValue,
                                      writeSparsely);
}

UsdRelationship
UsdEpiphyteEpiphyteAPI::GetParentRel() const
{
    return GetPrim().GetRelationship(UsdEpiphyteTokens->parent);
}

UsdRelationship
UsdEpiphyteEpiphyteAPI::CreateParentRel() const
{
    return GetPrim().CreateRelationship(UsdEpiphyteTokens->parent,
                                        /* custom = */ false);
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
UsdEpiphyteEpiphyteAPI::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames = {
        UsdEpiphyteTokens->uvPosition,
        UsdEpiphyteTokens->pointId,
    };
    static TfTokenVector allNames = _ConcatenateAttributeNames(
        UsdAPISchemaBase::GetSchemaAttributeNames(true), localNames);

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