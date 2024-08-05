#pragma once

#include "pxr/imaging/hd/api.h"
#include <pxr/imaging/hd/schema.h>

PXR_NAMESPACE_OPEN_SCOPE

//-----------------------------------------------------------------------------

#define HDEPIPHYTE_SCHEMA_TOKENS (epiphyte)((target, "parent"))(pointId)(uv)

TF_DECLARE_PUBLIC_TOKENS(HdEpiphyteSchemaTokens,
                         HD_API,
                         HDEPIPHYTE_SCHEMA_TOKENS);

//-----------------------------------------------------------------------------

class HdEpiphyteSchema : public HdSchema
{
public:
    HdEpiphyteSchema(HdContainerDataSourceHandle container)
      : HdSchema(container)
    {
    }

    // ACCESSORS

    HD_API
    HdPathDataSourceHandle GetPTarget();

    HD_API
    HdIntDataSourceHandle GetPointId();

    HD_API
    HdVec2fDataSourceHandle GetUv();

    // RETRIEVING AND CONSTRUCTING

    /// Builds a container data source which includes the provided child data
    /// sources. Parameters with nullptr values are excluded. This is a
    /// low-level interface. For cases in which it's desired to define
    /// the container with a sparse set of child fields, the Builder class
    /// is often more convenient and readable.
    HD_API
    static HdContainerDataSourceHandle BuildRetained(
        const HdPathDataSourceHandle& target,
        const HdIntDataSourceHandle& pointId,
        const HdVec2fDataSourceHandle& uv);

    /// \class HdEpiphyteSchema::Builder
    ///
    /// Utility class for setting sparse sets of child data source fields to be
    /// filled as arguments into BuildRetained. Because all setter methods
    /// return a reference to the instance, this can be used in the "builder
    /// pattern" form.
    class Builder
    {
    public:
        HD_API
        Builder& SetTarget(const HdPathDataSourceHandle& target);

        HD_API
        Builder& SetPointId(const HdIntDataSourceHandle& pointId);

        HD_API
        Builder& SetUv(const HdVec2fDataSourceHandle& uv);

        /// Returns a container data source containing the members set thus far.
        HD_API
        HdContainerDataSourceHandle Build();

    private:
        HdPathDataSourceHandle _target;
        HdIntDataSourceHandle _pointId;
        HdVec2fDataSourceHandle _uv;
    };

    /// Retrieves a container data source with the schema's default name token
    /// "epiphyte" from the parent container and constructs a
    /// HdEpiphyteSchema instance.
    /// Because the requested container data source may not exist, the result
    /// should be checked with IsDefined() or a bool comparison before use.
    HD_API
    static HdEpiphyteSchema GetFromParent(
        const HdContainerDataSourceHandle& fromParentContainer);

    /// Returns a token where the container representing this schema is found in
    /// a container by default.
    HD_API
    static const TfToken& GetSchemaToken();

    /// Returns an HdDataSourceLocator (relative to the prim-level data source)
    /// where the container representing this schema is found by default.
    HD_API
    static const HdDataSourceLocator& GetDefaultLocator();

    HD_API
    static const HdDataSourceLocator& GetTargetLocator();

    HD_API
    static const HdDataSourceLocator& GetUvLocator();

    HD_API
    static const HdDataSourceLocator& GetPointIdLocator();
};

PXR_NAMESPACE_CLOSE_SCOPE