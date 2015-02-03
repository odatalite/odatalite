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
    "Redundancy.0.9.2", /* Include.Namespace */
    "Redundancy" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/Redundancy", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _ThermalMetrics_ThermalMetrics_Temperatures =
{
    0, /* Nullable */
    0, /* Extended */
    "Temperatures", /* Name */
    "Collection(ThermalMetrics.Temperature)" /* Type */
};

static const EDM_Property _ThermalMetrics_ThermalMetrics_Fans =
{
    0, /* Nullable */
    0, /* Extended */
    "Fans", /* Name */
    "Collection(ThermalMetrics.Fan)" /* Type */
};

static const EDM_Property _ThermalMetrics_ThermalMetrics_Redundancy =
{
    0, /* Nullable */
    0, /* Extended */
    "Redundancy", /* Name */
    "Collection(Redundancy.Redundancy)" /* Type */
};

static const EDM_Property* _ThermalMetrics_ThermalMetrics_PropertiesArray[] =
{
    (const EDM_Property*)&_ThermalMetrics_ThermalMetrics_Temperatures,
    (const EDM_Property*)&_ThermalMetrics_ThermalMetrics_Fans,
    (const EDM_Property*)&_ThermalMetrics_ThermalMetrics_Redundancy
};

static const EDM_EntityType _ThermalMetrics_ThermalMetrics =
{
    "ThermalMetrics", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _ThermalMetrics_ThermalMetrics_PropertiesArray,
    OL_ARRAYSIZE(_ThermalMetrics_ThermalMetrics_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _ThermalMetrics_Temperature_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_Name =
{
    1, /* Nullable */
    0, /* Extended */
    "Name", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_Number =
{
    1, /* Nullable */
    0, /* Extended */
    "Number", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_Status =
{
    0, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_Units =
{
    1, /* Nullable */
    0, /* Extended */
    "Units", /* Name */
    "ThermalMetrics.TemperatureUnit" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_CurrentReading =
{
    1, /* Nullable */
    0, /* Extended */
    "CurrentReading", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_UpperThresholdNonCritical =
{
    1, /* Nullable */
    0, /* Extended */
    "UpperThresholdNonCritical", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_UpperThresholdCritical =
{
    1, /* Nullable */
    0, /* Extended */
    "UpperThresholdCritical", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_UpperThresholdFatal =
{
    1, /* Nullable */
    0, /* Extended */
    "UpperThresholdFatal", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_LowerThresholdNonCritical =
{
    1, /* Nullable */
    0, /* Extended */
    "LowerThresholdNonCritical", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_LowerThresholdCritical =
{
    1, /* Nullable */
    0, /* Extended */
    "LowerThresholdCritical", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_LowerThresholdFatal =
{
    1, /* Nullable */
    0, /* Extended */
    "LowerThresholdFatal", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_MinimumValue =
{
    1, /* Nullable */
    0, /* Extended */
    "MinimumValue", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_MaximumValue =
{
    1, /* Nullable */
    0, /* Extended */
    "MaximumValue", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_PhysicalContext =
{
    0, /* Nullable */
    0, /* Extended */
    "PhysicalContext", /* Name */
    "ThermalMetrics.PhysicalContext" /* Type */
};

static const EDM_Property _ThermalMetrics_Temperature_CorrelatableID =
{
    1, /* Nullable */
    0, /* Extended */
    "CorrelatableID", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _ThermalMetrics_Temperature_PropertiesArray[] =
{
    (const EDM_Property*)&_ThermalMetrics_Temperature_Oem,
    (const EDM_Property*)&_ThermalMetrics_Temperature_Name,
    (const EDM_Property*)&_ThermalMetrics_Temperature_Number,
    (const EDM_Property*)&_ThermalMetrics_Temperature_Status,
    (const EDM_Property*)&_ThermalMetrics_Temperature_Units,
    (const EDM_Property*)&_ThermalMetrics_Temperature_CurrentReading,
    (const EDM_Property*)&_ThermalMetrics_Temperature_UpperThresholdNonCritical,
    (const EDM_Property*)&_ThermalMetrics_Temperature_UpperThresholdCritical,
    (const EDM_Property*)&_ThermalMetrics_Temperature_UpperThresholdFatal,
    (const EDM_Property*)&_ThermalMetrics_Temperature_LowerThresholdNonCritical,
    (const EDM_Property*)&_ThermalMetrics_Temperature_LowerThresholdCritical,
    (const EDM_Property*)&_ThermalMetrics_Temperature_LowerThresholdFatal,
    (const EDM_Property*)&_ThermalMetrics_Temperature_MinimumValue,
    (const EDM_Property*)&_ThermalMetrics_Temperature_MaximumValue,
    (const EDM_Property*)&_ThermalMetrics_Temperature_PhysicalContext,
    (const EDM_Property*)&_ThermalMetrics_Temperature_CorrelatableID
};

static const EDM_ComplexType _ThermalMetrics_Temperature =
{
    "Temperature", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ThermalMetrics_Temperature_PropertiesArray,
    OL_ARRAYSIZE(_ThermalMetrics_Temperature_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _ThermalMetrics_TemperatureUnit_MembersArray[] =
{
    "Celsius",
    "Fahrenheit"
};

static const EDM_EnumType _ThermalMetrics_TemperatureUnit =
{
    "TemperatureUnit", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ThermalMetrics_TemperatureUnit_MembersArray,
    OL_ARRAYSIZE(_ThermalMetrics_TemperatureUnit_MembersArray)
};

static const char* _ThermalMetrics_PhysicalContext_MembersArray[] =
{
    "Room",
    "Intake",
    "Exhaust",
    "Front",
    "Back",
    "Upper",
    "Lower",
    "CPU",
    "GPU",
    "Backplane",
    "SystemBoard",
    "PowerSupply",
    "VoltageRegulator",
    "StorageDevice",
    "NetworkingDevice",
    "ComputeBay",
    "StorageBay",
    "NetworkBay",
    "ExpansionBay",
    "PowerSupplyBay"
};

static const EDM_EnumType _ThermalMetrics_PhysicalContext =
{
    "PhysicalContext", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ThermalMetrics_PhysicalContext_MembersArray,
    OL_ARRAYSIZE(_ThermalMetrics_PhysicalContext_MembersArray)
};

static const EDM_Property _ThermalMetrics_Fan_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_FanName =
{
    1, /* Nullable */
    0, /* Extended */
    "FanName", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_PhysicalContext =
{
    0, /* Nullable */
    0, /* Extended */
    "PhysicalContext", /* Name */
    "ThermalMetrics.PhysicalContext" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_CorrelatableID =
{
    1, /* Nullable */
    0, /* Extended */
    "CorrelatableID", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_Status =
{
    0, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_Units =
{
    1, /* Nullable */
    0, /* Extended */
    "Units", /* Name */
    "ThermalMetrics.FanUnits" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_CurrentReading =
{
    1, /* Nullable */
    0, /* Extended */
    "CurrentReading", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_UpperThresholdNonCritical =
{
    1, /* Nullable */
    0, /* Extended */
    "UpperThresholdNonCritical", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_UpperThresholdCritical =
{
    1, /* Nullable */
    0, /* Extended */
    "UpperThresholdCritical", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_UpperThresholdFatal =
{
    1, /* Nullable */
    0, /* Extended */
    "UpperThresholdFatal", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_LowerThresholdNonCritical =
{
    1, /* Nullable */
    0, /* Extended */
    "LowerThresholdNonCritical", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_LowerThresholdCritical =
{
    1, /* Nullable */
    0, /* Extended */
    "LowerThresholdCritical", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_LowerThresholdFatal =
{
    1, /* Nullable */
    0, /* Extended */
    "LowerThresholdFatal", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_MinimumValue =
{
    1, /* Nullable */
    0, /* Extended */
    "MinimumValue", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ThermalMetrics_Fan_MaximumValue =
{
    1, /* Nullable */
    0, /* Extended */
    "MaximumValue", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property* _ThermalMetrics_Fan_PropertiesArray[] =
{
    (const EDM_Property*)&_ThermalMetrics_Fan_Oem,
    (const EDM_Property*)&_ThermalMetrics_Fan_FanName,
    (const EDM_Property*)&_ThermalMetrics_Fan_PhysicalContext,
    (const EDM_Property*)&_ThermalMetrics_Fan_CorrelatableID,
    (const EDM_Property*)&_ThermalMetrics_Fan_Status,
    (const EDM_Property*)&_ThermalMetrics_Fan_Units,
    (const EDM_Property*)&_ThermalMetrics_Fan_CurrentReading,
    (const EDM_Property*)&_ThermalMetrics_Fan_UpperThresholdNonCritical,
    (const EDM_Property*)&_ThermalMetrics_Fan_UpperThresholdCritical,
    (const EDM_Property*)&_ThermalMetrics_Fan_UpperThresholdFatal,
    (const EDM_Property*)&_ThermalMetrics_Fan_LowerThresholdNonCritical,
    (const EDM_Property*)&_ThermalMetrics_Fan_LowerThresholdCritical,
    (const EDM_Property*)&_ThermalMetrics_Fan_LowerThresholdFatal,
    (const EDM_Property*)&_ThermalMetrics_Fan_MinimumValue,
    (const EDM_Property*)&_ThermalMetrics_Fan_MaximumValue
};

static const EDM_ComplexType _ThermalMetrics_Fan =
{
    "Fan", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ThermalMetrics_Fan_PropertiesArray,
    OL_ARRAYSIZE(_ThermalMetrics_Fan_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _ThermalMetrics_FanUnits_MembersArray[] =
{
    "RPM",
    "Percent"
};

static const EDM_EnumType _ThermalMetrics_FanUnits =
{
    "FanUnits", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ThermalMetrics_FanUnits_MembersArray,
    OL_ARRAYSIZE(_ThermalMetrics_FanUnits_MembersArray)
};

static const EDM_EntityType* _ThermalMetrics_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_ThermalMetrics_ThermalMetrics
};

static const EDM_ComplexType* _ThermalMetrics_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_ThermalMetrics_Temperature,
    (const EDM_ComplexType*)&_ThermalMetrics_Fan
};

static const EDM_EnumType* _ThermalMetrics_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_ThermalMetrics_TemperatureUnit,
    (const EDM_EnumType*)&_ThermalMetrics_PhysicalContext,
    (const EDM_EnumType*)&_ThermalMetrics_FanUnits
};

static const EDM_Schema _ThermalMetrics_Schema =
{
    "ThermalMetrics.0.9.2", /* Namespace */
    "ThermalMetrics", /* Alias */
    _ThermalMetrics_EntityTypesArray,
    OL_ARRAYSIZE(_ThermalMetrics_EntityTypesArray),
    _ThermalMetrics_ComplexTypesArray,
    OL_ARRAYSIZE(_ThermalMetrics_ComplexTypesArray),
    _ThermalMetrics_EnumTypesArray,
    OL_ARRAYSIZE(_ThermalMetrics_EnumTypesArray),
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
    &_ThermalMetrics_Schema
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
    &_3_Reference
};

const EDMX_Edmx ThermalMetrics_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

