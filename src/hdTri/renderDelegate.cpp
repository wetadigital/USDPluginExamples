//
// Copyright © 2020 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "debugCodes.h"
#include "renderBuffer.h"
#include "renderDelegate.h"
#include "renderParam.h"
#include "renderPass.h"

#include <pxr/imaging/hd/bprim.h>
#include <pxr/imaging/hd/camera.h>
#include <pxr/imaging/hd/rprim.h>
#include <pxr/imaging/hd/sprim.h>

PXR_NAMESPACE_OPEN_SCOPE

/// Supported Hydra prim types.
const TfTokenVector HdTriRenderDelegate::SUPPORTED_RPRIM_TYPES = {};
const TfTokenVector HdTriRenderDelegate::SUPPORTED_SPRIM_TYPES = {
    HdPrimTypeTokens->camera
};
const TfTokenVector HdTriRenderDelegate::SUPPORTED_BPRIM_TYPES = {
    HdPrimTypeTokens->renderBuffer
};

HdTriRenderDelegate::HdTriRenderDelegate()
  : HdRenderDelegate()
{
    _Setup();
}

HdTriRenderDelegate::HdTriRenderDelegate(const HdRenderSettingsMap& settingsMap)
  : HdRenderDelegate(settingsMap)
{
    _Setup();
}

HdTriRenderDelegate::~HdTriRenderDelegate()
{
    // Clean resources.
    _renderParam.reset();
}

TfTokenVector const&
HdTriRenderDelegate::GetSupportedRprimTypes() const
{
    return SUPPORTED_RPRIM_TYPES;
}

TfTokenVector const&
HdTriRenderDelegate::GetSupportedSprimTypes() const
{
    return SUPPORTED_SPRIM_TYPES;
}

TfTokenVector const&
HdTriRenderDelegate::GetSupportedBprimTypes() const
{
    return SUPPORTED_BPRIM_TYPES;
}

HdRenderParam*
HdTriRenderDelegate::GetRenderParam() const
{
    return _renderParam.get();
}

HdRenderSettingDescriptorList
HdTriRenderDelegate::GetRenderSettingDescriptors() const
{
    return _settingDescriptors;
}

HdResourceRegistrySharedPtr
HdTriRenderDelegate::GetResourceRegistry() const
{
    return _resourceRegistry;
}

HdRenderPassSharedPtr
HdTriRenderDelegate::CreateRenderPass(HdRenderIndex* index,
                                      const HdRprimCollection& collection)
{
    return HdRenderPassSharedPtr(new HdTriRenderPass(index, collection));
}

void
HdTriRenderDelegate::CommitResources(HdChangeTracker* tracker)
{}

HdRprim*
HdTriRenderDelegate::CreateRprim(const TfToken& typeId,
#if PXR_VERSION >= 2102
                                 const SdfPath& rprimId)
#else
                                 const SdfPath& rprimId,
                                 const SdfPath& instancerId)
#endif
{
    TF_DEBUG(HDTRI_GENERAL)
        .Msg("[%s] Create HdTri Rprim type %s id %s\n",
             TF_FUNC_NAME().c_str(),
             typeId.GetText(),
             rprimId.GetText());
    TF_CODING_ERROR(
        "Unknown Rprim type=%s id=%s", typeId.GetText(), rprimId.GetText());
    return nullptr;
}

void
HdTriRenderDelegate::DestroyRprim(HdRprim* rprim)
{
    TF_DEBUG(HDTRI_GENERAL)
        .Msg("[%s] Destroy Rprim id %s\n",
             TF_FUNC_NAME().c_str(),
             rprim->GetId().GetText());
    delete rprim;
}

HdSprim*
HdTriRenderDelegate::CreateSprim(const TfToken& typeId, const SdfPath& sprimId)
{
    if (typeId == HdPrimTypeTokens->camera) {
        return new HdCamera(sprimId);
    } else {
        TF_CODING_ERROR(
            "Unknown Sprim type=%s id=%s", typeId.GetText(), sprimId.GetText());
    }
    return nullptr;
}

HdSprim*
HdTriRenderDelegate::CreateFallbackSprim(const TfToken& typeId)
{
    if (typeId == HdPrimTypeTokens->camera) {
        return new HdCamera(SdfPath::EmptyPath());
    } else {
        TF_CODING_ERROR("Unknown Fallback Sprim type=%s id=%s",
                        typeId.GetText());
    }
    return nullptr;
}

void
HdTriRenderDelegate::DestroySprim(HdSprim* sprim)
{
    delete sprim;
}

HdBprim*
HdTriRenderDelegate::CreateBprim(const TfToken& typeId, const SdfPath& bprimId)
{
    if (typeId == HdPrimTypeTokens->renderBuffer) {
        return new HdTriRenderBuffer(bprimId);
    } else {
        TF_CODING_ERROR("Unknown Bprim Type %s", typeId.GetText());
    }

    return nullptr;
}

HdBprim*
HdTriRenderDelegate::CreateFallbackBprim(const TfToken& typeId)
{
    if (typeId == HdPrimTypeTokens->renderBuffer) {
        return new HdTriRenderBuffer(SdfPath::EmptyPath());
    } else {
        TF_CODING_ERROR("Unknown Bprim Type %s", typeId.GetText());
    }

    return nullptr;
}

void
HdTriRenderDelegate::DestroyBprim(HdBprim* bprim)
{
    delete bprim;
}

HdInstancer*
HdTriRenderDelegate::CreateInstancer(HdSceneDelegate* delegate,
#if PXR_VERSION >= 2102
                                     const SdfPath& id)
#else
                                     const SdfPath& id,
                                     const SdfPath& instancerId)
#endif
{
    TF_CODING_ERROR("Creating Instancer not supported id=%s", id.GetText());
    return nullptr;
}

void
HdTriRenderDelegate::DestroyInstancer(HdInstancer* instancer)
{
    TF_CODING_ERROR("Destroy instancer not supported");
}

HdAovDescriptor
HdTriRenderDelegate::GetDefaultAovDescriptor(const TfToken& aovName) const
{
    if (aovName == HdAovTokens->color) {
        return HdAovDescriptor(
            HdFormatUNorm8Vec4, true, VtValue(GfVec4f(0.0f)));
    } else if (aovName == HdAovTokens->depth) {
        return HdAovDescriptor(HdFormatFloat32, false, VtValue(1.0f));
    } else if (aovName == HdAovTokens->primId ||
               aovName == HdAovTokens->instanceId ||
               aovName == HdAovTokens->elementId) {
        return HdAovDescriptor(HdFormatInt32, false, VtValue(-1));
    }

    return HdAovDescriptor();
}

void
HdTriRenderDelegate::_Setup()
{
    _renderParam = std::unique_ptr<HdTriRenderParam>(new HdTriRenderParam());
    _resourceRegistry =
#if PXR_VERSION >= 2002
        std::shared_ptr<HdResourceRegistry>(new HdResourceRegistry());
#else
        boost::shared_ptr<HdResourceRegistry>(new HdResourceRegistry());
#endif
}

PXR_NAMESPACE_CLOSE_SCOPE
