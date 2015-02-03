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

static const EDM_Term _Extensions_AllowableValues =
{
    1, /* Nullable */
    0, /* Extended */
    "AllowableValues", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_ExtendedTerm _Extensions_Required =
{
    1, /* Nullable */
    1, /* Extended */
    "Required", /* Name */
    "Edm.Boolean", /* Type */
    NULL, /* BaseTerm */
    NULL, /* AppliesTo */
    "True", /* DefaultValue */
    NULL, /* MaxLength */
    NULL, /* Precision */
    NULL, /* Scale */
    NULL /* SRID */
};

static const EDM_Term _Extensions_InlineError =
{
    1, /* Nullable */
    0, /* Extended */
    "InlineError", /* Name */
    "Edm.Entity" /* Type */
};

static const EDM_ExtendedTerm _Extensions_ExpandReferences =
{
    1, /* Nullable */
    1, /* Extended */
    "ExpandReferences", /* Name */
    "Edm.Boolean", /* Type */
    NULL, /* BaseTerm */
    NULL, /* AppliesTo */
    "True", /* DefaultValue */
    NULL, /* MaxLength */
    NULL, /* Precision */
    NULL, /* Scale */
    NULL /* SRID */
};

static const EDM_ExtendedTerm _Extensions_IPv6Format =
{
    1, /* Nullable */
    1, /* Extended */
    "IPv6Format", /* Name */
    "Edm.Boolean", /* Type */
    NULL, /* BaseTerm */
    NULL, /* AppliesTo */
    "true", /* DefaultValue */
    NULL, /* MaxLength */
    NULL, /* Precision */
    NULL, /* Scale */
    NULL /* SRID */
};

static const EDM_Term _Extensions_DynamicPropertyPatterns =
{
    1, /* Nullable */
    0, /* Extended */
    "DynamicPropertyPatterns", /* Name */
    "Collection(Extensions.PropertyPattern)" /* Type */
};

static const EDM_Property _Extensions_PropertyPattern_Pattern =
{
    1, /* Nullable */
    0, /* Extended */
    "Pattern", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Extensions_PropertyPattern_Type =
{
    1, /* Nullable */
    0, /* Extended */
    "Type", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property* _Extensions_PropertyPattern_PropertiesArray[] =
{
    (const EDM_Property*)&_Extensions_PropertyPattern_Pattern,
    (const EDM_Property*)&_Extensions_PropertyPattern_Type
};

static const EDM_ComplexType _Extensions_PropertyPattern =
{
    "PropertyPattern", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Extensions_PropertyPattern_PropertiesArray,
    OL_ARRAYSIZE(_Extensions_PropertyPattern_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const EDM_ComplexType* _Extensions_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_Extensions_PropertyPattern
};

static const EDM_Term* _Extensions_TermsArray[] =
{
    (const EDM_Term*)&_Extensions_AllowableValues,
    (const EDM_Term*)&_Extensions_Required,
    (const EDM_Term*)&_Extensions_InlineError,
    (const EDM_Term*)&_Extensions_ExpandReferences,
    (const EDM_Term*)&_Extensions_IPv6Format,
    (const EDM_Term*)&_Extensions_DynamicPropertyPatterns
};

static const EDM_Schema _Extensions_Schema =
{
    "DMTFExtensions.0.9.2", /* Namespace */
    "Extensions", /* Alias */
    NULL, /* EntityTypes */
    0, /* NumEntityTypes */
    _Extensions_ComplexTypesArray,
    OL_ARRAYSIZE(_Extensions_ComplexTypesArray),
    NULL, /* EnumTypes */
    0, /* NumEnumTypes */
    NULL, /* Actions */
    0, /* NumActions */
    NULL, /* TypeDefinitions */
    0, /* NumTypeDefinitions */
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    _Extensions_TermsArray,
    OL_ARRAYSIZE(_Extensions_TermsArray)
};

static const EDM_Term _Validation_Pattern =
{
    1, /* Nullable */
    0, /* Extended */
    "Pattern", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Term _Validation_Minimum =
{
    1, /* Nullable */
    0, /* Extended */
    "Minimum", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Term _Validation_Maximum =
{
    1, /* Nullable */
    0, /* Extended */
    "Maximum", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Term* _Validation_TermsArray[] =
{
    (const EDM_Term*)&_Validation_Pattern,
    (const EDM_Term*)&_Validation_Minimum,
    (const EDM_Term*)&_Validation_Maximum
};

static const EDM_Schema _Validation_Schema =
{
    "Validation.0.9.2", /* Namespace */
    NULL, /* Alias */
    NULL, /* EntityTypes */
    0, /* NumEntityTypes */
    NULL, /* ComplexTypes */
    0, /* NumComplexTypes */
    NULL, /* EnumTypes */
    0, /* NumEnumTypes */
    NULL, /* Actions */
    0, /* NumActions */
    NULL, /* TypeDefinitions */
    0, /* NumTypeDefinitions */
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    _Validation_TermsArray,
    OL_ARRAYSIZE(_Validation_TermsArray)
};

static const EDM_Schema* _SchemasArray[] =
{
    &_Extensions_Schema,
    &_Validation_Schema
};

static const EDMX_DataServices _DataServices =
{
    _SchemasArray, /* Schemas */
    OL_ARRAYSIZE(_SchemasArray) /* NumSchemas */
};

static const EDMX_Reference* _ReferencesArray[] =
{
    &_0_Reference
};

const EDMX_Edmx DMTFExtensions_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

