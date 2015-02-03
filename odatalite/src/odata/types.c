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
#include "types.h"

/*
**==============================================================================
**
** _typeNames[]
**
**==============================================================================
*/

const char* __typeNames[] =
{
    "\004Null"+1,
    "\007Boolean"+1,
    "\007Integer"+1,
    "\004Real"+1,
    "\006String"+1,
    "\006Object"+1,
    "\005Array"+1
};

/*
**==============================================================================
**
** __valueSizes[]
**
**==============================================================================
*/

unsigned char __valueSizes[] =
{
    0,
    offsetof(JSON_Value, u.boolean) + sizeof(JSON_Boolean),
    offsetof(JSON_Value, u.integer) + sizeof(JSON_Integer),
    offsetof(JSON_Value, u.real) + sizeof(JSON_Real),
    offsetof(JSON_Value, u.string) + sizeof(JSON_String),
    offsetof(JSON_Value, u.object) + sizeof(JSON_Object),
    offsetof(JSON_Value, u.array) + sizeof(JSON_Array)
};

/*
**==============================================================================
**
** __odataTypeNames[]
**
**==============================================================================
*/

const char* __odataTypeNames[21] =
{
    "\004Null"+1,
    "\007Boolean"+1,
    "\005Int64"+1,
    "\006Double"+1,
    "\006String"+1,
    "\006Object"+1,
    "\005Array"+1,
    "\004Byte"+1,
    "\005SByte"+1,
    "\005Int16"+1,
    "\005Int32"+1,
    "\006Single"+1,
    "\007Decimal"+1,
    "\006Binary"+1,
    "\004Date"+1,
    "\011TimeOfDay"+1,
    "\016DateTimeOffset"+1,
    "\010Duration"+1,
    "\004Guid"+1,
    "\016NavigationLink"+1,
    "\017AssociationLink"+1
};

/*
**==============================================================================
**
** __odataTypeSizes[]
**
**==============================================================================
*/

unsigned char __odataTypeSizes[] =
{
    0,
    sizeof(OL_Boolean),
    sizeof(OL_Int64),
    sizeof(OL_Double),
    sizeof(OL_String),
    sizeof(OL_Object),
    sizeof(OL_Array),
    sizeof(OL_Byte),
    sizeof(OL_SByte),
    sizeof(OL_Int16),
    sizeof(OL_Int32),
    sizeof(OL_Single),
    sizeof(OL_Decimal),
    sizeof(OL_Binary),
    sizeof(OL_Date),
    sizeof(OL_TimeOfDay),
    sizeof(OL_DateTimeOffset),
    sizeof(OL_Duration),
    sizeof(OL_Guid),
    sizeof(OL_NavigationLink),
    sizeof(OL_AssociationLink)
};

