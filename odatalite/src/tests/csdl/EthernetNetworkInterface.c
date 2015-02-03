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
    "Org.OData.Measures.v1", /* Include.Namespace */
    "Measures" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://docs.oasis-open.org/odata/odata/v4.0/cs01/vocabularies/Org.OData.Measures.V1.xml", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _4_0_Include =
{
    "IPAddresses.0.9.2", /* Include.Namespace */
    "IPAddresses" /* Include.Alias */
};

static const EDMX_Include* _4_IncludesArray[] =
{
    &_4_0_Include
};

static const EDMX_Reference _4_Reference =
{
    "http://dmtf.org/schema/v1/IPAddresses", /* Uri */
    _4_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_4_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _5_0_Include =
{
    "NetworkService.0.9.2", /* Include.Namespace */
    "NetworkService" /* Include.Alias */
};

static const EDMX_Include* _5_IncludesArray[] =
{
    &_5_0_Include
};

static const EDMX_Reference _5_Reference =
{
    "http://dmtf.org/schema/v1/ManagerNetworkService", /* Uri */
    _5_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_5_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _6_0_Include =
{
    "VLanNetworkInterface.0.9.2", /* Include.Namespace */
    "VLanNetworkInterface" /* Include.Alias */
};

static const EDMX_Include* _6_IncludesArray[] =
{
    &_6_0_Include
};

static const EDMX_Reference _6_Reference =
{
    "http://dmtf.org/schema/v1/VLanNetworkInterface", /* Uri */
    _6_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_6_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_UEFIDevicePath =
{
    1, /* Nullable */
    0, /* Extended */
    "UEFIDevicePath", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_Status =
{
    1, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_FactoryMacAddress =
{
    1, /* Nullable */
    0, /* Extended */
    "FactoryMacAddress", /* Name */
    "EthernetNetworkInterface.MacAddress" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_MacAddress =
{
    1, /* Nullable */
    0, /* Extended */
    "MacAddress", /* Name */
    "EthernetNetworkInterface.MacAddress" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_LinkTechnology =
{
    1, /* Nullable */
    0, /* Extended */
    "LinkTechnology", /* Name */
    "EthernetNetworkInterface.LinkTechnology" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_SpeedMBps =
{
    1, /* Nullable */
    0, /* Extended */
    "SpeedMBps", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_Autosense =
{
    1, /* Nullable */
    0, /* Extended */
    "Autosense", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_FullDuplex =
{
    1, /* Nullable */
    0, /* Extended */
    "FullDuplex", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_FrameSize =
{
    1, /* Nullable */
    0, /* Extended */
    "FrameSize", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_VLANEnable =
{
    1, /* Nullable */
    0, /* Extended */
    "VLANEnable", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_VLANId =
{
    1, /* Nullable */
    0, /* Extended */
    "VLANId", /* Name */
    "EthernetNetworkInterface.VLanId" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_IPv6First =
{
    1, /* Nullable */
    0, /* Extended */
    "IPv6First", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_IPv6AddressPolicyTable =
{
    0, /* Nullable */
    0, /* Extended */
    "IPv6AddressPolicyTable", /* Name */
    "Collection(EthernetNetworkInterface.IPv6AddressPolicyEntry)" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_IPv4Addresses =
{
    0, /* Nullable */
    0, /* Extended */
    "IPv4Addresses", /* Name */
    "Collection(IPAddresses.IPV4Address)" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_IPv6Addresses =
{
    0, /* Nullable */
    0, /* Extended */
    "IPv6Addresses", /* Name */
    "Collection(IPAddresses.IPV6Address)" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_MaxIPv6StaticAddresses =
{
    1, /* Nullable */
    0, /* Extended */
    "MaxIPv6StaticAddresses", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_IPv6StaticAddresses =
{
    0, /* Nullable */
    0, /* Extended */
    "IPv6StaticAddresses", /* Name */
    "Collection(IPAddresses.IPV6StaticAddress)" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_IPv6DefaultGateway =
{
    1, /* Nullable */
    0, /* Extended */
    "IPv6DefaultGateway", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_NameServers =
{
    1, /* Nullable */
    0, /* Extended */
    "NameServers", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_HostName =
{
    1, /* Nullable */
    0, /* Extended */
    "HostName", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_FQDN =
{
    1, /* Nullable */
    0, /* Extended */
    "FQDN", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_SettingsResult =
{
    0, /* Nullable */
    0, /* Extended */
    "SettingsResult", /* Name */
    "Resource.SettingsResult" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_EthernetNetworkInterface_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "EthernetNetworkInterface.Links" /* Type */
};

static const EDM_Property* _EthernetNetworkInterface_EthernetNetworkInterface_PropertiesArray[] =
{
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_UEFIDevicePath,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_Status,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_FactoryMacAddress,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_MacAddress,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_LinkTechnology,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_SpeedMBps,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_Autosense,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_FullDuplex,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_FrameSize,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_VLANEnable,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_VLANId,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_IPv6First,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_IPv6AddressPolicyTable,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_IPv4Addresses,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_IPv6Addresses,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_MaxIPv6StaticAddresses,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_IPv6StaticAddresses,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_IPv6DefaultGateway,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_NameServers,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_HostName,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_FQDN,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_SettingsResult,
    (const EDM_Property*)&_EthernetNetworkInterface_EthernetNetworkInterface_Links
};

static const EDM_EntityType _EthernetNetworkInterface_EthernetNetworkInterface =
{
    "EthernetNetworkInterface", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _EthernetNetworkInterface_EthernetNetworkInterface_PropertiesArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_EthernetNetworkInterface_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_NavigationProperty _EthernetNetworkInterface_Links_Settings =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Settings", /* Name */
    "Resource.Settings", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _EthernetNetworkInterface_Links_NetworkServices =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "NetworkServices", /* Name */
    "Collection(NetworkService.ManagerNetworkService)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _EthernetNetworkInterface_Links_VLANs =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "VLANs", /* Name */
    "Collection(VLanNetworkInterface.VLANNetworkInterface)", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _EthernetNetworkInterface_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _EthernetNetworkInterface_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_EthernetNetworkInterface_Links_Oem
};

static const EDM_NavigationProperty* _EthernetNetworkInterface_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_EthernetNetworkInterface_Links_Settings,
    (const EDM_NavigationProperty*)&_EthernetNetworkInterface_Links_NetworkServices,
    (const EDM_NavigationProperty*)&_EthernetNetworkInterface_Links_VLANs
};

static const EDM_ComplexType _EthernetNetworkInterface_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _EthernetNetworkInterface_Links_PropertiesArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_Links_PropertiesArray),
    _EthernetNetworkInterface_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_Links_NavigationPropertiesArray)
};

static const char* _EthernetNetworkInterface_LinkTechnology_MembersArray[] =
{
    "Ethernet"
};

static const EDM_EnumType _EthernetNetworkInterface_LinkTechnology =
{
    "LinkTechnology", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_EthernetNetworkInterface_LinkTechnology_MembersArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_LinkTechnology_MembersArray)
};

static const EDM_TypeDefinition _EthernetNetworkInterface_MacAddress =
{
    "MacAddress", /* Name */
    "Edm.String" /* UnderlyingType */
};

static const EDM_TypeDefinition _EthernetNetworkInterface_VLanId =
{
    "VLanId", /* Name */
    "Edm.Int64" /* UnderlyingType */
};

static const EDM_Property _EthernetNetworkInterface_IPv6AddressPolicyEntry_Prefix =
{
    1, /* Nullable */
    0, /* Extended */
    "Prefix", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_IPv6AddressPolicyEntry_Precedence =
{
    1, /* Nullable */
    0, /* Extended */
    "Precedence", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _EthernetNetworkInterface_IPv6AddressPolicyEntry_Label =
{
    1, /* Nullable */
    0, /* Extended */
    "Label", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property* _EthernetNetworkInterface_IPv6AddressPolicyEntry_PropertiesArray[] =
{
    (const EDM_Property*)&_EthernetNetworkInterface_IPv6AddressPolicyEntry_Prefix,
    (const EDM_Property*)&_EthernetNetworkInterface_IPv6AddressPolicyEntry_Precedence,
    (const EDM_Property*)&_EthernetNetworkInterface_IPv6AddressPolicyEntry_Label
};

static const EDM_ComplexType _EthernetNetworkInterface_IPv6AddressPolicyEntry =
{
    "IPv6AddressPolicyEntry", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _EthernetNetworkInterface_IPv6AddressPolicyEntry_PropertiesArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_IPv6AddressPolicyEntry_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_EntityType* _EthernetNetworkInterface_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_EthernetNetworkInterface_EthernetNetworkInterface
};

static const EDM_ComplexType* _EthernetNetworkInterface_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_EthernetNetworkInterface_Links,
    (const EDM_ComplexType*)&_EthernetNetworkInterface_IPv6AddressPolicyEntry
};

static const EDM_EnumType* _EthernetNetworkInterface_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_EthernetNetworkInterface_LinkTechnology
};

static const EDM_TypeDefinition* _EthernetNetworkInterface_TypeDefinitionsArray[] =
{
    (const EDM_TypeDefinition*)&_EthernetNetworkInterface_MacAddress,
    (const EDM_TypeDefinition*)&_EthernetNetworkInterface_VLanId
};

static const EDM_Schema _EthernetNetworkInterface_Schema =
{
    "EthernetNetworkInterface.0.9.2", /* Namespace */
    "EthernetNetworkInterface", /* Alias */
    _EthernetNetworkInterface_EntityTypesArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_EntityTypesArray),
    _EthernetNetworkInterface_ComplexTypesArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_ComplexTypesArray),
    _EthernetNetworkInterface_EnumTypesArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_EnumTypesArray),
    NULL, /* Actions */
    0, /* NumActions */
    _EthernetNetworkInterface_TypeDefinitionsArray,
    OL_ARRAYSIZE(_EthernetNetworkInterface_TypeDefinitionsArray),
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_EthernetNetworkInterface_Schema
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
    &_6_Reference
};

const EDMX_Edmx EthernetNetworkInterface_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

