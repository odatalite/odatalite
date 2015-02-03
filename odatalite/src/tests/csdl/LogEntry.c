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
    "Resource.0.9.2", /* Include.Namespace */
    "Resource" /* Include.Alias */
};

static const EDMX_Include* _0_IncludesArray[] =
{
    &_0_0_Include
};

static const EDMX_Reference _0_Reference =
{
    "http://dmtf.org/schema/v1/Resource", /* Uri */
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

static const EDMX_Include _1_1_Include =
{
    "Validation.0.9.2", /* Include.Namespace */
    "Validation" /* Include.Alias */
};

static const EDMX_Include* _1_IncludesArray[] =
{
    &_1_0_Include,
    &_1_1_Include
};

static const EDMX_Reference _1_Reference =
{
    "http://dmtf.org/schema/v1/DMTFExtensions", /* Uri */
    _1_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_1_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _LogEntry_LogEntry_RecordId =
{
    0, /* Nullable */
    0, /* Extended */
    "RecordId", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_Severity =
{
    0, /* Nullable */
    0, /* Extended */
    "Severity", /* Name */
    "LogEntry.EventSeverity" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_Created =
{
    0, /* Nullable */
    0, /* Extended */
    "Created", /* Name */
    "Edm.DateTimeOffset" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_EntryType =
{
    0, /* Nullable */
    0, /* Extended */
    "EntryType", /* Name */
    "LogEntry.LogEntryType" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_OemRecordFormat =
{
    0, /* Nullable */
    0, /* Extended */
    "OemRecordFormat", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_EntryCode =
{
    0, /* Nullable */
    0, /* Extended */
    "EntryCode", /* Name */
    "LogEntry.LogEntryCode" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_SensorType =
{
    0, /* Nullable */
    0, /* Extended */
    "SensorType", /* Name */
    "LogEntry.SensorType" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_Number =
{
    0, /* Nullable */
    0, /* Extended */
    "Number", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_Message =
{
    0, /* Nullable */
    0, /* Extended */
    "Message", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_MessageId =
{
    0, /* Nullable */
    0, /* Extended */
    "MessageId", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_MessageArgs =
{
    1, /* Nullable */
    0, /* Extended */
    "MessageArgs", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_Property _LogEntry_LogEntry_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "LogEntry.Links" /* Type */
};

static const EDM_Property* _LogEntry_LogEntry_PropertiesArray[] =
{
    (const EDM_Property*)&_LogEntry_LogEntry_RecordId,
    (const EDM_Property*)&_LogEntry_LogEntry_Severity,
    (const EDM_Property*)&_LogEntry_LogEntry_Created,
    (const EDM_Property*)&_LogEntry_LogEntry_EntryType,
    (const EDM_Property*)&_LogEntry_LogEntry_OemRecordFormat,
    (const EDM_Property*)&_LogEntry_LogEntry_EntryCode,
    (const EDM_Property*)&_LogEntry_LogEntry_SensorType,
    (const EDM_Property*)&_LogEntry_LogEntry_Number,
    (const EDM_Property*)&_LogEntry_LogEntry_Message,
    (const EDM_Property*)&_LogEntry_LogEntry_MessageId,
    (const EDM_Property*)&_LogEntry_LogEntry_MessageArgs,
    (const EDM_Property*)&_LogEntry_LogEntry_Links
};

static const EDM_EntityType _LogEntry_LogEntry =
{
    "LogEntry", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _LogEntry_LogEntry_PropertiesArray,
    OL_ARRAYSIZE(_LogEntry_LogEntry_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_NavigationProperty _LogEntry_Links_OriginOfCondition =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "OriginOfCondition", /* Name */
    "Resource.Resource", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _LogEntry_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _LogEntry_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_LogEntry_Links_Oem
};

static const EDM_NavigationProperty* _LogEntry_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_LogEntry_Links_OriginOfCondition
};

static const EDM_ComplexType _LogEntry_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _LogEntry_Links_PropertiesArray,
    OL_ARRAYSIZE(_LogEntry_Links_PropertiesArray),
    _LogEntry_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_LogEntry_Links_NavigationPropertiesArray)
};

static const char* _LogEntry_EventSeverity_MembersArray[] =
{
    "OK",
    "Warning",
    "Critical"
};

static const EDM_EnumType _LogEntry_EventSeverity =
{
    "EventSeverity", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_LogEntry_EventSeverity_MembersArray,
    OL_ARRAYSIZE(_LogEntry_EventSeverity_MembersArray)
};

static const char* _LogEntry_LogEntryType_MembersArray[] =
{
    "Event",
    "SEL",
    "Oem"
};

static const EDM_EnumType _LogEntry_LogEntryType =
{
    "LogEntryType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_LogEntry_LogEntryType_MembersArray,
    OL_ARRAYSIZE(_LogEntry_LogEntryType_MembersArray)
};

static const char* _LogEntry_LogEntryCode_MembersArray[] =
{
    "Assert",
    "Deassert",
    "Lower Non-critical - going low",
    "Lower Non-critical - going high",
    "Lower Critical - going low",
    "Lower Critical - going high",
    "Lower Non-recoverable - going low",
    "Lower Non-recoverable - going high",
    "Upper Non-critical - going low",
    "Upper Non-critical - going high",
    "Upper Critical - going low",
    "Upper Critical - going high",
    "Upper Non-recoverable - going low",
    "Upper Non-recoverable - going high",
    "Transition to Idle",
    "Transition to Active",
    "Transition to Busy",
    "State Deasserted",
    "State Asserted",
    "Predictive Failure deasserted",
    "Predictive Failure asserted",
    "Limit Not Exceeded",
    "Limit Exceeded",
    "Performance Met",
    "Performance Lags",
    "Transition to OK",
    "Transition to Non-Critical from OK",
    "Transition to Critical from less severe",
    "Transition to Non-recoverable from less severe",
    "Transition to Non-Critical from more severe",
    "Transition to Critical from Non-recoverable",
    "Transition to Non-recoverable",
    "Monitor",
    "Informational",
    "Device Removed / Device Absent",
    "Device Inserted / Device Present",
    "Device Disabled",
    "Device Enabled",
    "Transition to Running",
    "Transition to In Test",
    "Transition to Power Off",
    "Transition to On Line",
    "Transition to Off Line",
    "Transition to Off Duty",
    "Transition to Degraded",
    "Transition to Power Save",
    "Install Error",
    "Fully Redundant",
    "Redundancy Lost",
    "Redundancy Degraded",
    "Non-redundant:Sufficient Resources from Redundant",
    "Non-redundant:Sufficient Resources from Insufficient Resources",
    "Non-redundant:Insufficient Resources",
    "Redundancy Degraded from Fully Redundant",
    "Redundancy Degraded from Non-redundant",
    "D0 Power State",
    "D1 Power State",
    "D2 Power State",
    "D3 Power State"
};

static const EDM_EnumType _LogEntry_LogEntryCode =
{
    "LogEntryCode", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_LogEntry_LogEntryCode_MembersArray,
    OL_ARRAYSIZE(_LogEntry_LogEntryCode_MembersArray)
};

static const char* _LogEntry_SensorType_MembersArray[] =
{
    "Platform Security Violation Attempt",
    "Temperature",
    "Voltage",
    "Current",
    "Fan",
    "Physical Chassis Security",
    "Processor",
    "Power Supply / Converter",
    "PowerUnit",
    "CoolingDevice",
    "Other Units-based Sensor",
    "Memory",
    "Drive Slot/Bay",
    "POST Memory Resize",
    "System Firmware Progress",
    "Event Logging Disabled",
    "System Event",
    "Critical Interrupt",
    "Button/Switch",
    "Module/Board",
    "Microcontroller/Coprocessor",
    "Add-in Card",
    "Chassis",
    "ChipSet",
    "Other FRU",
    "Cable/Interconnect",
    "Terminator",
    "SystemBoot/Restart",
    "Boot Error",
    "BaseOSBoot/InstallationStatus",
    "OS Stop/Shutdown",
    "Slot/Connector",
    "System ACPI PowerState",
    "Watchdog",
    "Platform Alert",
    "Entity Presence",
    "Monitor ASIC/IC",
    "LAN",
    "Management Subsystem Health",
    "Battery",
    "Session Audit",
    "Version Change",
    "FRUState"
};

static const EDM_EnumType _LogEntry_SensorType =
{
    "SensorType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_LogEntry_SensorType_MembersArray,
    OL_ARRAYSIZE(_LogEntry_SensorType_MembersArray)
};

static const EDM_EntityType* _LogEntry_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_LogEntry_LogEntry
};

static const EDM_ComplexType* _LogEntry_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_LogEntry_Links
};

static const EDM_EnumType* _LogEntry_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_LogEntry_EventSeverity,
    (const EDM_EnumType*)&_LogEntry_LogEntryType,
    (const EDM_EnumType*)&_LogEntry_LogEntryCode,
    (const EDM_EnumType*)&_LogEntry_SensorType
};

static const EDM_Schema _LogEntry_Schema =
{
    "LogEntry.0.9.2", /* Namespace */
    "LogEntry", /* Alias */
    _LogEntry_EntityTypesArray,
    OL_ARRAYSIZE(_LogEntry_EntityTypesArray),
    _LogEntry_ComplexTypesArray,
    OL_ARRAYSIZE(_LogEntry_ComplexTypesArray),
    _LogEntry_EnumTypesArray,
    OL_ARRAYSIZE(_LogEntry_EnumTypesArray),
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
    &_LogEntry_Schema
};

static const EDMX_DataServices _DataServices =
{
    _SchemasArray, /* Schemas */
    OL_ARRAYSIZE(_SchemasArray) /* NumSchemas */
};

static const EDMX_Reference* _ReferencesArray[] =
{
    &_0_Reference,
    &_1_Reference
};

const EDMX_Edmx LogEntry_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

