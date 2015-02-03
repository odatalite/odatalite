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
#ifndef _odata_h
#define _odata_h

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>
#include <limits.h>

/*
**==============================================================================
**
** OL_EXTERNC
** OL_EXTERNC_BEGIN
** OL_EXTERNC_END
**
**==============================================================================
*/

#if defined(__cplusplus)
# define OL_EXTERNC extern "C"
# define OL_EXTERNC_BEGIN extern "C" {
# define OL_EXTERNC_END }
#else
# define OL_EXTERNC
# define OL_EXTERNC_BEGIN
# define OL_EXTERNC_END
#endif

OL_EXTERNC_BEGIN

/*
**==============================================================================
**
** OL_EXPORT
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define OL_EXPORT __declspec(dllexport)
# define OL_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
# define OL_EXPORT __attribute__((visibility("default")))
# define OL_IMPORT /* empty */
#elif defined(sun)
# define OL_EXPORT __global
# define OL_IMPORT /* empty */
#else
# define OL_EXPORT
# define OL_IMPORT
#endif

/*
**==============================================================================
**
** OL_INLINE
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define OL_INLINE static __inline
# define OL_ALWAYS_INLINE OL_INLINE
#elif defined(__GNUC__)
# define OL_INLINE static __inline
# define OL_ALWAYS_INLINE __attribute__((always_inline)) OL_INLINE
#elif defined(sun)
# define OL_INLINE static inline
# define OL_ALWAYS_INLINE OL_INLINE
#elif defined(__PPC)
# define OL_INLINE __inline__
# define OL_ALWAYS_INLINE OL_INLINE
#else
# define OL_INLINE static __inline
# define OL_ALWAYS_INLINE OL_INLINE
#endif

#if 0
# undef OL_ALWAYS_INLINE
# define OL_ALWAYS_INLINE OL_INLINE
#endif

/*
**==============================================================================
**
** OL_PRINTF_FORMAT()
**
**==============================================================================
*/

#if defined(__GNUC__) && (__GNUC__ >= 4) && !defined(CONFIG_ENABLE_WCHAR)
# define OL_PRINTF_FORMAT(N,M) __attribute__((format(printf, N, M)))
#else
# define OL_PRINTF_FORMAT(N,M) /* empty */
#endif

/*
**==============================================================================
**
** OL_NPOS
**
**==============================================================================
*/

#define OL_NPOS ((size_t)-1)

/*
**==============================================================================
**
** OL_RETURN_IF_NULL(POINTER, RETURNVALUE)
**
**==============================================================================
*/

#if defined(OL_CHECK_FOR_NULL_POINTER)
# define OL_RETURN_IF_NULL(POINTER, RETURNVALUE) \
    do \
    { \
        if (POINTER == NULL) \
            return RETURNVALUE; \
    } \
    while (0)
#else
# define OL_RETURN_IF_NULL(POINTER, RETURNVALUE)
#endif

/*
**==============================================================================
**
** OL_ARRAYSIZE()
**
**==============================================================================
*/

#define OL_ARRAYSIZE(X) (sizeof(X)/sizeof(X[0]))

/*
**==============================================================================
**
** ODATA Flags
**
**==============================================================================
*/

#define OL_FLAG_STATIC_NAME           (1 << 0)
#define OL_FLAG_LENGTH_NAME           (1 << 1)
#define OL_FLAG_STATIC_VALUE          (1 << 2)
#define OL_FLAG_GET_AS_TYPE           (1 << 3)
#define OL_FLAG_ALLOW_DUPLICATES      (1 << 4)
#define OL_FLAG_HOMOGENEOUS_ARRAY     (1 << 5)
#define OL_FLAG_NULL                  (1 << 6)

/*
**==============================================================================
**
** OL_MetadataType
**     odata.metadata=none
**     odata.metadata=minimal
**     odata.metadata=full
**
**==============================================================================
*/

typedef enum _OL_MetadataType
{
    OL_MetadataType_None,
    OL_MetadataType_Minimal,
    OL_MetadataType_Full
}
OL_MetadataType;

/*
**==============================================================================
**
** OL_Result
**
**==============================================================================
*/

typedef enum _OL_Result
{
    OL_Result_Ok,
    OL_Result_Failed,
    OL_Result_AlreadyExists,
    OL_Result_NotFound,
    OL_Result_BadParameter,
    OL_Result_NotSupported,
    OL_Result_OutOfBounds,
    OL_Result_TypeMismatch,
    OL_Result_UnknownType,
    OL_Result_EndOfFile,
    OL_Result_SyntaxError,
    OL_Result_OutOfMemory,
    OL_Result_InternalError,
    OL_Result_InvalidName
    /* Reminder: update __resultStrings[] */
}
OL_Result;

/*
**==============================================================================
**
** enum OL_Type
**
**     +------------------------------+----------------------------+
**     | ODATA Type (interface type)  | JSON Type (internal type)  |
**     +------------------------------+----------------------------+
**     | OL_Type_Boolean              | JSON_Type_Boolean          |
**     | OL_Type_Byte                 | JSON_Type_Int64            |
**     | OL_Type_SByte                | JSON_Type_Int64            |
**     | OL_Type_Int16                | JSON_Type_Int64            |
**     | OL_Type_Int32                | JSON_Type_Int64            |
**     | OL_Type_Int64                | JSON_Type_String           |
**     | OL_Type_Single               | JSON_Type_Real             |
**     | OL_Type_Double               | JSON_Type_Real             |
**     | OL_Type_Decimal              | JSON_Type_Real             |
**     | OL_Type_String               | JSON_Type_String           |
**     | OL_Type_Binary               | JSON_Type_String           |
**     | OL_Type_Date                 | JSON_Type_String           |
**     | OL_Type_TimeOfDay            | JSON_Type_String           |
**     | OL_Type_DateTimeOffset       | JSON_Type_String           |
**     | OL_Type_Duration             | JSON_Type_String           |
**     | OL_Type_Guid                 | JSON_Type_String           |
**     | OL_Type_Object               | JSON_Type_Object           |
**     | OL_Type_NavigationLink       | JSON_Type_String           |
**     | OL_Type_AssociationLink      | JSON_Type_String           |
**     +------------------------------+----------------------------+
**
**==============================================================================
*/

typedef enum _OL_Type
{
    OL_Type_Null,
    OL_Type_Boolean,
    OL_Type_Int64,
    OL_Type_Double,
    OL_Type_String,
    OL_Type_Object,
    OL_Type_Array,
    OL_Type_Byte,
    OL_Type_SByte,
    OL_Type_Int16,
    OL_Type_Int32,
    OL_Type_Single,
    OL_Type_Decimal,
    OL_Type_Binary,
    OL_Type_Date,
    OL_Type_TimeOfDay,
    OL_Type_DateTimeOffset,
    OL_Type_Duration,
    OL_Type_Guid,
    OL_Type_NavigationLink,
    OL_Type_AssociationLink
}
OL_Type;

#define OL_TYPE_COUNT ((size_t)(OL_Type_AssociationLink + 1))

/*
**==============================================================================
**
** ODATA data types
**
**==============================================================================
*/

#define OL_TRUE ((OL_Boolean)1)
#define OL_FALSE ((OL_Boolean)0)

typedef unsigned char OL_Boolean;

typedef unsigned char OL_Byte;

typedef signed char OL_SByte;

typedef signed short OL_Int16;

