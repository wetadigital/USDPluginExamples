//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include "pxr/base/tf/envSetting.h"
#include "pxr/imaging/hd/sceneIndexPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdEpiphyteSceneIndexPlugin

///
class HdEpiphyteSceneIndexPlugin : public HdSceneIndexPlugin
{
public:
    HdEpiphyteSceneIndexPlugin();

protected:
    HdSceneIndexBaseRefPtr _AppendSceneIndex(
        const HdSceneIndexBaseRefPtr& inputScene,
        const HdContainerDataSourceHandle& inputArgs) override;
};

PXR_NAMESPACE_CLOSE_SCOPE