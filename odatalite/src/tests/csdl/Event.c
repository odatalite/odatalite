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

static const EDM_Property _Event_Event_Events =
{
    0, /* Nullable */
    0, /* Extended */
    "Events", /* Name */
    "Collection(Event.EventRecordWithContext)" /* Type */
};

static const EDM_Property* _Event_Event_PropertiesArray[] =
{
    (const EDM_Property*)&_Event_Event_Events
};

static const EDM_EntityType _Event_Event =
{
    "Event", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _Event_Event_PropertiesArray,
    OL_ARRAYSIZE(_Event_Event_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _Event_EventType_MembersArray[] =
{
    "StatusChange",
    "ResourceUpdated",
    "ResourceAdded",
    "ResourceRemoved",
    "Alert"
};

static const EDM_EnumType _Event_EventType =
{
    "EventType", /* Name */
    NULL, /* UnderlyingType */
    "true", /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Event_EventType_MembersArray,
    OL_ARRAYSIZE(_Event_EventType_MembersArray)
};

static const EDM_Property _Event_EventRecord_EventType =
{
    0, /* Nullable */
    0, /* Extended */
    "EventType", /* Name */
    "Event.EventType" /* Type */
};

static const EDM_Property _Event_EventRecord_EventID =
{
    0, /* Nullable */
    0, /* Extended */
    "EventID", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Event_EventRecord_EventTimestamp =
{
    0, /* Nullable */
    0, /* Extended */
    "EventTimestamp", /* Name */
    "Edm.DateTimeOffset" /* Type */
};

static const EDM_Property _Event_EventRecord_Severity =
{
    0, /* Nullable */
    0, /* Extended */
    "Severity", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Event_EventRecord_Message =
{
    0, /* Nullable */
    0, /* Extended */
    "Message", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Event_EventRecord_MessageID =
{
    0, /* Nullable */
    0, /* Extended */
    "MessageID", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Event_EventRecord_MessageArgs =
{
    0, /* Nullable */
    0, /* Extended */
    "MessageArgs", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_Property _Event_EventRecord_OriginOfCondition =
{
    0, /* Nullable */
    0, /* Extended */
    "OriginOfCondition", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _Event_EventRecord_PropertiesArray[] =
{
    (const EDM_Property*)&_Event_EventRecord_EventType,
    (const EDM_Property*)&_Event_EventRecord_EventID,
    (const EDM_Property*)&_Event_EventRecord_EventTimestamp,
    (const EDM_Property*)&_Event_EventRecord_Severity,
    (const EDM_Property*)&_Event_EventRecord_Message,
    (const EDM_Property*)&_Event_EventRecord_MessageID,
    (const EDM_Property*)&_Event_EventRecord_MessageArgs,
    (const EDM_Property*)&_Event_EventRecord_OriginOfCondition
};

static const EDM_ComplexType _Event_EventRecord =
{
    "EventRecord", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Event_EventRecord_PropertiesArray,
    OL_ARRAYSIZE(_Event_EventRecord_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _Event_EventRecordWithContext_Context =
{
    0, /* Nullable */
    0, /* Extended */
    "Context", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Event_EventRecordWithContext_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _Event_EventRecordWithContext_PropertiesArray[] =
{
    (const EDM_Property*)&_Event_EventRecordWithContext_Context,
    (const EDM_Property*)&_Event_EventRecordWithContext_Oem
};

static const EDM_ComplexType _Event_EventRecordWithContext =
{
    "EventRecordWithContext", /* Name */
    "Event.EventRecord", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Event_EventRecordWithContext_PropertiesArray,
    OL_ARRAYSIZE(_Event_EventRecordWithContext_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_EntityType* _Event_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_Event_Event
};

static const EDM_ComplexType* _Event_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_Event_EventRecord,
    (const EDM_ComplexType*)&_Event_EventRecordWithContext
};

static const EDM_EnumType* _Event_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_Event_EventType
};

static const EDM_Schema _Event_Schema =
{
    "Event.0.9.2", /* Namespace */
    "Event", /* Alias */
    _Event_EntityTypesArray,
    OL_ARRAYSIZE(_Event_EntityTypesArray),
    _Event_ComplexTypesArray,
    OL_ARRAYSIZE(_Event_ComplexTypesArray),
    _Event_EnumTypesArray,
    OL_ARRAYSIZE(_Event_EnumTypesArray),
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
    &_Event_Schema
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

const EDMX_Edmx Event_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

