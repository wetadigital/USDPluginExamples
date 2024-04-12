//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/imaging/hd/renderPass.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdTriRenderPass
///
/// Represents a single iteration of a render.
class HdTriRenderPass final : public HdRenderPass
{
public:
    HdTriRenderPass(HdRenderIndex* index, const HdRprimCollection& collection);
    virtual ~HdTriRenderPass();

protected:
    /// Draw the scene with the bound renderpass state.
    ///
    /// \param renderPassState Input parameters (including viewer parameters)
    /// for this renderpass. \param renderTags Which rendertags should be drawn
    /// this pass.
    virtual void _Execute(const HdRenderPassStateSharedPtr& renderPassState,
                          const TfTokenVector& renderTags) override;

    /// Determine whether the sample buffer has enough samples, to be considered
    /// final.
    virtual bool IsConverged() const override;

private:
    // Is converged?
    bool _converged = false;
};

PXR_NAMESPACE_CLOSE_SCOPE
