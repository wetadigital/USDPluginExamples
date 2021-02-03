//
// Copyright © 2021 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef USDTRI_API_H
#define USDTRI_API_H

#include "pxr/base/arch/export.h"

#if defined(PXR_STATIC)
#    define USDTRI_API
#    define USDTRI_API_TEMPLATE_CLASS(...)
#    define USDTRI_API_TEMPLATE_STRUCT(...)
#    define USDTRI_LOCAL
#else
#    if defined(USDTRI_EXPORTS)
#        define USDTRI_API ARCH_EXPORT
#        define USDTRI_API_TEMPLATE_CLASS(...)                                 \
            ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#        define USDTRI_API_TEMPLATE_STRUCT(...)                                \
            ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#    else
#        define USDTRI_API ARCH_IMPORT
#        define USDTRI_API_TEMPLATE_CLASS(...)                                 \
            ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#        define USDTRI_API_TEMPLATE_STRUCT(...)                                \
            ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#    endif
#    define USDTRI_LOCAL ARCH_HIDDEN
#endif

#endif