typedef signed int OL_Int32;

typedef signed long long OL_Int64;

typedef float OL_Single;

typedef double OL_Double;

typedef struct _OL_Decimal
{
    signed long long integral;
    signed long long fractional;
}
OL_Decimal;

typedef char OL_Char;

typedef OL_Char* OL_String;

typedef const OL_Char* OL_ConstString;

typedef struct _OL_Binary
{
    void* data;
    size_t size;
}
OL_Binary;

/* YYYY/MM/DD */
typedef struct _OL_Date
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
}
OL_Date;

/* Example: 00:00-23:59:59.999999999999 */
typedef struct _OL_TimeOfDay
{
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
    unsigned long long fractionalSecond;
}
OL_TimeOfDay;

typedef struct _OL_DateTimeOffset
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
    unsigned long long fractionalSecond;
}
OL_DateTimeOffset;

typedef struct _OL_Duration
{
    OL_Boolean negative;
    unsigned int days;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
    unsigned long long fractionalSecond;
}
OL_Duration;

/* AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE */
typedef struct _OL_Guid
{
    /* AAAAAAAA */
    unsigned int data1;

    /* BBBB */
    unsigned short data2;

    /* CCCC */
    unsigned short data3;

    /* DDDD */
    unsigned short data4;

    /* EEEE */
    unsigned short data5;

    /* EEEEEEEE */
    unsigned int data6;
}
OL_Guid;

typedef OL_String OL_NavigationLink;

typedef OL_String OL_AssociationLink;

typedef struct _OL_Value OL_Value;

typedef struct _OL_Array OL_Array;

typedef struct _OL_Object OL_Object;

/*
**==============================================================================
**
** OL_Union
**
**==============================================================================
*/

typedef union _OL_Union
{
    OL_Boolean boolean;
    OL_Byte byte;
    OL_SByte sByte;
    OL_Int16 int16;
    OL_Int32 int32;
    OL_Int64 int64;
    OL_Single single;
    OL_Double double_;
    OL_Decimal decimal;
    OL_String string;
    OL_Binary binary;
    OL_Date date;
    OL_TimeOfDay timeOfDay;
    OL_DateTimeOffset dateTimeOffset;
    OL_Duration duration;
    OL_Guid guid;
    OL_Object* object;
    OL_NavigationLink navigationLink;
    OL_AssociationLink associationLink;
    OL_Array* array;
    void* pointer; /* generic pointer for internal use */
    /* Note: must be exactly the same length as JSON_Value */
    unsigned char padding[32];
}
OL_Union;

/*
**==============================================================================
**
** OL_Value
**
**==============================================================================
*/

struct _OL_Value
{
    unsigned short type;
    OL_Union u;
};

/*
**==============================================================================
**
** OL_Scope_Option - options supported by OL_Scope_GetOption()
**
**==============================================================================
*/

typedef enum _OL_Scope_Option
{
    OL_Scope_Option_Role = 1 /* const char* */
}
OL_Scope_Option;

/*
**==============================================================================
**
** OL_Scope
**
**==============================================================================
*/

typedef struct _OL_URI OL_URI;
typedef struct _OL_Scope OL_Scope;
typedef struct _EDMX_Edmx EDMX_Edmx;

typedef struct _OL_ScopeFT
{
    OL_Result (*AddRef)(
        const OL_Scope* self);

    OL_Result (*Release)(
        OL_Scope* self);

    /* Release any objects held by this scope */
    OL_Result (*Clear)(
        OL_Scope* self);

    /* Reset the scope as though it were new */
    OL_Result (*Reset)(
        OL_Scope* self);

    OL_URI* (*NewURI)(
        const OL_Scope* self);

    OL_Array* (*NewArray)(
        const OL_Scope* self);

    OL_Object* (*NewObject)(
        const OL_Scope* self);

    OL_Result (*SendBeginEntitySet)(
        OL_Scope* self);

    OL_Result (*SendEntity)(
        OL_Scope* self,
        const OL_Object* object);

    OL_Result (*SendMetadataStruct)(
        OL_Scope* self,
        const EDMX_Edmx* edmx);

    OL_Result (*SendMetadataXML)(
        OL_Scope* self,
        const char* text,
        size_t size);

    OL_Result (*SendEndEntitySet)(
        OL_Scope* self,
        const char* skiptoken);

    OL_Result (*SendResult)(
        OL_Scope* self,
        OL_Result result,
        const OL_Char* format,
        va_list ap);

    void (*SetProviderData)(
        OL_Scope* self,
        void* ptr,
        void (*destructor)(void* ptr));

    void* (*GetProviderData)(
        OL_Scope* self);

    OL_Result (*GetOption)(
        const OL_Scope* scope,
        int option,
        void* value,
        size_t valueSize);
}
OL_ScopeFT;

struct _OL_Scope 
{
    OL_ScopeFT* ft;
};

OL_INLINE OL_Result OL_Scope_AddRef(
    const OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->AddRef(self);
}

OL_INLINE OL_Result OL_Scope_Release(
    OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Release(self);
}

OL_INLINE OL_Result OL_Scope_Clear(
    OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Clear(self);
}

OL_INLINE OL_Result OL_Scope_Reset(
    OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Reset(self);
}

OL_INLINE OL_URI* OL_Scope_NewURI(
    const OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, NULL);
    return self->ft->NewURI(self);
}

OL_INLINE OL_Array* OL_Scope_NewArray(
    const OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, NULL);
    return self->ft->NewArray(self);
}

OL_INLINE OL_Object* OL_Scope_NewObject(
    const OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, NULL);
    return self->ft->NewObject(self);
}

OL_INLINE OL_Result OL_Scope_SendBeginEntitySet(
    OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SendBeginEntitySet(self);
}

OL_INLINE OL_Result OL_Scope_SendEntity(
    OL_Scope* self,
    const OL_Object* object)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SendEntity(self, object);
}

OL_INLINE OL_Result OL_Scope_SendMetadataStruct(
    OL_Scope* self,
    const EDMX_Edmx* edmx)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SendMetadataStruct(self, edmx);
}

OL_INLINE OL_Result OL_Scope_SendMetadataXML(
    OL_Scope* self,
    const char* data,
    size_t size)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SendMetadataXML(self, data, size);
}

OL_INLINE OL_Result OL_Scope_SendEndEntitySet(
    OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SendEndEntitySet(self, NULL);
}

OL_INLINE OL_Result OL_Scope_SendEndEntitySetWithSkiptoken(
    OL_Scope* self,
    const char* skiptoken)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SendEndEntitySet(self, skiptoken);
}


OL_INLINE OL_Result OL_Scope_SendResult(
    OL_Scope* self,
    OL_Result result)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SendResult(self, result, NULL, NULL);
}

OL_INLINE OL_Result OL_Scope_SendResultV(
    OL_Scope* self,
    OL_Result result,
    const char* format,
    va_list ap)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SendResult(self, result, format, ap);
}

OL_PRINTF_FORMAT(3, 4)
OL_INLINE OL_Result OL_Scope_SendResultF(
    OL_Scope* self,
    OL_Result result,
    const char* format,
    ...)
{
    va_list ap;
    OL_Result r;

    va_start(ap, format);
    r = self->ft->SendResult(self, result, format, ap);
    va_end(ap);

    return r;
}

