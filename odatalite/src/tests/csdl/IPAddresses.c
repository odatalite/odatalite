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

static const EDM_Property _IPAddresses_IPV4Address_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property _IPAddresses_IPV4Address_Address =
{
    1, /* Nullable */
    0, /* Extended */
    "Address", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _IPAddresses_IPV4Address_SubnetMask =
{
    1, /* Nullable */
    0, /* Extended */
    "SubnetMask", /* Name */
    "IPAddresses.SubnetMask" /* Type */
};

static const EDM_Property _IPAddresses_IPV4Address_AddressOrigin =
{
    1, /* Nullable */
    0, /* Extended */
    "AddressOrigin", /* Name */
    "IPAddresses.IPv4AddressOrigin" /* Type */
};

static const EDM_Property _IPAddresses_IPV4Address_Gateway =
{
    1, /* Nullable */
    0, /* Extended */
    "Gateway", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _IPAddresses_IPV4Address_PropertiesArray[] =
{
    (const EDM_Property*)&_IPAddresses_IPV4Address_Oem,
    (const EDM_Property*)&_IPAddresses_IPV4Address_Address,
    (const EDM_Property*)&_IPAddresses_IPV4Address_SubnetMask,
    (const EDM_Property*)&_IPAddresses_IPV4Address_AddressOrigin,
    (const EDM_Property*)&_IPAddresses_IPV4Address_Gateway
};

static const EDM_ComplexType _IPAddresses_IPV4Address =
{
    "IPV4Address", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _IPAddresses_IPV4Address_PropertiesArray,
    OL_ARRAYSIZE(_IPAddresses_IPV4Address_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _IPAddresses_IPV6Address_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property _IPAddresses_IPV6Address_Address =
{
    1, /* Nullable */
    0, /* Extended */
    "Address", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _IPAddresses_IPV6Address_PrefixLength =
{
    1, /* Nullable */
    0, /* Extended */
    "PrefixLength", /* Name */
    "IPAddresses.PrefixLength" /* Type */
};

static const EDM_Property _IPAddresses_IPV6Address_AddressOrigin =
{
    1, /* Nullable */
    0, /* Extended */
    "AddressOrigin", /* Name */
    "IPAddresses.IPv6AddressOrigin" /* Type */
};

static const EDM_Property _IPAddresses_IPV6Address_AddressState =
{
    1, /* Nullable */
    0, /* Extended */
    "AddressState", /* Name */
    "IPAddresses.AddressState" /* Type */
};

static const EDM_Property* _IPAddresses_IPV6Address_PropertiesArray[] =
{
    (const EDM_Property*)&_IPAddresses_IPV6Address_Oem,
    (const EDM_Property*)&_IPAddresses_IPV6Address_Address,
    (const EDM_Property*)&_IPAddresses_IPV6Address_PrefixLength,
    (const EDM_Property*)&_IPAddresses_IPV6Address_AddressOrigin,
    (const EDM_Property*)&_IPAddresses_IPV6Address_AddressState
};

static const EDM_ComplexType _IPAddresses_IPV6Address =
{
    "IPV6Address", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _IPAddresses_IPV6Address_PropertiesArray,
    OL_ARRAYSIZE(_IPAddresses_IPV6Address_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _IPAddresses_IPv4AddressOrigin_MembersArray[] =
{
    "DHCP",
    "Static"
};

static const EDM_EnumType _IPAddresses_IPv4AddressOrigin =
{
    "IPv4AddressOrigin", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_IPAddresses_IPv4AddressOrigin_MembersArray,
    OL_ARRAYSIZE(_IPAddresses_IPv4AddressOrigin_MembersArray)
};

static const char* _IPAddresses_IPv6AddressOrigin_MembersArray[] =
{
    "DHCP",
    "Static",
    "SLAAC"
};

static const EDM_EnumType _IPAddresses_IPv6AddressOrigin =
{
    "IPv6AddressOrigin", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_IPAddresses_IPv6AddressOrigin_MembersArray,
    OL_ARRAYSIZE(_IPAddresses_IPv6AddressOrigin_MembersArray)
};

static const EDM_TypeDefinition _IPAddresses_SubnetMask =
{
    "SubnetMask", /* Name */
    "Edm.String" /* UnderlyingType */
};

static const EDM_TypeDefinition _IPAddresses_PrefixLength =
{
    "PrefixLength", /* Name */
    "Edm.Int64" /* UnderlyingType */
};

static const char* _IPAddresses_AddressState_MembersArray[] =
{
    "Preferred",
    "Deprecated",
    "Tentative",
    "Failed"
};

static const EDM_EnumType _IPAddresses_AddressState =
{
    "AddressState", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_IPAddresses_AddressState_MembersArray,
    OL_ARRAYSIZE(_IPAddresses_AddressState_MembersArray)
};

static const EDM_Property _IPAddresses_IPV6StaticAddress_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property _IPAddresses_IPV6StaticAddress_Address =
{
    1, /* Nullable */
    0, /* Extended */
    "Address", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _IPAddresses_IPV6StaticAddress_PrefixLength =
{
    1, /* Nullable */
    0, /* Extended */
    "PrefixLength", /* Name */
    "IPAddresses.PrefixLength" /* Type */
};

static const EDM_Property* _IPAddresses_IPV6StaticAddress_PropertiesArray[] =
{
    (const EDM_Property*)&_IPAddresses_IPV6StaticAddress_Oem,
    (const EDM_Property*)&_IPAddresses_IPV6StaticAddress_Address,
    (const EDM_Property*)&_IPAddresses_IPV6StaticAddress_PrefixLength
};

static const EDM_ComplexType _IPAddresses_IPV6StaticAddress =
{
    "IPV6StaticAddress", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _IPAddresses_IPV6StaticAddress_PropertiesArray,
    OL_ARRAYSIZE(_IPAddresses_IPV6StaticAddress_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType* _IPAddresses_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_IPAddresses_IPV4Address,
    (const EDM_ComplexType*)&_IPAddresses_IPV6Address,
    (const EDM_ComplexType*)&_IPAddresses_IPV6StaticAddress
};

static const EDM_EnumType* _IPAddresses_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_IPAddresses_IPv4AddressOrigin,
    (const EDM_EnumType*)&_IPAddresses_IPv6AddressOrigin,
    (const EDM_EnumType*)&_IPAddresses_AddressState
};

static const EDM_TypeDefinition* _IPAddresses_TypeDefinitionsArray[] =
{
    (const EDM_TypeDefinition*)&_IPAddresses_SubnetMask,
    (const EDM_TypeDefinition*)&_IPAddresses_PrefixLength
};

static const EDM_Schema _IPAddresses_Schema =
{
    "IPAddresses.0.9.2", /* Namespace */
    "IPAddresses", /* Alias */
    NULL, /* EntityTypes */
    0, /* NumEntityTypes */
    _IPAddresses_ComplexTypesArray,
    OL_ARRAYSIZE(_IPAddresses_ComplexTypesArray),
    _IPAddresses_EnumTypesArray,
    OL_ARRAYSIZE(_IPAddresses_EnumTypesArray),
    NULL, /* Actions */
    0, /* NumActions */
    _IPAddresses_TypeDefinitionsArray,
    OL_ARRAYSIZE(_IPAddresses_TypeDefinitionsArray),
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_IPAddresses_Schema
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

const EDMX_Edmx IPAddresses_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

