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
#include "odata.h"
#include <base/buf.h>
#include <base/roundpow2.h>
#include "jsonarray.h"
#include "types.h"
#include "getters.h"
#include "setters.h"
#include "destructors.h"
#include "return.h"

#define ARRAY_MIN_CAPACITY 8

extern JSON_ArrayFT __JSON_Array_ft;

static void _DestructArrayElements(
    JSONArray* self)
{
    size_t i;

    for (i = 0; i < self->count; i++)
    {
        JSONArrayElement* elem = &self->elements[i];

        if (elem->binaryData)
            AllocPut(&self->alloc, elem->binaryData);

        if (elem->type == JSON_Type_String &&
            (elem->flags & JSON_FLAG_STATIC_VALUE))
        {
            continue;
        }

        {
            ValueDestructor dtor = GetDestructor(elem->value.type);

            if (dtor)
                (*dtor)(&elem->value, elem->flags, &self->alloc);
        }
    }
}

static OL_Result _AddRef(
    const JSON_Array* self_)
{
    JSONArray* self = (JSONArray*)self_;

    if (!self || self->magic != ARRAY_MAGIC)
        RETURN(OL_Result_BadParameter);

    if (self->refCount == 0)
        RETURN(OL_Result_Failed);

    /* Increment the reference count */
    self->refCount++;

    return OL_Result_Ok;
}

static OL_Result _Release(
    JSON_Array* self_)
{
    JSONArray* self = (JSONArray*)self_;

    /* Check the parameters */
    if (!self || self->magic != ARRAY_MAGIC)
        RETURN(OL_Result_BadParameter);

    DEBUG_ASSERT(self->refCount != 0);

    /* Decrement the reference count */
    if (--self->refCount != 0)
        return OL_Result_Ok;

    /* Destruct each JSONArray.element[i] */
    _DestructArrayElements(self);

    /* Free JSONArray.elements[] */
    AllocPut(&self->alloc, self->elements);

    /* Clear JSONArray.magic (to detect subsequent invalid 'self' pointer use) */
    self->magic = 0xDDDDDDDD;

    /* Free the array structure */
    Free(self);

    return OL_Result_Ok;
}

static JSON_Array* _Clone(
    const JSON_Array* self_)
{
    const JSONArray* self = (const JSONArray*)self_;
    JSONArray* newArray;
    const size_t ALLOCBUFSIZE = 1024;
    size_t n;
    size_t i;

    /* Check parameters */
    if (!self || self->magic != ARRAY_MAGIC)
        return NULL;
    
    /* Align size to next multiple of 8 */
    n = ((sizeof(JSONArray) + 7) & ~7);

    /* Allocate the memory (self + alignment + extra bytes) */
    if (!(newArray = (JSONArray*)Malloc(n + ALLOCBUFSIZE)))
        return NULL;

    /* Set JSONArray.ft */
    newArray->base.ft = &__JSON_Array_ft;

    /* Set JSONArray.magic */
    newArray->magic = ARRAY_MAGIC;

    /* Set JSONArray.refCount */
    newArray->refCount = 1;

    /* Initialize JSONArray.alloc */
    AllocInit(&newArray->alloc, (char*)newArray + n, ALLOCBUFSIZE);

    /* Allocate JSONArray.elements[] */
    if (!(newArray->elements = AllocGet(
        &newArray->alloc,
        self->capacity * sizeof(JSONArrayElement))))
    {
        _Release(&newArray->base);
        return NULL;
    }

    /* Set JSONArray.count */
    newArray->count = 0;

    /* Set JSONArray.capacity */
    newArray->capacity = self->capacity;

    /* Set JSONArray.flags */
    if (self->flags & OL_FLAG_HOMOGENEOUS_ARRAY)
        newArray->flags = OL_FLAG_HOMOGENEOUS_ARRAY;

    /* Set JSONArray.type */
    newArray->type = self->type;

    /* Copy JSONArray.elements[] */
    for (i = 0; i < self->count; i++)
    {
        /* ArrayElem.value */
        {
            ValueSetter setter = GetSetter(self->elements[i].type);

            if (!setter)
            {
                _Release(&newArray->base);
                return NULL;
            }

            if ((*setter)(
                &newArray->elements[i].value, 
                &self->elements[i].value, 
                0, 
                &newArray->alloc) != 0)
            {
                _Release(&newArray->base);
                return NULL;
            }
        }

        /* ArrayElem.type */
        newArray->elements[i].type = self->elements[i].type;

        /* ArrayElem.flags */
        newArray->elements[i].flags = 0;

        /* ArrayElem.binaryData */
        newArray->elements[i].binaryData = NULL;

        /* JSONArray.count */
        newArray->count++;
    }

    return &newArray->base;
}

