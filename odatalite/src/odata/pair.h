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
#ifndef _odata_pair_h
#define _odata_pair_h

#include <base/alloc.h>
#include <base/str.h>
#include "json.h"
#include "types.h"
#include "destructors.h"

typedef struct _Pair
{
    char* name;
    size_t nameLen;
    unsigned int nameCode;
    JSON_Value value;
    unsigned int flags;

    /* extra memory allocated by the Binary getter */
    void* binaryData;

    /* Type passed to set function (maybe different than internal type) */
    unsigned short type;
}
Pair;

int PairConstruct(
    Pair* pair,
    const char* name,
    size_t nameLen,
    unsigned int nameCode,
    const JSON_Value* value,
    unsigned int flags,
    Alloc* alloc);

void __PairDestruct(
    Pair* pair,
    Alloc* alloc);

ALWAYS_INLINE void PairDestruct(
    Pair* pair,
    Alloc* alloc)
{
    if ((pair->flags & JSON_FLAG_STATIC_NAME) &&
        (pair->flags & JSON_FLAG_STATIC_VALUE) &&
        pair->type == JSON_Type_String)
    {
        return;
    }

    __PairDestruct(pair, alloc);
}

int PairSet(
    Pair* pair,
    const JSON_Value* value,
    unsigned int flags,
    Alloc* alloc);

OL_Result PairGet(
    const Pair* pair,
    JSON_Value* value,
    unsigned int* flags,
    Alloc* alloc);

/* Call when
 *     type is JSON_Type_String
 *     flags contains JSON_FLAG_LENGTH_NAME
 *     flags contains JSON_FLAG_STATIC_NAME
 *     flags contains JSON_FLAG_STATIC_VALUE
 */
INLINE void PairConstructStringSpecial(
    Pair* pair,
    const char* name,
    unsigned int nameCode,
    const JSON_Value* value)
{
    pair->nameLen = name[-1];
    pair->nameCode = nameCode;
    pair->name = (char*)name;

    pair->value.type = JSON_Type_String;
    pair->value.u.string = value->u.string;

    pair->flags = 
        JSON_FLAG_LENGTH_NAME |
        JSON_FLAG_STATIC_NAME |
        JSON_FLAG_STATIC_VALUE;
    pair->type = JSON_Type_String;
}

/* Call when all these are true:
 *     (pair->type == JSON_Type_String)
 *     (pair->flags & JSON_FLAG_STATIC_NAME)
 *     (pair->flags & JSON_FLAG_STATIC_VALUE)
 *     (type == JSON_Type_String)
 *     (flags & JSON_FLAG_STATIC_NAME)
 *     (flags & JSON_FLAG_STATIC_VALUE)
 */
INLINE void PairSetStringSpecial(
    Pair* pair,
    const JSON_Value* value,
    Alloc* alloc)
{
    pair->value.u.string = value->u.string;
    pair->type = JSON_Type_String;
}

#endif /* _odata_pair_h */
