//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include "pxr/imaging/hd/filteringSceneIndex.h"
#include "pxr/base/gf/vec2f.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DECLARE_REF_PTRS(HdEpiphyteSceneIndex);

class HdEpiphyteSceneIndex : public HdSingleInputFilteringSceneIndexBase
{
public:
    /// Creates a new Epiphyte prim scene index.
    static HdEpiphyteSceneIndexRefPtr New(
        HdSceneIndexBaseRefPtr const& inputScene)
    {
        return TfCreateRefPtr(new HdEpiphyteSceneIndex(inputScene));
    }

    HdSceneIndexPrim GetPrim(const SdfPath& primPath) const override;

    SdfPathVector GetChildPrimPaths(const SdfPath& primPath) const override;

protected:
    HdEpiphyteSceneIndex(HdSceneIndexBaseRefPtr const& inputScene);

    // satisfying HdSingleInputFilteringSceneIndexBase
    void _PrimsAdded(
        const HdSceneIndexBase& sender,
        const HdSceneIndexObserver::AddedPrimEntries& entries) override;

    void _PrimsRemoved(
        const HdSceneIndexBase& sender,
        const HdSceneIndexObserver::RemovedPrimEntries& entries) override;

    void _PrimsDirtied(
        const HdSceneIndexBase& sender,
        const HdSceneIndexObserver::DirtiedPrimEntries& entries) override;

    struct _EpiphyteBinding
    {
        SdfPath parent;
    };
    using _PrimToEpiphyteBindings = std::map<SdfPath, _EpiphyteBinding>;
    _PrimToEpiphyteBindings _primtToEpiphyteBinding;

    //    // Record  bindings of prim at primPath. That is, add entries to the
    //    // below data structures if needed and increase ref-counts.
    //    // Optionally, return prims of type coord system that this scene index
    //    needs
    //    // to add.
    void _AddBindingsForPrim(const SdfPath& primPath);
    //    // Remove coordSys bindings. That is, decrease ref-counts and remove
    //    entries
    //    // from below data structures if needed.
    //    // Optionally, return prims of type coord system that this scene index
    //    needs
    //    // to remove.
    //    void _RemoveBindings(const _Bindings &bindings,
    //                         SdfPathSet * removedCoordSysPrims);
    //    // Similar to above, but give the prim path explicitly to look-up
    //    bindings
    //    // in map.
    void _RemoveBindingsForPrim(const SdfPath& primPath);
    //    // Removes bindings for given prim and all its descendants stored in
    //    below
    //    // data structures.
};

PXR_NAMESPACE_CLOSE_SCOPE