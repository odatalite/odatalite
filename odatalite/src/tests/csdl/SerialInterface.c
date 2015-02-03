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

static const EDM_Property _SerialInterface_SerialInterface_SignalType =
{
    0, /* Nullable */
    0, /* Extended */
    "SignalType", /* Name */
    "SerialInterface.SignalType" /* Type */
};

static const EDM_Property _SerialInterface_SerialInterface_BitRate =
{
    0, /* Nullable */
    0, /* Extended */
    "BitRate", /* Name */
    "SerialInterface.BitRate" /* Type */
};

static const EDM_Property _SerialInterface_SerialInterface_Parity =
{
    0, /* Nullable */
    0, /* Extended */
    "Parity", /* Name */
    "SerialInterface.Parity" /* Type */
};

static const EDM_Property _SerialInterface_SerialInterface_DataBits =
{
    0, /* Nullable */
    0, /* Extended */
    "DataBits", /* Name */
    "SerialInterface.DataBits" /* Type */
};

static const EDM_Property _SerialInterface_SerialInterface_StopBits =
{
    0, /* Nullable */
    0, /* Extended */
    "StopBits", /* Name */
    "SerialInterface.StopBits" /* Type */
};

static const EDM_Property _SerialInterface_SerialInterface_FlowControl =
{
    0, /* Nullable */
    0, /* Extended */
    "FlowControl", /* Name */
    "SerialInterface.FlowControl" /* Type */
};

static const EDM_Property _SerialInterface_SerialInterface_PinOut =
{
    1, /* Nullable */
    0, /* Extended */
    "PinOut", /* Name */
    "SerialInterface.PinOut" /* Type */
};

static const EDM_Property* _SerialInterface_SerialInterface_PropertiesArray[] =
{
    (const EDM_Property*)&_SerialInterface_SerialInterface_SignalType,
    (const EDM_Property*)&_SerialInterface_SerialInterface_BitRate,
    (const EDM_Property*)&_SerialInterface_SerialInterface_Parity,
    (const EDM_Property*)&_SerialInterface_SerialInterface_DataBits,
    (const EDM_Property*)&_SerialInterface_SerialInterface_StopBits,
    (const EDM_Property*)&_SerialInterface_SerialInterface_FlowControl,
    (const EDM_Property*)&_SerialInterface_SerialInterface_PinOut
};

static const EDM_EntityType _SerialInterface_SerialInterface =
{
    "SerialInterface", /* Name */
    "Resource.Resource", /* BaseType */
    NULL, /* Abstract */
    NULL, /* OpenType */
    NULL, /* HasStream */
    NULL, /* Key */
    _SerialInterface_SerialInterface_PropertiesArray,
    OL_ARRAYSIZE(_SerialInterface_SerialInterface_PropertiesArray),
    NULL, /* NavigationProperties */
    0 /* NumNavigationProperties */
};

static const char* _SerialInterface_SignalType_MembersArray[] =
{
    "Rs232",
    "Rs485"
};

static const EDM_EnumType _SerialInterface_SignalType =
{
    "SignalType", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_SerialInterface_SignalType_MembersArray,
    OL_ARRAYSIZE(_SerialInterface_SignalType_MembersArray)
};

static const char* _SerialInterface_BitRate_MembersArray[] =
{
    "1200",
    "2400",
    "4800",
    "9600",
    "19200",
    "38400",
    "57600",
    "115200",
    "230400"
};

static const EDM_EnumType _SerialInterface_BitRate =
{
    "BitRate", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_SerialInterface_BitRate_MembersArray,
    OL_ARRAYSIZE(_SerialInterface_BitRate_MembersArray)
};

static const char* _SerialInterface_Parity_MembersArray[] =
{
    "None",
    "Even",
    "Odd",
    "Mark",
    "Space"
};

static const EDM_EnumType _SerialInterface_Parity =
{
    "Parity", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_SerialInterface_Parity_MembersArray,
    OL_ARRAYSIZE(_SerialInterface_Parity_MembersArray)
};

static const char* _SerialInterface_DataBits_MembersArray[] =
{
    "5",
    "6",
    "7",
    "8"
};

static const EDM_EnumType _SerialInterface_DataBits =
{
    "DataBits", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_SerialInterface_DataBits_MembersArray,
    OL_ARRAYSIZE(_SerialInterface_DataBits_MembersArray)
};

static const char* _SerialInterface_StopBits_MembersArray[] =
{
    "1",
    "2"
};

static const EDM_EnumType _SerialInterface_StopBits =
{
    "StopBits", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_SerialInterface_StopBits_MembersArray,
    OL_ARRAYSIZE(_SerialInterface_StopBits_MembersArray)
};

static const char* _SerialInterface_FlowControl_MembersArray[] =
{
    "None",
    "Software",
    "Hardware"
};

static const EDM_EnumType _SerialInterface_FlowControl =
{
    "FlowControl", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_SerialInterface_FlowControl_MembersArray,
    OL_ARRAYSIZE(_SerialInterface_FlowControl_MembersArray)
};

static const char* _SerialInterface_PinOut_MembersArray[] =
{
    "Cisco",
    "Cyclades",
    "Digi"
};

static const EDM_EnumType _SerialInterface_PinOut =
{
    "PinOut", /* Name */
    NULL, /* UnderlyingType */
    NULL, /* IsFlags */
    EDM_MemberType_String,
    (const void** const)_SerialInterface_PinOut_MembersArray,
    OL_ARRAYSIZE(_SerialInterface_PinOut_MembersArray)
};

static const EDM_EntityType* _SerialInterface_EntityTypesArray[] =
{
    (const EDM_EntityType*)&_SerialInterface_SerialInterface
};

static const EDM_EnumType* _SerialInterface_EnumTypesArray[] =
{
    (const EDM_EnumType*)&_SerialInterface_SignalType,
    (const EDM_EnumType*)&_SerialInterface_BitRate,
    (const EDM_EnumType*)&_SerialInterface_Parity,
    (const EDM_EnumType*)&_SerialInterface_DataBits,
    (const EDM_EnumType*)&_SerialInterface_StopBits,
    (const EDM_EnumType*)&_SerialInterface_FlowControl,
    (const EDM_EnumType*)&_SerialInterface_PinOut
};

static const EDM_Schema _SerialInterface_Schema =
{
    "SerialInterface.0.9.2", /* Namespace */
    "SerialInterface", /* Alias */
    _SerialInterface_EntityTypesArray,
    OL_ARRAYSIZE(_SerialInterface_EntityTypesArray),
    NULL, /* ComplexTypes */
    0, /* NumComplexTypes */
    _SerialInterface_EnumTypesArray,
    OL_ARRAYSIZE(_SerialInterface_EnumTypesArray),
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
    &_SerialInterface_Schema
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

const EDMX_Edmx SerialInterface_Edmx =
{
    _ReferencesArray, /* References */
    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */
    &_DataServices
};

