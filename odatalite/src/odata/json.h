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
#ifndef _json_h
#define _json_h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "odata.h"

/*
**==============================================================================
**
** JSON Flags
**
**==============================================================================
*/

#define JSON_FLAG_STATIC_NAME           (1 << 0)
#define JSON_FLAG_LENGTH_NAME           (1 << 1)
#define JSON_FLAG_STATIC_VALUE          (1 << 2)
#define JSON_FLAG_GET_AS_TYPE           (1 << 3)
#define JSON_FLAG_ALLOW_DUPLICATES      (1 << 4)
#define JSON_FLAG_HOMOGENEOUS_ARRAY     (1 << 5)

/*
**==============================================================================
**
** enum JSON_Type
**
**==============================================================================
*/

typedef enum _JSON_Type
{
    JSON_Type_Null,
    JSON_Type_Boolean,
    JSON_Type_Integer,
    JSON_Type_Real,
    JSON_Type_String,
    JSON_Type_Object,
    JSON_Type_Array
}
JSON_Type;

/*
**==============================================================================
**
** JSON data Types
**
**==============================================================================
*/

#define JSON_TRUE ((JSON_Boolean)1)
#define JSON_FALSE ((JSON_Boolean)0)

typedef unsigned char JSON_Null;

typedef unsigned char JSON_Boolean;

typedef signed long long JSON_Integer;

typedef double JSON_Real;

typedef char JSON_Char;

typedef JSON_Char* JSON_String;

typedef const JSON_Char* JSON_ConstString;

typedef struct _JSON_Object JSON_Object;

typedef struct _JSON_Array JSON_Array;

typedef struct _JSON_Value JSON_Value;

/*
**==============================================================================
**
** JSON_Union
**
**==============================================================================
*/

typedef union _JSON_Union
{
    unsigned char boolean;
    signed long long integer;
    double real;
    JSON_Char* string;
    JSON_Object* object;
    JSON_Array* array;
    void* pointer; /* generic pointer for internal use */
    unsigned char padding[32];
}
JSON_Union;

/*
**==============================================================================
**
** JSON_Value
**
**==============================================================================
*/

struct _JSON_Value
{
    unsigned short type;
    JSON_Union u;
};

/*
**==============================================================================
**
** JSON_Array
**
**==============================================================================
*/

typedef struct _JSON_ArrayFT
{
    OL_Result (*AddRef)(
        const JSON_Array* self);

    OL_Result (*Release)(
        JSON_Array* self);

    JSON_Array* (*Clone)(
        const JSON_Array* self);

    OL_Result (*Clear)(
        JSON_Array* self);

    OL_Result (*SetFlags)(
        JSON_Array* self,
        unsigned int flags);

    size_t (*Count)(
        const JSON_Array* self);

    OL_Result (*Append)(
        JSON_Array* self, 
        const JSON_Value* value,
        unsigned int flags);

    OL_Result (*Set)(
        JSON_Array* self, 
        size_t index,
        const JSON_Value* value,
        unsigned int flags);

    OL_Result (*Get)(
        const JSON_Array* self, 
        size_t index,
        JSON_Value* value,
        unsigned int* flags);

    OL_Result (*Remove)(
        JSON_Array* self, 
        size_t index);

    OL_Result (*Print)(
        const JSON_Array* self,
        size_t indent);
}
JSON_ArrayFT;

struct _JSON_Array 
{
    JSON_ArrayFT* ft;
};

OL_INLINE OL_Result JSON_Array_AddRef(
    const JSON_Array* self)
{
    return self->ft->AddRef(self);
}

OL_INLINE OL_Result JSON_Array_Release(
    JSON_Array* self)
{
    return self->ft->Release(self);
}

OL_INLINE JSON_Array* JSON_Array_Clone(
    const JSON_Array* self)
{
    return self->ft->Clone(self);
}

OL_INLINE OL_Result JSON_Array_Clear(
    JSON_Array* self)
{
    return self->ft->Clear(self);
}

OL_INLINE OL_Result JSON_Array_SetFlags(
    JSON_Array* self,
    unsigned int flags)
{
    return self->ft->SetFlags(self, flags);
}

OL_INLINE size_t JSON_Array_Count(
    const JSON_Array* self)
{
    return self->ft->Count(self);
}

OL_INLINE OL_Result JSON_Array_Append(
    JSON_Array* self, 
    const JSON_Value* value)
{
    return self->ft->Append(self, value, 0);
}

