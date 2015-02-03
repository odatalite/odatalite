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

static const EDM_Property _Redundancy_Redundancy_Oem =
{
    0, /* Nullable */
    0, /* Extended */
    "Oem", /* Name */
    "Resource.Oem" /* Type */
};

static const EDM_Property _Redundancy_Redundancy_ActiveCorrelatableIDs =
{
    1, /* Nullable */
    0, /* Extended */
    "ActiveCorrelatableIDs", /* Name */
    "Collection(Edm.String)" /* Type */
};

static const EDM_Property _Redundancy_Redundancy_Name =
{
    0, /* Nullable */
    0, /* Extended */
    "Name", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _Redundancy_Redundancy_Mode =
{
    1, /* Nullable */
    0, /* Extended */
    "Mode", /* Name */
    "Collection(Redundancy.RedundancyMode)" /* Type */
};

static const EDM_Property _Redundancy_Redundancy_MaxNumSupported =
{
    1, /* Nullable */
    0, /* Extended */
    "MaxNumSupported", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _Redundancy_Redundancy_MinNumNeeded =
{
    1, /* Nullable */
    0, /* Extended */
    "MinNumNeeded", /* Name */
    "Edm.Int64" /* Type */
};

static const EDM_Property _Redundancy_Redundancy_Status =
{
    0, /* Nullable */
    0, /* Extended */
    "Status", /* Name */
    "Resource.Status" /* Type */
};

static const EDM_Property* _Redundancy_Redundancy_PropertiesArray[] =
{
    (const EDM_Property*)&_Redundancy_Redundancy_Oem,
    (const EDM_Property*)&_Redundancy_Redundancy_ActiveCorrelatableIDs,
    (const EDM_Property*)&_Redundancy_Redundancy_Name,
    (const EDM_Property*)&_Redundancy_Redundancy_Mode,
    (const EDM_Property*)&_Redundancy_Redundancy_MaxNumSupported,
    (const EDM_Property*)&_Redundancy_Redundancy_MinNumNeeded,
    (const EDM_Property*)&_Redundancy_Redundancy_Status
};

static const EDM_ComplexType _Redundancy_Redundancy =
{
    "Redundancy", /* Name */
    NULL, /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    _Redundancy_Redundancy_PropertiesArray,
    OL_ARRAYSIZE(_Redundancy_Redundancy_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _Redundancy_RedundancyMode_MembersArray[] =
{
    "Failover",
    "N+1",
    "LoadBalanced",
    "Sparing",
    "LimitedSparing"
};

static const EDM_EnumType _Redundancy_RedundancyMode =
{
    "RedundancyMode", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_Redundancy_RedundancyMode_MembersArray,
    OL_ARRAYSIZE(_Redundancy_RedundancyMode_MembersArray)
};

static const EDM_ComplexType* _Redundancy_ComplexTypesArray[] =
{
    (const EDM_ComplexType*)&_Redundancy_Redundancy
};

static const EDM_EnumType* _Redundancy_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_Redundancy_RedundancyMode
};

static const EDM_Schema _Redundancy_Schema =
{
    "Redundancy.0.9.2", /* Namespace */
    "Redundancy", /* Alias */
    NULL, /* EntityTypes */
    0, /* NumEntityTypes */
    _Redundancy_ComplexTypesArray,
    OL_ARRAYSIZE(_Redundancy_ComplexTypesArray),
    _Redundancy_EnumTypesArray,
    OL_ARRAYSIZE(_Redundancy_EnumTypesArray),
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
    &_Redundancy_Schema
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

const EDMX_Edmx Redundancy_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

