//
// Copyright © 2021 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#ifndef USDTRI_GENERATED_TRIANGLE_H
#define USDTRI_GENERATED_TRIANGLE_H

/// \file usdTri/triangle.h

#include "pxr/pxr.h"
#include "./api.h"
#include "pxr/usd/usdGeom/gprim.h"
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
// TRIANGLE                                                                   //
// -------------------------------------------------------------------------- //

/// \class UsdTriTriangle
///
/// An equilateral triangle, whose vertices are equidistant to the
/// origin and lie on the XY plane in object-space.
///
class UsdTriTriangle : public UsdGeomGprim
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaType
    static const UsdSchemaType schemaType = UsdSchemaType::ConcreteTyped;

    /// Construct a UsdTriTriangle on UsdPrim \p prim .
    /// Equivalent to UsdTriTriangle::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdTriTriangle(const UsdPrim& prim = UsdPrim())
      : UsdGeomGprim(prim)
    {}

    /// Construct a UsdTriTriangle on the prim held by \p schemaObj .
    /// Should be preferred over UsdTriTriangle(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdTriTriangle(const UsdSchemaBase& schemaObj)
      : UsdGeomGprim(schemaObj)
    {}

    /// Destructor.
    USDTRI_API
    virtual ~UsdTriTriangle();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDTRI_API
    static const TfTokenVector& GetSchemaAttributeNames(
        bool includeInherited = true);

    /// Return a UsdTriTriangle holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdTriTriangle(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDTRI_API
    static UsdTriTriangle Get(const UsdStagePtr& stage, const SdfPath& path);

    /// Attempt to ensure a \a UsdPrim adhering to this schema at \p path
    /// is defined (according to UsdPrim::IsDefined()) on this stage.
    ///
    /// If a prim adhering to this schema at \p path is already defined on this
    /// stage, return that prim.  Otherwise author an \a SdfPrimSpec with
    /// \a specifier == \a SdfSpecifierDef and this schema's prim type name for
    /// the prim at \p path at the current EditTarget.  Author \a SdfPrimSpec s
    /// with \p specifier == \a SdfSpecifierDef and empty typeName at the
    /// current EditTarget for any nonexistent, or existing but not \a Defined
    /// ancestors.
    ///
    /// The given \a path must be an absolute prim path that does not contain
    /// any variant selections.
    ///
    /// If it is impossible to author any of the necessary PrimSpecs, (for
    /// example, in case \a path cannot map to the current UsdEditTarget's
    /// namespace) issue an error and return an invalid \a UsdPrim.
    ///
    /// Note that this method may return a defined prim whose typeName does not
    /// specify this schema class, in case a stronger typeName opinion overrides
    /// the opinion at the current EditTarget.
    ///
    USDTRI_API
    static UsdTriTriangle Define(const UsdStagePtr& stage, const SdfPath& path);

protected:
    /// Returns the type of schema this class belongs to.
    ///
    /// \sa UsdSchemaType
    USDTRI_API
    UsdSchemaType _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDTRI_API
    static const TfType& _GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDTRI_API
    const TfType& _GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // SIDELENGTH
    // --------------------------------------------------------------------- //
    /// The length of each side of the equilateral triangle.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `double sideLength = 1` |
    /// | C++ Type | double |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
    USDTRI_API
    UsdAttribute GetSideLengthAttr() const;

    /// See GetSideLengthAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDTRI_API
    UsdAttribute CreateSideLengthAttr(VtValue const& defaultValue = VtValue(),
                                      bool writeSparsely = false) const;

public:
    // --------------------------------------------------------------------- //
    // EXTENT
    // --------------------------------------------------------------------- //
    /// Fallback extent value of a triangle with side length of 1.0.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float3[] extent = [(-0.5, -0.28867513, 0), (0.5,
    /// 0.57735026, 0)]` | | C++ Type | VtArray<GfVec3f> | | \ref Usd_Datatypes
    /// "Usd Type" | SdfValueTypeNames->Float3Array |
    USDTRI_API
    UsdAttribute GetExtentAttr() const;

    /// See GetExtentAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDTRI_API
    UsdAttribute CreateExtentAttr(VtValue const& defaultValue = VtValue(),
                                  bool writeSparsely = false) const;

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

    /// Compute the extent for the triangle defined by its side length.
    ///
    /// \retval true Successful extent computation.
    /// \retval false Failure to compute extent.
    USDGEOM_API
    static bool ComputeExtent(double sideLength, VtVec3fArray* extent);

    /// \overload
    /// Computes the extent as if the matrix \p transform was first applied.
    USDGEOM_API
    static bool ComputeExtent(double sideLength,
                              const GfMatrix4d& transform,
                              VtVec3fArray* extent);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
