//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef USDEPIPHYTE_API_H
#define USDEPIPHYTE_API_H

#include "pxr/base/arch/export.h"

#if defined(PXR_STATIC)
#    define USDEPIPHYTE_API
#    define USDEPIPHYTE_API_TEMPLATE_CLASS(...)
#    define USDEPIPHYTE_API_TEMPLATE_STRUCT(...)
#    define USDEPIPHYTE_LOCAL
#else
#    if defined(USDEPIPHYTE_EXPORTS)
#        define USDEPIPHYTE_API ARCH_EXPORT
#        define USDEPIPHYTE_API_TEMPLATE_CLASS(...)                            \
            ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#        define USDEPIPHYTE_API_TEMPLATE_STRUCT(...)                           \
            ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#    else
#        define USDEPIPHYTE_API ARCH_IMPORT
#        define USDEPIPHYTE_API_TEMPLATE_CLASS(...)                            \
            ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#        define USDEPIPHYTE_API_TEMPLATE_STRUCT(...)                           \
            ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#    endif
#    define USDEPIPHYTE_LOCAL ARCH_HIDDEN
#endif

#endif