static OL_Result _Clear(
    JSON_Array* self_)
{
    JSONArray* self = (JSONArray*)self_;

    /* Check the parameters */
    if (!self || self->magic != ARRAY_MAGIC)
        RETURN(OL_Result_BadParameter);

    DEBUG_ASSERT(self->refCount != 0);

    /* Destruct each JSONArray.element[i] */
    _DestructArrayElements(self);

    /* JSONArray.count */
    self->count = 0;

    /* JSONArray.type */
    self->type = 0;

    return OL_Result_Ok;
}

static OL_Result _SetFlags(
    JSON_Array* self_,
    unsigned int flags)
{
    JSONArray* self = (JSONArray*)self_;
    unsigned int f = 0;

    if (!self || self->magic != ARRAY_MAGIC)
        RETURN(OL_Result_BadParameter);

    if (flags & JSON_FLAG_STATIC_VALUE)
    {
        f |= JSON_FLAG_STATIC_VALUE;
        flags &= ~JSON_FLAG_STATIC_VALUE;
    }

    if (flags & JSON_FLAG_HOMOGENEOUS_ARRAY)
    {
        f |= JSON_FLAG_HOMOGENEOUS_ARRAY;
        flags &= ~JSON_FLAG_HOMOGENEOUS_ARRAY;
    }

    /* If any unconsumed flags */
    if (flags)
        RETURN(OL_Result_Failed);

    self->flags = f;
    return OL_Result_Ok;
}

static size_t _Count(
    const JSON_Array* self_)
{
    const JSONArray* self = (const JSONArray*)self_;

    if (!self || self->magic != ARRAY_MAGIC)
        return (size_t)-1;

    return self->count;
}

static OL_Result _Append(
    JSON_Array* self_,
    const JSON_Value* value,
    unsigned int flags)
{
    JSONArray* self = (JSONArray*)self_;

    /* Check parameters */
    if (!self || self->magic != ARRAY_MAGIC || !value)
        RETURN(OL_Result_BadParameter);

    /* Check type for homogeneous arrays */
    if ((self->flags & OL_FLAG_HOMOGENEOUS_ARRAY) &&
        self->count > 0 &&
        self->type != value->type)
    {
        RETURN(OL_Result_TypeMismatch);
    }

    /* Add array-level flags */
    flags |= self->flags;

    /* Extend allocation to make room for new elements */
    if (self->count + 1 > self->capacity)
    {
        JSONArrayElement* elements;
        unsigned int capacity = self->count + 1;

        if (capacity < ARRAY_MIN_CAPACITY)
            capacity = ARRAY_MIN_CAPACITY;
        else
            capacity = RoundPow2(capacity);

        /* Allocate memory */
        if (AllocResize(
            &self->alloc,
            self->elements,
            capacity * sizeof(JSONArrayElement),
            self->capacity * sizeof(JSONArrayElement),
            (void**)&elements))
        {
            RETURN(OL_Result_Failed);
        }

        self->elements = elements;
        self->capacity = capacity;
    }

    /* Add new element */
    {
        JSONArrayElement* elem = &self->elements[self->count];

        /* JSONArrayElement.value */
        if (value->type == JSON_Type_String && (flags & JSON_FLAG_STATIC_VALUE))
        {
            elem->value.type = JSON_Type_String;
            elem->value.u.string = value->u.string;
        }
        else
        {
            ValueSetter setter;

            if (!(setter = GetSetter(value->type)))
                RETURN(OL_Result_Failed);

            if ((*setter)(&elem->value, value, flags, &self->alloc) != 0)
                RETURN(OL_Result_Failed);
        }

        /* JSONArrayElement.flags */
        elem->flags = flags;

        /* JSONArrayElement.type */
        elem->type = value->type;

        /* JSONArrayElement.binaryData */
        elem->binaryData = NULL;

        /* Increment element count */
        self->count++;
    }

    self->type = value->type;

    return OL_Result_Ok;
}

static OL_Result _Set(
    JSON_Array* self_, 
    size_t index,
    const JSON_Value* value,
    unsigned int flags)
{
    JSONArray* self = (JSONArray*)self_;

    /* Check parameters */
    if (!self || self->magic != ARRAY_MAGIC || !value)
        RETURN(OL_Result_BadParameter);

    /* Check for bounds error */
    if (index >= self->count)
        RETURN(OL_Result_OutOfBounds);

    /* Check type */
    if ((self->flags & JSON_FLAG_HOMOGENEOUS_ARRAY) &&
        value->type != self->type)
    {
        RETURN(OL_Result_TypeMismatch);
    }

    /* Replace existing value */
    {
        JSONArrayElement newElem;
        JSONArrayElement* oldElem = &self->elements[index];
        ValueDestructor dtor;

        if (oldElem->binaryData)
        {
            AllocPut(&self->alloc, oldElem->binaryData);
            oldElem->binaryData = NULL;
        }

        {
            ValueSetter setter;

            if (!(setter = GetSetter(value->type)))
                RETURN(OL_Result_Failed);

            if ((*setter)(&newElem.value, value, flags, &self->alloc) != 0)
                RETURN(OL_Result_Failed);
        }

        if ((dtor = GetDestructor(oldElem->value.type)))
            (*dtor)(&oldElem->value, oldElem->flags, &self->alloc);

        self->elements[index] = newElem;
    }

    return OL_Result_Ok;
}

