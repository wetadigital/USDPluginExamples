//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#pragma once

#include <pxr/pxr.h>
#include <pxr/usd/sdf/fileFormat.h>
#include <pxr/usd/pcp/dynamicFileFormatInterface.h>
#include <pxr/base/tf/staticTokens.h>

PXR_NAMESPACE_OPEN_SCOPE

/* clang-format off */
#define USD_TRIANGLE_FILE_FORMAT_TOKENS             \
    ((Id, "usdTriangleFileFormat"))                 \
    ((Version, "1.0"))                              \
    ((Target, "usd"))                               \
    ((Extension, "triangle"))                       \
    ((SideLength, "Usd_Triangle_SideLength"))
/* clang-format on */

TF_DECLARE_PUBLIC_TOKENS(UsdTriangleFileFormatTokens,
                         USD_TRIANGLE_FILE_FORMAT_TOKENS);

TF_DECLARE_WEAK_AND_REF_PTRS(UsdTriangleFileFormat);

/// \class UsdTriangleFileFormat
///
/// A simple file format plugin which "expands" any payload with a .triangle
/// suffix into a UsdGeomMesh representation of a equilateral triangle.
class UsdTriangleFileFormat
  : public SdfFileFormat
  , public PcpDynamicFileFormatInterface
{
public:
    // We can always "read" (given that we never need to actually examine the
    // contents).
    bool CanRead(const std::string& filePath) const override;

    // Author USD scene description into the output layer for a given .triangle
    // file.
    bool Read(SdfLayer* layer,
              const std::string& resolvedPath,
              bool metadataOnly) const override;

    // Author .usda text format when writing to string or stream.
    bool WriteToString(
        const SdfLayer& layer,
        std::string* str,
        const std::string& comment = std::string()) const override;
    bool WriteToStream(const SdfSpecHandle& spec,
                       std::ostream& out,
                       size_t indent) const override;

    // Read fields values (from context) and write into file format args.
    void ComposeFieldsForFileFormatArguments(
        const std::string& assetPath,
        const PcpDynamicFileFormatContext& context,
        FileFormatArguments* args,
        VtValue* contextDependencyData) const override;

    // Check if a field change affects any of the file format arguments
    // affecting the triangle (spoilers: the answer is yes).
    bool CanFieldChangeAffectFileFormatArguments(
        const TfToken& field,
        const VtValue& oldValue,
        const VtValue& newValue,
        const VtValue& contextDependencyData) const override;

protected:
    SDF_FILE_FORMAT_FACTORY_ACCESS;

    virtual ~UsdTriangleFileFormat();
    UsdTriangleFileFormat();
};

PXR_NAMESPACE_CLOSE_SCOPE
