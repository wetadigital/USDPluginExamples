//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef USDEPIPHYTE_TOKENS_H
#define USDEPIPHYTE_TOKENS_H

/// \file usdEpiphyte/tokens.h

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

/// \class UsdEpiphyteTokensType
///
/// \link UsdEpiphyteTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdEpiphyteTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdEpiphyteTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdEpiphyteTokens->parent);
/// \endcode
struct UsdEpiphyteTokensType
{
    USDEPIPHYTE_API UsdEpiphyteTokensType();
    /// \brief "parent"
    ///
    /// UsdEpiphytesEpiphyteAPI
    const TfToken parent;
    /// \brief "pointId"
    ///
    /// UsdEpiphytesEpiphyteAPI
    const TfToken pointId;
    /// \brief "uvPosition"
    ///
    /// UsdEpiphytesEpiphyteAPI
    const TfToken uvPosition;
    /// \brief "EpiphyteAPI"
    ///
    /// Schema identifer and family for UsdEpiphytesEpiphyteAPI
    const TfToken EpiphyteAPI;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdEpiphyteTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdEpiphyteTokensType
extern USDEPIPHYTE_API TfStaticData<UsdEpiphyteTokensType> UsdEpiphyteTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif