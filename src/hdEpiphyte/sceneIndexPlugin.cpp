
//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//

#include "sceneIndexPlugin.h"
#include "epiphyteSceneIndex.h"
#include <pxr/imaging/hd/sceneIndexPluginRegistry.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    HdSceneIndexPluginRegistry::Define<HdEpiphyteSceneIndexPlugin>();
}

TF_REGISTRY_FUNCTION(HdSceneIndexPlugin)
{
    HdSceneIndexPluginRegistry::GetInstance().RegisterSceneIndexForRenderer(
        TfToken(), // empty token means all renderers
        TfToken("HdEpiphyteSceneIndexPlugin"),
        nullptr, // no argument data necessary
        0,       // insertion phase
        HdSceneIndexPluginRegistry::InsertionOrderAtStart);
}

HdEpiphyteSceneIndexPlugin::HdEpiphyteSceneIndexPlugin() = default;

HdSceneIndexBaseRefPtr
HdEpiphyteSceneIndexPlugin::_AppendSceneIndex(
    const HdSceneIndexBaseRefPtr& inputScene,
    const HdContainerDataSourceHandle& inputArgs)
{
    return HdEpiphyteSceneIndex::New(inputScene);
}

PXR_NAMESPACE_CLOSE_SCOPE