//
// Copyright © 2021 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef USDTRI_TOKENS_H
#define USDTRI_TOKENS_H

/// \file usdTri/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "pxr/pxr.h"
#include "./api.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/token.h"
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

/// \class UsdTriTokensType
///
/// \link UsdTriTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdTriTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdTriTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdTriTokens->extent);
/// \endcode
struct UsdTriTokensType
{
    USDTRI_API UsdTriTokensType();
    /// \brief "extent"
    ///
    /// UsdTriTriangle
    const TfToken extent;
    /// \brief "sideLength"
    ///
    /// UsdTriTriangle
    const TfToken sideLength;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdTriTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdTriTokensType
extern USDTRI_API TfStaticData<UsdTriTokensType> UsdTriTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif
