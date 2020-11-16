#include "fileFormat.h"

#include <pxr/pxr.h>

#include <pxr/usd/pcp/dynamicFileFormatContext.h>
#include <pxr/usd/usd/usdaFileFormat.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>

#include <fstream>
#include <string>

PXR_NAMESPACE_OPEN_SCOPE

// Default value of the triangle side length.
static const double defaultSideLengthValue = 1.0;

// Convenience function to extract the length value from a file format context.
static double
_ExtractSideLengthFromContext(const PcpDynamicFileFormatContext& context)
{
    // Default sideLength.
    double sideLength = defaultSideLengthValue;

    VtValue value;
    if (!context.ComposeValue(UsdTriangleFileFormatTokens->SideLength,
                              &value) ||
        value.IsEmpty()) {
        return sideLength;
    }

    if (!value.IsHolding<double>()) {
        TF_CODING_ERROR("Expected '%s' value to hold a double, got '%s'",
                        UsdTriangleFileFormatTokens->SideLength.GetText(),
                        TfStringify(value).c_str());
        return sideLength;
    }

    return value.UncheckedGet<double>();
}

static double
_ExtractSideLengthFromArgs(const SdfFileFormat::FileFormatArguments& args)
{
    // Default sideLength.
    double sideLength = defaultSideLengthValue;

    // Find "sideLength" file format argument.
    auto it = args.find(UsdTriangleFileFormatTokens->SideLength);
    if (it == args.end()) {
        return sideLength;
    }

    // Try to convert the string value to the actual output value type.
    double extractVal;
    bool success = true;
    extractVal = TfUnstringify<double>(it->second, &success);
    if (!success) {
        TF_CODING_ERROR(
            "Could not convert arg string '%s' to value of type double",
            UsdTriangleFileFormatTokens->SideLength.GetText());
        return sideLength;
    }

    sideLength = extractVal;
    return sideLength;
}

TF_DEFINE_PUBLIC_TOKENS(UsdTriangleFileFormatTokens,
                        USD_TRIANGLE_FILE_FORMAT_TOKENS);

TF_REGISTRY_FUNCTION(TfType)
{
    SDF_DEFINE_FILE_FORMAT(UsdTriangleFileFormat, SdfFileFormat);
}

UsdTriangleFileFormat::UsdTriangleFileFormat()
  : SdfFileFormat(UsdTriangleFileFormatTokens->Id,
                  UsdTriangleFileFormatTokens->Version,
                  UsdTriangleFileFormatTokens->Target,
                  UsdTriangleFileFormatTokens->Extension)
{}

UsdTriangleFileFormat::~UsdTriangleFileFormat() {}

bool
UsdTriangleFileFormat::CanRead(const std::string& filePath) const
{
    return true;
}

bool
UsdTriangleFileFormat::Read(SdfLayer* layer,
                            const std::string& resolvedPath,
                            bool metadataOnly) const
{
    if (!TF_VERIFY(layer)) {
        return false;
    }

    // Extract file format arguments.
    FileFormatArguments args;
    std::string layerPath;
    SdfLayer::SplitIdentifier(layer->GetIdentifier(), &layerPath, &args);
    double sideLength = _ExtractSideLengthFromArgs(args);

    // Create a new anonymous layer and wrap a stage around it.
    SdfLayerRefPtr newLayer = SdfLayer::CreateAnonymous(".usd");
    UsdStageRefPtr stage = UsdStage::Open(newLayer);

    // Define a Mesh, set as default prim.
    UsdGeomMesh mesh = UsdGeomMesh::Define(stage, SdfPath("/Triangle"));
    stage->SetDefaultPrim(mesh.GetPrim());

    // Author mesh attributes (describing a length-scaled equilateral triangle).
    VtIntArray faceVertexCounts(1, 3);
    mesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));

    VtIntArray faceVertexIndices{ 0, 1, 2 };
    mesh.CreateFaceVertexIndicesAttr(VtValue(faceVertexIndices));

    VtVec3fArray points{
        GfVec3f(0.0f, 0.57735027f * sideLength, 0.0f),
        GfVec3f(-0.5f * sideLength, -0.28867513f * sideLength, 0.0f),
        GfVec3f(0.5f * sideLength, -0.28867513f * sideLength, 0.0f)
    };
    mesh.CreatePointsAttr(VtValue(points));

    // Copy contents into output layer.
    layer->TransferContent(newLayer);

    return true;
}

bool
UsdTriangleFileFormat::WriteToString(const SdfLayer& layer,
                                     std::string* str,
                                     const std::string& comment) const
{
    // Write the generated contents in usda text format.
    return SdfFileFormat::FindById(UsdUsdaFileFormatTokens->Id)
        ->WriteToString(layer, str, comment);
}

bool
UsdTriangleFileFormat::WriteToStream(const SdfSpecHandle& spec,
                                     std::ostream& out,
                                     size_t indent) const
{
    // Write the generated contents in usda text format.
    return SdfFileFormat::FindById(UsdUsdaFileFormatTokens->Id)
        ->WriteToStream(spec, out, indent);
}

void
UsdTriangleFileFormat::ComposeFieldsForFileFormatArguments(
    const std::string& assetPath,
    const PcpDynamicFileFormatContext& context,
    FileFormatArguments* args,
    VtValue* contextDependencyData) const
{
    double sideLength = _ExtractSideLengthFromContext(context);
    (*args)[UsdTriangleFileFormatTokens->SideLength] = TfStringify(sideLength);
}

bool
UsdTriangleFileFormat::CanFieldChangeAffectFileFormatArguments(
    const TfToken& field,
    const VtValue& oldValue,
    const VtValue& newValue,
    const VtValue& contextDependencyData) const
{
    // Check if the "sideLength" argument changed.
    double oldLength = oldValue.IsHolding<double>()
                           ? oldValue.UncheckedGet<double>()
                           : defaultSideLengthValue;
    double newLength = newValue.IsHolding<double>()
                           ? newValue.UncheckedGet<double>()
                           : defaultSideLengthValue;

    return oldLength != newLength;
}

PXR_NAMESPACE_CLOSE_SCOPE
