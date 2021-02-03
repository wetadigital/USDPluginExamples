//
// Copyright © 2021 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include <pxr/usd/usd/stage.h>
#include <pxr/base/tf/diagnostic.h>
#include <usdpluginexamples/usdTri/triangle.h>

PXR_NAMESPACE_USING_DIRECTIVE

int
main(int argc, char* argv[])
{
    // Create a new stage.
    UsdStageRefPtr stage = UsdStage::CreateInMemory();

    // Define a Triangle.
    UsdTriTriangle triangle =
        UsdTriTriangle::Define(stage, SdfPath("/myTriangle"));
    TF_AXIOM(triangle);

    // Validate side length attr fallback value.
    double sideLength;
    TF_AXIOM(triangle.GetSideLengthAttr().Get(&sideLength));
    TF_AXIOM(sideLength == 1.0f);

    return EXIT_SUCCESS;
}
