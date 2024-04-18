//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "./triangle.h"
#include "pxr/usd/usd/schemaBase.h"

#include "pxr/usd/sdf/primSpec.h"

#include "pxr/usd/usd/pyConversions.h"
#include "pxr/base/tf/pyContainerConversions.h"
#include "pxr/base/tf/pyResultConversions.h"
#include "pxr/base/tf/pyUtils.h"
#include "pxr/base/tf/wrapTypeHelpers.h"

#include <boost/python.hpp>

#include <string>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

#define WRAP_CUSTOM                                                            \
    template<class Cls>                                                        \
    static void _CustomWrapCode(Cls& _class)

// fwd decl.
WRAP_CUSTOM;

static UsdAttribute
_CreateSideLengthAttr(UsdTriTriangle& self,
                      object defaultVal,
                      bool writeSparsely)
{
    return self.CreateSideLengthAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double),
        writeSparsely);
}

static UsdAttribute
_CreateExtentAttr(UsdTriTriangle& self, object defaultVal, bool writeSparsely)
{
    return self.CreateExtentAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float3Array),
        writeSparsely);
}

static std::string
_Repr(const UsdTriTriangle& self)
{
    std::string primRepr = TfPyRepr(self.GetPrim());
    return TfStringPrintf("UsdTri.Triangle(%s)", primRepr.c_str());
}

} // anonymous namespace

void
wrapUsdTriTriangle()
{
    typedef UsdTriTriangle This;

    class_<This, bases<UsdGeomGprim>> cls("Triangle");

    cls.def(init<UsdPrim>(arg("prim")))
        .def(init<UsdSchemaBase const&>(arg("schemaObj")))
        .def(TfTypePythonClass())

        .def("Get", &This::Get, (arg("stage"), arg("path")))
        .staticmethod("Get")

        .def("Define", &This::Define, (arg("stage"), arg("path")))
        .staticmethod("Define")

        .def("GetSchemaAttributeNames",
             &This::GetSchemaAttributeNames,
             arg("includeInherited") = true,
             return_value_policy<TfPySequenceToList>())
        .staticmethod("GetSchemaAttributeNames")

        .def("_GetStaticTfType",
             (TfType const& (*)())TfType::Find<This>,
             return_value_policy<return_by_value>())
        .staticmethod("_GetStaticTfType")

        .def(!self)

        .def("GetSideLengthAttr", &This::GetSideLengthAttr)
        .def("CreateSideLengthAttr",
             &_CreateSideLengthAttr,
             (arg("defaultValue") = object(), arg("writeSparsely") = false))

        .def("GetExtentAttr", &This::GetExtentAttr)
        .def("CreateExtentAttr",
             &_CreateExtentAttr,
             (arg("defaultValue") = object(), arg("writeSparsely") = false))

        .def("__repr__", ::_Repr);

    _CustomWrapCode(cls);
}

// ===================================================================== //
// Feel free to add custom code below this line, it will be preserved by
// the code generator.  The entry point for your custom code should look
// minimally like the following:
//
// WRAP_CUSTOM {
//     _class
//         .def("MyCustomMethod", ...)
//     ;
// }
//
// Of course any other ancillary or support code may be provided.
//
// Just remember to wrap code in the appropriate delimiters:
// 'namespace {', '}'.
//
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

namespace {

WRAP_CUSTOM {}

}