OL_INLINE OL_Result JSON_Array_AppendF(
    JSON_Array* self, 
    const JSON_Value* value,
    unsigned int flags)
{
    return self->ft->Append(self, value, flags);
}

OL_INLINE OL_Result JSON_Array_Set(
    JSON_Array* self, 
    size_t index,
    const JSON_Value* value)
{
    return self->ft->Set(self, index, value, 0);
}

OL_INLINE OL_Result JSON_Array_SetF(
    JSON_Array* self, 
    size_t index,
    const JSON_Value* value,
    unsigned int flags)
{
    return self->ft->Set(self, index, value, flags);
}

OL_INLINE OL_Result JSON_Array_Get(
    const JSON_Array* self, 
    size_t index,
    JSON_Value* value)
{
    return self->ft->Get(self, index, value, NULL);
}

OL_INLINE OL_Result JSON_Array_GetF(
    const JSON_Array* self, 
    size_t index,
    JSON_Value* value,
    unsigned int* flags)
{
    return self->ft->Get(self, index, value, flags);
}

OL_INLINE OL_Result JSON_Array_GetAs(
    const JSON_Array* self, 
    size_t index,
    unsigned short type,
    JSON_Value* value)
{
    unsigned int flags = JSON_FLAG_GET_AS_TYPE;
    value->type = type;
    return self->ft->Get(self, index, value, &flags);
}

OL_INLINE OL_Result JSON_Array_Remove(
    JSON_Array* self, 
    size_t index)
{
    return self->ft->Remove(self, index);
}

OL_INLINE OL_Result JSON_Array_Print(
    const JSON_Array* self,
    size_t indent)
{
    return self->ft->Print(self, indent);
}

JSON_Array* JSON_Array_New();

/*
**==============================================================================
**
** JSON_OutStream
**
**==============================================================================
*/

typedef struct _JSON_OutStream JSON_OutStream;

typedef struct _JSON_OutStreamFT
{
    OL_Result (*Put)(
        JSON_OutStream* os,
        const OL_Char* data,
        size_t size);
}
JSON_OutStreamFT;

struct _JSON_OutStream
{
    JSON_OutStreamFT* ft;
};

/*
**==============================================================================
**
** JSON_Object
**
**==============================================================================
*/

typedef struct JSON_ObjectFT
{
    OL_Result (*AddRef)(
        const JSON_Object* self);

    OL_Result (*Release)(
        JSON_Object* self);

    JSON_Object* (*Clone)(
        const JSON_Object* self);

    OL_Result (*Clear)(
        JSON_Object* self);

    OL_Result (*SetFlags)(
        JSON_Object* self,
        unsigned int flags);

    size_t (*Count)(
        const JSON_Object* self);

    OL_Result (*Add)(
        JSON_Object* self, 
        const JSON_Char* name,
        const JSON_Value* value,
        unsigned int flags);

    OL_Result (*Set)(
        JSON_Object* self, 
        const JSON_Char* name,
        const JSON_Value* value,
        unsigned int flags);

    OL_Result (*Get)(
        const JSON_Object* self, 
        const JSON_Char* name,
        JSON_Value* value,
        unsigned int* flags);

    OL_Result (*Remove)(
        JSON_Object* self, 
        const JSON_Char* name,
        unsigned int flags);

    OL_Result (*SetAt)(
        JSON_Object* self, 
        size_t pos,
        const JSON_Value* value,
        unsigned int flags);

    OL_Result (*GetAt)(
        const JSON_Object* self, 
        size_t pos,
        const JSON_Char** name,
        JSON_Value* value,
        unsigned int* flags);

    OL_Result (*RemoveAt)(
        JSON_Object* self, 
        size_t pos,
        unsigned int flags);

    OL_Result (*Print)(
        const JSON_Object* self,
        size_t indent);

    OL_Result (*Serialize)(
        const JSON_Object* self,
        JSON_OutStream* outStream,
        size_t depth);

    OL_Result (*Deserialize)(
        JSON_Object* self,
        JSON_Char* data,
        size_t size,
        size_t* offset);
}
JSON_ObjectFT;

struct _JSON_Object 
{
    JSON_ObjectFT* ft;
};

OL_INLINE OL_Result JSON_Object_AddRef(
    const JSON_Object* self)
{
    return self->ft->AddRef(self);
}

