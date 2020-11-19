//
// Copyright © 2020 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "renderBuffer.h"
#include "renderer.h"

#include <pxr/base/gf/vec2f.h>

PXR_NAMESPACE_OPEN_SCOPE

// 2D operation for checking if a point is inside a triangle.
static bool
_PointInsideTriangle(const GfVec2f& point, const GfVec2f triangle[3])
{
    float dX = point[0] - triangle[2][0];
    float dY = point[1] - triangle[2][1];
    float dX21 = triangle[2][0] - triangle[1][0];
    float dY12 = triangle[1][1] - triangle[2][1];
    float D = dY12 * (triangle[0][0] - triangle[2][0]) +
              dX21 * (triangle[0][1] - triangle[2][1]);
    float s = dY12 * dX + dX21 * dY;
    float t = (triangle[2][1] - triangle[0][1]) * dX +
              (triangle[0][0] - triangle[2][0]) * dY;
    if (D < 0) {
        return s <= 0 && t <= 0 && s + t >= D;
    } else {
        return s >= 0 && t >= 0 && s + t <= D;
    }
}

void
HdTriRenderer::DrawTriangle(HdTriRenderBuffer* colorBuffer)
{
    // Gather format information.
    // (size of each pixel, and of each pixel component).
    HdFormat format = colorBuffer->GetFormat();
    size_t formatSize = HdDataSizeOfFormat(format);
    size_t componentCount = HdGetComponentCount(format);

    // Begin buffer write.
    uint8_t* buffer = static_cast<uint8_t*>(colorBuffer->Map());

    // Compute raster-space coordinates composing a equilateral
    // triangle, whose sideLength is proportionate to the buffer width.
    float sideLength = (float)colorBuffer->GetWidth() * 0.45f;
    GfVec2f centerOffset((float)colorBuffer->GetWidth() * 0.5f,
                         (float)colorBuffer->GetHeight() * 0.41f);
    GfVec2f trianglePoints[3] = {
        GfVec2f(0.0f, 0.57735027f * sideLength) + centerOffset,
        GfVec2f(-0.5f * sideLength, -0.28867513f * sideLength) + centerOffset,
        GfVec2f(0.5f * sideLength, -0.28867513f * sideLength) + centerOffset
    };

    // Iterate over all raster coordinates.
    for (uint32_t y = 0; y < colorBuffer->GetHeight(); ++y) {
        for (uint32_t x = 0; x < colorBuffer->GetWidth(); ++x) {
            // Compute the raster index (pixel) offset.
            uint32_t bufferIndex = (y * colorBuffer->GetWidth()) + x;

            // Compute the byte offset, based on raster format.
            uint8_t* dst = &buffer[bufferIndex * formatSize];

            // Check if the raster coordinate is inside the 2D triangle.
            GfVec2f rasterCoord(x, y);
            if (_PointInsideTriangle(rasterCoord, trianglePoints)) {
                // Fill with white color.
                for (size_t c = 0; c < componentCount; ++c) {
                    dst[c] = 255;
                }
            }
        }
    }

    // End buffer write.
    colorBuffer->Unmap();
}

PXR_NAMESPACE_CLOSE_SCOPE
