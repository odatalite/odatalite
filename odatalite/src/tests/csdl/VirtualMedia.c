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

static const EDM_Property _VirtualMedia_VirtualMedia_ImageName =
{
    1, /* Nullable */
    0, /* Extended */
    "ImageName", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _VirtualMedia_VirtualMedia_Image =
{
    1, /* Nullable */
    0, /* Extended */
    "Image", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Property _VirtualMedia_VirtualMedia_MediaTypes =
{
    0, /* Nullable */
    0, /* Extended */
    "MediaTypes", /* Name */
    "Collection(VirtualMedia.MediaType)" /* Type */
};

static const EDM_Property _VirtualMedia_VirtualMedia_ConnectedVia =
{
    1, /* Nullable */
    0, /* Extended */
    "ConnectedVia", /* Name */
    "VirtualMedia.ConnectedVia" /* Type */
};

static const EDM_Property _VirtualMedia_VirtualMedia_Inserted =
{
    1, /* Nullable */
    0, /* Extended */
    "Inserted", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property _VirtualMedia_VirtualMedia_WriteProtected =
{
    1, /* Nullable */
    0, /* Extended */
    "WriteProtected", /* Name */
    "Edm.Boolean" /* Type */
};

static const EDM_Property* _VirtualMedia_VirtualMedia_PropertiesArray[] =
{
    (const EDM_Property*)&_VirtualMedia_VirtualMedia_ImageName,
    (const EDM_Property*)&_VirtualMedia_VirtualMedia_Image,
    (const EDM_Property*)&_VirtualMedia_VirtualMedia_MediaTypes,
    (const EDM_Property*)&_VirtualMedia_VirtualMedia_ConnectedVia,
    (const EDM_Property*)&_VirtualMedia_VirtualMedia_Inserted,
    (const EDM_Property*)&_VirtualMedia_VirtualMedia_WriteProtected
};

static const EDM_EntityType _VirtualMedia_VirtualMedia =
{
    "VirtualMedia", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _VirtualMedia_VirtualMedia_PropertiesArray,
    OL_ARRAYSIZE(_VirtualMedia_VirtualMedia_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _VirtualMedia_MediaType_MembersArray[] =
{
    "CD",
    "Floppy",
    "USBStick",
    "DVD"
};

static const EDM_EnumType _VirtualMedia_MediaType =
{
    "MediaType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_VirtualMedia_MediaType_MembersArray,
    OL_ARRAYSIZE(_VirtualMedia_MediaType_MembersArray)
};

static const char* _VirtualMedia_ConnectedVia_MembersArray[] =
{
    "NotConnected",
    "URI",
    "Applet"
};

static const EDM_EnumType _VirtualMedia_ConnectedVia =
{
    "ConnectedVia", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_VirtualMedia_ConnectedVia_MembersArray,
    OL_ARRAYSIZE(_VirtualMedia_ConnectedVia_MembersArray)
};

static const EDM_EntityType* _VirtualMedia_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_VirtualMedia_VirtualMedia
};

static const EDM_EnumType* _VirtualMedia_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_VirtualMedia_MediaType,
    (const EDM_EnumType*)&_VirtualMedia_ConnectedVia
};

static const EDM_Schema _VirtualMedia_Schema =
{
    "VirtualMedia.0.9.2", /* Namespace */
    "VirtualMedia", /* Alias */
    _VirtualMedia_EntityTypesArray,
    OL_ARRAYSIZE(_VirtualMedia_EntityTypesArray),
    NULL, /* ComplexTypes */
    0, /* NumComplexTypes */
    _VirtualMedia_EnumTypesArray,
    OL_ARRAYSIZE(_VirtualMedia_EnumTypesArray),
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
    &_VirtualMedia_Schema
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

const EDMX_Edmx VirtualMedia_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

