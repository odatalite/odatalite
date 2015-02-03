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
    "LogEntry.0.9.2", /* Include.Namespace */
    "LogEntry" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/LogEntry", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _LogService_LogService_MaxNumberOfRecords =
{
    0, /* Nullable */
    0, /* Extended */
    "MaxNumberOfRecords", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _LogService_LogService_OverWritePolicy =
{
    0, /* Nullable */
    0, /* Extended */
    "OverWritePolicy", /* Name */
    "LogService.OverWritePolicy" /* Type */
};

static const EDM_Property _LogService_LogService_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "LogService.Links" /* Type */
};

static const EDM_Property _LogService_LogService_Actions =
{
    0, /* Nullable */
    0, /* Extended */
    "Actions", /* Name */
    "LogService.Actions" /* Type */
};

static const EDM_Property* _LogService_LogService_PropertiesArray[] =
{
    (const EDM_Property*)&_LogService_LogService_MaxNumberOfRecords,
    (const EDM_Property*)&_LogService_LogService_OverWritePolicy,
    (const EDM_Property*)&_LogService_LogService_Links,
    (const EDM_Property*)&_LogService_LogService_Actions
};

static const EDM_EntityType _LogService_LogService =
{
    "LogService", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _LogService_LogService_PropertiesArray,
    OL_ARRAYSIZE(_LogService_LogService_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_Property _LogService_Actions_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "LogService.OemActions" /* Type */
};

static const EDM_Property* _LogService_Actions_PropertiesArray[] =
{
    (const EDM_Property*)&_LogService_Actions_Oem
};

static const EDM_ComplexType _LogService_Actions =
{
    "Actions", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _LogService_Actions_PropertiesArray,
    OL_ARRAYSIZE(_LogService_Actions_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType _LogService_OemActions =
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

static const EDM_NavigationProperty _LogService_Links_Entries =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Entries", /* Name */
    "Collection(LogEntry.LogEntry)", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _LogService_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _LogService_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_LogService_Links_Oem
};

static const EDM_NavigationProperty* _LogService_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_LogService_Links_Entries
};

static const EDM_ComplexType _LogService_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _LogService_Links_PropertiesArray,
    OL_ARRAYSIZE(_LogService_Links_PropertiesArray),
    _LogService_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_LogService_Links_NavigationPropertiesArray)
};

static const char* _LogService_OverWritePolicy_MembersArray[] =
{
    "Unknown",
    "WrapsWhenFull",
    "NeverOverWrites"
};

static const EDM_EnumType _LogService_OverWritePolicy =
{
    "OverWritePolicy", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_LogService_OverWritePolicy_MembersArray,
    OL_ARRAYSIZE(_LogService_OverWritePolicy_MembersArray)
};

static const EDM_Parameter _LogService_ClearLog_LogService =
{
    "LogService", /* Name */
    "LogService.Actions", /* Type */
    NULL /* Nullable */
};

static const EDM_Parameter* _LogService_ClearLog_ParametersArray[] =
{
    (const EDM_Parameter*)&_LogService_ClearLog_LogService
};

static const EDM_Action _LogService_ClearLog =
{
    "ClearLog", /* Name */
    "true", /* IsBound */
    NULL, /* EntitySetPath */
    _LogService_ClearLog_ParametersArray,
    OL_ARRAYSIZE(_LogService_ClearLog_ParametersArray),
};

static const EDM_EntityType* _LogService_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_LogService_LogService
};

static const EDM_ComplexType* _LogService_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_LogService_Actions,
    (const EDM_ComplexType*)&_LogService_OemActions,
    (const EDM_ComplexType*)&_LogService_Links
};

static const EDM_EnumType* _LogService_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_LogService_OverWritePolicy
};

static const EDM_Action* _LogService_ActionsArray[] =
{
    (const EDM_Action*)&_LogService_ClearLog
};

static const EDM_Schema _LogService_Schema =
{
    "LogService.0.9.2", /* Namespace */
    "LogService", /* Alias */
    _LogService_EntityTypesArray,
    OL_ARRAYSIZE(_LogService_EntityTypesArray),
    _LogService_ComplexTypesArray,
    OL_ARRAYSIZE(_LogService_ComplexTypesArray),
    _LogService_EnumTypesArray,
    OL_ARRAYSIZE(_LogService_EnumTypesArray),
    _LogService_ActionsArray,
    OL_ARRAYSIZE(_LogService_ActionsArray),
    NULL, /* TypeDefinitions */
    0, /* NumTypeDefinitions */
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    NULL, /* Terms */
    0 /* NumTerms */
};

static const EDM_Schema* _SchemasArray[] =
{
    &_LogService_Schema
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

const EDMX_Edmx LogService_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

