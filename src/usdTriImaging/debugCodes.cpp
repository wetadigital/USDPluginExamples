#include "debugCodes.h"

#include <pxr/base/tf/registryManager.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
    TF_DEBUG_ENVIRONMENT_SYMBOL(USDTRIIMAGING,
                                "Global debug symbol for usdTriImaging.");
}

PXR_NAMESPACE_CLOSE_SCOPE
