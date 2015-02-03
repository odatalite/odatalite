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
#ifndef _odata_types_h
#define _odata_types_h

#include "json.h"

/*
**==============================================================================
**
** TypeNameOf()
**
**==============================================================================
*/

extern const char* __typeNames[];

OL_INLINE const char* TypeNameOf(unsigned short type)
{
    return __typeNames[type];
}

/*
**==============================================================================
**
** TypeSizeOf()
**
**==============================================================================
*/

extern unsigned char __odataTypeSizes[];

OL_INLINE size_t TypeSizeOf(unsigned short type)
{
    return __odataTypeSizes[type];
}

/*
**==============================================================================
**
** ValueSizeOf()
**
**==============================================================================
*/

extern unsigned char __valueSizes[];

OL_INLINE size_t ValueSizeOf(unsigned short type)
{
    return __valueSizes[type];
}

/*
**==============================================================================
**
** AssignValue()
**
**==============================================================================
*/

OL_INLINE void ValueAssignUnpadded(JSON_Value* lhs, const JSON_Value* rhs)
{
    typedef struct _Value
    {
        JSON_Boolean null;
        unsigned short type;
        union
        {
            unsigned char null;
            unsigned char boolean;
            signed long long integer;
            double real;
            JSON_Char* string;
            JSON_Object* object;
            JSON_Array* array;
        }
        u;
    }
    Value;

    /* Faster than *lhs = *rhs (excludes assignment of padded bytes) */
#if 0 /* strict-aliasing error */
    *((Value*)lhs) = *((Value*)rhs);
#else
    memcpy(lhs, rhs, sizeof(Value));
#endif
}

/*
**==============================================================================
**
** IsRawType()
**
**==============================================================================
*/

OL_INLINE JSON_Boolean IsRawType(JSON_Type type)
{
    return type < JSON_Type_String;
}

/*
**==============================================================================
**
** ODATATypeNameOf()
**
**==============================================================================
*/

extern const char* __odataTypeNames[21];

OL_INLINE const char* ODATATypeNameOf(unsigned short type)
{
    if (type >= OL_ARRAYSIZE(__odataTypeNames))
        return NULL;
    return __odataTypeNames[type];
}

/*
**==============================================================================
**
** ODATATypeSizeOf()
**
**==============================================================================
*/

extern unsigned char __odataTypeSizes[];

OL_INLINE size_t ODATATypeSizeOf(unsigned short type)
{
    return __odataTypeSizes[type];
}

#endif /* _odata_types_h */