OL_INLINE OL_Result JSON_Object_Release(
    JSON_Object* self)
{
    return self->ft->Release(self);
}

OL_INLINE JSON_Object* JSON_Object_Clone(
    const JSON_Object* self)
{
    return self->ft->Clone(self);
}

OL_INLINE OL_Result JSON_Object_Clear(
    JSON_Object* self)
{
    return self->ft->Clear(self);
}

OL_INLINE OL_Result JSON_Object_SetFlags(
    JSON_Object* self,
    unsigned int flags)
{
    return self->ft->SetFlags(self, flags);
}

OL_INLINE size_t JSON_Object_Count(
    const JSON_Object* self)
{
    return self->ft->Count(self);
}

OL_INLINE OL_Result JSON_Object_Add(
    JSON_Object* self, 
    const JSON_Char* name,
    const JSON_Value* value)
{
    return self->ft->Add(self, name, value, 0);
}

OL_INLINE OL_Result JSON_Object_AddF(
    JSON_Object* self, 
    const JSON_Char* name,
    const JSON_Value* value,
    unsigned int flags)
{
    return self->ft->Add(self, name, value, flags);
}

OL_INLINE OL_Result JSON_Object_Set(
    JSON_Object* self, 
    const JSON_Char* name,
    const JSON_Value* value)
{
    return self->ft->Set(self, name, value, 0);
}

OL_INLINE OL_Result JSON_Object_SetF(
    JSON_Object* self, 
    const JSON_Char* name,
    const JSON_Value* value,
    unsigned int flags)
{
    return self->ft->Set(self, name, value, flags);
}

OL_INLINE OL_Result JSON_Object_Get(
    const JSON_Object* self, 
    const JSON_Char* name,
    JSON_Value* value)
{
    return self->ft->Get(self, name, value, NULL);
}

OL_INLINE OL_Result JSON_Object_GetF(
    const JSON_Object* self, 
    const JSON_Char* name,
    JSON_Value* value,
    unsigned int* flags)
{
    return self->ft->Get(self, name, value, flags);
}

OL_INLINE OL_Result JSON_Object_GetAs(
    const JSON_Object* self, 
    const JSON_Char* name,
    unsigned short type,
    JSON_Value* value)
{
    unsigned int flags = JSON_FLAG_GET_AS_TYPE;
    /* Suppress strinct aliasing warning */
    value->type = type;
    return self->ft->Get(self, name, value, &flags);
}

OL_INLINE OL_Result JSON_Object_Remove(
    JSON_Object* self, 
    const JSON_Char* name,
    unsigned int flags)
{
    return self->ft->Remove(self, name, flags);
}

OL_INLINE OL_Result JSON_Object_SetAt(
    JSON_Object* self, 
    size_t pos,
    const JSON_Value* value)
{
    return self->ft->SetAt(self, pos, value, 0);
}

OL_INLINE OL_Result JSON_Object_SetAtF(
    JSON_Object* self, 
    size_t pos,
    const JSON_Value* value,
    unsigned int flags)
{
    return self->ft->SetAt(self, pos, value, flags);
}

OL_INLINE OL_Result JSON_Object_GetAt(
    const JSON_Object* self, 
    size_t pos,
    const JSON_Char** name,
    JSON_Value* value)
{
    return self->ft->GetAt(self, pos, name, value, 0);
}

OL_INLINE OL_Result JSON_Object_GetAtF(
    const JSON_Object* self, 
    size_t pos,
    const JSON_Char** name,
    JSON_Value* value,
    unsigned int* flags)
{
    return self->ft->GetAt(self, pos, name, value, flags);
}

OL_INLINE OL_Result JSON_Object_GetAtAs(
    const JSON_Object* self, 
    size_t pos,
    const JSON_Char** name,
    unsigned short type,
    JSON_Value* value)
{
    unsigned int flags = JSON_FLAG_GET_AS_TYPE;
    value->type = type;
    return self->ft->GetAt(self, pos, name, value, &flags);
}

OL_INLINE OL_Result JSON_Object_RemoveAt(
    JSON_Object* self, 
    size_t pos,
    unsigned int flags)
{
    return self->ft->RemoveAt(self, pos, flags);
}

OL_INLINE OL_Result JSON_Object_Print(
    const JSON_Object* self,
    size_t indent)
{
    return self->ft->Print(self, indent);
}

