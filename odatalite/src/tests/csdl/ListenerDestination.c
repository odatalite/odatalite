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
    "Event.0.9.2", /* Include.Namespace */
    "Event" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/Event", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _ListenerDestination_ListenerDestination_Destination =
{
    0, /* Nullable */
    0, /* Extended */
    "Destination", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ListenerDestination_ListenerDestination_HttpHeaders =
{
    1, /* Nullable */
    0, /* Extended */
    "HttpHeaders", /* Name */
    "Collection(ListenerDestination.HttpHeaderProperty)" /* Type */
};

static const EDM_Property _ListenerDestination_ListenerDestination_EventTypes =
{
    0, /* Nullable */
    0, /* Extended */
    "EventTypes", /* Name */
    "Collection(Event.EventType)" /* Type */
};

static const EDM_Property _ListenerDestination_ListenerDestination_TTLCount =
{
    0, /* Nullable */
    0, /* Extended */
    "TTLCount", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _ListenerDestination_ListenerDestination_TTLUnits =
{
    0, /* Nullable */
    0, /* Extended */
    "TTLUnits", /* Name */
    "ListenerDestination.TTLUnits" /* Type */
};

static const EDM_Property _ListenerDestination_ListenerDestination_Context =
{
    0, /* Nullable */
    0, /* Extended */
    "Context", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ListenerDestination_ListenerDestination_Protocol =
{
    0, /* Nullable */
    0, /* Extended */
    "Protocol", /* Name */
    "ListenerDestination.ListenerDestinationProtocol" /* Type */
};

static const EDM_Property _ListenerDestination_ListenerDestination_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "ListenerDestination.Links" /* Type */
};

static const EDM_Property* _ListenerDestination_ListenerDestination_PropertiesArray[] =
{
    (const EDM_Property*)&_ListenerDestination_ListenerDestination_Destination,
    (const EDM_Property*)&_ListenerDestination_ListenerDestination_HttpHeaders,
    (const EDM_Property*)&_ListenerDestination_ListenerDestination_EventTypes,
    (const EDM_Property*)&_ListenerDestination_ListenerDestination_TTLCount,
    (const EDM_Property*)&_ListenerDestination_ListenerDestination_TTLUnits,
    (const EDM_Property*)&_ListenerDestination_ListenerDestination_Context,
    (const EDM_Property*)&_ListenerDestination_ListenerDestination_Protocol,
    (const EDM_Property*)&_ListenerDestination_ListenerDestination_Links
};

static const EDM_EntityType _ListenerDestination_ListenerDestination =
{
    "ListenerDestination", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _ListenerDestination_ListenerDestination_PropertiesArray,
    OL_ARRAYSIZE(_ListenerDestination_ListenerDestination_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _ListenerDestination_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _ListenerDestination_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_ListenerDestination_Links_Oem
};

static const EDM_ComplexType _ListenerDestination_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _ListenerDestination_Links_PropertiesArray,
    OL_ARRAYSIZE(_ListenerDestination_Links_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType _ListenerDestination_HttpHeaderProperty =
{
    "HttpHeaderProperty", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* Properties */
    0, /* NumProperties */
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _ListenerDestination_ListenerDestinationProtocol_MembersArray[] =
{
    "SPMA"
};

static const EDM_EnumType _ListenerDestination_ListenerDestinationProtocol =
{
    "ListenerDestinationProtocol", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ListenerDestination_ListenerDestinationProtocol_MembersArray,
    OL_ARRAYSIZE(_ListenerDestination_ListenerDestinationProtocol_MembersArray)
};

static const char* _ListenerDestination_TTLUnits_MembersArray[] =
{
    "seconds",
    "minutes",
    "days"
};

static const EDM_EnumType _ListenerDestination_TTLUnits =
{
    "TTLUnits", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_ListenerDestination_TTLUnits_MembersArray,
    OL_ARRAYSIZE(_ListenerDestination_TTLUnits_MembersArray)
};

static const EDM_EntityType* _ListenerDestination_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_ListenerDestination_ListenerDestination
};

static const EDM_ComplexType* _ListenerDestination_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_ListenerDestination_Links,
    (const EDM_ComplexType*)&_ListenerDestination_HttpHeaderProperty
};

static const EDM_EnumType* _ListenerDestination_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_ListenerDestination_ListenerDestinationProtocol,
    (const EDM_EnumType*)&_ListenerDestination_TTLUnits
};

static const EDM_Schema _ListenerDestination_Schema =
{
    "ListenerDestination.0.9.2", /* Namespace */
    "ListenerDestination", /* Alias */
    _ListenerDestination_EntityTypesArray,
    OL_ARRAYSIZE(_ListenerDestination_EntityTypesArray),
    _ListenerDestination_ComplexTypesArray,
    OL_ARRAYSIZE(_ListenerDestination_ComplexTypesArray),
    _ListenerDestination_EnumTypesArray,
    OL_ARRAYSIZE(_ListenerDestination_EnumTypesArray),
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
    &_ListenerDestination_Schema
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

const EDMX_Edmx ListenerDestination_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

