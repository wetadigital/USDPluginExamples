//
// Copyright © 2024 Weta FX Limited
//
// SPDX-License-Identifier: Apache-2.0
//

#include "hdEpiphyteSchema.h"
#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdEpiphyteSchemaTokens, HDEPIPHYTE_SCHEMA_TOKENS);

HdPathDataSourceHandle
HdEpiphyteSchema::GetPTarget()
{
    return _GetTypedDataSource<HdPathDataSource>(
        HdEpiphyteSchemaTokens->target);
}
HdIntDataSourceHandle
HdEpiphyteSchema::GetPointId()
{
    return _GetTypedDataSource<HdIntDataSource>(
        HdEpiphyteSchemaTokens->pointId);
}
HdVec2fDataSourceHandle
HdEpiphyteSchema::GetUv()
{
    return _GetTypedDataSource<HdVec2fDataSource>(HdEpiphyteSchemaTokens->uv);
}

/*static*/
HdContainerDataSourceHandle
HdEpiphyteSchema::BuildRetained(const HdPathDataSourceHandle& target,
                                const HdIntDataSourceHandle& pointId,
                                const HdVec2fDataSourceHandle& uv)
{
    TfToken names[3];
    HdDataSourceBaseHandle values[3];

    size_t count = 0;
    if (target) {
        names[count] = HdEpiphyteSchemaTokens->target;
        values[count++] = target;
    }
    if (pointId) {
        names[count] = HdEpiphyteSchemaTokens->pointId;
        values[count++] = pointId;
    }
    if (uv) {
        names[count] = HdEpiphyteSchemaTokens->uv;
        values[count++] = uv;
    }
    return HdRetainedContainerDataSource::New(count, names, values);
}

/*static*/
HdEpiphyteSchema
HdEpiphyteSchema::GetFromParent(
    const HdContainerDataSourceHandle& fromParentContainer)
{
    return HdEpiphyteSchema(
        fromParentContainer
            ? HdContainerDataSource::Cast(
                  fromParentContainer->Get(HdEpiphyteSchemaTokens->epiphyte))
            : nullptr);
}

/*static*/
const TfToken&
HdEpiphyteSchema::GetSchemaToken()
{
    return HdEpiphyteSchemaTokens->epiphyte;
}
/*static*/
const HdDataSourceLocator&
HdEpiphyteSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(HdEpiphyteSchemaTokens->epiphyte);
    return locator;
}

const HdDataSourceLocator&
HdEpiphyteSchema::GetTargetLocator()
{
    static const HdDataSourceLocator locator(HdEpiphyteSchemaTokens->epiphyte,
                                             HdEpiphyteSchemaTokens->target);
    return locator;
}

const HdDataSourceLocator&
HdEpiphyteSchema::GetUvLocator()
{
    static const HdDataSourceLocator locator(HdEpiphyteSchemaTokens->epiphyte,
                                             HdEpiphyteSchemaTokens->uv);
    return locator;
}

const HdDataSourceLocator&
HdEpiphyteSchema::GetPointIdLocator()
{
    static const HdDataSourceLocator locator(HdEpiphyteSchemaTokens->epiphyte,
                                             HdEpiphyteSchemaTokens->pointId);
    return locator;
}
HdEpiphyteSchema::Builder&
HdEpiphyteSchema::Builder::SetTarget(const HdPathDataSourceHandle& target)
{
    _target = target;
    return *this;
}
HdEpiphyteSchema::Builder&
HdEpiphyteSchema::Builder::SetPointId(const HdIntDataSourceHandle& pointId)
{
    _pointId = pointId;
    return *this;
}
HdEpiphyteSchema::Builder&
HdEpiphyteSchema::Builder::SetUv(const HdVec2fDataSourceHandle& uv)
{
    _uv = uv;
    return *this;
}

HdContainerDataSourceHandle
HdEpiphyteSchema::Builder::Build()
{
    return HdEpiphyteSchema::BuildRetained(_target, _pointId, _uv);
}

PXR_NAMESPACE_CLOSE_SCOPE