OL_INLINE void OL_Scope_SetProviderData(
    OL_Scope* self,
    void* ptr,
    void (*destructor)(void* ptr))
{
    self->ft->SetProviderData(self, ptr, destructor);
}

OL_INLINE void* OL_Scope_GetProviderData(
    OL_Scope* self)
{
    OL_RETURN_IF_NULL(self, NULL);
    return self->ft->GetProviderData(self);
}

OL_INLINE OL_Result OL_Scope_GetOption(
    const OL_Scope* self,
    int option,
    void* value,
    size_t valueSize)
{
    OL_RETURN_IF_NULL(self, 0);
    return self->ft->GetOption(self, option, value, valueSize);
}

OL_Scope* __OL_Scope_New();

/*
**==============================================================================
**
** OL_Array
**
**==============================================================================
*/

typedef struct _OL_ArrayFT
{
    OL_Result (*AddRef)(
        const OL_Array* self);

    OL_Result (*Release)(
        OL_Array* self);

    OL_Array* (*Clone)(
        const OL_Array* self);

    OL_Result (*Clear)(
        OL_Array* self);

    OL_Result (*SetFlags)(
        OL_Array* self,
        unsigned int flags);

    size_t (*Count)(
        const OL_Array* self);

    OL_Result (*Append)(
        OL_Array* self, 
        const OL_Value* value,
        unsigned int flags);

    OL_Result (*Set)(
        OL_Array* self, 
        size_t index,
        const OL_Value* value,
        unsigned int flags);

    OL_Result (*Get)(
        const OL_Array* self, 
        size_t index,
        OL_Value* value,
        unsigned int* flags);

    OL_Result (*Remove)(
        OL_Array* self, 
        size_t index);

    OL_Result (*Print)(
        const OL_Array* self,
        size_t indent);
}
OL_ArrayFT;

struct _OL_Array 
{
    OL_ArrayFT* ft;
};

OL_INLINE OL_Result OL_Array_AddRef(
    const OL_Array* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->AddRef(self);
}

OL_INLINE OL_Result OL_Array_Release(
    OL_Array* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Release(self);
}

OL_INLINE OL_Array* OL_Array_Clone(
    const OL_Array* self)
{
    OL_RETURN_IF_NULL(self, NULL);
    return self->ft->Clone(self);
}

OL_INLINE OL_Result OL_Array_Clear(
    OL_Array* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Clear(self);
}

OL_INLINE OL_Result OL_Array_SetFlags(
    OL_Array* self,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SetFlags(self, flags);
}

OL_INLINE size_t OL_Array_Count(
    const OL_Array* self)
{
    OL_RETURN_IF_NULL(self, (size_t)-1);
    return self->ft->Count(self);
}

OL_INLINE OL_Result OL_Array_Append(
    OL_Array* self, 
    const OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Append(self, value, 0);
}

OL_INLINE OL_Result OL_Array_AppendF(
    OL_Array* self, 
    const OL_Value* value,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Append(self, value, flags);
}

OL_INLINE OL_Result OL_Array_Set(
    OL_Array* self, 
    size_t index,
    const OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Set(self, index, value, 0);
}

OL_INLINE OL_Result OL_Array_SetF(
    OL_Array* self, 
    size_t index,
    const OL_Value* value,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Set(self, index, value, flags);
}

OL_INLINE OL_Result OL_Array_Get(
    const OL_Array* self, 
    size_t index,
    OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Get(self, index, value, NULL);
}

OL_INLINE OL_Result OL_Array_GetF(
    const OL_Array* self, 
    size_t index,
    OL_Value* value,
    unsigned int* flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Get(self, index, value, flags);
}

OL_INLINE OL_Result OL_Array_GetAs(
    const OL_Array* self, 
    size_t index,
    unsigned short type,
    OL_Value* value)
{
    unsigned int flags = OL_FLAG_GET_AS_TYPE;
    value->type = type;
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Get(self, index, value, &flags);
}

OL_INLINE OL_Result OL_Array_Remove(
    OL_Array* self, 
    size_t index)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Remove(self, index);
}

OL_INLINE OL_Result OL_Array_Print(
    const OL_Array* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Print(self, 0);
}

OL_INLINE OL_Result OL_Array_PrintIndent(
    const OL_Array* self,
    size_t indent)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Print(self, indent);
}

OL_Array* __OL_Array_New();

/*
**==============================================================================
**
** OL_OutStream
**
**==============================================================================
*/

typedef struct _OL_OutStream OL_OutStream;

typedef struct _OL_OutStreamFT
{
    OL_Result (*Put)(
        OL_OutStream* os,
        const OL_Char* data,
        size_t size);
}
OL_OutStreamFT;

struct _OL_OutStream
{
    OL_OutStreamFT* ft;
};

/*
**==============================================================================
**
** OL_Object
**
**==============================================================================
*/

typedef struct _OL_ObjectFT
{
    OL_Result (*AddRef)(
        const OL_Object* self);

    OL_Result (*Release)(
        OL_Object* self);

    OL_Object* (*Clone)(
        const OL_Object* self);

    OL_Result (*Clear)(
        OL_Object* self);

    OL_Result (*SetFlags)(
        OL_Object* self,
        unsigned int flags);

    size_t (*Count)(
        const OL_Object* self);

    OL_Result (*Add)(
        OL_Object* self, 
        const OL_Char* name,
        const OL_Value* value,
        unsigned int flags);

    OL_Result (*Set)(
        OL_Object* self, 
        const OL_Char* name,
        const OL_Value* value,
        unsigned int flags);

    OL_Result (*Get)(
        const OL_Object* self, 
        const OL_Char* name,
        OL_Value* value,
        unsigned int* flags);

    OL_Result (*Remove)(
        OL_Object* self, 
        const OL_Char* name,
        unsigned int flags);

    OL_Result (*SetAt)(
        OL_Object* self, 
        size_t pos,
        const OL_Value* value,
        unsigned int flags);

    OL_Result (*GetAt)(
        const OL_Object* self, 
        size_t pos,
        const OL_Char** name,
        OL_Value* value,
        unsigned int* flags);

    OL_Result (*RemoveAt)(
        OL_Object* self, 
        size_t pos,
        unsigned int flags);

    OL_Result (*Print)(
        const OL_Object* self,
        size_t indent);

    OL_Result (*Serialize)(
        const OL_Object* self,
        OL_OutStream* outStream,
        size_t indent);

    OL_Result (*Deserialize)(
        OL_Object* self,
        OL_Char* data,
        size_t size,
        size_t* offset);
}
OL_ObjectFT;

struct _OL_Object 
{
    OL_ObjectFT* ft;
};

OL_INLINE OL_Result OL_Object_AddRef(
    const OL_Object* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->AddRef(self);
}

OL_INLINE OL_Result OL_Object_Release(
    OL_Object* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Release(self);
}

OL_INLINE OL_Object* OL_Object_Clone(
    const OL_Object* self)
{
    OL_RETURN_IF_NULL(self, NULL);
    return self->ft->Clone(self);
}

OL_INLINE OL_Result OL_Object_Clear(
    OL_Object* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Clear(self);
}

OL_INLINE OL_Result OL_Object_SetFlags(
    OL_Object* self,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SetFlags(self, flags);
}

OL_INLINE size_t OL_Object_Count(
    const OL_Object* self)
{
    OL_RETURN_IF_NULL(self, (size_t)-1);
    return self->ft->Count(self);
}

