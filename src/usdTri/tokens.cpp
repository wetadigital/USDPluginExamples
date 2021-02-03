//
// Copyright © 2021 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "./tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdTriTokensType::UsdTriTokensType()
  : extent("extent", TfToken::Immortal)
  , sideLength("sideLength", TfToken::Immortal)
  , allTokens({ extent, sideLength })
{}

TfStaticData<UsdTriTokensType> UsdTriTokens;

PXR_NAMESPACE_CLOSE_SCOPE
