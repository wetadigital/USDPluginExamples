//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "debugCodes.h"
#include "pxr/base/tf/debug.h"
#include <pxr/base/tf/registryManager.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
    TF_DEBUG_ENVIRONMENT_SYMBOL(
        USDTRI_GENERATIVE, "Debug symbol for the usdTri GenerativeProcedural.");
}

PXR_NAMESPACE_CLOSE_SCOPE