OL_INLINE OL_Result OL_Object_Add(
    OL_Object* self, 
    const OL_Char* name,
    const OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Add(self, name, value, 0);
}

OL_INLINE OL_Result OL_Object_AddF(
    OL_Object* self, 
    const OL_Char* name,
    const OL_Value* value,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Add(self, name, value, flags);
}

OL_INLINE OL_Result OL_Object_Set(
    OL_Object* self, 
    const OL_Char* name,
    const OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Set(self, name, value, 0);
}

OL_INLINE OL_Result OL_Object_SetF(
    OL_Object* self, 
    const OL_Char* name,
    const OL_Value* value,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Set(self, name, value, flags);
}

OL_INLINE OL_Result OL_Object_Get(
    const OL_Object* self, 
    const OL_Char* name,
    OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Get(self, name, value, NULL);
}

OL_INLINE OL_Result OL_Object_GetF(
    const OL_Object* self, 
    const OL_Char* name,
    OL_Value* value,
    unsigned int* flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Get(self, name, value, flags);
}

OL_INLINE OL_Result OL_Object_GetAs(
    const OL_Object* self, 
    const OL_Char* name,
    unsigned short type,
    OL_Value* value)
{
    unsigned int flags = OL_FLAG_GET_AS_TYPE;
    value->type = type;
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Get(self, name, value, &flags);
}

OL_INLINE OL_Result OL_Object_Remove(
    OL_Object* self, 
    const OL_Char* name,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Remove(self, name, flags);
}

OL_INLINE OL_Result OL_Object_SetAt(
    OL_Object* self, 
    size_t pos,
    const OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SetAt(self, pos, value, 0);
}

OL_INLINE OL_Result OL_Object_SetAtF(
    OL_Object* self, 
    size_t pos,
    const OL_Value* value,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SetAt(self, pos, value, flags);
}

OL_INLINE OL_Result OL_Object_GetAt(
    const OL_Object* self, 
    size_t pos,
    const OL_Char** name,
    OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->GetAt(self, pos, name, value, NULL);
}

OL_INLINE OL_Result OL_Object_GetAtF(
    const OL_Object* self, 
    size_t pos,
    const OL_Char** name,
    OL_Value* value,
    unsigned int* flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->GetAt(self, pos, name, value, flags);
}

OL_INLINE OL_Result OL_Object_GetAtAs(
    const OL_Object* self, 
    size_t pos,
    const OL_Char** name,
    unsigned short type,
    OL_Value* value)
{
    unsigned int flags = OL_FLAG_GET_AS_TYPE;
    value->type = type;
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->GetAt(self, pos, name, value, &flags);
}

OL_INLINE OL_Result OL_Object_RemoveAt(
    OL_Object* self, 
    size_t pos,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->RemoveAt(self, pos, flags);
}

OL_INLINE OL_Result OL_Object_Print(
    const OL_Object* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Print(self, 0);
}

OL_INLINE OL_Result OL_Object_PrintIndent(
    const OL_Object* self,
    size_t indent)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Print(self, indent);
}

OL_INLINE OL_Result OL_Object_Serialize(
    const OL_Object* self,
    OL_OutStream* outStream,
    size_t indent)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Serialize(self, outStream, indent);
}

OL_INLINE OL_Result OL_Object_Deserialize(
    OL_Object* self,
    OL_Char* data,
    size_t size,
    size_t* offset)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Deserialize(self, data, size, offset);
}

OL_Object* __OL_Object_New();

/*
**==============================================================================
**
** OL_URI
**
**==============================================================================
*/

#define OL_QUERY_OPTION_FILTER     (1 << 0)
#define OL_QUERY_OPTION_EXPAND     (1 << 1)
#define OL_QUERY_OPTION_SELECT     (1 << 2)
#define OL_QUERY_OPTION_ORDERBY    (1 << 3)
#define OL_QUERY_OPTION_TOP        (1 << 4)
#define OL_QUERY_OPTION_SKIP       (1 << 5)
#define OL_QUERY_OPTION_COUNT      (1 << 6)
#define OL_QUERY_OPTION_SEARCH     (1 << 7)
#define OL_QUERY_OPTION_FORMAT     (1 << 8)
#define OL_QUERY_OPTION_VALUE      (1 << 9)
#define OL_QUERY_OPTION_SKIPTOKEN  (1 << 10)

typedef struct _OL_URIFT
{
    OL_Result (*AddRef)(
        const OL_URI* self);

    OL_Result (*Release)(
        OL_URI* self);

    OL_URI* (*Clone)(
        const OL_URI* self);

    OL_Result (*Clear)(
        OL_URI* self);

    OL_Result (*SetFlags)(
        OL_URI* self,
        unsigned int flags);

    size_t (*Count)(
        const OL_URI* self);
       
    size_t (*KeyCount)(
        const OL_URI* self,
        size_t index);

    const OL_Char* (*GetName)(
        const OL_URI* self,
        size_t index);

    OL_Result (*GetKey)(
        const OL_URI* self, 
        size_t index,
        const OL_Char* name,
        OL_Value* value);

    OL_Result (*GetKeyAt)(
        const OL_URI* self, 
        size_t index,
        size_t keyIndex,
        const OL_Char** name,
        OL_Value* value);

    OL_Result (*Parse)(
        OL_URI* self,
        OL_Char* uri,
        OL_Char* error,
        size_t errorSize);

    OL_Result (*Format)(
        const OL_URI* self,
        char* buf,
        size_t size);

    unsigned int (*GetQueryOptionFlags)(
        const OL_URI* self);

    OL_Result (*GetQueryOption)(
        const OL_URI* self,
        unsigned int option,
        void* value,
        size_t valueSize);

    OL_Result (*Print)(
        const OL_URI* self,
        size_t indent);
}
OL_URIFT;

struct _OL_URI 
{
    OL_URIFT* ft;
};

OL_INLINE OL_Result OL_URI_AddRef(
    const OL_URI* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->AddRef(self);
}

OL_INLINE OL_Result OL_URI_Release(
    OL_URI* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Release(self);
}

OL_INLINE OL_URI* OL_URI_Clone(
    const OL_URI* self)
{
    OL_RETURN_IF_NULL(self, NULL);
    return self->ft->Clone(self);
}

OL_INLINE OL_Result OL_URI_Clear(
    OL_URI* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Clear(self);
}

OL_INLINE OL_Result OL_URI_SetFlags(
    OL_URI* self,
    unsigned int flags)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->SetFlags(self, flags);

}

OL_INLINE size_t OL_URI_Count(
    const OL_URI* self)
{
    OL_RETURN_IF_NULL(self, (size_t)-1);
    return self->ft->Count(self);
}

OL_INLINE size_t OL_URI_KeyCount(
    const OL_URI* self,
    size_t index)
{
    OL_RETURN_IF_NULL(self, (size_t)-1);
    return self->ft->KeyCount(self, index);
}

OL_INLINE const OL_Char* OL_URI_GetName(
    const OL_URI* self,
    size_t index)
{
    OL_RETURN_IF_NULL(self, (size_t)-1);
    return self->ft->GetName(self, index);
}

OL_INLINE OL_Result OL_URI_GetKey(
    const OL_URI* self, 
    size_t index,
    const OL_Char* name,
    OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->GetKey(self, index, name, value);
}

OL_INLINE OL_Result OL_URI_GetKeyAt(
    const OL_URI* self, 
    size_t index,
    size_t keyIndex,
    const OL_Char** name,
    OL_Value* value)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->GetKeyAt(self, index, keyIndex, name, value);
}

