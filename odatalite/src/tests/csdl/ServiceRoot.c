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
    "EventService.0.9.2", /* Include.Namespace */
    "EventService" /* Include.Alias */
};

static const EDMX_Include* _2_IncludesArray[] =
{
    &_2_0_Include
};

static const EDMX_Reference _2_Reference =
{
    "http://dmtf.org/schema/v1/EventService", /* Uri */
    _2_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_2_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _3_0_Include =
{
    "AccountService.0.9.2", /* Include.Namespace */
    "AccountService" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/AccountService", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _4_0_Include =
{
    "ComputerSystem.0.9.2", /* Include.Namespace */
    "ComputerSystem" /* Include.Alias */
};

static const EDMX_Include* _4_IncludesArray[] =
{
    &_4_0_Include
};

static const EDMX_Reference _4_Reference =
{
    "http://dmtf.org/schema/v1/ComputerSystem", /* Uri */
    _4_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_4_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _5_0_Include =
{
    "Chassis.0.9.2", /* Include.Namespace */
    "Chassis" /* Include.Alias */
};

static const EDMX_Include* _5_IncludesArray[] =
{
    &_5_0_Include
};

static const EDMX_Reference _5_Reference =
{
    "http://dmtf.org/schema/v1/Chassis", /* Uri */
    _5_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_5_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _6_0_Include =
{
    "Managers.0.9.2", /* Include.Namespace */
    "Manager" /* Include.Alias */
};

static const EDMX_Include* _6_IncludesArray[] =
{
    &_6_0_Include
};

static const EDMX_Reference _6_Reference =
{
    "http://dmtf.org/schema/v1/Manager", /* Uri */
    _6_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_6_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _7_0_Include =
{
    "TaskService.0.9.2", /* Include.Namespace */
    "TaskService" /* Include.Alias */
};

static const EDMX_Include* _7_IncludesArray[] =
{
    &_7_0_Include
};

static const EDMX_Reference _7_Reference =
{
    "http://dmtf.org/schema/v1/TaskService", /* Uri */
    _7_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_7_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _8_0_Include =
{
    "Session.0.9.2", /* Include.Namespace */
    "Session" /* Include.Alias */
};

static const EDMX_Include* _8_IncludesArray[] =
{
    &_8_0_Include
};

static const EDMX_Reference _8_Reference =
{
    "http://dmtf.org/schema/v1/Session", /* Uri */
    _8_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_8_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _9_0_Include =
{
    "Messages.0.9.2", /* Include.Namespace */
    "Messages" /* Include.Alias */
};

static const EDMX_Include* _9_IncludesArray[] =
{
    &_9_0_Include
};

static const EDMX_Reference _9_Reference =
{
    "http://dmtf.org/schema/v1/Messages", /* Uri */
    _9_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_9_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Singleton _ServiceContainer_Service =
{
    "Service", /* Name */
    "ServiceRoot.ServiceRoot" /* Type */
};

static const EDM_Singleton* _ServiceContainer_SingletonsArray[] =
{
    (const EDM_Singleton*)&_ServiceContainer_Service
};

static const EDM_EntityContainer _ServiceRoot_ServiceContainer =
{
    "ServiceContainer", /* Name */
    NULL, /* Extends */
    _ServiceContainer_SingletonsArray,
    OL_ARRAYSIZE(_ServiceContainer_SingletonsArray)
};

static const EDM_Property _ServiceRoot_ServiceRoot_Time =
{
    1, /* Nullable */
    0, /* Extended */
    "Time", /* Name */
    "Edm.DateTimeOffset" /* Type */
};

static const EDM_Property _ServiceRoot_ServiceRoot_ServiceVersion =
{
    0, /* Nullable */
    0, /* Extended */
    "ServiceVersion", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _ServiceRoot_ServiceRoot_UUID =
{
    1, /* Nullable */
    0, /* Extended */
    "UUID", /* Name */
    "ServiceRoot.UUID" /* Type */
};

static const EDM_Property _ServiceRoot_ServiceRoot_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "ServiceRoot.ServiceRootLinks" /* Type */
};

static const EDM_Property* _ServiceRoot_ServiceRoot_PropertiesArray[] =
{
    (const EDM_Property*)&_ServiceRoot_ServiceRoot_Time,
    (const EDM_Property*)&_ServiceRoot_ServiceRoot_ServiceVersion,
    (const EDM_Property*)&_ServiceRoot_ServiceRoot_UUID,
    (const EDM_Property*)&_ServiceRoot_ServiceRoot_Links
};

static const EDM_EntityType _ServiceRoot_ServiceRoot =
{
    "ServiceRoot", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _ServiceRoot_ServiceRoot_PropertiesArray,
    OL_ARRAYSIZE(_ServiceRoot_ServiceRoot_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_NavigationProperty _ServiceRoot_ServiceRootLinks_Systems =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Systems", /* Name */
    "Collection(ComputerSystem.ComputerSystem)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ServiceRoot_ServiceRootLinks_Chassis =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Chassis", /* Name */
    "Collection(Chassis.Chassis)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ServiceRoot_ServiceRootLinks_Managers =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Managers", /* Name */
    "Collection(Manager.Manager)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ServiceRoot_ServiceRootLinks_Tasks =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Tasks", /* Name */
    "Collection(TaskService.TaskService)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ServiceRoot_ServiceRootLinks_AccountService =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "AccountService", /* Name */
    "AccountService.AccountService", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ServiceRoot_ServiceRootLinks_EventService =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "EventService", /* Name */
    "EventService.EventService", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty _ServiceRoot_ServiceRootLinks_Registries =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Registries", /* Name */
    "Collection(Messages.MessageRegistry)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty* _ServiceRoot_ServiceRootLinks_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_ServiceRoot_ServiceRootLinks_Systems,
    (const EDM_NavigationProperty*)&_ServiceRoot_ServiceRootLinks_Chassis,
    (const EDM_NavigationProperty*)&_ServiceRoot_ServiceRootLinks_Managers,
    (const EDM_NavigationProperty*)&_ServiceRoot_ServiceRootLinks_Tasks,
    (const EDM_NavigationProperty*)&_ServiceRoot_ServiceRootLinks_AccountService,
    (const EDM_NavigationProperty*)&_ServiceRoot_ServiceRootLinks_EventService,
    (const EDM_NavigationProperty*)&_ServiceRoot_ServiceRootLinks_Registries
};

static const EDM_ComplexType _ServiceRoot_ServiceRootLinks =
{
    "ServiceRootLinks", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* Properties */
    0, /* NumProperties */
    _ServiceRoot_ServiceRootLinks_NavigationPropertiesArray,
    OL_ARRAYSIZE(_ServiceRoot_ServiceRootLinks_NavigationPropertiesArray)
};

static const EDM_TypeDefinition _ServiceRoot_UUID =
{
    "UUID", /* Name */
    "Edm.String" /* UnderlyingType */
};

static const EDM_EntityType* _ServiceRoot_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_ServiceRoot_ServiceRoot
};

static const EDM_ComplexType* _ServiceRoot_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_ServiceRoot_ServiceRootLinks
};

static const EDM_TypeDefinition* _ServiceRoot_TypeDefinitionsArray[] =
{
    (const EDM_TypeDefinition*)&_ServiceRoot_UUID
};

static const EDM_EntityContainer* _ServiceRoot_EntityContainersArray[] =
{
    (const EDM_EntityContainer*)&_ServiceRoot_ServiceContainer
};

static const EDM_Schema _ServiceRoot_Schema =
{
    "ServiceRoot.0.9.2", /* Namespace */
    "ServiceRoot", /* Alias */
    _ServiceRoot_EntityTypesArray,
    OL_ARRAYSIZE(_ServiceRoot_EntityTypesArray),
    _ServiceRoot_ComplexTypesArray,
    OL_ARRAYSIZE(_ServiceRoot_ComplexTypesArray),
    NULL, /* EnumTypes */
    0, /* NumEnumTypes */
    NULL, /* Actions */
    0, /* NumActions */
    _ServiceRoot_TypeDefinitionsArray,
    OL_ARRAYSIZE(_ServiceRoot_TypeDefinitionsArray),
    _ServiceRoot_EntityContainersArray,
    OL_ARRAYSIZE(_ServiceRoot_EntityContainersArray),
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_ServiceRoot_Schema
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
    &_9_Reference
};

const EDMX_Edmx ServiceRoot_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

