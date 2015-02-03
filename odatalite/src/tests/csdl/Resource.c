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
    "Messages.0.9.2", /* Include.Namespace */
    "Messages" /* Include.Alias */
};

static const EDMX_Include* _2_IncludesArray[] =
{
    &_2_0_Include
};

static const EDMX_Reference _2_Reference =
{
    "http://dmtf.org/schema/v1/Messages", /* Uri */
    _2_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_2_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Key _Resource_Resource_Key =
{
    {
        "Id", /* PropertyRef.Name */
        NULL, /* PropertyRef.Alias */
    }
};

static const EDM_Property _Resource_Resource_Id =
{
    0, /* Nullable */
    0, /* Extended */
    "Id", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Resource_Resource_Description =
{
    1, /* Nullable */
    0, /* Extended */
    "Description", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Resource_Resource_Name =
{
    0, /* Nullable */
    0, /* Extended */
    "Name", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Resource_Resource_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property _Resource_Resource_Modified =
{
    0, /* Nullable */
    0, /* Extended */
    "Modified", /* Name */
    "Edm.DateTimeOffset" /* Type */
};

static const EDM_Property _Resource_Resource_Status =
{
    1, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property* _Resource_Resource_PropertiesArray[] =
{
    (const EDM_Property*)&_Resource_Resource_Id,
    (const EDM_Property*)&_Resource_Resource_Description,
    (const EDM_Property*)&_Resource_Resource_Name,
    (const EDM_Property*)&_Resource_Resource_Oem,
    (const EDM_Property*)&_Resource_Resource_Modified,
    (const EDM_Property*)&_Resource_Resource_Status
};

static const EDM_EntityType _Resource_Resource =
{
    "Resource", /* Name */
    NULL, /* BaseType */
    "true", /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    &_Resource_Resource_Key, /* Key */
    _Resource_Resource_PropertiesArray,
    OL_ARRAYSIZE(_Resource_Resource_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType _Resource_Oem =
{
    "Oem", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* Properties */
    0, /* NumProperties */
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _Resource_Status_State =
{
    1, /* Nullable */
    0, /* Extended */
    "State", /* Name */
    "Resource.State" /* Type */
};

static const EDM_Property _Resource_Status_HealthRollup =
{
    1, /* Nullable */
    0, /* Extended */
    "HealthRollup", /* Name */
    "Resource.Health" /* Type */
};

static const EDM_Property _Resource_Status_Health =
{
    1, /* Nullable */
    0, /* Extended */
    "Health", /* Name */
    "Resource.Health" /* Type */
};

static const EDM_Property _Resource_Status_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _Resource_Status_PropertiesArray[] =
{
    (const EDM_Property*)&_Resource_Status_State,
    (const EDM_Property*)&_Resource_Status_HealthRollup,
    (const EDM_Property*)&_Resource_Status_Health,
    (const EDM_Property*)&_Resource_Status_Oem
};

static const EDM_ComplexType _Resource_Status =
{
    "Status", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Resource_Status_PropertiesArray,
    OL_ARRAYSIZE(_Resource_Status_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _Resource_State_MembersArray[] =
{
    "Enabled",
    "Disabled",
    "Offline",
    "InTest",
    "Starting",
    "Absent"
};

static const EDM_EnumType _Resource_State =
{
    "State", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Resource_State_MembersArray,
    OL_ARRAYSIZE(_Resource_State_MembersArray)
};

static const char* _Resource_Health_MembersArray[] =
{
    "OK",
    "Warning",
    "Critical"
};

static const EDM_EnumType _Resource_Health =
{
    "Health", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Resource_Health_MembersArray,
    OL_ARRAYSIZE(_Resource_Health_MembersArray)
};

static const EDM_TypeDefinition _Resource_SettingsRef =
{
    "SettingsRef", /* Name */
    "Edm.String" /* UnderlyingType */
};

static const EDM_Property _Resource_Settings_href =
{
    0, /* Nullable */
    0, /* Extended */
    "href", /* Name */
    "Resource.SettingsRef" /* Type */
};

static const EDM_Property* _Resource_Settings_PropertiesArray[] =
{
    (const EDM_Property*)&_Resource_Settings_href
};

static const EDM_ComplexType _Resource_Settings =
{
    "Settings", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Resource_Settings_PropertiesArray,
    OL_ARRAYSIZE(_Resource_Settings_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _Resource_SettingsResult_Operation =
{
    0, /* Nullable */
    0, /* Extended */
    "Operation", /* Name */
    "Resource.SettingsOperation" /* Type */
};

static const EDM_Property _Resource_SettingsResult_Time =
{
    1, /* Nullable */
    0, /* Extended */
    "Time", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Resource_SettingsResult_ETag =
{
    1, /* Nullable */
    0, /* Extended */
    "ETag", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Resource_SettingsResult_Messages =
{
    1, /* Nullable */
    0, /* Extended */
    "Messages", /* Name */
    "Collection(Messages.SettingsMessage)" /* Type */
};

static const EDM_Property* _Resource_SettingsResult_PropertiesArray[] =
{
    (const EDM_Property*)&_Resource_SettingsResult_Operation,
    (const EDM_Property*)&_Resource_SettingsResult_Time,
    (const EDM_Property*)&_Resource_SettingsResult_ETag,
    (const EDM_Property*)&_Resource_SettingsResult_Messages
};

static const EDM_ComplexType _Resource_SettingsResult =
{
    "SettingsResult", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Resource_SettingsResult_PropertiesArray,
    OL_ARRAYSIZE(_Resource_SettingsResult_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _Resource_SettingsOperation_MembersArray[] =
{
    "SettingsApply"
};

static const EDM_EnumType _Resource_SettingsOperation =
{
    "SettingsOperation", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Resource_SettingsOperation_MembersArray,
    OL_ARRAYSIZE(_Resource_SettingsOperation_MembersArray)
};

static const EDM_EntityType* _Resource_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_Resource_Resource
};

static const EDM_ComplexType* _Resource_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_Resource_Oem,
    (const EDM_ComplexType*)&_Resource_Status,
    (const EDM_ComplexType*)&_Resource_Settings,
    (const EDM_ComplexType*)&_Resource_SettingsResult
};

static const EDM_EnumType* _Resource_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_Resource_State,
    (const EDM_EnumType*)&_Resource_Health,
    (const EDM_EnumType*)&_Resource_SettingsOperation
};

static const EDM_TypeDefinition* _Resource_TypeDefinitionsArray[] =
{
    (const EDM_TypeDefinition*)&_Resource_SettingsRef
};

static const EDM_Schema _Resource_Schema =
{
    "Resource.0.9.2", /* Namespace */
    "Resource", /* Alias */
    _Resource_EntityTypesArray,
    OL_ARRAYSIZE(_Resource_EntityTypesArray),
    _Resource_ComplexTypesArray,
    OL_ARRAYSIZE(_Resource_ComplexTypesArray),
    _Resource_EnumTypesArray,
    OL_ARRAYSIZE(_Resource_EnumTypesArray),
    NULL, /* Actions */
    0, /* NumActions */
    _Resource_TypeDefinitionsArray,
    OL_ARRAYSIZE(_Resource_TypeDefinitionsArray),
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_Resource_Schema
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

const EDMX_Edmx Resource_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

