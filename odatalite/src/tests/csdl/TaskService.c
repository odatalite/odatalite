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
    "Tasks.0.9.2", /* Include.Namespace */
    "Tasks" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/Task", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _TaskService_TaskService_MaxNumberOfTasks =
{
    0, /* Nullable */
    0, /* Extended */
    "MaxNumberOfTasks", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _TaskService_TaskService_CompletedTaskOverWritePolicy =
{
    0, /* Nullable */
    0, /* Extended */
    "CompletedTaskOverWritePolicy", /* Name */
    "TaskService.OverWritePolicy" /* Type */
};

static const EDM_Property _TaskService_TaskService_LifeCycleEventOnTaskStateChange =
{
    0, /* Nullable */
    0, /* Extended */
    "LifeCycleEventOnTaskStateChange", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property _TaskService_TaskService_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "TaskService.Links" /* Type */
};

static const EDM_Property* _TaskService_TaskService_PropertiesArray[] =
{
    (const EDM_Property*)&_TaskService_TaskService_MaxNumberOfTasks,
    (const EDM_Property*)&_TaskService_TaskService_CompletedTaskOverWritePolicy,
    (const EDM_Property*)&_TaskService_TaskService_LifeCycleEventOnTaskStateChange,
    (const EDM_Property*)&_TaskService_TaskService_Links
};

static const EDM_EntityType _TaskService_TaskService =
{
    "TaskService", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _TaskService_TaskService_PropertiesArray,
    OL_ARRAYSIZE(_TaskService_TaskService_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_NavigationProperty _TaskService_Links_Tasks =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Tasks", /* Name */
    "Collection(Tasks.Task)", /* Type */
    NULL, /* Partner */
};

static const EDM_NavigationProperty* _TaskService_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_TaskService_Links_Tasks
};

static const EDM_ComplexType _TaskService_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* Properties */
    0, /* NumProperties */
    _TaskService_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_TaskService_Links_NavigationPropertiesArray)
};

static const char* _TaskService_OverWritePolicy_MembersArray[] =
{
    "Manual",
    "Oldest"
};

static const EDM_EnumType _TaskService_OverWritePolicy =
{
    "OverWritePolicy", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_TaskService_OverWritePolicy_MembersArray,
    OL_ARRAYSIZE(_TaskService_OverWritePolicy_MembersArray)
};

static const EDM_EntityType* _TaskService_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_TaskService_TaskService
};

static const EDM_ComplexType* _TaskService_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_TaskService_Links
};

static const EDM_EnumType* _TaskService_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_TaskService_OverWritePolicy
};

static const EDM_Schema _TaskService_Schema =
{
    "TaskService.0.9.2", /* Namespace */
    "TaskService", /* Alias */
    _TaskService_EntityTypesArray,
    OL_ARRAYSIZE(_TaskService_EntityTypesArray),
    _TaskService_ComplexTypesArray,
    OL_ARRAYSIZE(_TaskService_ComplexTypesArray),
    _TaskService_EnumTypesArray,
    OL_ARRAYSIZE(_TaskService_EnumTypesArray),
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
    &_TaskService_Schema
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

const EDMX_Edmx TaskService_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

