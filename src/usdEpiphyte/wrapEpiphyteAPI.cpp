//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//

#include "./epiphyteAPI.h"
#include "pxr/usd/usd/schemaBase.h"

#include "pxr/usd/sdf/primSpec.h"

#include "pxr/usd/usd/pyConversions.h"
#include "pxr/base/tf/pyAnnotatedBoolResult.h"
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
_CreateUvPositionAttr(UsdEpiphyteEpiphyteAPI& self,
                      object defaultVal,
                      bool writeSparsely)
{
    return self.CreateUvPositionAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float2),
        writeSparsely);
}

static UsdAttribute
_CreatePointIdAttr(UsdEpiphyteEpiphyteAPI& self,
                   object defaultVal,
                   bool writeSparsely)
{
    return self.CreatePointIdAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Int), writeSparsely);
}

static std::string
_Repr(const UsdEpiphyteEpiphyteAPI& self)
{
    std::string primRepr = TfPyRepr(self.GetPrim());
    return TfStringPrintf("UsdEpiphyte.EpiphyteAPI(%s)", primRepr.c_str());
}

struct UsdEpiphyteEpiphyteAPI_CanApplyResult
  : public TfPyAnnotatedBoolResult<std::string>
{
    UsdEpiphyteEpiphyteAPI_CanApplyResult(bool val, std::string const& msg)
      : TfPyAnnotatedBoolResult<std::string>(val, msg)
    {
    }
};

static UsdEpiphyteEpiphyteAPI_CanApplyResult
_WrapCanApply(const UsdPrim& prim)
{
    std::string whyNot;
    bool result = UsdEpiphyteEpiphyteAPI::CanApply(prim, &whyNot);
    return UsdEpiphyteEpiphyteAPI_CanApplyResult(result, whyNot);
}

} // anonymous namespace

void
wrapUsdEpiphyteEpiphyteAPI()
{
    typedef UsdEpiphyteEpiphyteAPI This;

    UsdEpiphyteEpiphyteAPI_CanApplyResult::Wrap<
        UsdEpiphyteEpiphyteAPI_CanApplyResult>("_CanApplyResult", "whyNot");

    class_<This, bases<UsdAPISchemaBase>> cls("EpiphyteAPI");

    cls.def(init<UsdPrim>(arg("prim")))
        .def(init<UsdSchemaBase const&>(arg("schemaObj")))
        .def(TfTypePythonClass())

        .def("Get", &This::Get, (arg("stage"), arg("path")))
        .staticmethod("Get")

        .def("CanApply", &_WrapCanApply, (arg("prim")))
        .staticmethod("CanApply")

        .def("Apply", &This::Apply, (arg("prim")))
        .staticmethod("Apply")

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

        .def("GetUvPositionAttr", &This::GetUvPositionAttr)
        .def("CreateUvPositionAttr",
             &_CreateUvPositionAttr,
             (arg("defaultValue") = object(), arg("writeSparsely") = false))

        .def("GetPointIdAttr", &This::GetPointIdAttr)
        .def("CreatePointIdAttr",
             &_CreatePointIdAttr,
             (arg("defaultValue") = object(), arg("writeSparsely") = false))

        .def("GetParentRel", &This::GetParentRel)
        .def("CreateParentRel", &This::CreateParentRel)
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