//
// Copyright © 2023 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "renderPass.h"
#include "renderBuffer.h"
#include "renderer.h"
#include "debugCodes.h"

#include <pxr/imaging/hd/aov.h>
#include <pxr/imaging/hd/renderPassState.h>

PXR_NAMESPACE_OPEN_SCOPE

HdTriRenderPass::HdTriRenderPass(HdRenderIndex* index,
                                 const HdRprimCollection& collection)
  : HdRenderPass(index, collection)
{
}

HdTriRenderPass::~HdTriRenderPass() {}

bool
HdTriRenderPass::IsConverged() const
{
    return _converged;
}

void
HdTriRenderPass::_Execute(const HdRenderPassStateSharedPtr& renderPassState,
                          const TfTokenVector& renderTags)
{
    TF_DEBUG(HDTRI_GENERAL)
        .Msg("[%s] Executing render pass\n", TF_FUNC_NAME().c_str());

    // Iterate over each AOV.
    HdRenderPassAovBindingVector aovBindings =
        renderPassState->GetAovBindings();
    for (const HdRenderPassAovBinding& aovBinding : aovBindings) {

        // We will only write into the color AOV buffer.
        if (aovBinding.aovName == HdAovTokens->color) {
            HdTriRenderBuffer* renderBuffer =
                static_cast<HdTriRenderBuffer*>(aovBinding.renderBuffer);
            HdTriRenderer::DrawTriangle(renderBuffer);
        }
    }

    _converged = true;
}

PXR_NAMESPACE_CLOSE_SCOPE
