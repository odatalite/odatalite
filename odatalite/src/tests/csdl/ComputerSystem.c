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
    "Chassis.0.9.2", /* Include.Namespace */
    "Chassis" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/Chassis", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _4_0_Include =
{
    "LogService.0.9.2", /* Include.Namespace */
    "LogService" /* Include.Alias */
};

static const EDMX_Include* _4_IncludesArray[] =
{
    &_4_0_Include
};

static const EDMX_Reference _4_Reference =
{
    "http://dmtf.org/schema/v1/LogService", /* Uri */
    _4_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_4_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _5_0_Include =
{
    "EthernetNetworkInterface.0.9.2", /* Include.Namespace */
    "EthernetNetworkInterface" /* Include.Alias */
};

static const EDMX_Include* _5_IncludesArray[] =
{
    &_5_0_Include
};

static const EDMX_Reference _5_Reference =
{
    "http://dmtf.org/schema/v1/EthernetNetworkInterface", /* Uri */
    _5_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_5_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _6_0_Include =
{
    "SimpleStorage.0.9.2", /* Include.Namespace */
    "SimpleStorage" /* Include.Alias */
};

static const EDMX_Include* _6_IncludesArray[] =
{
    &_6_0_Include
};

static const EDMX_Reference _6_Reference =
{
    "http://dmtf.org/schema/v1/SimpleStorage", /* Uri */
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
    "Firmware.0.9.2", /* Include.Namespace */
    "Firmware" /* Include.Alias */
};

static const EDMX_Include* _8_IncludesArray[] =
{
    &_8_0_Include
};

static const EDMX_Reference _8_Reference =
{
    "http://dmtf.org/schema/v1/Firmware", /* Uri */
    _8_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_8_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _ComputerSystem_ComputerSystem_SystemType =
{
    0, /* Nullable */
    0, /* Extended */
    "SystemType", /* Name */
    "ComputerSystem.SystemType" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "ComputerSystem.Links" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_AssetTag =
{
    1, /* Nullable */
    0, /* Extended */
    "AssetTag", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Manufacturer =
{
    1, /* Nullable */
    0, /* Extended */
    "Manufacturer", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Model =
{
    1, /* Nullable */
    0, /* Extended */
    "Model", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_SKU =
{
    1, /* Nullable */
    0, /* Extended */
    "SKU", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_SerialNumber =
{
    1, /* Nullable */
    0, /* Extended */
    "SerialNumber", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Version =
{
    1, /* Nullable */
    0, /* Extended */
    "Version", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_PartNumber =
{
    1, /* Nullable */
    0, /* Extended */
    "PartNumber", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_VirtualSerialNumber =
{
    1, /* Nullable */
    0, /* Extended */
    "VirtualSerialNumber", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_UUID =
{
    1, /* Nullable */
    0, /* Extended */
    "UUID", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_HostCorrelation =
{
    0, /* Nullable */
    0, /* Extended */
    "HostCorrelation", /* Name */
    "ComputerSystem.HostCorrelation" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_BIOSPOSTCode =
{
    1, /* Nullable */
    0, /* Extended */
    "BIOSPOSTCode", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_IndicatorLED =
{
    1, /* Nullable */
    0, /* Extended */
    "IndicatorLED", /* Name */
    "ComputerSystem.IndicatorLED" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Power =
{
    1, /* Nullable */
    0, /* Extended */
    "Power", /* Name */
    "ComputerSystem.PowerState" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Boot =
{
    0, /* Nullable */
    0, /* Extended */
    "Boot", /* Name */
    "ComputerSystem.Boot" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Bios =
{
    0, /* Nullable */
    0, /* Extended */
    "Bios", /* Name */
    "ComputerSystem.Bios" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Processors =
{
    0, /* Nullable */
    0, /* Extended */
    "Processors", /* Name */
    "ComputerSystem.Processors" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Memory =
{
    0, /* Nullable */
    0, /* Extended */
    "Memory", /* Name */
    "ComputerSystem.Memory" /* Type */
};

static const EDM_Property _ComputerSystem_ComputerSystem_Actions =
{
    0, /* Nullable */
    0, /* Extended */
    "Actions", /* Name */
    "ComputerSystem.Actions" /* Type */
};

static const EDM_Property* _ComputerSystem_ComputerSystem_PropertiesArray[] =
{
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_SystemType,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Links,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_AssetTag,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Manufacturer,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Model,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_SKU,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_SerialNumber,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Version,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_PartNumber,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_VirtualSerialNumber,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_UUID,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_HostCorrelation,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_BIOSPOSTCode,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_IndicatorLED,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Power,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Boot,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Bios,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Processors,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Memory,
    (const EDM_Property*)&_ComputerSystem_ComputerSystem_Actions
};

static const EDM_EntityType _ComputerSystem_ComputerSystem =
{
    "ComputerSystem", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _ComputerSystem_ComputerSystem_PropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_ComputerSystem_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_NavigationProperty _ComputerSystem_Links_Chassis =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Chassis", /* Name */
    "Collection(Chassis.Chassis)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ComputerSystem_Links_ManagedBy =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "ManagedBy", /* Name */
    "Collection(ManagerAccount.ManagerAccount)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ComputerSystem_Links_SimpleNetwork =
{
    EDM_NavigationProperty_Flags_Nullable |
    EDM_NavigationProperty_Flags_ContainsTarget, /* Flags */
    "SimpleNetwork", /* Name */
    "Collection(EthernetNetworkInterface.EthernetNetworkInterface)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ComputerSystem_Links_SimpleStorage =
{
    EDM_NavigationProperty_Flags_Nullable |
    EDM_NavigationProperty_Flags_ContainsTarget, /* Flags */
    "SimpleStorage", /* Name */
    "Collection(SimpleStorage.SimpleStorage)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ComputerSystem_Links_LogService =
{
    EDM_NavigationProperty_Flags_Nullable |
    EDM_NavigationProperty_Flags_ContainsTarget, /* Flags */
    "LogService", /* Name */
    "Collection(LogService.LogService)", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _ComputerSystem_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _ComputerSystem_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_ComputerSystem_Links_Oem
};

static const EDM_NavigationProperty* _ComputerSystem_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_ComputerSystem_Links_Chassis,
    (const EDM_NavigationProperty*)&_ComputerSystem_Links_ManagedBy,
    (const EDM_NavigationProperty*)&_ComputerSystem_Links_SimpleNetwork,
    (const EDM_NavigationProperty*)&_ComputerSystem_Links_SimpleStorage,
    (const EDM_NavigationProperty*)&_ComputerSystem_Links_LogService
};

static const EDM_ComplexType _ComputerSystem_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ComputerSystem_Links_PropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_Links_PropertiesArray),
    _ComputerSystem_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_Links_NavigationPropertiesArray)
};

static const EDM_Property _ComputerSystem_Actions_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "ComputerSystem.OemActions" /* Type */
};

static const EDM_Property* _ComputerSystem_Actions_PropertiesArray[] =
{
    (const EDM_Property*)&_ComputerSystem_Actions_Oem
};

static const EDM_ComplexType _ComputerSystem_Actions =
{
    "Actions", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ComputerSystem_Actions_PropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_Actions_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType _ComputerSystem_OemActions =
{
    "OemActions", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* Properties */
    0, /* NumProperties */
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Parameter _ComputerSystem_Reset_ComputerSystem =
{
    "ComputerSystem", /* Name */
    "ComputerSystem.Actions", /* Type */
    NULL /* Nullable */
};

static const EDM_Parameter _ComputerSystem_Reset_ResetType =
{
    "ResetType", /* Name */
    "ComputerSystem.ResetType", /* Type */
    NULL /* Nullable */
};

static const EDM_Parameter* _ComputerSystem_Reset_ParametersArray[] =
{
    (const EDM_Parameter*)&_ComputerSystem_Reset_ComputerSystem,
    (const EDM_Parameter*)&_ComputerSystem_Reset_ResetType
};

static const EDM_Action _ComputerSystem_Reset =
{
    "Reset", /* Name */
    NULL, /* IsBound */
    NULL, /* EntitySetPath */
    _ComputerSystem_Reset_ParametersArray,
    OL_ARRAYSIZE(_ComputerSystem_Reset_ParametersArray),
};

static const char* _ComputerSystem_ResetType_MembersArray[] =
{
    "On",
    "ForceOff",
    "GracefulRestart",
    "ForceRestart",
    "Nmi",
    "ForceOn",
    "PushPowerButton"
};

static const EDM_EnumType _ComputerSystem_ResetType =
{
    "ResetType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ComputerSystem_ResetType_MembersArray,
    OL_ARRAYSIZE(_ComputerSystem_ResetType_MembersArray)
};

static const char* _ComputerSystem_SystemType_MembersArray[] =
{
    "Physical",
    "Virtual",
    "OS",
    "PhysicallyPartitioned",
    "VirtuallyPartitioned"
};

static const EDM_EnumType _ComputerSystem_SystemType =
{
    "SystemType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ComputerSystem_SystemType_MembersArray,
    OL_ARRAYSIZE(_ComputerSystem_SystemType_MembersArray)
};

static const char* _ComputerSystem_IndicatorLED_MembersArray[] =
{
    "Unknown",
    "Lit",
    "Blinking",
    "Off"
};

static const EDM_EnumType _ComputerSystem_IndicatorLED =
{
    "IndicatorLED", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ComputerSystem_IndicatorLED_MembersArray,
    OL_ARRAYSIZE(_ComputerSystem_IndicatorLED_MembersArray)
};

static const char* _ComputerSystem_PowerState_MembersArray[] =
{
    "On",
    "Off",
    "Unknown",
    "Reset"
};

static const EDM_EnumType _ComputerSystem_PowerState =
{
    "PowerState", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ComputerSystem_PowerState_MembersArray,
    OL_ARRAYSIZE(_ComputerSystem_PowerState_MembersArray)
};

static const EDM_Property _ComputerSystem_Boot_BootSourceOverrideTarget =
{
    1, /* Nullable */
    0, /* Extended */
    "BootSourceOverrideTarget", /* Name */
    "ComputerSystem.BootSource" /* Type */
};

static const EDM_Property _ComputerSystem_Boot_BootSourceOverrideSupported =
{
    1, /* Nullable */
    0, /* Extended */
    "BootSourceOverrideSupported", /* Name */
    "Collection(ComputerSystem.BootSourceSupported)" /* Type */
};

static const EDM_Property _ComputerSystem_Boot_BootSourceOverrideEnabled =
{
    1, /* Nullable */
    0, /* Extended */
    "BootSourceOverrideEnabled", /* Name */
    "ComputerSystem.BootSourceOverrideEnabled" /* Type */
};

static const EDM_Property _ComputerSystem_Boot_UefiTargetBootSourceOverrideSupported =
{
    0, /* Nullable */
    0, /* Extended */
    "UefiTargetBootSourceOverrideSupported", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_Property _ComputerSystem_Boot_UefiTargetBootSourceOverride =
{
    1, /* Nullable */
    0, /* Extended */
    "UefiTargetBootSourceOverride", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _ComputerSystem_Boot_PropertiesArray[] =
{
    (const EDM_Property*)&_ComputerSystem_Boot_BootSourceOverrideTarget,
    (const EDM_Property*)&_ComputerSystem_Boot_BootSourceOverrideSupported,
    (const EDM_Property*)&_ComputerSystem_Boot_BootSourceOverrideEnabled,
    (const EDM_Property*)&_ComputerSystem_Boot_UefiTargetBootSourceOverrideSupported,
    (const EDM_Property*)&_ComputerSystem_Boot_UefiTargetBootSourceOverride
};

static const EDM_ComplexType _ComputerSystem_Boot =
{
    "Boot", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ComputerSystem_Boot_PropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_Boot_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _ComputerSystem_BootSource_MembersArray[] =
{
    "None",
    "Pxe",
    "Floppy",
    "Cd",
    "Usb",
    "Hdd",
    "BiosSetup",
    "Utilities",
    "Diags",
    "UefiShell",
    "UefiTarget"
};

static const EDM_EnumType _ComputerSystem_BootSource =
{
    "BootSource", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ComputerSystem_BootSource_MembersArray,
    OL_ARRAYSIZE(_ComputerSystem_BootSource_MembersArray)
};

static const char* _ComputerSystem_BootSourceSupported_MembersArray[] =
{
    "None",
    "Pxe",
    "Floppy",
    "Cd",
    "Usb",
    "Hdd",
    "BiosSetup",
    "Utilities",
    "Diags",
    "UefiShell",
    "UefiTarget"
};

static const EDM_EnumType _ComputerSystem_BootSourceSupported =
{
    "BootSourceSupported", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ComputerSystem_BootSourceSupported_MembersArray,
    OL_ARRAYSIZE(_ComputerSystem_BootSourceSupported_MembersArray)
};

static const char* _ComputerSystem_BootSourceOverrideEnabled_MembersArray[] =
{
    "Disabled",
    "Once",
    "Continuous"
};

static const EDM_EnumType _ComputerSystem_BootSourceOverrideEnabled =
{
    "BootSourceOverrideEnabled", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ComputerSystem_BootSourceOverrideEnabled_MembersArray,
    OL_ARRAYSIZE(_ComputerSystem_BootSourceOverrideEnabled_MembersArray)
};

static const EDM_Property _ComputerSystem_Bios_Current =
{
    0, /* Nullable */
    0, /* Extended */
    "Current", /* Name */
    "Firmware.FWVersion" /* Type */
};

static const EDM_Property* _ComputerSystem_Bios_PropertiesArray[] =
{
    (const EDM_Property*)&_ComputerSystem_Bios_Current
};

static const EDM_ComplexType _ComputerSystem_Bios =
{
    "Bios", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ComputerSystem_Bios_PropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_Bios_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _ComputerSystem_Processors_Count =
{
    1, /* Nullable */
    0, /* Extended */
    "Count", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ComputerSystem_Processors_ProcessorFamily =
{
    1, /* Nullable */
    0, /* Extended */
    "ProcessorFamily", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_Processors_Status =
{
    0, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property* _ComputerSystem_Processors_PropertiesArray[] =
{
    (const EDM_Property*)&_ComputerSystem_Processors_Count,
    (const EDM_Property*)&_ComputerSystem_Processors_ProcessorFamily,
    (const EDM_Property*)&_ComputerSystem_Processors_Status
};

static const EDM_ComplexType _ComputerSystem_Processors =
{
    "Processors", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ComputerSystem_Processors_PropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_Processors_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _ComputerSystem_Memory_TotalSystemMemoryGB =
{
    1, /* Nullable */
    0, /* Extended */
    "TotalSystemMemoryGB", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ComputerSystem_Memory_Status =
{
    0, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property* _ComputerSystem_Memory_PropertiesArray[] =
{
    (const EDM_Property*)&_ComputerSystem_Memory_TotalSystemMemoryGB,
    (const EDM_Property*)&_ComputerSystem_Memory_Status
};

static const EDM_ComplexType _ComputerSystem_Memory =
{
    "Memory", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ComputerSystem_Memory_PropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_Memory_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _ComputerSystem_HostCorrelation_IPAddress =
{
    1, /* Nullable */
    0, /* Extended */
    "IPAddress", /* Name */
    "Collection(ComputerSystem.IPAddress)" /* Type */
};

static const EDM_Property _ComputerSystem_HostCorrelation_HostMACAddress =
{
    1, /* Nullable */
    0, /* Extended */
    "HostMACAddress", /* Name */
    "Collection(ComputerSystem.MacAddress)" /* Type */
};

static const EDM_Property _ComputerSystem_HostCorrelation_HostName =
{
    1, /* Nullable */
    0, /* Extended */
    "HostName", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ComputerSystem_HostCorrelation_HostFQDN =
{
    1, /* Nullable */
    0, /* Extended */
    "HostFQDN", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _ComputerSystem_HostCorrelation_PropertiesArray[] =
{
    (const EDM_Property*)&_ComputerSystem_HostCorrelation_IPAddress,
    (const EDM_Property*)&_ComputerSystem_HostCorrelation_HostMACAddress,
    (const EDM_Property*)&_ComputerSystem_HostCorrelation_HostName,
    (const EDM_Property*)&_ComputerSystem_HostCorrelation_HostFQDN
};

static const EDM_ComplexType _ComputerSystem_HostCorrelation =
{
    "HostCorrelation", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ComputerSystem_HostCorrelation_PropertiesArray,
    OL_ARRAYSIZE(_ComputerSystem_HostCorrelation_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_TypeDefinition _ComputerSystem_IPAddress =
{
    "IPAddress", /* Name */
    "Edm.String" /* UnderlyingType */
};

static const EDM_TypeDefinition _ComputerSystem_MacAddress =
{
    "MacAddress", /* Name */
    "Edm.String" /* UnderlyingType */
};

static const EDM_EntityType* _ComputerSystem_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_ComputerSystem_ComputerSystem
};

static const EDM_ComplexType* _ComputerSystem_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_ComputerSystem_Links,
    (const EDM_ComplexType*)&_ComputerSystem_Actions,
    (const EDM_ComplexType*)&_ComputerSystem_OemActions,
    (const EDM_ComplexType*)&_ComputerSystem_Boot,
    (const EDM_ComplexType*)&_ComputerSystem_Bios,
    (const EDM_ComplexType*)&_ComputerSystem_Processors,
    (const EDM_ComplexType*)&_ComputerSystem_Memory,
    (const EDM_ComplexType*)&_ComputerSystem_HostCorrelation
};

static const EDM_EnumType* _ComputerSystem_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_ComputerSystem_ResetType,
    (const EDM_EnumType*)&_ComputerSystem_SystemType,
    (const EDM_EnumType*)&_ComputerSystem_IndicatorLED,
    (const EDM_EnumType*)&_ComputerSystem_PowerState,
    (const EDM_EnumType*)&_ComputerSystem_BootSource,
    (const EDM_EnumType*)&_ComputerSystem_BootSourceSupported,
    (const EDM_EnumType*)&_ComputerSystem_BootSourceOverrideEnabled
};

static const EDM_Action* _ComputerSystem_ActionsArray[] =
{
    (const EDM_Action*)&_ComputerSystem_Reset
};

static const EDM_TypeDefinition* _ComputerSystem_TypeDefinitionsArray[] =
{
    (const EDM_TypeDefinition*)&_ComputerSystem_IPAddress,
    (const EDM_TypeDefinition*)&_ComputerSystem_MacAddress
};

static const EDM_Schema _ComputerSystem_Schema =
{
    "ComputerSystem.0.9.2", /* Namespace */
    "ComputerSystem", /* Alias */
    _ComputerSystem_EntityTypesArray,
    OL_ARRAYSIZE(_ComputerSystem_EntityTypesArray),
    _ComputerSystem_ComplexTypesArray,
    OL_ARRAYSIZE(_ComputerSystem_ComplexTypesArray),
    _ComputerSystem_EnumTypesArray,
    OL_ARRAYSIZE(_ComputerSystem_EnumTypesArray),
    _ComputerSystem_ActionsArray,
    OL_ARRAYSIZE(_ComputerSystem_ActionsArray),
    _ComputerSystem_TypeDefinitionsArray,
    OL_ARRAYSIZE(_ComputerSystem_TypeDefinitionsArray),
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_ComputerSystem_Schema
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

const EDMX_Edmx ComputerSystem_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