OL_INLINE OL_Result OL_URI_Parse(
    OL_URI* self,
    OL_Char* uri,
    OL_Char* error,
    size_t errorSize)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Parse(self, uri, error, errorSize);
}

OL_INLINE OL_Result OL_URI_Format(
    const OL_URI* self,
    char* buf,
    size_t size)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Format(self, buf, size);
}

OL_INLINE OL_Result OL_URI_Print(
    const OL_URI* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->Print(self, 0);
}

OL_INLINE unsigned int OL_URI_GetQueryOptionFlags(
    const OL_URI* self)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->GetQueryOptionFlags(self);
}

OL_INLINE OL_Result OL_URI_GetQueryOption(
    const OL_URI* self,
    unsigned int option,
    void* value,
    size_t valueSize)
{
    OL_RETURN_IF_NULL(self, OL_Result_BadParameter);
    return self->ft->GetQueryOption(self, option, value, valueSize);
}

OL_INLINE OL_Result OL_URI_GetKeyString(
    const OL_URI* self,
    size_t index,
    const OL_Char* name,
    const OL_Char** x)
{
    OL_Value v;
    OL_Result r = OL_URI_GetKey(self, index, name, &v);

    if (r != OL_Result_Ok)
        return r;

    if (v.type != OL_Type_String)
        return OL_Result_TypeMismatch;

    if (x)
        *x = v.u.string;

    return OL_Result_Ok;
}

OL_INLINE OL_Result OL_URI_GetKeyInt64(
    const OL_URI* self,
    size_t index,
    const OL_Char* name,
    OL_Int64* x)
{
    OL_Value v;
    OL_Result r = OL_URI_GetKey(self, index, name, &v);

    if (r != OL_Result_Ok)
        return r;

    if (v.type != OL_Type_Int64)
        return OL_Result_TypeMismatch;

    if (x)
        *x = v.u.int64;

    return OL_Result_Ok;
}

OL_INLINE OL_Result OL_URI_GetKeyDouble(
    const OL_URI* self,
    size_t index,
    const OL_Char* name,
    OL_Double* x)
{
    OL_Value v;
    OL_Result r = OL_URI_GetKey(self, index, name, &v);

    if (r != OL_Result_Ok)
        return r;

    if (v.type != OL_Type_Double)
        return OL_Result_TypeMismatch;

    if (x)
        *x = v.u.double_;

    return OL_Result_Ok;
}

OL_URI* __OL_URI_New();

/*
**==============================================================================
**
** OL_Provider
**
**==============================================================================
*/

typedef struct _OL_Provider OL_Provider;

typedef struct _OL_ProviderFT
{
    void (*Load)(
        OL_Provider* self,
        OL_Scope* scope);

    void (*Unload)(
        OL_Provider* self,
        OL_Scope* scope);

    void (*Get)(
        OL_Provider* self,
        OL_Scope* scope,
        const OL_URI* uri);

    void (*Post)(
        OL_Provider* self,
        OL_Scope* scope,
        const OL_URI* uri,
        const OL_Object* object);

    void (*Put)(
        OL_Provider* self,
        OL_Scope* scope,
        const OL_URI* uri,
        const OL_Object* object);

    void (*Patch)(
        OL_Provider* self,
        OL_Scope* scope,
        const OL_URI* uri,
        const OL_Object* object);

    void (*Delete)(
        OL_Provider* self,
        OL_Scope* scope,
        const OL_URI* uri);
}
OL_ProviderFT;

struct _OL_Provider 
{
    OL_ProviderFT* ft;
};

#define OL_PROVIDERENTRYPOINT "OL_ProviderEntryPoint"

typedef OL_Provider* (*OL_ProviderEntryPointProc)();


/*
**==============================================================================
**
** OL_String Helpers
**
**==============================================================================
*/

