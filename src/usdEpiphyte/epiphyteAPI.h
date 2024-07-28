//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//

#ifndef USDEPIPHYTE_GENERATED_EPIPHYTEAPI_H
#define USDEPIPHYTE_GENERATED_EPIPHYTEAPI_H

/// \file usdEpiphyte/EpiphyteAPI.h

#include "pxr/pxr.h"
#include "./api.h"
#include "pxr/usd/usd/apiSchemaBase.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include "./tokens.h"

#include "pxr/base/vt/value.h"

#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/matrix4d.h"

#include "pxr/base/tf/token.h"
#include "pxr/base/tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// EPIPHYTEAPI //
// -------------------------------------------------------------------------- //

/// \class UsdEpiphyteEpiphyteAPI
///
///
class UsdEpiphyteEpiphyteAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::SingleApplyAPI;

    /// Construct a UsdEpiphyteEpiphyteAPI on UsdPrim \p prim .
    /// Equivalent to UsdEpiphyteEpiphyteAPI::Get(prim.GetStage(),
    /// prim.GetPath()) for a \em valid \p prim, but will not immediately throw
    /// an error for an invalid \p prim
    explicit UsdEpiphyteEpiphyteAPI(const UsdPrim& prim = UsdPrim())
      : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a UsdEpiphyteEpiphyteAPI on the prim held by \p schemaObj .
    /// Should be preferred over UsdEpiphyteEpiphyteAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdEpiphyteEpiphyteAPI(const UsdSchemaBase& schemaObj)
      : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    USDEPIPHYTE_API
    virtual ~UsdEpiphyteEpiphyteAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDEPIPHYTE_API
    static const TfTokenVector& GetSchemaAttributeNames(
        bool includeInherited = true);

    /// Return a UsdEpiphyteEpiphyteAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdEpiphyteEpiphyteAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDEPIPHYTE_API
    static UsdEpiphyteEpiphyteAPI Get(const UsdStagePtr& stage,
                                      const SdfPath& path);

    /// Returns true if this <b>single-apply</b> API schema can be applied to
    /// the given \p prim. If this schema can not be a applied to the prim,
    /// this returns false and, if provided, populates \p whyNot with the
    /// reason it can not be applied.
    ///
    /// Note that if CanApply returns false, that does not necessarily imply
    /// that calling Apply will fail. Callers are expected to call CanApply
    /// before calling Apply if they want to ensure that it is valid to
    /// apply a schema.
    ///
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::CanApplyAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    USDEPIPHYTE_API
    static bool CanApply(const UsdPrim& prim, std::string* whyNot = nullptr);

    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "EPIPHYTEAPI" to the
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    ///
    /// \return A valid UsdEpiphyteEpiphyteAPI object is returned upon success.
    /// An invalid (or empty) UsdEpiphyteEpiphyteAPI object is returned upon
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions
    /// resulting in failure.
    ///
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::CanApplyAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    USDEPIPHYTE_API
    static UsdEpiphyteEpiphyteAPI Apply(const UsdPrim& prim);

protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDEPIPHYTE_API
    UsdSchemaKind _GetSchemaKind() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDEPIPHYTE_API
    static const TfType& _GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDEPIPHYTE_API
    const TfType& _GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // UVPOSITION
    // --------------------------------------------------------------------- //
    /// The Offset
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float2 uvPosition` |
    /// | C++ Type | GfVec2f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float2 |
    USDEPIPHYTE_API
    UsdAttribute GetUvPositionAttr() const;

    /// See GetUvPositionAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDEPIPHYTE_API
    UsdAttribute CreateUvPositionAttr(VtValue const& defaultValue = VtValue(),
                                      bool writeSparsely = false) const;

public:
    // --------------------------------------------------------------------- //
    // POINTID
    // --------------------------------------------------------------------- //
    /// The PointId
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int pointId` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    USDEPIPHYTE_API
    UsdAttribute GetPointIdAttr() const;

    /// See GetPointIdAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDEPIPHYTE_API
    UsdAttribute CreatePointIdAttr(VtValue const& defaultValue = VtValue(),
                                   bool writeSparsely = false) const;

public:
    // --------------------------------------------------------------------- //
    // PARENT
    // --------------------------------------------------------------------- //
    /// The Parent Object
    ///
    USDEPIPHYTE_API
    UsdRelationship GetParentRel() const;

    /// See GetParentRel(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create
    USDEPIPHYTE_API
    UsdRelationship CreateParentRel() const;

public:
    // ===================================================================== //
    // Feel free to add custom code below this line, it will be preserved by
    // the code generator.
    //
    // Just remember to:
    //  - Close the class declaration with };
    //  - Close the namespace with PXR_NAMESPACE_CLOSE_SCOPE
    //  - Close the include guard with #endif
    // ===================================================================== //
    // --(BEGIN CUSTOM CODE)--
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif