//
// Copyright © 2021 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/imaging/hd/renderBuffer.h>
#include <pxr/base/gf/vec3i.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdTriRenderBuffer
///
/// A block of memory which we are rendering into.
class HdTriRenderBuffer : public HdRenderBuffer
{
public:
    HdTriRenderBuffer(const SdfPath& bprimId);

    /// Allocate a new buffer with the given dimensions and format.
    virtual bool Allocate(const GfVec3i& dimensions,
                          HdFormat format,
                          bool multiSampled) override;

    /// Accessor for buffer width.
    virtual unsigned int GetWidth() const override;

    /// Accessor for buffer height.
    virtual unsigned int GetHeight() const override;

    /// Accessor for buffer depth.
    virtual unsigned int GetDepth() const override;

    /// Accessor for buffer format.
    virtual HdFormat GetFormat() const override;

    /// Accessor for the buffer multisample state.
    virtual bool IsMultiSampled() const override;

    /// Map the buffer for reading/writing. The control flow should be Map(),
    /// before any I/O, followed by memory access, followed by Unmap() when
    /// done.
    virtual void* Map() override;

    /// Unmap the buffer.
    virtual void Unmap() override;

    /// Return whether any clients have this buffer mapped currently.
    virtual bool IsMapped() const override;

    /// Is the buffer converged?
    virtual bool IsConverged() const override;

    /// Set the convergence.
    void SetConverged(bool converged);

    /// Resolve the sample buffer into final values.
    virtual void Resolve() override;

private:
    // Release any allocated resources.
    virtual void _Deallocate() override;

    // Buffer dimensions.
    GfVec3i _dimensions = GfVec3i(0, 0, 0);

    // Buffer format.
    HdFormat _format = HdFormatInvalid;

    // The actual buffer of bytes.
    std::vector<uint8_t> _buffer;

    // The number of callers mapping this buffer.
    std::atomic<int> _mappers{ 0 };

    // Whether the buffer has been marked as converged.
    std::atomic<bool> _converged{ false };
};

PXR_NAMESPACE_CLOSE_SCOPE
