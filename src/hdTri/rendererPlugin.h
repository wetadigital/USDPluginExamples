//
// Copyright © 2023 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/imaging/hd/rendererPlugin.h>

PXR_NAMESPACE_OPEN_SCOPE

/// Plugin entry points (construction, destruction) for the tri render delegate.
class HdTriRendererPlugin final : public HdRendererPlugin
{
public:
    HdTriRendererPlugin() = default;
    ~HdTriRendererPlugin() override = default;

    /// Cannot copy.
    HdTriRendererPlugin(const HdTriRendererPlugin&) = delete;
    HdTriRendererPlugin& operator=(const HdTriRendererPlugin&) = delete;

    /// Create a new tri render delegate instance.
    virtual HdRenderDelegate* CreateRenderDelegate() override;

    /// Delete a tri render delegate instance.
    virtual void DeleteRenderDelegate(
        HdRenderDelegate* renderDelegate) override;

    /// Is this plugin supported?
    virtual bool IsSupported(bool gpuEnabled = true) const override;
};

PXR_NAMESPACE_CLOSE_SCOPE
