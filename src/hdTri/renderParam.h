//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/imaging/hd/renderDelegate.h>
#include <pxr/pxr.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdTriRenderParam
///
/// Object created by the render delegate to transport top-level scene state
/// to each prim during Sync().
class HdTriRenderParam final : public HdRenderParam
{
public:
    HdTriRenderParam();
    virtual ~HdTriRenderParam() = default;
};

PXR_NAMESPACE_CLOSE_SCOPE
