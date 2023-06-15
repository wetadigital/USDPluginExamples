//
// Copyright © 2023 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include <pxr/base/tf/registryManager.h>
#include <pxr/base/tf/scriptModuleLoader.h>
#include <pxr/base/tf/token.h>
#include <pxr/pxr.h>

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfScriptModuleLoader)
{
    // List of direct dependencies for this library.
    const std::vector<TfToken> reqs = {
        TfToken("js"), TfToken("plug"),  TfToken("sdf"),
        TfToken("tf"), TfToken("trace"), TfToken("usd"),
        TfToken("vt"), TfToken("work"),  TfToken("usdGeom"),
    };
    TfScriptModuleLoader::GetInstance().RegisterLibrary(
        TfToken("usdTri"), TfToken("usdpluginexamples.UsdTri"), reqs);
}

PXR_NAMESPACE_CLOSE_SCOPE
