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
    "DMTFExtensions.0.9.2", /* Include.Namespace */
    "DMTF" /* Include.Alias */
};

static const EDMX_Include _0_1_Include =
{
    "Validation.0.9.2", /* Include.Namespace */
    "Validation" /* Include.Alias */
};

static const EDMX_Include* _0_IncludesArray[] =
{
    &_0_0_Include,
    &_0_1_Include
};

static const EDMX_Reference _0_Reference =
{
    "http://dmtf.org/schema/v1/DMTFExtensions", /* Uri */
    _0_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_0_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDMX_Include _1_0_Include =
{
    "Resource.0.9.2", /* Include.Namespace */
    "Resource" /* Include.Alias */
};

static const EDMX_Include* _1_IncludesArray[] =
{
    &_1_0_Include
};

static const EDMX_Reference _1_Reference =
{
    "http://dmtf.org/schema/v1/Resource", /* Uri */
    _1_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_1_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _Messages_MessageRegistry_Language =
{
    0, /* Nullable */
    0, /* Extended */
    "Language", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_MessageRegistry_RegistryPrefix =
{
    0, /* Nullable */
    0, /* Extended */
    "RegistryPrefix", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_MessageRegistry_Version =
{
    0, /* Nullable */
    0, /* Extended */
    "Version", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_MessageRegistry_OwningEntity =
{
    0, /* Nullable */
    0, /* Extended */
    "OwningEntity", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_MessageRegistry_Messages =
{
    0, /* Nullable */
    0, /* Extended */
    "Messages", /* Name */
    "Collection(Messages.MessageProperty)" /* Type */
};

static const EDM_Property* _Messages_MessageRegistry_PropertiesArray[] =
{
    (const EDM_Property*)&_Messages_MessageRegistry_Language,
    (const EDM_Property*)&_Messages_MessageRegistry_RegistryPrefix,
    (const EDM_Property*)&_Messages_MessageRegistry_Version,
    (const EDM_Property*)&_Messages_MessageRegistry_OwningEntity,
    (const EDM_Property*)&_Messages_MessageRegistry_Messages
};

static const EDM_EntityType _Messages_MessageRegistry =
{
    "MessageRegistry", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _Messages_MessageRegistry_PropertiesArray,
    OL_ARRAYSIZE(_Messages_MessageRegistry_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType _Messages_MessageProperty =
{
    "MessageProperty", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* Properties */
    0, /* NumProperties */
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _Messages_Message_Description =
{
    0, /* Nullable */
    0, /* Extended */
    "Description", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_Message_Message =
{
    0, /* Nullable */
    0, /* Extended */
    "Message", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_Message_Severity =
{
    0, /* Nullable */
    0, /* Extended */
    "Severity", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_Message_NumberOfArgs =
{
    0, /* Nullable */
    0, /* Extended */
    "NumberOfArgs", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _Messages_Message_ParamTypes =
{
    1, /* Nullable */
    0, /* Extended */
    "ParamTypes", /* Name */
    "Collection(Messages.ParamType)" /* Type */
};

static const EDM_Property _Messages_Message_Resolution =
{
    0, /* Nullable */
    0, /* Extended */
    "Resolution", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _Messages_Message_PropertiesArray[] =
{
    (const EDM_Property*)&_Messages_Message_Description,
    (const EDM_Property*)&_Messages_Message_Message,
    (const EDM_Property*)&_Messages_Message_Severity,
    (const EDM_Property*)&_Messages_Message_NumberOfArgs,
    (const EDM_Property*)&_Messages_Message_ParamTypes,
    (const EDM_Property*)&_Messages_Message_Resolution
};

static const EDM_ComplexType _Messages_Message =
{
    "Message", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Messages_Message_PropertiesArray,
    OL_ARRAYSIZE(_Messages_Message_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _Messages_ParamType_MembersArray[] =
{
    "string",
    "number"
};

static const EDM_EnumType _Messages_ParamType =
{
    "ParamType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Messages_ParamType_MembersArray,
    OL_ARRAYSIZE(_Messages_ParamType_MembersArray)
};

static const EDM_Property _Messages_SettingsMessage_MessageId =
{
    0, /* Nullable */
    0, /* Extended */
    "MessageId", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_SettingsMessage_MessageArgs =
{
    0, /* Nullable */
    0, /* Extended */
    "MessageArgs", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_Property _Messages_SettingsMessage_Message =
{
    0, /* Nullable */
    0, /* Extended */
    "Message", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Messages_SettingsMessage_PropertiesInError =
{
    0, /* Nullable */
    0, /* Extended */
    "PropertiesInError", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_Property _Messages_SettingsMessage_Severity =
{
    0, /* Nullable */
    0, /* Extended */
    "Severity", /* Name */
    "Resource.Health" /* Type */
};

static const EDM_Property _Messages_SettingsMessage_Resolution =
{
    0, /* Nullable */
    0, /* Extended */
    "Resolution", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _Messages_SettingsMessage_PropertiesArray[] =
{
    (const EDM_Property*)&_Messages_SettingsMessage_MessageId,
    (const EDM_Property*)&_Messages_SettingsMessage_MessageArgs,
    (const EDM_Property*)&_Messages_SettingsMessage_Message,
    (const EDM_Property*)&_Messages_SettingsMessage_PropertiesInError,
    (const EDM_Property*)&_Messages_SettingsMessage_Severity,
    (const EDM_Property*)&_Messages_SettingsMessage_Resolution
};

static const EDM_ComplexType _Messages_SettingsMessage =
{
    "SettingsMessage", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Messages_SettingsMessage_PropertiesArray,
    OL_ARRAYSIZE(_Messages_SettingsMessage_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_EntityType* _Messages_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_Messages_MessageRegistry
};

static const EDM_ComplexType* _Messages_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_Messages_MessageProperty,
    (const EDM_ComplexType*)&_Messages_Message,
    (const EDM_ComplexType*)&_Messages_SettingsMessage
};

static const EDM_EnumType* _Messages_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_Messages_ParamType
};

static const EDM_Schema _Messages_Schema =
{
    "Messages.0.9.2", /* Namespace */
    "Messages", /* Alias */
    _Messages_EntityTypesArray,
    OL_ARRAYSIZE(_Messages_EntityTypesArray),
    _Messages_ComplexTypesArray,
    OL_ARRAYSIZE(_Messages_ComplexTypesArray),
    _Messages_EnumTypesArray,
    OL_ARRAYSIZE(_Messages_EnumTypesArray),
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
    &_Messages_Schema
};

static const EDMX_DataServices _DataServices =
{
    _SchemasArray, /* Schemas */
    OL_ARRAYSIZE(_SchemasArray) /* NumSchemas */
};

static const EDMX_Reference* _ReferencesArray[] =
{
    &_0_Reference,
    &_1_Reference
};

const EDMX_Edmx Messages_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

