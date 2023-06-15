//
// Copyright © 2023 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

PXR_NAMESPACE_OPEN_SCOPE

// Forward declarations.
class HdTriRenderBuffer;

/// \class HdTriRenderer
///
/// A triangle renderer.
class HdTriRenderer final
{
public:
    /// Draw a triangle into a color buffer.
    ///
    /// \param colorBuffer A 2D color buffer.
    static void DrawTriangle(HdTriRenderBuffer* colorBuffer);
};

PXR_NAMESPACE_CLOSE_SCOPE
