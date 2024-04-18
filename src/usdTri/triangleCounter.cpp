//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//

/* A simple program which opens an input USD file, and prints
 * the number of prims of type "Triangle" in the composed stage */

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/primRange.h>
#include <usdpluginexamples/usdTri/triangle.h>

PXR_NAMESPACE_USING_DIRECTIVE

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("usage: triangleCounter <USD_FILE>\n");
        return EXIT_FAILURE;
    }

    int triangleCount = 0;
    UsdStageRefPtr stage = UsdStage::Open(argv[1]);
    for (UsdPrim prim : stage->TraverseAll()) {
        if (prim.IsA<UsdTriTriangle>()) {
            triangleCount++;
        }
    }

    printf("Number of triangles: %i\n", triangleCount);
    return EXIT_SUCCESS;
}
