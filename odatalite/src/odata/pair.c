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
#include <string.h>
#include <base/alloc.h>
#include <base/str.h>
#include "pair.h"
#include "types.h"
#include "name.h"
#include "getters.h"
#include "setters.h"
#include "destructors.h"

int PairConstruct(
    Pair* pair,
    const char* name,
    size_t nameLen,
    unsigned int nameCode,
    const JSON_Value* value,
    unsigned int flags,
    Alloc* alloc)
{
    /* Set Pair.nameLen */
    pair->nameLen = nameLen;

    /* Set Pair.nameCode */
    pair->nameCode = nameCode;

    /* Set Pair.name */
    if (!(pair->name = NameDup(alloc, name, pair->nameLen, flags)))
        return -1;

    /* Set Pair.value */
    if (value->type == JSON_Type_String && (flags & JSON_FLAG_STATIC_VALUE))
    {
        pair->value.type = JSON_Type_String;
        pair->value.u.string = value->u.string;
    }
    else
    {
        ValueSetter setter = GetSetter(value->type);

        if (!setter)
            return -1;

        if ((*setter)(&pair->value, value, flags, alloc) != 0)
        {
            AllocPut(alloc, pair->name);
            return -1;
        }
    }

    /* Set Pair.flags */
    pair->flags = flags;

    /* Set Pair.type */
    pair->type = value->type;

    /* Set Pair.binaryData */
    pair->binaryData = NULL;

    return 0;
}

void __PairDestruct(
    Pair* pair,
    Alloc* alloc)
{
    /* Release Pair.name */
    if (!(pair->flags & JSON_FLAG_STATIC_NAME))
        AllocPut(alloc, pair->name);

    if (pair->type == JSON_Type_String && (pair->flags&JSON_FLAG_STATIC_VALUE))
    {
        return;
    }

    /* Release Pair.value */
    {
        ValueDestructor dtor = GetDestructor(pair->value.type);

        if (dtor)
            (*dtor)(&pair->value, pair->flags, alloc);
    }

    /* Release binary data (allocated by get operation) */
    if (pair->binaryData)
        AllocPut(alloc, pair->binaryData);
}

int PairSet(
    Pair* pair,
    const JSON_Value* value,
    unsigned int flags,
    Alloc* alloc)
{
    JSON_Value tmpValue;

    /* Construct the new value */
    {
        ValueSetter setter = GetSetter(value->type);

        if (!setter)
            return -1;

        if ((*setter)(&tmpValue, value, flags, alloc) != 0)
        {
            return -1;
        }
    }

    /* Destruct the old value */
    {
        ValueDestructor dtor = GetDestructor(pair->value.type);

        if (dtor)
            (*dtor)(&pair->value, pair->flags, alloc);
    }

    /* Set Pair.value */
    pair->value = tmpValue;

    /* Pair.flags */
    if (flags & JSON_FLAG_STATIC_VALUE)
        pair->flags |= JSON_FLAG_STATIC_VALUE;

    /* Set Pair.type */
    pair->type = value->type;

    return 0;
}

OL_Result PairGet(
    const Pair* pair,
    JSON_Value* value,
    unsigned int* flags,
    Alloc* alloc)
{
    unsigned short getAsType;

    if (flags && *flags & JSON_FLAG_GET_AS_TYPE)
        getAsType = value->type;
    else
        getAsType = pair->type;

    /* Get the value */
    {
        ValueGetter getter = GetGetter(getAsType);

        if (!getter)
            return OL_Result_UnknownType;

        if ((*getter)(value, &pair->value, getAsType, flags, alloc) != 0)
            return OL_Result_TypeMismatch;

        if (pair->type == OL_Type_Binary)
        {
            if (pair->binaryData)
                AllocPut(alloc, ((Pair*)pair)->binaryData);

            ((Pair*)pair)->binaryData = ((OL_Value*)value)->u.binary.data;
        }
    }

    return OL_Result_Ok;
}
