//
// Copyright © 2023 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "renderBuffer.h"
#include "debugCodes.h"

PXR_NAMESPACE_OPEN_SCOPE

HdTriRenderBuffer::HdTriRenderBuffer(const SdfPath& bprimId)
  : HdRenderBuffer(bprimId)
{
}

bool
HdTriRenderBuffer::Allocate(const GfVec3i& dimensions,
                            HdFormat format,
                            bool multiSampled)
{
    TF_DEBUG(HDTRI_GENERAL)
        .Msg("[%s] Allocate render buffer id=%s, dimensions=(%i, %i, %i), "
             "format=%i\n",
             TF_FUNC_NAME().c_str(),
             GetId().GetText(),
             dimensions[0],
             dimensions[1],
             dimensions[2],
             format);

    _Deallocate();

    // 2D buffer for now!
    TF_VERIFY(dimensions[2] == 1);

    _dimensions = dimensions;
    _format = format;
    _buffer.resize(_dimensions[0] * _dimensions[1] * _dimensions[2] *
                   HdDataSizeOfFormat(format));

    TF_DEBUG(HDTRI_GENERAL)
        .Msg("[%s] Render buffer id=%s, size=%lu\n",
             TF_FUNC_NAME().c_str(),
             GetId().GetText(),
             _buffer.size());

    return true;
}

unsigned int
HdTriRenderBuffer::GetWidth() const
{
    return _dimensions[0];
}

unsigned int
HdTriRenderBuffer::GetHeight() const
{
    return _dimensions[1];
}

unsigned int
HdTriRenderBuffer::GetDepth() const
{
    return _dimensions[2];
}

HdFormat
HdTriRenderBuffer::GetFormat() const
{
    return _format;
}

bool
HdTriRenderBuffer::IsMultiSampled() const
{
    return false;
}

void*
HdTriRenderBuffer::Map()
{
    _mappers.fetch_add(1);
    return static_cast<void*>(_buffer.data());
}

void
HdTriRenderBuffer::Unmap()
{
    _mappers.fetch_sub(1);
}

bool
HdTriRenderBuffer::IsMapped() const
{
    return _mappers.load() > 0;
}

bool
HdTriRenderBuffer::IsConverged() const
{
    return _converged.load();
}

void
HdTriRenderBuffer::SetConverged(bool converged)
{
    _converged.store(converged);
}

void
HdTriRenderBuffer::Resolve()
{
    // Nothing to do, there is only a single internal buffer for read/write.
    return;
}

void
HdTriRenderBuffer::_Deallocate()
{
    TF_VERIFY(!IsMapped());

    // Reset to default/empty values.
    _dimensions = GfVec3i(0, 0, 0);
    _format = HdFormatInvalid;
    _buffer.resize(0);
    _mappers.store(0);
    _converged.store(false);
}

PXR_NAMESPACE_CLOSE_SCOPE
