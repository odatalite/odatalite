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
    "ManagerAccount.0.9.2", /* Include.Namespace */
    "ManagerAccount" /* Include.Alias */
};

static const EDMX_Include* _3_IncludesArray[] =
{
    &_3_0_Include
};

static const EDMX_Reference _3_Reference =
{
    "http://dmtf.org/schema/v1/ManagerAccount", /* Uri */
    _3_IncludesArray, /* Includes */
    OL_ARRAYSIZE(_3_IncludesArray), /* NumIncludes */
    NULL, /* NumIncludeAnnotations */
    0 /* NumIncludeAnnotations */
};

static const EDM_Property _AccountService_AccountService_AuthFailureLoggingThreshold =
{
    0, /* Nullable */
    0, /* Extended */
    "AuthFailureLoggingThreshold", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _AccountService_AccountService_MinPasswordLength =
{
    0, /* Nullable */
    0, /* Extended */
    "MinPasswordLength", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _AccountService_AccountService_Links =
{
    0, /* Nullable */
    0, /* Extended */
    "Links", /* Name */
    "AccountService.Links" /* Type */
};

static const EDM_Property* _AccountService_AccountService_PropertiesArray[] =
{
    (const EDM_Property*)&_AccountService_AccountService_AuthFailureLoggingThreshold,
    (const EDM_Property*)&_AccountService_AccountService_MinPasswordLength,
    (const EDM_Property*)&_AccountService_AccountService_Links
};

static const EDM_EntityType _AccountService_AccountService =
{
    "AccountService", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _AccountService_AccountService_PropertiesArray,
    OL_ARRAYSIZE(_AccountService_AccountService_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_NavigationProperty _AccountService_Links_Accounts =
{
    EDM_NavigationProperty_Flags_Nullable, /* Flags */
    "Accounts", /* Name */
    "Collection(ManagerAccount.ManagerAccount)", /* Type */
    NULL, /* Partner */
};

static const EDM_Property _AccountService_Links_Oem =
{
    1, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property* _AccountService_Links_PropertiesArray[] =
{
    (const EDM_Property*)&_AccountService_Links_Oem
};

static const EDM_NavigationProperty* _AccountService_Links_NavigationPropertiesArray[] =
{
    (const EDM_NavigationProperty*)&_AccountService_Links_Accounts
};

static const EDM_ComplexType _AccountService_Links =
{
    "Links", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _AccountService_Links_PropertiesArray,
    OL_ARRAYSIZE(_AccountService_Links_PropertiesArray),
    _AccountService_Links_NavigationPropertiesArray,
    OL_ARRAYSIZE(_AccountService_Links_NavigationPropertiesArray)
};

static const EDM_EntityType* _AccountService_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_AccountService_AccountService
};

static const EDM_ComplexType* _AccountService_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_AccountService_Links
};

static const EDM_Schema _AccountService_Schema =
{
    "AccountService.0.9.2", /* Namespace */
    "AccountService", /* Alias */
    _AccountService_EntityTypesArray,
    OL_ARRAYSIZE(_AccountService_EntityTypesArray),
    _AccountService_ComplexTypesArray,
    OL_ARRAYSIZE(_AccountService_ComplexTypesArray),
    NULL, /* EnumTypes */
    0, /* NumEnumTypes */
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
    &_AccountService_Schema
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

const EDMX_Edmx AccountService_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