OL_INLINE OL_Result JSON_Object_Serialize(
    const JSON_Object* self,
    JSON_OutStream* outStream,
    size_t depth)
{
    return self->ft->Serialize(self, outStream, depth);
}

OL_INLINE OL_Result JSON_Object_Deserialize(
    JSON_Object* self,
    JSON_Char* data,
    size_t size,
    size_t* offset)
{
    return self->ft->Deserialize(self, data, size, offset);
}

JSON_Object* JSON_Object_New();

/*
**==============================================================================
**
** JSON_Boolean Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result JSON_Object_AddBoolean(
    JSON_Object* self,
    const JSON_Char* name,
    JSON_Boolean x)
{
    JSON_Value v;
    v.type = JSON_Type_Boolean;
    v.u.boolean = x;
    return JSON_Object_Add(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_SetBoolean(
    JSON_Object* self,
    const JSON_Char* name,
    JSON_Boolean x)
{
    JSON_Value v;
    v.type = JSON_Type_Boolean;
    v.u.boolean = x;
    return JSON_Object_Set(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_GetBoolean(
    JSON_Object* self,
    const JSON_Char* name,
    JSON_Boolean* x)
{
    JSON_Value v;
    OL_Result r = JSON_Object_GetAs(self, name, JSON_Type_Boolean, &v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.boolean;

    return OL_Result_Ok;
}

OL_INLINE JSON_Value JSON_BooleanValue(const JSON_Boolean x)
{
    JSON_Value v;
    v.u.boolean = x;
    v.type = JSON_Type_Boolean;
    return v;
}

/*
**==============================================================================
**
** JSON_Integer Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result JSON_Object_AddInteger(
    JSON_Object* self,
    const JSON_Char* name,
    const JSON_Integer x)
{
    JSON_Value v;
    v.type = JSON_Type_Integer;
    v.u.integer = x;
    return JSON_Object_Add(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_SetInteger(
    JSON_Object* self,
    const JSON_Char* name,
    const JSON_Integer x)
{
    JSON_Value v;
    v.type = JSON_Type_Integer;
    v.u.integer = x;
    return JSON_Object_Set(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_GetInteger(
    JSON_Object* self,
    const JSON_Char* name,
    JSON_Integer* x)
{
    JSON_Value v;
    OL_Result r = JSON_Object_GetAs(self, name, JSON_Type_Integer, &v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.integer;

    return OL_Result_Ok;
}

OL_INLINE JSON_Value JSON_IntegerValue(const JSON_Integer x)
{
    JSON_Value v;
    v.u.integer = x;
    v.type = JSON_Type_Integer;
    return v;
}

/*
**==============================================================================
**
** JSON_Real Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result JSON_Object_AddReal(
    JSON_Object* self,
    const JSON_Char* name,
    JSON_Real x)
{
    JSON_Value v;
    v.type = JSON_Type_Real;
    v.u.real = x;
    return JSON_Object_Add(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_SetReal(
    JSON_Object* self,
    const JSON_Char* name,
    JSON_Real x)
{
    JSON_Value v;
    v.type = JSON_Type_Real;
    v.u.real = x;
    return JSON_Object_Set(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_GetReal(
    JSON_Object* self,
    const JSON_Char* name,
    JSON_Real* x)
{
    JSON_Value v;
    OL_Result r = JSON_Object_GetAs(self, name, JSON_Type_Real, &v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.real;

    return OL_Result_Ok;
}

OL_INLINE JSON_Value JSON_RealValue(const JSON_Real x)
{
    JSON_Value v;
    v.u.real = x;
    v.type = JSON_Type_Real;
    return v;
}

/*
**==============================================================================
**
** JSON_String Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result JSON_Object_AddString(
    JSON_Object* self,
    const JSON_Char* name,
    const JSON_Char* x)
{
    JSON_Value v;
    v.type = JSON_Type_String;
    v.u.string = (JSON_Char*)x;
    return JSON_Object_Add(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_SetString(
    JSON_Object* self,
    const JSON_Char* name,
    const JSON_Char* x)
{
    JSON_Value v;
    v.type = JSON_Type_String;
    v.u.string = (JSON_Char*)x;
    return JSON_Object_Set(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_GetString(
    JSON_Object* self,
    const JSON_Char* name,
    const JSON_Char** x)
{
    JSON_Value v;
    OL_Result r = JSON_Object_GetAs(self, name, JSON_Type_String, &v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.string;

    return OL_Result_Ok;
}

OL_INLINE JSON_Value JSON_StringValue(const JSON_Char* str)
{
    JSON_Value v;
    v.u.string = (JSON_Char*)str;
    v.type = JSON_Type_String;
    return v;
}

/*
**==============================================================================
**
** JSON_Object Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result JSON_Object_AddObject(
    JSON_Object* self,
    const JSON_Char* name,
    const JSON_Object* x)
{
    JSON_Value v;
    v.type = JSON_Type_Object;
    v.u.object = (JSON_Object*)x;
    return JSON_Object_Add(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_SetObject(
    JSON_Object* self,
    const JSON_Char* name,
    const JSON_Object* x)
{
    JSON_Value v;
    v.type = JSON_Type_Object;
    v.u.object = (JSON_Object*)x;
    return JSON_Object_Set(self, name, &v);
}

OL_INLINE OL_Result JSON_Object_GetObject(
    JSON_Object* self,
    const JSON_Char* name,
    const JSON_Object** x)
{
    JSON_Value v;
    OL_Result r = JSON_Object_GetAs(self, name, JSON_Type_Object, &v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.object;

    return OL_Result_Ok;
}

OL_INLINE JSON_Value JSON_ObjectValue(JSON_Object* x)
{
    JSON_Value v;
    v.u.object = x;
    v.type = JSON_Type_Object;
    return v;
}

/*
********************************************************************************
********************************************************************************
**
**  Schema types
**
********************************************************************************
********************************************************************************
*/

