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
    "DMTFExtensions.0.9.2", /* Include.Namespace */
    "DMTF" /* Include.Alias */
};

static const EDMX_Include* _1_IncludesArray[] =
{
    &_1_0_Include
};

static const EDMX_Reference _1_Reference =
{
    "http://dmtf.org/schema/v1/DMTFExtensions", /* Uri */
    _1_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_1_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _2_0_Include =
{
    "Resource.0.9.2", /* Include.Namespace */
    "Resource" /* Include.Alias */
};

static const EDMX_Include* _2_IncludesArray[] =
{
    &_2_0_Include
};

static const EDMX_Reference _2_Reference =
{
    "http://dmtf.org/schema/v1/Resource", /* Uri */
    _2_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_2_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _3_0_Include =
{
    "LogService.0.9.2", /* Include.Namespace */
    "LogService" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/LogService", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _4_0_Include =
{
    "ThermalMetrics.0.9.2", /* Include.Namespace */
    "ThermalMetrics" /* Include.Alias */
};

static const EDMX_Include* _4_IncludesArray[] =
{
    &_4_0_Include
};

static const EDMX_Reference _4_Reference =
{
    "http://dmtf.org/schema/v1/ThermalMetrics", /* Uri */
    _4_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_4_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _5_0_Include =
{
    "PowerMetrics.0.9.2", /* Include.Namespace */
    "PowerMetrics" /* Include.Alias */
};

static const EDMX_Include* _5_IncludesArray[] =
{
    &_5_0_Include
};

static const EDMX_Reference _5_Reference =
{
    "http://dmtf.org/schema/v1/PowerMetrics", /* Uri */
    _5_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_5_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _6_0_Include =
{
    "MiscMetrics.0.9.2", /* Include.Namespace */
    "MiscMetrics" /* Include.Alias */
};

static const EDMX_Include* _6_IncludesArray[] =
{
    &_6_0_Include
};

static const EDMX_Reference _6_Reference =
{
    "http://dmtf.org/schema/v1/MiscMetrics", /* Uri */
    _6_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_6_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _7_0_Include =
{
    "ManagerAccount.0.9.2", /* Include.Namespace */
    "ManagerAccount" /* Include.Alias */
};

static const EDMX_Include* _7_IncludesArray[] =
{
    &_7_0_Include
};

static const EDMX_Reference _7_Reference =
{
    "http://dmtf.org/schema/v1/ManagerAccount", /* Uri */
    _7_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_7_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _8_0_Include =
{
    "ComputerSystem.0.9.2", /* Include.Namespace */
    "ComputerSystem" /* Include.Alias */
};

static const EDMX_Include* _8_IncludesArray[] =
{
    &_8_0_Include
};

static const EDMX_Reference _8_Reference =
{
    "http://dmtf.org/schema/v1/ComputerSystem", /* Uri */
    _8_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_8_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _Chassis_Chassis_ChassisType =
{
    0, /* Nullable */
    0, /* Extended */
    "ChassisType", /* Name */
    "Chassis.ChassisType" /* Type */
};

static const EDM_Property _Chassis_Chassis_Manufacturer =
{
    1, /* Nullable */
    0, /* Extended */
    "Manufacturer", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Chassis_Chassis_Model =
{
    1, /* Nullable */
    0, /* Extended */
    "Model", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Chassis_Chassis_SKU =
{
    1, /* Nullable */
    0, /* Extended */
    "SKU", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Chassis_Chassis_SerialNumber =
{
    1, /* Nullable */
    0, /* Extended */
    "SerialNumber", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Chassis_Chassis_Version =
{
    1, /* Nullable */
    0, /* Extended */
    "Version", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Chassis_Chassis_PartNumber =
{
    1, /* Nullable */
    0, /* Extended */
    "PartNumber", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Chassis_Chassis_AssetTag =
{
    1, /* Nullable */
    0, /* Extended */
    "AssetTag", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Chassis_Chassis_IndicatorLED =
{
    1, /* Nullable */
    0, /* Extended */
    "IndicatorLED", /* Name */
    "Chassis.IndicatorLED" /* Type */
};

static const EDM_Property _Chassis_Chassis_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "Chassis.Links" /* Type */
};

static const EDM_Property* _Chassis_Chassis_PropertiesArray[] =
{
    (const EDM_Property*)&_Chassis_Chassis_ChassisType,
    (const EDM_Property*)&_Chassis_Chassis_Manufacturer,
    (const EDM_Property*)&_Chassis_Chassis_Model,
    (const EDM_Property*)&_Chassis_Chassis_SKU,
    (const EDM_Property*)&_Chassis_Chassis_SerialNumber,
    (const EDM_Property*)&_Chassis_Chassis_Version,
    (const EDM_Property*)&_Chassis_Chassis_PartNumber,
    (const EDM_Property*)&_Chassis_Chassis_AssetTag,
    (const EDM_Property*)&_Chassis_Chassis_IndicatorLED,
    (const EDM_Property*)&_Chassis_Chassis_Links
};

static const EDM_EntityType _Chassis_Chassis =
{
    "Chassis", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _Chassis_Chassis_PropertiesArray,
    OL_ARRAYSIZE(_Chassis_Chassis_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_NavigationProperty _Chassis_Links_LogService =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "LogService", /* Name */
    "LogService.LogService", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Chassis_Links_ComputerSystems =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "ComputerSystems", /* Name */
    "Collection(ComputerSystem.ComputerSystem)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Chassis_Links_ManagedBy =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "ManagedBy", /* Name */
    "Collection(ManagerAccount.ManagerAccount)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Chassis_Links_ThermalMetrics =
{
    EDM_NavigationProperty_Flags_Nullable |
    EDM_NavigationProperty_Flags_ContainsTarget, /* Flags */
    "ThermalMetrics", /* Name */
    "ThermalMetrics.ThermalMetrics", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Chassis_Links_PowerMetrics =
{
    EDM_NavigationProperty_Flags_Nullable |
    EDM_NavigationProperty_Flags_ContainsTarget, /* Flags */
    "PowerMetrics", /* Name */
    "PowerMetrics.PowerMetrics", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Chassis_Links_MiscMetrics =
{
    EDM_NavigationProperty_Flags_Nullable |
    EDM_NavigationProperty_Flags_ContainsTarget, /* Flags */
    "MiscMetrics", /* Name */
    "MiscMetrics.MiscMetrics", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Chassis_Links_ContainedBy =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "ContainedBy", /* Name */
    "Chassis.Chassis", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Chassis_Links_Contains =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Contains", /* Name */
    "Collection(Chassis.Chassis)", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _Chassis_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _Chassis_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_Chassis_Links_Oem
};

static const EDM_NavigationProperty* _Chassis_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_Chassis_Links_LogService,
    (const EDM_NavigationProperty*)&_Chassis_Links_ComputerSystems,
    (const EDM_NavigationProperty*)&_Chassis_Links_ManagedBy,
    (const EDM_NavigationProperty*)&_Chassis_Links_ThermalMetrics,
    (const EDM_NavigationProperty*)&_Chassis_Links_PowerMetrics,
    (const EDM_NavigationProperty*)&_Chassis_Links_MiscMetrics,
    (const EDM_NavigationProperty*)&_Chassis_Links_ContainedBy,
    (const EDM_NavigationProperty*)&_Chassis_Links_Contains
};

static const EDM_ComplexType _Chassis_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Chassis_Links_PropertiesArray,
    OL_ARRAYSIZE(_Chassis_Links_PropertiesArray),
    _Chassis_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_Chassis_Links_NavigationPropertiesArray)
};

static const char* _Chassis_ChassisType_MembersArray[] =
{
    "Rack",
    "Blade",
    "Enclosure",
    "StandAlone",
    "RackMount",
    "Card",
    "Cartridge",
    "Row",
    "Pod",
    "Expansion",
    "Sidecar",
    "Zone",
    "Sled",
    "Shelf",
    "Other"
};

static const EDM_EnumType _Chassis_ChassisType =
{
    "ChassisType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Chassis_ChassisType_MembersArray,
    OL_ARRAYSIZE(_Chassis_ChassisType_MembersArray)
};

static const char* _Chassis_IndicatorLED_MembersArray[] =
{
    "Unknown",
    "Lit",
    "Blinking",
    "Off"
};

static const EDM_EnumType _Chassis_IndicatorLED =
{
    "IndicatorLED", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Chassis_IndicatorLED_MembersArray,
    OL_ARRAYSIZE(_Chassis_IndicatorLED_MembersArray)
};

static const EDM_EntityType* _Chassis_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_Chassis_Chassis
};

static const EDM_ComplexType* _Chassis_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_Chassis_Links
};

static const EDM_EnumType* _Chassis_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_Chassis_ChassisType,
    (const EDM_EnumType*)&_Chassis_IndicatorLED
};

static const EDM_Schema _Chassis_Schema =
{
    "Chassis.0.9.2", /* Namespace */
    "Chassis", /* Alias */
    _Chassis_EntityTypesArray,
    OL_ARRAYSIZE(_Chassis_EntityTypesArray),
    _Chassis_ComplexTypesArray,
    OL_ARRAYSIZE(_Chassis_ComplexTypesArray),
    _Chassis_EnumTypesArray,
    OL_ARRAYSIZE(_Chassis_EnumTypesArray),
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
    &_Chassis_Schema
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
    &_5_Reference,
    &_6_Reference,
    &_7_Reference,
    &_8_Reference
};

const EDMX_Edmx Chassis_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

