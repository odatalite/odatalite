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
    "Org.OData.Measures.V1", /* Include.Namespace */
    "OData.Measures" /* Include.Alias */
};

static const EDMX_Include* _2_IncludesArray[] =
{
    &_2_0_Include
};

static const EDMX_Reference _2_Reference =
{
    "http://docs.oasis-open.org/odata/odata/v4.0/cs01/vocabularies/Org.OData.Measures.V1.xml", /* Uri */
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

static const EDM_Property _NetworkService_ManagerNetworkService_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "NetworkService.Links" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_HostName =
{
    1, /* Nullable */
    0, /* Extended */
    "HostName", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_FQDN =
{
    1, /* Nullable */
    0, /* Extended */
    "FQDN", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_SessionTimeoutMinutes =
{
    1, /* Nullable */
    0, /* Extended */
    "SessionTimeoutMinutes", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_HTTP =
{
    0, /* Nullable */
    0, /* Extended */
    "HTTP", /* Name */
    "NetworkService.Protocol" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_HTTPS =
{
    0, /* Nullable */
    0, /* Extended */
    "HTTPS", /* Name */
    "NetworkService.Protocol" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_SNMP =
{
    0, /* Nullable */
    0, /* Extended */
    "SNMP", /* Name */
    "NetworkService.Protocol" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_VirtualMedia =
{
    0, /* Nullable */
    0, /* Extended */
    "VirtualMedia", /* Name */
    "NetworkService.Protocol" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_Telnet =
{
    0, /* Nullable */
    0, /* Extended */
    "Telnet", /* Name */
    "NetworkService.Protocol" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_SSDP =
{
    0, /* Nullable */
    0, /* Extended */
    "SSDP", /* Name */
    "NetworkService.SSDProtocol" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_IPMI =
{
    0, /* Nullable */
    0, /* Extended */
    "IPMI", /* Name */
    "NetworkService.Protocol" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_SSH =
{
    0, /* Nullable */
    0, /* Extended */
    "SSH", /* Name */
    "NetworkService.Protocol" /* Type */
};

static const EDM_Property _NetworkService_ManagerNetworkService_KVMIP =
{
    0, /* Nullable */
    0, /* Extended */
    "KVMIP", /* Name */
    "NetworkService.Protocol" /* Type */
};

static const EDM_Property* _NetworkService_ManagerNetworkService_PropertiesArray[] =
{
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_Links,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_HostName,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_FQDN,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_SessionTimeoutMinutes,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_HTTP,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_HTTPS,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_SNMP,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_VirtualMedia,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_Telnet,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_SSDP,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_IPMI,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_SSH,
    (const EDM_Property*)&_NetworkService_ManagerNetworkService_KVMIP
};

static const EDM_EntityType _NetworkService_ManagerNetworkService =
{
    "ManagerNetworkService", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _NetworkService_ManagerNetworkService_PropertiesArray,
    OL_ARRAYSIZE(_NetworkService_ManagerNetworkService_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_NavigationProperty _NetworkService_Links_Settings =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Settings", /* Name */
    "Resource.Settings", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _NetworkService_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _NetworkService_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_NetworkService_Links_Oem
};

static const EDM_NavigationProperty* _NetworkService_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_NetworkService_Links_Settings
};

static const EDM_ComplexType _NetworkService_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _NetworkService_Links_PropertiesArray,
    OL_ARRAYSIZE(_NetworkService_Links_PropertiesArray),
    _NetworkService_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_NetworkService_Links_NavigationPropertiesArray)
};

static const EDM_Property _NetworkService_Protocol_Enabled =
{
    1, /* Nullable */
    0, /* Extended */
    "Enabled", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property _NetworkService_Protocol_Port =
{
    1, /* Nullable */
    0, /* Extended */
    "Port", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property* _NetworkService_Protocol_PropertiesArray[] =
{
    (const EDM_Property*)&_NetworkService_Protocol_Enabled,
    (const EDM_Property*)&_NetworkService_Protocol_Port
};

static const EDM_ComplexType _NetworkService_Protocol =
{
    "Protocol", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _NetworkService_Protocol_PropertiesArray,
    OL_ARRAYSIZE(_NetworkService_Protocol_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _NetworkService_SSDProtocol_NotifyMulticastIntervalSeconds =
{
    1, /* Nullable */
    0, /* Extended */
    "NotifyMulticastIntervalSeconds", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _NetworkService_SSDProtocol_NotifyTTL =
{
    1, /* Nullable */
    0, /* Extended */
    "NotifyTTL", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _NetworkService_SSDProtocol_NotifyIPv6Scope =
{
    1, /* Nullable */
    0, /* Extended */
    "NotifyIPv6Scope", /* Name */
    "NetworkService.NotifyIPv6Scope" /* Type */
};

static const EDM_Property* _NetworkService_SSDProtocol_PropertiesArray[] =
{
    (const EDM_Property*)&_NetworkService_SSDProtocol_NotifyMulticastIntervalSeconds,
    (const EDM_Property*)&_NetworkService_SSDProtocol_NotifyTTL,
    (const EDM_Property*)&_NetworkService_SSDProtocol_NotifyIPv6Scope
};

static const EDM_ComplexType _NetworkService_SSDProtocol =
{
    "SSDProtocol", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _NetworkService_SSDProtocol_PropertiesArray,
    OL_ARRAYSIZE(_NetworkService_SSDProtocol_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _NetworkService_NotifyIPv6Scope_MembersArray[] =
{
    "Link",
    "Site",
    "Organization"
};

static const EDM_EnumType _NetworkService_NotifyIPv6Scope =
{
    "NotifyIPv6Scope", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_NetworkService_NotifyIPv6Scope_MembersArray,
    OL_ARRAYSIZE(_NetworkService_NotifyIPv6Scope_MembersArray)
};

static const EDM_EntityType* _NetworkService_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_NetworkService_ManagerNetworkService
};

static const EDM_ComplexType* _NetworkService_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_NetworkService_Links,
    (const EDM_ComplexType*)&_NetworkService_Protocol,
    (const EDM_ComplexType*)&_NetworkService_SSDProtocol
};

static const EDM_EnumType* _NetworkService_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_NetworkService_NotifyIPv6Scope
};

static const EDM_Schema _NetworkService_Schema =
{
    "NetworkService.0.9.2", /* Namespace */
    "NetworkService", /* Alias */
    _NetworkService_EntityTypesArray,
    OL_ARRAYSIZE(_NetworkService_EntityTypesArray),
    _NetworkService_ComplexTypesArray,
    OL_ARRAYSIZE(_NetworkService_ComplexTypesArray),
    _NetworkService_EnumTypesArray,
    OL_ARRAYSIZE(_NetworkService_EnumTypesArray),
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
    &_NetworkService_Schema
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

const EDMX_Edmx ManagerNetworkService_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

