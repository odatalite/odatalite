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

static const EDMX_Include _4_0_Include =
{
    "Event.0.9.2", /* Include.Namespace */
    "Event" /* Include.Alias */
};

static const EDMX_Include* _4_IncludesArray[] =
{
    &_4_0_Include
};

static const EDMX_Reference _4_Reference =
{
    "http://dmtf.org/schema/v1/Event", /* Uri */
    _4_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_4_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _5_0_Include =
{
    "ListenerDestination.0.9.2", /* Include.Namespace */
    "ListenerDestination" /* Include.Alias */
};

static const EDMX_Include* _5_IncludesArray[] =
{
    &_5_0_Include
};

static const EDMX_Reference _5_Reference =
{
    "http://dmtf.org/schema/v1/ListenerDestination", /* Uri */
    _5_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_5_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _EventService_EventService_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "EventService.Links" /* Type */
};

static const EDM_Property _EventService_EventService_DeliveryRetryAttempts =
{
    0, /* Nullable */
    0, /* Extended */
    "DeliveryRetryAttempts", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _EventService_EventService_DeliveryRetryIntervalInSeconds =
{
    0, /* Nullable */
    0, /* Extended */
    "DeliveryRetryIntervalInSeconds", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _EventService_EventService_SubscriptionRemovalAction =
{
    0, /* Nullable */
    0, /* Extended */
    "SubscriptionRemovalAction", /* Name */
    "EventService.SubscriptionRemovalAction" /* Type */
};

static const EDM_Property _EventService_EventService_SubscriptionRemovalTimeIntervalInMinutes =
{
    0, /* Nullable */
    0, /* Extended */
    "SubscriptionRemovalTimeIntervalInMinutes", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _EventService_EventService_EventTypesForSubscription =
{
    0, /* Nullable */
    0, /* Extended */
    "EventTypesForSubscription", /* Name */
    "Collection(Event.EventType)" /* Type */
};

static const EDM_Property _EventService_EventService_Actions =
{
    0, /* Nullable */
    0, /* Extended */
    "Actions", /* Name */
    "EventService.Actions" /* Type */
};

static const EDM_Property* _EventService_EventService_PropertiesArray[] =
{
    (const EDM_Property*)&_EventService_EventService_Links,
    (const EDM_Property*)&_EventService_EventService_DeliveryRetryAttempts,
    (const EDM_Property*)&_EventService_EventService_DeliveryRetryIntervalInSeconds,
    (const EDM_Property*)&_EventService_EventService_SubscriptionRemovalAction,
    (const EDM_Property*)&_EventService_EventService_SubscriptionRemovalTimeIntervalInMinutes,
    (const EDM_Property*)&_EventService_EventService_EventTypesForSubscription,
    (const EDM_Property*)&_EventService_EventService_Actions
};

static const EDM_EntityType _EventService_EventService =
{
    "EventService", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _EventService_EventService_PropertiesArray,
    OL_ARRAYSIZE(_EventService_EventService_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _EventService_Actions_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "EventService.OemActions" /* Type */
};

static const EDM_Property* _EventService_Actions_PropertiesArray[] =
{
    (const EDM_Property*)&_EventService_Actions_Oem
};

static const EDM_ComplexType _EventService_Actions =
{
    "Actions", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _EventService_Actions_PropertiesArray,
    OL_ARRAYSIZE(_EventService_Actions_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType _EventService_OemActions =
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

static const EDM_NavigationProperty _EventService_Links_Subscriptions =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Subscriptions", /* Name */
    "Collection(ListenerDestination.ListenerDestination)", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _EventService_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _EventService_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_EventService_Links_Oem
};

static const EDM_NavigationProperty* _EventService_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_EventService_Links_Subscriptions
};

static const EDM_ComplexType _EventService_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _EventService_Links_PropertiesArray,
    OL_ARRAYSIZE(_EventService_Links_PropertiesArray),
    _EventService_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_EventService_Links_NavigationPropertiesArray)
};

static const EDM_Parameter _EventService_SubmitTestEvent_EventService =
{
    "EventService", /* Name */
    "EventService.Actions", /* Type */
    NULL /* Nullable */
};

static const EDM_Parameter _EventService_SubmitTestEvent_EventType =
{
    "EventType", /* Name */
    "Event.EventType", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter _EventService_SubmitTestEvent_EventID =
{
    "EventID", /* Name */
    "Edm.String", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter _EventService_SubmitTestEvent_EventTimestamp =
{
    "EventTimestamp", /* Name */
    "Edm.DateTimeOffset", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter _EventService_SubmitTestEvent_Severity =
{
    "Severity", /* Name */
    "Edm.String", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter _EventService_SubmitTestEvent_Message =
{
    "Message", /* Name */
    "Edm.String", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter _EventService_SubmitTestEvent_MessageID =
{
    "MessageID", /* Name */
    "Edm.String", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter _EventService_SubmitTestEvent_MessageArgs =
{
    "MessageArgs", /* Name */
    "Collection(Edm.String)", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter _EventService_SubmitTestEvent_OriginOfCondition =
{
    "OriginOfCondition", /* Name */
    "Edm.String", /* Type */
    "false" /* Nullable */
};

static const EDM_Parameter* _EventService_SubmitTestEvent_ParametersArray[] =
{
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_EventService,
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_EventType,
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_EventID,
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_EventTimestamp,
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_Severity,
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_Message,
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_MessageID,
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_MessageArgs,
    (const EDM_Parameter*)&_EventService_SubmitTestEvent_OriginOfCondition
};

static const EDM_Action _EventService_SubmitTestEvent =
{
    "SubmitTestEvent", /* Name */
    "true", /* IsBound */
    NULL, /* EntitySetPath */
    _EventService_SubmitTestEvent_ParametersArray,
    OL_ARRAYSIZE(_EventService_SubmitTestEvent_ParametersArray),
};

static const char* _EventService_SubscriptionRemovalAction_MembersArray[] =
{
    "Remove",
    "Disable",
    "Ignore"
};

static const EDM_EnumType _EventService_SubscriptionRemovalAction =
{
    "SubscriptionRemovalAction", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_EventService_SubscriptionRemovalAction_MembersArray,
    OL_ARRAYSIZE(_EventService_SubscriptionRemovalAction_MembersArray)
};

static const EDM_EntityType* _EventService_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_EventService_EventService
};

static const EDM_ComplexType* _EventService_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_EventService_Actions,
    (const EDM_ComplexType*)&_EventService_OemActions,
    (const EDM_ComplexType*)&_EventService_Links
};

static const EDM_EnumType* _EventService_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_EventService_SubscriptionRemovalAction
};

static const EDM_Action* _EventService_ActionsArray[] =
{
    (const EDM_Action*)&_EventService_SubmitTestEvent
};

static const EDM_Schema _EventService_Schema =
{
    "EventService.0.9.2", /* Namespace */
    "EventService", /* Alias */
    _EventService_EntityTypesArray,
    OL_ARRAYSIZE(_EventService_EntityTypesArray),
    _EventService_ComplexTypesArray,
    OL_ARRAYSIZE(_EventService_ComplexTypesArray),
    _EventService_EnumTypesArray,
    OL_ARRAYSIZE(_EventService_EnumTypesArray),
    _EventService_ActionsArray,
    OL_ARRAYSIZE(_EventService_ActionsArray),
    NULL, /* TypeDefinitions */
    0, /* NumTypeDefinitions */
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_EventService_Schema
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
    &_5_Reference
};

const EDMX_Edmx EventService_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