typedef struct _JSON_Property JSON_Property;
typedef struct _JSON_Member JSON_Member;
typedef struct _JSON_EnumType JSON_EnumType;
typedef struct _JSON_ComplexType JSON_ComplexType;
typedef struct _JSON_EntityType JSON_EntityType;
typedef struct _JSON_Schema JSON_Schema;

/*
**==============================================================================
**
**  JSON_Property
**
**==============================================================================
*/

#define JSON_PROPERTY_FLAG_PRIMITIVETYPE (1 << 0)
#define JSON_PROPERTY_FLAG_COMPLEXTYPE   (1 << 1)
#define JSON_PROPERTY_FLAG_ENTITYTYPE    (1 << 2)
#define JSON_PROPERTY_FLAG_ENUMTYPE      (1 << 3)
#define JSON_PROPERTY_FLAG_NULLABLE      (1 << 4)
#define JSON_PROPERTY_FLAG_ARRAY         (1 << 5)

struct _JSON_Property
{
    unsigned char flags;

    /* JSON_Type */
    unsigned char type;

    /* Index into complexTypes[] or enumTypes[] or entityTypes[] */
    unsigned short index;

    const char* name;
};

/*
**==============================================================================
**
**  Member
**
**==============================================================================
*/

struct _JSON_Member
{
    const char* name;
    JSON_Integer value;
};

/*
**==============================================================================
**
**  EnumType
**
**==============================================================================
*/

#define JSON_ENUMTYPE_FLAG_ISFLAGS       (1 << 0)

struct _JSON_EnumType
{
    unsigned char flags;
    unsigned char underlyingType;
    unsigned char membersSize;
    const char* name;
    const JSON_Member** members;
};

/*
**==============================================================================
**
**  JSON_ComplexType
**
**==============================================================================
*/

#define JSON_COMPLEXTYPE_FLAG_OPENTYPE   (1 << 0)

struct _JSON_ComplexType /* extends JSON_BaseType */
{
    unsigned char flags;
    const char* name;
    const JSON_Property** properties;
    size_t propertiesSize;
};

/*
**==============================================================================
**
**  JSON_EntityType
**
**==============================================================================
*/

#define JSON_ENTITYTYPE_FLAG_OPENTYPE   (1 << 0)

struct _JSON_EntityType
{
    unsigned char flags;
    const char* name;
    const char* baseType;

    const JSON_Property** properties;
    size_t propertiesSize;
};

/*
**==============================================================================
**
**  JSON_Schema
**
**==============================================================================
*/

struct _JSON_Schema
{
    const JSON_EntityType** entityTypes;
    size_t entityTypesSize;

    const JSON_EnumType** enumTypes;
    size_t enumTypesSize;

    const JSON_ComplexType** complexTypes;
    size_t complexTypesSize;
};

#endif /* _json_h */
