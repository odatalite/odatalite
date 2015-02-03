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
    "ComputerSystem.0.9.2", /* Include.Namespace */
    "ComputerSystem" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/ComputerSystem", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _4_0_Include =
{
    "Chassis.0.9.2", /* Include.Namespace */
    "Chassis" /* Include.Alias */
};

static const EDMX_Include* _4_IncludesArray[] =
{
    &_4_0_Include
};

static const EDMX_Reference _4_Reference =
{
    "http://dmtf.org/schema/v1/Chassis", /* Uri */
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
    "NetworkService.0.9.2", /* Include.Namespace */
    "NetworkService" /* Include.Alias */
};

static const EDMX_Include* _6_IncludesArray[] =
{
    &_6_0_Include
};

static const EDMX_Reference _6_Reference =
{
    "http://dmtf.org/schema/v1/ManagerNetworkService", /* Uri */
    _6_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_6_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _7_0_Include =
{
    "LogService.0.9.2", /* Include.Namespace */
    "LogService" /* Include.Alias */
};

static const EDMX_Include* _7_IncludesArray[] =
{
    &_7_0_Include
};

static const EDMX_Reference _7_Reference =
{
    "http://dmtf.org/schema/v1/LogService", /* Uri */
    _7_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_7_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _8_0_Include =
{
    "VirtualMedia.0.9.2", /* Include.Namespace */
    "VirtualMedia" /* Include.Alias */
};

static const EDMX_Include* _8_IncludesArray[] =
{
    &_8_0_Include
};

static const EDMX_Reference _8_Reference =
{
    "http://dmtf.org/schema/v1/VirtualMedia", /* Uri */
    _8_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_8_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _9_0_Include =
{
    "SerialInterface.0.9.2", /* Include.Namespace */
    "SerialInterface" /* Include.Alias */
};

static const EDMX_Include* _9_IncludesArray[] =
{
    &_9_0_Include
};

static const EDMX_Reference _9_Reference =
{
    "http://dmtf.org/schema/v1/SerialInterface", /* Uri */
    _9_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_9_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _10_0_Include =
{
    "Firmware.0.9.2", /* Include.Namespace */
    "Firmware" /* Include.Alias */
};

static const EDMX_Include* _10_IncludesArray[] =
{
    &_10_0_Include
};

static const EDMX_Reference _10_Reference =
{
    "http://dmtf.org/schema/v1/Firmware", /* Uri */
    _10_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_10_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _Manager_Manager_ManagerType =
{
    0, /* Nullable */
    0, /* Extended */
    "ManagerType", /* Name */
    "Manager.ManagerType" /* Type */
};

static const EDM_Property _Manager_Manager_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "Manager.Links" /* Type */
};

static const EDM_Property _Manager_Manager_UUID =
{
    1, /* Nullable */
    0, /* Extended */
    "UUID", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Manager_Manager_Model =
{
    1, /* Nullable */
    0, /* Extended */
    "Model", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Manager_Manager_Firmware =
{
    0, /* Nullable */
    0, /* Extended */
    "Firmware", /* Name */
    "Firmware.FirmwareRevision" /* Type */
};

static const EDM_Property _Manager_Manager_SerialConsole =
{
    0, /* Nullable */
    0, /* Extended */
    "SerialConsole", /* Name */
    "Manager.SerialConsole" /* Type */
};

static const EDM_Property _Manager_Manager_CommandShell =
{
    1, /* Nullable */
    0, /* Extended */
    "CommandShell", /* Name */
    "Manager.CommandShell" /* Type */
};

static const EDM_Property _Manager_Manager_GraphicalConsole =
{
    1, /* Nullable */
    0, /* Extended */
    "GraphicalConsole", /* Name */
    "Manager.GraphicalConsole" /* Type */
};

static const EDM_Property _Manager_Manager_Redundancy =
{
    0, /* Nullable */
    0, /* Extended */
    "Redundancy", /* Name */
    "Redundancy.Redundancy" /* Type */
};

static const EDM_Property _Manager_Manager_Actions =
{
    0, /* Nullable */
    0, /* Extended */
    "Actions", /* Name */
    "Manager.Actions" /* Type */
};

static const EDM_Property* _Manager_Manager_PropertiesArray[] =
{
    (const EDM_Property*)&_Manager_Manager_ManagerType,
    (const EDM_Property*)&_Manager_Manager_Links,
    (const EDM_Property*)&_Manager_Manager_UUID,
    (const EDM_Property*)&_Manager_Manager_Model,
    (const EDM_Property*)&_Manager_Manager_Firmware,
    (const EDM_Property*)&_Manager_Manager_SerialConsole,
    (const EDM_Property*)&_Manager_Manager_CommandShell,
    (const EDM_Property*)&_Manager_Manager_GraphicalConsole,
    (const EDM_Property*)&_Manager_Manager_Redundancy,
    (const EDM_Property*)&_Manager_Manager_Actions
};

static const EDM_EntityType _Manager_Manager =
{
    "Manager", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _Manager_Manager_PropertiesArray,
    OL_ARRAYSIZE(_Manager_Manager_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _Manager_Actions_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Manager.OemActions" /* Type */
};

static const EDM_Property* _Manager_Actions_PropertiesArray[] =
{
    (const EDM_Property*)&_Manager_Actions_Oem
};

static const EDM_ComplexType _Manager_Actions =
{
    "Actions", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Manager_Actions_PropertiesArray,
    OL_ARRAYSIZE(_Manager_Actions_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType _Manager_OemActions =
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

static const EDM_NavigationProperty _Manager_Links_ManagerForServers =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "ManagerForServers", /* Name */
    "Collection(ComputerSystem.ComputerSystem)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Manager_Links_ManagerForChassis =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "ManagerForChassis", /* Name */
    "Collection(Chassis.Chassis)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Manager_Links_EthernetNICs =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "EthernetNICs", /* Name */
    "Collection(EthernetNetworkInterface.EthernetNetworkInterface)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Manager_Links_SerialInterfaces =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "SerialInterfaces", /* Name */
    "Collection(SerialInterface.SerialInterface)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Manager_Links_NetworkService =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "NetworkService", /* Name */
    "NetworkService.ManagerNetworkService", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Manager_Links_Logs =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Logs", /* Name */
    "Collection(LogService.LogService)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _Manager_Links_VirtualMedia =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "VirtualMedia", /* Name */
    "Collection(VirtualMedia.VirtualMedia)", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _Manager_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _Manager_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_Manager_Links_Oem
};

static const EDM_NavigationProperty* _Manager_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_Manager_Links_ManagerForServers,
    (const EDM_NavigationProperty*)&_Manager_Links_ManagerForChassis,
    (const EDM_NavigationProperty*)&_Manager_Links_EthernetNICs,
    (const EDM_NavigationProperty*)&_Manager_Links_SerialInterfaces,
    (const EDM_NavigationProperty*)&_Manager_Links_NetworkService,
    (const EDM_NavigationProperty*)&_Manager_Links_Logs,
    (const EDM_NavigationProperty*)&_Manager_Links_VirtualMedia
};

static const EDM_ComplexType _Manager_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Manager_Links_PropertiesArray,
    OL_ARRAYSIZE(_Manager_Links_PropertiesArray),
    _Manager_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_Manager_Links_NavigationPropertiesArray)
};

static const EDM_Parameter _Manager_Reset_Manager =
{
    "Manager", /* Name */
    "Manager.Actions", /* Type */
    NULL /* Nullable */
};

static const EDM_Parameter* _Manager_Reset_ParametersArray[] =
{
    (const EDM_Parameter*)&_Manager_Reset_Manager
};

static const EDM_Action _Manager_Reset =
{
    "Reset", /* Name */
    NULL, /* IsBound */
    NULL, /* EntitySetPath */
    _Manager_Reset_ParametersArray,
    OL_ARRAYSIZE(_Manager_Reset_ParametersArray),
};

static const EDM_Parameter _Manager_ForceFailover_Manager =
{
    "Manager", /* Name */
    "Manager.Actions", /* Type */
    NULL /* Nullable */
};

static const EDM_Parameter _Manager_ForceFailover_href =
{
    "href", /* Name */
    "Collection(Resource.Resource)", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter* _Manager_ForceFailover_ParametersArray[] =
{
    (const EDM_Parameter*)&_Manager_ForceFailover_Manager,
    (const EDM_Parameter*)&_Manager_ForceFailover_href
};

static const EDM_Action _Manager_ForceFailover =
{
    "ForceFailover", /* Name */
    NULL, /* IsBound */
    NULL, /* EntitySetPath */
    _Manager_ForceFailover_ParametersArray,
    OL_ARRAYSIZE(_Manager_ForceFailover_ParametersArray),
};

static const EDM_Parameter _Manager_ModifyRedundancySet_Manager =
{
    "Manager", /* Name */
    "Manager.Actions", /* Type */
    NULL /* Nullable */
};

static const EDM_Parameter _Manager_ModifyRedundancySet_Add =
{
    "Add", /* Name */
    "Collection(Resource.Resource)", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter _Manager_ModifyRedundancySet_Remove =
{
    "Remove", /* Name */
    "Collection(Resource.Resource)", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter* _Manager_ModifyRedundancySet_ParametersArray[] =
{
    (const EDM_Parameter*)&_Manager_ModifyRedundancySet_Manager,
    (const EDM_Parameter*)&_Manager_ModifyRedundancySet_Add,
    (const EDM_Parameter*)&_Manager_ModifyRedundancySet_Remove
};

static const EDM_Action _Manager_ModifyRedundancySet =
{
    "ModifyRedundancySet", /* Name */
    NULL, /* IsBound */
    NULL, /* EntitySetPath */
    _Manager_ModifyRedundancySet_ParametersArray,
    OL_ARRAYSIZE(_Manager_ModifyRedundancySet_ParametersArray),
};

static const char* _Manager_ManagerType_MembersArray[] =
{
    "ManagementController",
    "EnclosureManager",
    "BMC"
};

static const EDM_EnumType _Manager_ManagerType =
{
    "ManagerType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Manager_ManagerType_MembersArray,
    OL_ARRAYSIZE(_Manager_ManagerType_MembersArray)
};

static const EDM_Property _Manager_ManagerService_Enabled =
{
    0, /* Nullable */
    0, /* Extended */
    "Enabled", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property _Manager_ManagerService_MaxConcurrentSessions =
{
    0, /* Nullable */
    0, /* Extended */
    "MaxConcurrentSessions", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property* _Manager_ManagerService_PropertiesArray[] =
{
    (const EDM_Property*)&_Manager_ManagerService_Enabled,
    (const EDM_Property*)&_Manager_ManagerService_MaxConcurrentSessions
};

static const EDM_ComplexType _Manager_ManagerService =
{
    "ManagerService", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Manager_ManagerService_PropertiesArray,
    OL_ARRAYSIZE(_Manager_ManagerService_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _Manager_SerialConnectTypesSupported_MembersArray[] =
{
    "SSH",
    "Telnet",
    "IPMI",
    "Oem"
};

static const EDM_EnumType _Manager_SerialConnectTypesSupported =
{
    "SerialConnectTypesSupported", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Manager_SerialConnectTypesSupported_MembersArray,
    OL_ARRAYSIZE(_Manager_SerialConnectTypesSupported_MembersArray)
};

static const char* _Manager_CommandConnectTypesSupported_MembersArray[] =
{
    "SSH",
    "Telnet",
    "IPMI",
    "Oem"
};

static const EDM_EnumType _Manager_CommandConnectTypesSupported =
{
    "CommandConnectTypesSupported", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Manager_CommandConnectTypesSupported_MembersArray,
    OL_ARRAYSIZE(_Manager_CommandConnectTypesSupported_MembersArray)
};

static const char* _Manager_GraphicalConnectTypesSupported_MembersArray[] =
{
    "KVMIP",
    "Oem"
};

static const EDM_EnumType _Manager_GraphicalConnectTypesSupported =
{
    "GraphicalConnectTypesSupported", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Manager_GraphicalConnectTypesSupported_MembersArray,
    OL_ARRAYSIZE(_Manager_GraphicalConnectTypesSupported_MembersArray)
};

static const EDM_Property _Manager_SerialConsole_ConnectTypesSupported =
{
    0, /* Nullable */
    0, /* Extended */
    "ConnectTypesSupported", /* Name */
    "Collection(Manager.SerialConnectTypesSupported)" /* Type */
};

static const EDM_Property* _Manager_SerialConsole_PropertiesArray[] =
{
    (const EDM_Property*)&_Manager_SerialConsole_ConnectTypesSupported
};

static const EDM_ComplexType _Manager_SerialConsole =
{
    "SerialConsole", /* Name */
    "Manager.ManagerService", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Manager_SerialConsole_PropertiesArray,
    OL_ARRAYSIZE(_Manager_SerialConsole_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _Manager_CommandShell_ConnectTypesSupported =
{
    0, /* Nullable */
    0, /* Extended */
    "ConnectTypesSupported", /* Name */
    "Collection(Manager.CommandConnectTypesSupported)" /* Type */
};

static const EDM_Property* _Manager_CommandShell_PropertiesArray[] =
{
    (const EDM_Property*)&_Manager_CommandShell_ConnectTypesSupported
};

static const EDM_ComplexType _Manager_CommandShell =
{
    "CommandShell", /* Name */
    "Manager.ManagerService", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Manager_CommandShell_PropertiesArray,
    OL_ARRAYSIZE(_Manager_CommandShell_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _Manager_GraphicalConsole_ConnectTypesSupported =
{
    0, /* Nullable */
    0, /* Extended */
    "ConnectTypesSupported", /* Name */
    "Collection(Manager.GraphicalConnectTypesSupported)" /* Type */
};

static const EDM_Property* _Manager_GraphicalConsole_PropertiesArray[] =
{
    (const EDM_Property*)&_Manager_GraphicalConsole_ConnectTypesSupported
};

static const EDM_ComplexType _Manager_GraphicalConsole =
{
    "GraphicalConsole", /* Name */
    "Manager.ManagerService", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Manager_GraphicalConsole_PropertiesArray,
    OL_ARRAYSIZE(_Manager_GraphicalConsole_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_EntityType* _Manager_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_Manager_Manager
};

static const EDM_ComplexType* _Manager_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_Manager_Actions,
    (const EDM_ComplexType*)&_Manager_OemActions,
    (const EDM_ComplexType*)&_Manager_Links,
    (const EDM_ComplexType*)&_Manager_ManagerService,
    (const EDM_ComplexType*)&_Manager_SerialConsole,
    (const EDM_ComplexType*)&_Manager_CommandShell,
    (const EDM_ComplexType*)&_Manager_GraphicalConsole
};

static const EDM_EnumType* _Manager_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_Manager_ManagerType,
    (const EDM_EnumType*)&_Manager_SerialConnectTypesSupported,
    (const EDM_EnumType*)&_Manager_CommandConnectTypesSupported,
    (const EDM_EnumType*)&_Manager_GraphicalConnectTypesSupported
};

static const EDM_Action* _Manager_ActionsArray[] =
{
    (const EDM_Action*)&_Manager_Reset,
    (const EDM_Action*)&_Manager_ForceFailover,
    (const EDM_Action*)&_Manager_ModifyRedundancySet
};

static const EDM_Schema _Manager_Schema =
{
    "Manager.0.9.2", /* Namespace */
    "Manager", /* Alias */
    _Manager_EntityTypesArray,
    OL_ARRAYSIZE(_Manager_EntityTypesArray),
    _Manager_ComplexTypesArray,
    OL_ARRAYSIZE(_Manager_ComplexTypesArray),
    _Manager_EnumTypesArray,
    OL_ARRAYSIZE(_Manager_EnumTypesArray),
    _Manager_ActionsArray,
    OL_ARRAYSIZE(_Manager_ActionsArray),
    NULL, /* TypeDefinitions */
    0, /* NumTypeDefinitions */
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_Manager_Schema
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
    &_8_Reference,
    &_9_Reference,
    &_10_Reference
};

const EDMX_Edmx Manager_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

