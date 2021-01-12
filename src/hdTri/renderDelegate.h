//
// Copyright © 2020 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/imaging/hd/renderDelegate.h>
#include <pxr/imaging/hd/resourceRegistry.h>

PXR_NAMESPACE_OPEN_SCOPE

class HdTriRenderParam;

/// \class HdTriRenderDelegate
///
/// Hydra renderer interface for the tri renderer.
class HdTriRenderDelegate final : public HdRenderDelegate
{
public:
    /// Default constructor.
    HdTriRenderDelegate();

    /// Constructor with render settings.
    HdTriRenderDelegate(const HdRenderSettingsMap& settingsMap);

    /// Destrucutor.
    virtual ~HdTriRenderDelegate() override;

    /// Cannot copy.
    HdTriRenderDelegate(const HdTriRenderDelegate&) = delete;
    HdTriRenderDelegate& operator=(const HdTriRenderDelegate&) = delete;

    /// Query supported hydra prim types.
    virtual const TfTokenVector& GetSupportedRprimTypes() const override;
    virtual const TfTokenVector& GetSupportedSprimTypes() const override;
    virtual const TfTokenVector& GetSupportedBprimTypes() const override;

    /// Return this delegate's render param, which provides top-level scene
    /// state.
    ///   \return An instance of HdEmbreeRenderParam.
    virtual HdRenderParam* GetRenderParam() const override;

    /// Returns a list of user-configurable render settings, available in the
    /// UI.
    virtual HdRenderSettingDescriptorList GetRenderSettingDescriptors()
        const override;

    /// Get the resource registry.
    virtual HdResourceRegistrySharedPtr GetResourceRegistry() const override;

    /// Create render pass.
    virtual HdRenderPassSharedPtr CreateRenderPass(
        HdRenderIndex* index,
        const HdRprimCollection& collection) override;

    /// Create an instancer.
    virtual HdInstancer* CreateInstancer(HdSceneDelegate* delegate,
#if PXR_VERSION >= 2102
                                         const SdfPath& id) override;
#else
                                         const SdfPath& id,
                                         const SdfPath& instancerId) override;
#endif

    /// Destroy an instancer.
    virtual void DestroyInstancer(HdInstancer* instancer) override;

    /// Create a new Rprim.
    virtual HdRprim* CreateRprim(const TfToken& typeId,
#if PXR_VERSION >= 2102
                                 const SdfPath& rprimId) override;
#else
                                 const SdfPath& rprimId,
                                 const SdfPath& instancerId) override;
#endif

    virtual void DestroyRprim(HdRprim* rprim) override;

    /// Create a new Sprim.
    virtual HdSprim* CreateSprim(const TfToken& typeId,
                                 const SdfPath& sprimId) override;

    /// TODO.
    virtual HdSprim* CreateFallbackSprim(const TfToken& typeId) override;

    /// Destroy an existing Sprim.
    virtual void DestroySprim(HdSprim* sprim) override;

    /// Create a new buffer prim.
    virtual HdBprim* CreateBprim(const TfToken& typeId,
                                 const SdfPath& bprimId) override;

    /// Create a fallback buffer prim.
    virtual HdBprim* CreateFallbackBprim(const TfToken& typeId) override;

    /// Destroy an existing Bprim.
    virtual void DestroyBprim(HdBprim* bprim) override;

    /// Do work.
    virtual void CommitResources(HdChangeTracker* tracker) override;

    /// Return the AOV description for \param aovName.
    /// This will be used to initialize the aov buffers.
    virtual HdAovDescriptor GetDefaultAovDescriptor(
        const TfToken& aovName) const override;

private:
    // Setup routine (used in both constructors).
    void _Setup();

    static const TfTokenVector SUPPORTED_RPRIM_TYPES;
    static const TfTokenVector SUPPORTED_SPRIM_TYPES;
    static const TfTokenVector SUPPORTED_BPRIM_TYPES;

    std::unique_ptr<HdTriRenderParam> _renderParam;
    HdRenderSettingDescriptorList _settingDescriptors;

    HdResourceRegistrySharedPtr _resourceRegistry;
};

PXR_NAMESPACE_CLOSE_SCOPE