OL_ALWAYS_INLINE OL_Result OL_Object_AddString(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char* x)
{
    OL_Value v;
    v.type = OL_Type_String;
    v.u.string = (OL_Char*)x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetString(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char* x)
{
    OL_Value v;
    v.type = OL_Type_String;
    v.u.string = (OL_Char*)x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetString(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char** x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_String, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.string;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Binary Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddBinary(
    OL_Object* self,
    const OL_Char* name,
    OL_Binary x)
{
    OL_Value v;
    v.type = OL_Type_Binary;
    v.u.binary = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetBinary(
    OL_Object* self,
    const OL_Char* name,
    OL_Binary x)
{
    OL_Value v;
    v.type = OL_Type_Binary;
    v.u.binary = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetBinary(
    OL_Object* self,
    const OL_Char* name,
    OL_Binary* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Binary, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.binary;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Boolean Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddBoolean(
    OL_Object* self,
    const OL_Char* name,
    OL_Boolean x)
{
    OL_Value v;
    v.type = OL_Type_Boolean;
    v.u.boolean = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetBoolean(
    OL_Object* self,
    const OL_Char* name,
    OL_Boolean x)
{
    OL_Value v;
    v.type = OL_Type_Boolean;
    v.u.boolean = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetBoolean(
    OL_Object* self,
    const OL_Char* name,
    OL_Boolean* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Boolean, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.boolean;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Byte Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddByte(
    OL_Object* self,
    const OL_Char* name,
    OL_Byte x)
{
    OL_Value v;
    v.type = OL_Type_Byte;
    v.u.byte = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetByte(
    OL_Object* self,
    const OL_Char* name,
    OL_Byte x)
{
    OL_Value v;
    v.type = OL_Type_Byte;
    v.u.byte = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetByte(
    OL_Object* self,
    const OL_Char* name,
    OL_Byte* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Byte, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.byte;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_SByte Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddSByte(
    OL_Object* self,
    const OL_Char* name,
    OL_SByte x)
{
    OL_Value v;
    v.type = OL_Type_SByte;
    v.u.sByte = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetSByte(
    OL_Object* self,
    const OL_Char* name,
    OL_SByte x)
{
    OL_Value v;
    v.type = OL_Type_SByte;
    v.u.sByte = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetSByte(
    OL_Object* self,
    const OL_Char* name,
    OL_SByte* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_SByte, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.sByte;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Int16 Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddInt16(
    OL_Object* self,
    const OL_Char* name,
    const OL_Int16 x)
{
    OL_Value v;
    v.type = OL_Type_Int16;
    v.u.int16 = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetInt16(
    OL_Object* self,
    const OL_Char* name,
    const OL_Int16 x)
{
    OL_Value v;
    v.type = OL_Type_Int16;
    v.u.int16 = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetInt16(
    OL_Object* self,
    const OL_Char* name,
    OL_Int16* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Int16, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.int16;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Int32 Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddInt32(
    OL_Object* self,
    const OL_Char* name,
    const OL_Int32 x)
{
    OL_Value v;
    v.type = OL_Type_Int32;
    v.u.int32 = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetInt32(
    OL_Object* self,
    const OL_Char* name,
    const OL_Int32 x)
{
    OL_Value v;
    v.type = OL_Type_Int32;
    v.u.int32 = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetInt32(
    OL_Object* self,
    const OL_Char* name,
    OL_Int32* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Int32, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.int32;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Int64 Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddInt64(
    OL_Object* self,
    const OL_Char* name,
    const OL_Int64 x)
{
    OL_Value v;
    v.type = OL_Type_Int64;
    v.u.int64 = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetInt64(
    OL_Object* self,
    const OL_Char* name,
    const OL_Int64 x)
{
    OL_Value v;
    v.type = OL_Type_Int64;
    v.u.int64 = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetInt64(
    OL_Object* self,
    const OL_Char* name,
    OL_Int64* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Int64, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.int64;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Single Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddSingle(
    OL_Object* self,
    const OL_Char* name,
    OL_Single x)
{
    OL_Value v;
    v.type = OL_Type_Single;
    v.u.single = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetSingle(
    OL_Object* self,
    const OL_Char* name,
    OL_Single x)
{
    OL_Value v;
    v.type = OL_Type_Single;
    v.u.single = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetSingle(
    OL_Object* self,
    const OL_Char* name,
    OL_Single* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Single, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.single;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Double Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddDouble(
    OL_Object* self,
    const OL_Char* name,
    OL_Double x)
{
    OL_Value v;
    v.type = OL_Type_Double;
    v.u.double_ = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetDouble(
    OL_Object* self,
    const OL_Char* name,
    OL_Double x)
{
    OL_Value v;
    v.type = OL_Type_Double;
    v.u.double_ = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetDouble(
    OL_Object* self,
    const OL_Char* name,
    OL_Double* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Double, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.double_;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Decimal Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddDecimal(
    OL_Object* self,
    const OL_Char* name,
    OL_Decimal x)
{
    OL_Value v;
    v.type = OL_Type_Decimal;
    v.u.decimal = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetDecimal(
    OL_Object* self,
    const OL_Char* name,
    OL_Decimal x)
{
    OL_Value v;
    v.type = OL_Type_Decimal;
    v.u.decimal = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetDecimal(
    OL_Object* self,
    const OL_Char* name,
    OL_Decimal* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Decimal, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.decimal;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Date Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddDate(
    OL_Object* self,
    const OL_Char* name,
    OL_Date x)
{
    OL_Value v;
    v.type = OL_Type_Date;
    v.u.date = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetDate(
    OL_Object* self,
    const OL_Char* name,
    OL_Date x)
{
    OL_Value v;
    v.type = OL_Type_Date;
    v.u.date = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetDate(
    OL_Object* self,
    const OL_Char* name,
    OL_Date* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Date, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.date;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_TimeOfDay Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddTimeOfDay(
    OL_Object* self,
    const OL_Char* name,
    OL_TimeOfDay x)
{
    OL_Value v;
    v.type = OL_Type_TimeOfDay;
    v.u.timeOfDay = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetTimeOfDay(
    OL_Object* self,
    const OL_Char* name,
    OL_TimeOfDay x)
{
    OL_Value v;
    v.type = OL_Type_TimeOfDay;
    v.u.timeOfDay = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetTimeOfDay(
    OL_Object* self,
    const OL_Char* name,
    OL_TimeOfDay* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_TimeOfDay, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.timeOfDay;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_DateTimeOffset Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddDateTimeOffset(
    OL_Object* self,
    const OL_Char* name,
    OL_DateTimeOffset x)
{
    OL_Value v;
    v.type = OL_Type_DateTimeOffset;
    v.u.dateTimeOffset = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetDateTimeOffset(
    OL_Object* self,
    const OL_Char* name,
    OL_DateTimeOffset x)
{
    OL_Value v;
    v.type = OL_Type_DateTimeOffset;
    v.u.dateTimeOffset = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetDateTimeOffset(
    OL_Object* self,
    const OL_Char* name,
    OL_DateTimeOffset* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_DateTimeOffset, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.dateTimeOffset;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Duration Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddDuration(
    OL_Object* self,
    const OL_Char* name,
    OL_Duration x)
{
    OL_Value v;
    v.type = OL_Type_Duration;
    v.u.duration = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetDuration(
    OL_Object* self,
    const OL_Char* name,
    OL_Duration x)
{
    OL_Value v;
    v.type = OL_Type_Duration;
    v.u.duration = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetDuration(
    OL_Object* self,
    const OL_Char* name,
    OL_Duration* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Duration, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.duration;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Guid Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddGuid(
    OL_Object* self,
    const OL_Char* name,
    OL_Guid x)
{
    OL_Value v;
    v.type = OL_Type_Guid;
    v.u.guid = x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetGuid(
    OL_Object* self,
    const OL_Char* name,
    OL_Guid x)
{
    OL_Value v;
    v.type = OL_Type_Guid;
    v.u.guid = x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetGuid(
    OL_Object* self,
    const OL_Char* name,
    OL_Guid* x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Guid, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.guid;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Object Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddObject(
    OL_Object* self,
    const OL_Char* name,
    const OL_Object* x)
{
    OL_Value v;
    v.type = OL_Type_Object;
    v.u.object = (OL_Object*)x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetObject(
    OL_Object* self,
    const OL_Char* name,
    const OL_Object* x)
{
    OL_Value v;
    v.type = OL_Type_Object;
    v.u.object = (OL_Object*)x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetObject(
    OL_Object* self,
    const OL_Char* name,
    const OL_Object** x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Object, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.object;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_Array Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddArray(
    OL_Object* self,
    const OL_Char* name,
    const OL_Array* x)
{
    OL_Value v;
    v.type = OL_Type_Array;
    v.u.array = (OL_Array*)x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetArray(
    OL_Object* self,
    const OL_Char* name,
    const OL_Array* x)
{
    OL_Value v;
    v.type = OL_Type_Array;
    v.u.array = (OL_Array*)x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetArray(
    OL_Object* self,
    const OL_Char* name,
    const OL_Array** x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_Array, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.array;

    return OL_Result_Ok;
}


/*
**==============================================================================
**
** OL_NavigationLink Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddNavigationLink(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char* x)
{
    OL_Value v;
    v.type = OL_Type_NavigationLink;
    v.u.navigationLink = (OL_Char*)x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetNavigationLink(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char* x)
{
    OL_Value v;
    v.type = OL_Type_NavigationLink;
    v.u.navigationLink = (OL_Char*)x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetNavigationLink(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char** x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_NavigationLink, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.navigationLink;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_AssociationLink Helpers
**
**==============================================================================
*/

OL_INLINE OL_Result OL_Object_AddAssociationLink(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char* x)
{
    OL_Value v;
    v.type = OL_Type_AssociationLink;
    v.u.associationLink = (OL_Char*)x;
    return OL_Object_Add(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_SetAssociationLink(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char* x)
{
    OL_Value v;
    v.type = OL_Type_AssociationLink;
    v.u.associationLink = (OL_Char*)x;
    return OL_Object_Set(self, name, (OL_Value*)&v);
}

OL_INLINE OL_Result OL_Object_GetAssociationLink(
    OL_Object* self,
    const OL_Char* name,
    const OL_Char** x)
{
    OL_Value v;
    OL_Result r = OL_Object_GetAs(
        self, name, OL_Type_AssociationLink, (OL_Value*)&v);

    if (r != OL_Result_Ok)
        return r;

    if (x)
        *x = v.u.associationLink;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** OL_StringValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_StringValue(const OL_Char* str)
{
    OL_Value v;
    v.u.string = (OL_Char*)str;
    v.type = OL_Type_String;
    return v;
}

/*
**==============================================================================
**
** OL_BinaryValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_BinaryValue(
    const void* data,
    size_t size)
{
    OL_Value v;
    v.u.binary.data = (void*)data;
    v.u.binary.size = size;
    v.type = OL_Type_Binary;
    return v;
}

/*
**==============================================================================
**
** OL_BooleanValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_BooleanValue(const OL_Boolean x)
{
    OL_Value v;
    v.u.boolean = x;
    v.type = OL_Type_Boolean;
    return v;
}

/*
**==============================================================================
**
** OL_ByteValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_ByteValue(const OL_Byte x)
{
    OL_Value v;
    v.u.byte = x;
    v.type = OL_Type_Byte;
    return v;
}

/*
**==============================================================================
**
** OL_SByteValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_SByteValue(const OL_SByte x)
{
    OL_Value v;
    v.u.sByte = x;
    v.type = OL_Type_SByte;
    return v;
}

/*
**==============================================================================
**
** OL_Int16Value()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_Int16Value(const OL_Int16 x)
{
    OL_Value v;
    v.u.int16 = x;
    v.type = OL_Type_Int16;
    return v;
}

/*
**==============================================================================
**
** OL_Int32Value()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_Int32Value(const OL_Int32 x)
{
    OL_Value v;
    v.u.int32 = x;
    v.type = OL_Type_Int32;
    return v;
}

/*
**==============================================================================
**
** OL_Int64Value()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_Int64Value(const OL_Int64 x)
{
    OL_Value v;
    v.u.int64 = x;
    v.type = OL_Type_Int64;
    return v;
}

/*
**==============================================================================
**
** OL_SingleValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_SingleValue(const OL_Single x)
{
    OL_Value v;
    v.u.single = x;
    v.type = OL_Type_Single;
    return v;
}

/*
**==============================================================================
**
** OL_DoubleValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_DoubleValue(const OL_Double x)
{
    OL_Value v;
    v.u.double_ = x;
    v.type = OL_Type_Double;
    return v;
}

/*
**==============================================================================
**
** OL_DecimalValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_DecimalValue(const OL_Decimal x)
{
    OL_Value v;
    v.u.decimal = x;
    v.type = OL_Type_Decimal;
    return v;
}

/*
**==============================================================================
**
** OL_DateValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_DateValue(
    unsigned int year,
    unsigned int month,
    unsigned int day)
{
    OL_Value v;
    v.u.date.year = year;
    v.u.date.month = month;
    v.u.date.day = day;
    v.type = OL_Type_Date;
    return v;
}

/*
**==============================================================================
**
** OL_TimeOfDayValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_TimeOfDayValue(
    unsigned int hour,
    unsigned int minute,
    unsigned int second,
    unsigned long long fractionalSecond)
{
    OL_Value v;
    v.u.timeOfDay.hour = hour;
    v.u.timeOfDay.minute = minute;
    v.u.timeOfDay.second = second;
    v.u.timeOfDay.fractionalSecond = fractionalSecond;
    v.type = OL_Type_TimeOfDay;
    return v;
}

/*
**==============================================================================
**
** OL_DateTimeOffsetValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_DateTimeOffsetValue(
    unsigned int year,
    unsigned int month,
    unsigned int day,
    unsigned int hour,
    unsigned int minute,
    unsigned int second,
    unsigned long long fractionalSecond)
{
    OL_Value v;
    v.u.dateTimeOffset.year = year;
    v.u.dateTimeOffset.month = month;
    v.u.dateTimeOffset.day = day;
    v.u.dateTimeOffset.hour = hour;
    v.u.dateTimeOffset.minute = minute;
    v.u.dateTimeOffset.second = second;
    v.u.dateTimeOffset.fractionalSecond = fractionalSecond;
    v.type = OL_Type_DateTimeOffset;
    return v;
}

/*
**==============================================================================
**
** OL_DurationValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_DurationValue(
    OL_Boolean negative,
    unsigned int days,
    unsigned int hour,
    unsigned int minute,
    unsigned int second,
    unsigned long long fractionalSecond)
{
    OL_Value v;
    v.u.duration.negative = negative;
    v.u.duration.days = days;
    v.u.duration.hour = hour;
    v.u.duration.minute = minute;
    v.u.duration.second = second;
    v.u.duration.fractionalSecond = fractionalSecond;
    v.type = OL_Type_Duration;
    return v;
}

/*
**==============================================================================
**
** OL_GuidValue()
**
**==============================================================================
*/

/* AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE */
OL_INLINE OL_Value OL_GuidValue(
    unsigned int data1, /* AAAAAAAA */
    unsigned short data2, /* BBBB */
    unsigned short data3, /* CCCC */
    unsigned short data4, /* DDDD */
    unsigned short data5, /* EEEE */
    unsigned int data6) /* EEEEEEEE */
{
    OL_Value v;
    v.type = OL_Type_Guid;
    v.u.guid.data1 = data1;
    v.u.guid.data2 = data2;
    v.u.guid.data3 = data3;
    v.u.guid.data4 = data4;
    v.u.guid.data5 = data5;
    v.u.guid.data6 = data6;
    return v;
}

/*
**==============================================================================
**
** OL_ObjectValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_ObjectValue(OL_Object* x)
{
    OL_Value v;
    v.u.object = x;
    v.type = OL_Type_Object;
    return v;
}

/*
**==============================================================================
**
** OL_ArrayValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_ArrayValue(OL_Array* x)
{
    OL_Value v;
    v.u.array = x;
    v.type = OL_Type_Array;
    return v;
}

/*
**==============================================================================
**
** OL_NavigationLinkValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_NavigationLinkValue(OL_NavigationLink x)
{
    OL_Value v;
    v.u.navigationLink = x;
    v.type = OL_Type_NavigationLink;
    return v;
}

/*
**==============================================================================
**
** OL_AssociationLinkValue()
**
**==============================================================================
*/

OL_INLINE OL_Value OL_AssociationLinkValue(OL_AssociationLink x)
{
    OL_Value v;
    v.u.associationLink = x;
    v.type = OL_Type_AssociationLink;
    return v;
}

/*
**==============================================================================
**
** Meta Data Typedefs
**
**==============================================================================
*/

typedef struct _EDM_Action EDM_Action;
typedef struct _EDM_ComplexType EDM_ComplexType;
typedef struct _EDM_EntityType EDM_EntityType;
typedef struct _EDM_EnumType EDM_EnumType;
typedef struct _EDM_ExtendedProperty EDM_ExtendedProperty;
typedef struct _EDM_Function EDM_Function;
typedef struct _EDMX_IncludeAnnotations EDMX_IncludeAnnotations;
typedef struct _EDMX_Include EDMX_Include;
typedef struct _EDM_Key EDM_Key;
typedef struct _EDM_Member EDM_Member;
typedef struct _EDM_NavigationProperty EDM_NavigationProperty;
typedef struct _EDM_Parameter EDM_Parameter;
typedef struct _EDM_Property EDM_Property;
typedef struct _EDM_PropertyRef EDM_PropertyRef;
typedef struct _EDMX_Reference EDMX_Reference;
typedef struct _EDM_Schema EDM_Schema;
typedef struct _EDM_Singleton EDM_Singleton;
typedef struct _EDM_TypeDefinition EDM_TypeDefinition;
typedef struct _EDM_EntityContainer EDM_EntityContainer;
typedef struct _EDM_Term EDM_Term;
typedef struct _EDM_ExtendedTerm EDM_ExtendedTerm;
typedef struct _EDMX_DataServices EDMX_DataServices;

/*
**==============================================================================
**
** EDMX_Include
**
**==============================================================================
*/

struct _EDMX_Include
{
    const char* Namespace; /* required */
    const char* Alias; /* optional */
};

/*
**==============================================================================
**
** EDMX_IncludeAnnotations
**
**==============================================================================
*/

struct _EDMX_IncludeAnnotations
{
    const char* TermNamespace; /* required */
    const char* Qualifier; /* optional */
    const char* TargetNamespace; /* optional */
};

/*
**==============================================================================
**
** EDMX_Reference
**
**==============================================================================
*/

struct _EDMX_Reference
{
    const char* Uri;

    const EDMX_Include* const* Includes;
    size_t NumIncludes;

    const EDMX_IncludeAnnotations* const* IncludeAnnotations;
    size_t NumIncludeAnnotations;
};

/*
**==============================================================================
**
** EDM_Property
**
**==============================================================================
*/

struct _EDM_Property
{
    unsigned char Nullable;
    unsigned char Extended;
    const char* Name;
    const char* Type;
};

struct _EDM_ExtendedProperty /* extends EDM_Property */
{
    /* Inherited properties */
    unsigned char Nullable;
    unsigned char Extended;
    const char* Name;
    const char* Type;

    /* Extended properties */
    const char* MaxLength;
    const char* Precision;
    const char* Scale;
    const char* Unicode;
    const char* SRID;
    const char* DefaultValue;
};

/*
**==============================================================================
**
** EDM_NavigationProperty
**
**==============================================================================
*/

#define EDM_NavigationProperty_Flags_Nullable            (1 << 0)
#define EDM_NavigationProperty_Flags_ContainsTarget      (1 << 1)

struct _EDM_NavigationProperty
{
    unsigned int Flags;
    const char* Name;
    const char* Type;
    const char* Partner;
};

/*
**==============================================================================
**
** EDM_PropertyRef
**
**==============================================================================
*/

struct _EDM_PropertyRef
{
    const char* Name;
    const char* Alias;
};

/*
**==============================================================================
**
** EDM_Key
**
**==============================================================================
*/

struct _EDM_Key
{
    EDM_PropertyRef PropertyRef;
};

/*
**==============================================================================
**
** EDM_EntityType
**
**==============================================================================
*/

struct _EDM_EntityType
{
    const char* Name;
    const char* BaseType;
    const char* Abstract;
    const char* OpenType;
    const char* HasStream;

    const EDM_Key* Key;

    const EDM_Property* const* Properties;
    size_t NumProperties;

    const EDM_NavigationProperty* const* NavigationProperties;
    size_t NumNavigationProperties;
};

/*
**==============================================================================
**
** EDM_ComplexType
**
**==============================================================================
*/

struct _EDM_ComplexType
{
    const char* Name;
    const char* BaseType;
    const char* Abstract;
    const char* OpenType;

    const EDM_Property* const* Properties;
    size_t NumProperties;

    const EDM_NavigationProperty* const* NavigationProperties;
    size_t NumNavigationProperties;
};

/*
**==============================================================================
**
** EDM_Member
**
**==============================================================================
*/

struct _EDM_Member
{
    const char* Name;
    const char* Value;
};

typedef enum _EDM_MemberType
{
    EDM_MemberType_Struct, /* Members are EDM_Member structures */
    EDM_MemberType_String  /* Members are simple strings */
}
EDM_MemberType;

/*
**==============================================================================
**
** EDM_EnumType
**
**==============================================================================
*/

#define EDM_EnumType_Flags_IsFlags       (1 << 0) /* default=false */

struct _EDM_EnumType
{
    const char* Name;
    const char* UnderlyingType;
    const char* IsFlags;
    EDM_MemberType MemberType;
    const void** const Members;
    size_t NumMembers;
};

/*
**==============================================================================
**
** EDM_Schema
**
**==============================================================================
*/

struct _EDM_Schema
{
    const char* Namespace;
    const char* Alias;

    const EDM_EntityType* const* EntityTypes;
    size_t NumEntityTypes;

    const EDM_ComplexType* const* ComplexTypes;
    size_t NumComplexTypes;

    const EDM_EnumType* const* EnumTypes;
    size_t NumEnumTypes;

    const EDM_Action* const* Actions;
    size_t NumActions;

    const EDM_TypeDefinition* const* TypeDefinitions;
    size_t NumTypeDefinitions;

    const EDM_EntityContainer* const* EntityContainers;
    size_t NumEntityContainers;

    const EDM_Term* const* Terms;
    size_t NumTerms;
};

/*
**==============================================================================
**
** EDM_Parameter
**
**==============================================================================
*/

struct _EDM_Parameter
{
    const char* Name;
    const char* Type;
    const char* Nullable;
};

/*
**==============================================================================
**
** EDM_Action
**
**==============================================================================
*/

struct _EDM_Action
{
    const char* Name;
    const char* EntitySetPath;
    const char* IsBound;
    const EDM_Parameter* const* Parameters;
    size_t NumParameters;
};

/*
**==============================================================================
**
** EDM_Function
**
**==============================================================================
*/

#define EDM_Function_Flags_IsBound (1 << 0) /* default=false */
#define EDM_Function_Flags_IsComposable (1 << 0) /* default=false */

struct _EDM_Function
{
    unsigned int Flags;
    const char* Name;
    const char* EntitySetPath;
    const char* ReturnType;
    const char* Type;
    const EDM_Parameter* const* Parameters;
    size_t NumParameters;
};

/*
**==============================================================================
**
** EDM_TypeDefinition
**
**==============================================================================
*/

struct _EDM_TypeDefinition
{
    const char* Name;
    const char* UnderlyingType;
};

/*
**==============================================================================
**
** EDMX_DataServices
**
**==============================================================================
*/

struct _EDMX_DataServices
{
    /* Must contain one or more */
    const EDM_Schema* const* Schemas;
    size_t NumSchemas;
};

/*
**==============================================================================
**
** EDMX_Edmx
**
**==============================================================================
*/

struct _EDMX_Edmx
{
    /* May contain zero or more */
    const EDMX_Reference* const* References;
    size_t NumReferences;

    /* Must contain one */
    const EDMX_DataServices* DataServices;
};

/*
**==============================================================================
**
** EDM_Singleton
**
**==============================================================================
*/

struct _EDM_Singleton
{
    const char* Name;
    const char* Type;
};

/*
**==============================================================================
**
** EDM_EntityContainer
**
**==============================================================================
*/

struct _EDM_EntityContainer
{
    const char* Name; /* required */
    const char* Extends; /* optional */
    const EDM_Singleton* const* Singletons;
    size_t NumSingletons;
};

/*
**==============================================================================
**
** EDM_Term
**
**==============================================================================
*/

struct _EDM_Term
{
    unsigned char Nullable;
    unsigned char Extended;
    const char* Name; /* required */
    const char* Type ; /* required */
};

struct _EDM_ExtendedTerm /* extends EDM_Term */
{
    unsigned char Nullable;
    unsigned char Extended;
    const char* Name; /* required */
    const char* Type; /* required */

    const char* BaseTerm;
    const char* AppliesTo;
    const char* DefaultValue;
    const char* MaxLength;
    const char* Precision;
    const char* Scale;
    const char* SRID;
};

OL_EXTERNC_END

#endif /* _odata_h */
