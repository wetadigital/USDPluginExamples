//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "./tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdEpiphyteTokensType::UsdEpiphyteTokensType()
  : parent("parent", TfToken::Immortal)
  , pointId("pointId", TfToken::Immortal)
  , uvPosition("uvPosition", TfToken::Immortal)
  , EpiphyteAPI("EpiphyteAPI", TfToken::Immortal)
  , allTokens({ parent, pointId, uvPosition, EpiphyteAPI })
{
}

TfStaticData<UsdEpiphyteTokensType> UsdEpiphyteTokens;

PXR_NAMESPACE_CLOSE_SCOPE