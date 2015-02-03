/*
**==============================================================================
**
** ODatatLite ver. 0.0.3
**
** Copyright (c) Microsoft Corporation
**
** All rights reserved. 
**
** MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy ** of this software and associated documentation files (the ""Software""), to 
** deal in the Software without restriction, including without limitation the 
** rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
** sell copies of the Software, and to permit persons to whom the Software is 
** furnished to do so, subject to the following conditions: The above copyright ** notice and this permission notice shall be included in all copies or 
** substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
** THE SOFTWARE.
**
**==============================================================================
*/
#include <odata/odata.h>

static const EDMX_Include _0_0_Include =
{
    "Org.OData.Core.V1", /* Include.Namespace */
    "OData" /* Include.Alias */
};

static const EDMX_Include* _0_IncludesArray[] =
{
    &_0_0_Include
};

static const EDMX_Reference _0_Reference =
{
    "http://docs.oasis-open.org/odata/odata/v4.0/cs01/vocabularies/Org.OData.Core.V1.xml", /* Uri */
    _0_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_0_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _1_0_Include =
{
    "Org.OData.Measures.V1", /* Include.Namespace */
    "OData.Measures" /* Include.Alias */
};

static const EDMX_Include* _1_IncludesArray[] =
{
    &_1_0_Include
};

static const EDMX_Reference _1_Reference =
{
    "http://docs.oasis-open.org/odata/odata/v4.0/cs01/vocabularies/Org.OData.Measures.V1.xml", /* Uri */
    _1_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_1_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _2_0_Include =
{
    "DMTFExtensions.0.9.2", /* Include.Namespace */
    "DMTF" /* Include.Alias */
};

static const EDMX_Include _2_1_Include =
{
    "Validation.0.9.2", /* Include.Namespace */
    "Validation" /* Include.Alias */
};

static const EDMX_Include* _2_IncludesArray[] =
{
    &_2_0_Include,
    &_2_1_Include
};

static const EDMX_Reference _2_Reference =
{
    "http://dmtf.org/schema/v1/DMTFExtensions", /* Uri */
    _2_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_2_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _3_0_Include =
{
    "Resource.0.9.2", /* Include.Namespace */
    "Resource" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/Resource", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _4_0_Include =
{
    "Redundancy.0.9.2", /* Include.Namespace */
    "Redundancy" /* Include.Alias */
};

static const EDMX_Include* _4_IncludesArray[] =
{
    &_4_0_Include
};

static const EDMX_Reference _4_Reference =
{
    "http://dmtf.org/schema/v1/Redundancy", /* Uri */
    _4_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_4_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _5_0_Include =
{
    "Firmware.0.9.2", /* Include.Namespace */
    "Firmware" /* Include.Alias */
};

static const EDMX_Include* _5_IncludesArray[] =
{
    &_5_0_Include
};

static const EDMX_Reference _5_Reference =
{
    "http://dmtf.org/schema/v1/Firmware", /* Uri */
    _5_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_5_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _PowerMetrics_PowerMetrics_PowerConsumedWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "PowerConsumedWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetrics_PowerRequestedWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "PowerRequestedWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetrics_PowerAvailableWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "PowerAvailableWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetrics_PowerCapacityWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "PowerCapacityWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetrics_PowerAllocatedWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "PowerAllocatedWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetrics_PowerMetrics =
{
    0, /* Nullable */
    0, /* Extended */
    "PowerMetrics", /* Name */
    "PowerMetrics.PowerMetric" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetrics_PowerLimit =
{
    0, /* Nullable */
    0, /* Extended */
    "PowerLimit", /* Name */
    "PowerMetrics.PowerLimit" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetrics_PowerSupplies =
{
    0, /* Nullable */
    0, /* Extended */
    "PowerSupplies", /* Name */
    "Collection(PowerMetrics.PowerSupply)" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetrics_Redundancy =
{
    1, /* Nullable */
    0, /* Extended */
    "Redundancy", /* Name */
    "Collection(Redundancy.Redundancy)" /* Type */
};

static const EDM_Property* _PowerMetrics_PowerMetrics_PropertiesArray[] =
{
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_PowerConsumedWatts,
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_PowerRequestedWatts,
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_PowerAvailableWatts,
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_PowerCapacityWatts,
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_PowerAllocatedWatts,
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_PowerMetrics,
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_PowerLimit,
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_PowerSupplies,
    (const EDM_Property*)&_PowerMetrics_PowerMetrics_Redundancy
};

static const EDM_EntityType _PowerMetrics_PowerMetrics =
{
    "PowerMetrics", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _PowerMetrics_PowerMetrics_PropertiesArray,
    OL_ARRAYSIZE(_PowerMetrics_PowerMetrics_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _PowerMetrics_PowerMetric_IntervalInMin =
{
    1, /* Nullable */
    0, /* Extended */
    "IntervalInMin", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetric_MinConsumedWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "MinConsumedWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetric_MaxConsumedWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "MaxConsumedWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerMetric_AverageConsumedWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "AverageConsumedWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property* _PowerMetrics_PowerMetric_PropertiesArray[] =
{
    (const EDM_Property*)&_PowerMetrics_PowerMetric_IntervalInMin,
    (const EDM_Property*)&_PowerMetrics_PowerMetric_MinConsumedWatts,
    (const EDM_Property*)&_PowerMetrics_PowerMetric_MaxConsumedWatts,
    (const EDM_Property*)&_PowerMetrics_PowerMetric_AverageConsumedWatts
};

static const EDM_ComplexType _PowerMetrics_PowerMetric =
{
    "PowerMetric", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _PowerMetrics_PowerMetric_PropertiesArray,
    OL_ARRAYSIZE(_PowerMetrics_PowerMetric_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _PowerMetrics_PowerLimit_LimitInWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "LimitInWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerLimit_LimitException =
{
    1, /* Nullable */
    0, /* Extended */
    "LimitException", /* Name */
    "PowerMetrics.PowerLimitException" /* Type */
};

static const EDM_Property _PowerMetrics_PowerLimit_CorrectionInMs =
{
    1, /* Nullable */
    0, /* Extended */
    "CorrectionInMs", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerLimit_CorrelatableID =
{
    1, /* Nullable */
    0, /* Extended */
    "CorrelatableID", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_Property* _PowerMetrics_PowerLimit_PropertiesArray[] =
{
    (const EDM_Property*)&_PowerMetrics_PowerLimit_LimitInWatts,
    (const EDM_Property*)&_PowerMetrics_PowerLimit_LimitException,
    (const EDM_Property*)&_PowerMetrics_PowerLimit_CorrectionInMs,
    (const EDM_Property*)&_PowerMetrics_PowerLimit_CorrelatableID
};

static const EDM_ComplexType _PowerMetrics_PowerLimit =
{
    "PowerLimit", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _PowerMetrics_PowerLimit_PropertiesArray,
    OL_ARRAYSIZE(_PowerMetrics_PowerLimit_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _PowerMetrics_PowerLimitException_MembersArray[] =
{
    "NoAction",
    "HardPowerOff",
    "LogEventOnly",
    "Oem"
};

static const EDM_EnumType _PowerMetrics_PowerLimitException =
{
    "PowerLimitException", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_PowerMetrics_PowerLimitException_MembersArray,
    OL_ARRAYSIZE(_PowerMetrics_PowerLimitException_MembersArray)
};

static const EDM_Property _PowerMetrics_PowerSupply_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_Name =
{
    1, /* Nullable */
    0, /* Extended */
    "Name", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_CorrelatableID =
{
    1, /* Nullable */
    0, /* Extended */
    "CorrelatableID", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_Status =
{
    0, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_PowerSupplyType =
{
    1, /* Nullable */
    0, /* Extended */
    "PowerSupplyType", /* Name */
    "PowerMetrics.PowerSupplyType" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_LineInputVoltageType =
{
    1, /* Nullable */
    0, /* Extended */
    "LineInputVoltageType", /* Name */
    "PowerMetrics.LineInputVoltageType" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_LineInputVoltage =
{
    1, /* Nullable */
    0, /* Extended */
    "LineInputVoltage", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_PowerCapacityWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "PowerCapacityWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_LastPowerOutputWatts =
{
    1, /* Nullable */
    0, /* Extended */
    "LastPowerOutputWatts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_Model =
{
    1, /* Nullable */
    0, /* Extended */
    "Model", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_FirmwareVersion =
{
    1, /* Nullable */
    0, /* Extended */
    "FirmwareVersion", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_SerialNumber =
{
    1, /* Nullable */
    0, /* Extended */
    "SerialNumber", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_PartNumber =
{
    1, /* Nullable */
    0, /* Extended */
    "PartNumber", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _PowerMetrics_PowerSupply_SparePartNumber =
{
    1, /* Nullable */
    0, /* Extended */
    "SparePartNumber", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _PowerMetrics_PowerSupply_PropertiesArray[] =
{
    (const EDM_Property*)&_PowerMetrics_PowerSupply_Oem,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_Name,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_CorrelatableID,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_Status,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_PowerSupplyType,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_LineInputVoltageType,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_LineInputVoltage,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_PowerCapacityWatts,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_LastPowerOutputWatts,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_Model,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_FirmwareVersion,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_SerialNumber,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_PartNumber,
    (const EDM_Property*)&_PowerMetrics_PowerSupply_SparePartNumber
};

static const EDM_ComplexType _PowerMetrics_PowerSupply =
{
    "PowerSupply", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _PowerMetrics_PowerSupply_PropertiesArray,
    OL_ARRAYSIZE(_PowerMetrics_PowerSupply_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _PowerMetrics_PowerSupplyType_MembersArray[] =
{
    "Unknown",
    "AC",
    "DC"
};

static const EDM_EnumType _PowerMetrics_PowerSupplyType =
{
    "PowerSupplyType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_PowerMetrics_PowerSupplyType_MembersArray,
    OL_ARRAYSIZE(_PowerMetrics_PowerSupplyType_MembersArray)
};

static const char* _PowerMetrics_LineInputVoltageType_MembersArray[] =
{
    "Unknown",
    "ACLowLine",
    "ACMidLine",
    "ACHighLine",
    "DCNeg48V",
    "DC480V"
};

static const EDM_EnumType _PowerMetrics_LineInputVoltageType =
{
    "LineInputVoltageType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_PowerMetrics_LineInputVoltageType_MembersArray,
    OL_ARRAYSIZE(_PowerMetrics_LineInputVoltageType_MembersArray)
};

static const EDM_EntityType* _PowerMetrics_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_PowerMetrics_PowerMetrics
};

static const EDM_ComplexType* _PowerMetrics_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_PowerMetrics_PowerMetric,
    (const EDM_ComplexType*)&_PowerMetrics_PowerLimit,
    (const EDM_ComplexType*)&_PowerMetrics_PowerSupply
};

static const EDM_EnumType* _PowerMetrics_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_PowerMetrics_PowerLimitException,
    (const EDM_EnumType*)&_PowerMetrics_PowerSupplyType,
    (const EDM_EnumType*)&_PowerMetrics_LineInputVoltageType
};

static const EDM_Schema _PowerMetrics_Schema =
{
    "PowerMetrics.0.9.2", /* Namespace */
    "PowerMetrics", /* Alias */
    _PowerMetrics_EntityTypesArray,
    OL_ARRAYSIZE(_PowerMetrics_EntityTypesArray),
    _PowerMetrics_ComplexTypesArray,
    OL_ARRAYSIZE(_PowerMetrics_ComplexTypesArray),
    _PowerMetrics_EnumTypesArray,
    OL_ARRAYSIZE(_PowerMetrics_EnumTypesArray),
    NULL, /* Actions */
    0, /* NumActions */
    NULL, /* TypeDefinitions */
    0, /* NumTypeDefinitions */
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_PowerMetrics_Schema
};

static const EDMX_DataServices _DataServices =
{
    _SchemasArray, /* Schemas */
    OL_ARRAYSIZE(_SchemasArray) /* NumSchemas */
};

static const EDMX_Reference* _ReferencesArray[] =
{
    &_0_Reference,
    &_1_Reference,
    &_2_Reference,
    &_3_Reference,
    &_4_Reference,
    &_5_Reference
};

const EDMX_Edmx PowerMetrics_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

