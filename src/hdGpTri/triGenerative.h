//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//

#include <pxr/imaging/hdGp/sceneIndexPlugin.h>
#include <pxr/imaging/hdGp/generativeProcedural.h>
#include <pxr/imaging/hdGp/generativeProceduralPlugin.h>
#include <pxr/imaging/hdGp/generativeProceduralPluginRegistry.h>

PXR_NAMESPACE_OPEN_SCOPE

class _MakeTriGenerativeProcedural : public HdGpGenerativeProcedural
{

public:
    _MakeTriGenerativeProcedural(const SdfPath& i_primPath);

    static HdGpGenerativeProcedural* New(const SdfPath& i_primPath);

    HdGpGenerativeProcedural::DependencyMap UpdateDependencies(
        const HdSceneIndexBaseRefPtr& i_inputScene) override;

    ChildPrimTypeMap Update(const HdSceneIndexBaseRefPtr& i_inputScene,
                            const ChildPrimTypeMap& i_previousResult,
                            const DependencyMap& i_dirtiedDependencies,
                            HdSceneIndexObserver::DirtiedPrimEntries*
                                o_outputDirtiedPrims) override;

    HdSceneIndexPrim GetChildPrim(const HdSceneIndexBaseRefPtr& i_inputScene,
                                  const SdfPath& i_childPrimPath) override;

private:
    HdContainerDataSourceHandle _GetChildMeshDs();
    HdContainerDataSourceHandle _GetChildPrimvarsDs();

    double _sideLength = 1.0f;
    HdSampledDataSourceHandle _displayColorDs;
    HdSampledDataSourceHandle _sideLengthDs;
};

class TriProceduralPlugin : public HdGpGenerativeProceduralPlugin
{
public:
    TriProceduralPlugin() = default;

    HdGpGenerativeProcedural* Construct(
        const SdfPath& i_proceduralPrimPath) override;
};

PXR_NAMESPACE_CLOSE_SCOPE