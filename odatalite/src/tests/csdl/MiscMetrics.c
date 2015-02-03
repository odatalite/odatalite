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

static const EDM_Property _MiscMetrics_MiscMetrics_Intrusion =
{
    0, /* Nullable */
    0, /* Extended */
    "Intrusion", /* Name */
    "Collection(MiscMetrics.Intrusion)" /* Type */
};

static const EDM_Property _MiscMetrics_MiscMetrics_Misc =
{
    0, /* Nullable */
    0, /* Extended */
    "Misc", /* Name */
    "Collection(MiscMetrics.MiscellaneousMetrics)" /* Type */
};

static const EDM_Property* _MiscMetrics_MiscMetrics_PropertiesArray[] =
{
    (const EDM_Property*)&_MiscMetrics_MiscMetrics_Intrusion,
    (const EDM_Property*)&_MiscMetrics_MiscMetrics_Misc
};

static const EDM_EntityType _MiscMetrics_MiscMetrics =
{
    "MiscMetrics", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _MiscMetrics_MiscMetrics_PropertiesArray,
    OL_ARRAYSIZE(_MiscMetrics_MiscMetrics_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _MiscMetrics_Metric_Name =
{
    0, /* Nullable */
    0, /* Extended */
    "Name", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _MiscMetrics_Metric_Number =
{
    1, /* Nullable */
    0, /* Extended */
    "Number", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _MiscMetrics_Metric_Status =
{
    0, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property _MiscMetrics_Metric_CurrentReading =
{
    1, /* Nullable */
    0, /* Extended */
    "CurrentReading", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _MiscMetrics_Metric_PropertiesArray[] =
{
    (const EDM_Property*)&_MiscMetrics_Metric_Name,
    (const EDM_Property*)&_MiscMetrics_Metric_Number,
    (const EDM_Property*)&_MiscMetrics_Metric_Status,
    (const EDM_Property*)&_MiscMetrics_Metric_CurrentReading
};

static const EDM_ComplexType _MiscMetrics_Metric =
{
    "Metric", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _MiscMetrics_Metric_PropertiesArray,
    OL_ARRAYSIZE(_MiscMetrics_Metric_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _MiscMetrics_Intrusion_SensorType =
{
    0, /* Nullable */
    0, /* Extended */
    "SensorType", /* Name */
    "MiscMetrics.IntrusionSensorType" /* Type */
};

static const EDM_Property* _MiscMetrics_Intrusion_PropertiesArray[] =
{
    (const EDM_Property*)&_MiscMetrics_Intrusion_SensorType
};

static const EDM_ComplexType _MiscMetrics_Intrusion =
{
    "Intrusion", /* Name */
    "MiscMetrics.Metric", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _MiscMetrics_Intrusion_PropertiesArray,
    OL_ARRAYSIZE(_MiscMetrics_Intrusion_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _MiscMetrics_IntrusionSensorType_MembersArray[] =
{
    "Physical(Chassis) Security",
    "Platform Security Violation Attempt"
};

static const EDM_EnumType _MiscMetrics_IntrusionSensorType =
{
    "IntrusionSensorType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_MiscMetrics_IntrusionSensorType_MembersArray,
    OL_ARRAYSIZE(_MiscMetrics_IntrusionSensorType_MembersArray)
};

static const EDM_Property _MiscMetrics_MiscellaneousMetrics_SensorType =
{
    0, /* Nullable */
    0, /* Extended */
    "SensorType", /* Name */
    "MiscMetrics.MiscellaneousSensorType" /* Type */
};

static const EDM_Property* _MiscMetrics_MiscellaneousMetrics_PropertiesArray[] =
{
    (const EDM_Property*)&_MiscMetrics_MiscellaneousMetrics_SensorType
};

static const EDM_ComplexType _MiscMetrics_MiscellaneousMetrics =
{
    "MiscellaneousMetrics", /* Name */
    "MiscMetrics.Metric", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _MiscMetrics_MiscellaneousMetrics_PropertiesArray,
    OL_ARRAYSIZE(_MiscMetrics_MiscellaneousMetrics_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _MiscMetrics_MiscellaneousSensorType_MembersArray[] =
{
    "OtherUnitsBasedSensor",
    "Memory",
    "DriveSlotOrBay",
    "POSTMemoryResize",
    "SystemFirmwareProgress",
    "EventLoggingDisabled",
    "SystemEvent",
    "CriticalInterrupt",
    "ButtonOrSwitch",
    "ModuleOrBoard",
    "MicrocontrollerOrCoprocessor",
    "AddInCard",
    "Chassis",
    "ChipSet",
    "OtherFRU",
    "CableOrInterconnect",
    "Terminator",
    "SystemBootOrRestart",
    "BootError",
    "BaseOSBootOrInstallationStatus",
    "OSStopOrShutdown",
    "SlotOrConnector",
    "SystemACPIPowerState",
    "Watchdog",
    "PlatformAlert",
    "EntityPresence",
    "MonitorASICOrIC",
    "LAN",
    "ManagementSubsystemHealth",
    "SessionAudit",
    "VersionChange",
    "FRUState",
    "Humidity",
    "Water"
};

static const EDM_EnumType _MiscMetrics_MiscellaneousSensorType =
{
    "MiscellaneousSensorType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_MiscMetrics_MiscellaneousSensorType_MembersArray,
    OL_ARRAYSIZE(_MiscMetrics_MiscellaneousSensorType_MembersArray)
};

static const EDM_EntityType* _MiscMetrics_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_MiscMetrics_MiscMetrics
};

static const EDM_ComplexType* _MiscMetrics_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_MiscMetrics_Metric,
    (const EDM_ComplexType*)&_MiscMetrics_Intrusion,
    (const EDM_ComplexType*)&_MiscMetrics_MiscellaneousMetrics
};

static const EDM_EnumType* _MiscMetrics_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_MiscMetrics_IntrusionSensorType,
    (const EDM_EnumType*)&_MiscMetrics_MiscellaneousSensorType
};

static const EDM_Schema _MiscMetrics_Schema =
{
    "MiscMetrics.0.9.2", /* Namespace */
    "MiscMetrics", /* Alias */
    _MiscMetrics_EntityTypesArray,
    OL_ARRAYSIZE(_MiscMetrics_EntityTypesArray),
    _MiscMetrics_ComplexTypesArray,
    OL_ARRAYSIZE(_MiscMetrics_ComplexTypesArray),
    _MiscMetrics_EnumTypesArray,
    OL_ARRAYSIZE(_MiscMetrics_EnumTypesArray),
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
    &_MiscMetrics_Schema
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
    &_2_Reference
};

const EDMX_Edmx MiscMetrics_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