static OL_Result _Get(
    const JSON_Array* self_,
    size_t index,
    JSON_Value* value,
    unsigned int* flags)
{
    const JSONArray* self = (const JSONArray*)self_;

    /* Check parameters */
    if (!self || self->magic != ARRAY_MAGIC)
        RETURN(OL_Result_BadParameter);

    /* Check for bounds error */
    if (index >= self->count)
        RETURN(OL_Result_OutOfBounds);

    /* Set 'value' parameter */
    if (value)
    {
        const JSONArrayElement* elem = &self->elements[index];
        unsigned short getAsType;

        /* Resolve the 'getAsType' */
        if (flags && *flags & JSON_FLAG_GET_AS_TYPE)
            getAsType = value->type;
        else
            getAsType = elem->type;

        /* Get value */
        {
            ValueGetter getter = GetGetter(getAsType);

            if (!(getter = GetGetter(getAsType)))
                RETURN(OL_Result_Failed);

            if ((*getter)(value, &elem->value, getAsType, flags,
                (Alloc*)&self->alloc) != 0)
            {
                RETURN(OL_Result_TypeMismatch);
            }

            if (elem->type == OL_Type_Binary)
            {
                if (elem->binaryData)
                {
                    AllocPut(
                        (Alloc*)&self->alloc, 
                        ((JSONArrayElement*)elem)->binaryData);
                }

                ((JSONArrayElement*)elem)->binaryData = 
                    ((OL_Value*)value)->u.binary.data;
            }
        }
    }

    return OL_Result_Ok;
}

static OL_Result _Remove(
    JSON_Array* self_,
    size_t index)
{
    JSONArray* self = (JSONArray*)self_;

    /* Check parameters */
    if (!self || self->magic != ARRAY_MAGIC)
        RETURN(OL_Result_BadParameter);

    /* Check for bounds error */
    if (index >= self->count)
        RETURN(OL_Result_OutOfBounds);

    /* Destruct this element */
    {
        JSONArrayElement* elem = &self->elements[index];
        ValueDestructor dtor;

        if (elem->binaryData)
            AllocPut(&self->alloc, elem->binaryData);

        if ((dtor = GetDestructor(elem->value.type)))
            (*dtor)(&elem->value, elem->flags, &self->alloc);
    }

    /* Remove the pair from the array */
    {
        size_t r = self->count - index - 1;

        if (r)
        {
            memmove(
                &self->elements[index], 
                &self->elements[index+1], 
                r * sizeof(JSONArrayElement));
        }

        self->count--;
    }

    /* If the number of elements is now zero, clear the type */
    if (self->count == 0)
        self->type = 0;

    return OL_Result_Ok;
}

static OL_Result _Print(
    const JSON_Array* self,
    size_t indent)
{
    extern OL_Result __SerializeArray(
        Buf* out,
        const JSON_Value* v,
        size_t depth);
    OL_Result r;
    Buf out = BUF_INITIALIZER;
    JSON_Value v;

    v.type = JSON_Type_Array;
    v.u.array = (JSON_Array*)self;

    if ((r = __SerializeArray(&out, &v, indent)) != OL_Result_Ok)
        return r;

    printf("%.*s\n", (int)out.size, out.data);

    Free(out.data);

    return OL_Result_Ok;
}

JSON_ArrayFT __JSON_Array_ft =
{
    _AddRef,
    _Release,
    _Clone,
    _Clear,
    _SetFlags,
    _Count,
    _Append,
    _Set,
    _Get,
    _Remove,
    _Print,
};

JSON_Array* JSON_Array_New()
{
    JSONArray* self;
    size_t allocBufSize;
    size_t n;
    
    /* Align size to next multiple of 8 */
    n = ((sizeof(JSONArray) + 7) & ~7);

    /* Compute allocBufSize */
    allocBufSize = ARRAY_MIN_CAPACITY * sizeof(JSONArrayElement) + 256;

    /* Allocate array structure */
    if (!(self = (JSONArray*)Malloc(n + allocBufSize)))
        return NULL;

    /* Set JSONArray.ft */
    self->base.ft = &__JSON_Array_ft;

    /* Set JSONArray.magic */
    self->magic = ARRAY_MAGIC;

    /* Set JSONArray.refCount */
    self->refCount = 1;

    /* Set JSONArray.alloc */
    AllocInit(&self->alloc, (char*)self + n, allocBufSize);

    /* Set JSONArray.elements */
    self->elements = NULL;

    /* Set JSONArray.count */
    self->count = 0;

    /* Set JSONArray.capacity */
    self->capacity = 0; 

    /* Set JSONArray.flags */
    self->flags = 0;

    /* Set JSONArray.type */
    self->type = 0;

    return (JSON_Array*)self;
}

