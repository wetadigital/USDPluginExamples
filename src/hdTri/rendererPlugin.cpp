//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "renderDelegate.h"
#include "rendererPlugin.h"

#include <pxr/imaging/hd/rendererPluginRegistry.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    HdRendererPluginRegistry::Define<HdTriRendererPlugin>();
}

HdRenderDelegate*
HdTriRendererPlugin::CreateRenderDelegate()
{
    return new HdTriRenderDelegate();
}

void
HdTriRendererPlugin::DeleteRenderDelegate(HdRenderDelegate* renderDelegate)
{
    delete renderDelegate;
}

bool
HdTriRendererPlugin::IsSupported(bool gpuEnabled) const
{
    return true;
}

PXR_NAMESPACE_CLOSE_SCOPE
