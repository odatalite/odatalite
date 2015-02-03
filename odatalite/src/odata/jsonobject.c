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
#include "name.h"
#include "json.h"
#include <string.h>
#include <stdarg.h>
#include "common.h"
#include "pair.h"
#include <base/iprintf.h>
#include <base/alloc.h>
#include <base/str.h>
#include "jsonobject.h"
#include "getters.h"
#include "setters.h"
#include "destructors.h"
#include "outstream.h"
#include "serialize.h"

#define OBJECT_MIN_CAPACITY 32

extern JSON_ObjectFT __JSON_Object_ft;

static void _Construct(
    JSONObject* self,
    size_t n,
    size_t allocBufSize)
{
    /* Set JSONObject.ft */
    self->base.ft = &__JSON_Object_ft;

    /* Set JSONObject.magic */
    self->magic = OBJECT_MAGIC;

    /* Set JSONObject.refCount */
    self->refCount = 1;

    /* Initialize JSONObject.alloc */
    AllocInit(&self->alloc, (char*)self + n, allocBufSize);

    /* Set JSONObject.pairs */
    self->pairs = NULL;

    /* Set JSONObject.count */
    self->count = 0;

    /* Set JSONObject.capacity */
    self->capacity = 0;

    /* Set JSONObject.flags */
    self->flags = 0;
}

INLINE int _IsValidNavigationLinkName(const char* name)
{
    char* p = strrchr(name, '@');
    return p && strcmp(p, "@odata.navigationLink") == 0;
}

ALWAYS_INLINE size_t _Find(
    const JSONObject* self,
    const char* name,
    unsigned int nameCode)
{
#if 0
    size_t i;

    for (i = 0; i < self->count; i++)
    {
        const Pair* pair = &self->pairs[i];

        if (pair->nameCode == nameCode && strcmp(pair->name, name) == 0)
            return i;
    }

    /* Not found */
    return (size_t)-1;
#else
    const Pair* p = self->pairs;
    const Pair* end = self->pairs + self->count;

    for (; p != end; p++)
    {
        if (p->nameCode == nameCode && strcmp(p->name, name) == 0)
            return p - self->pairs;
    }

    return (size_t)-1;
#endif
}

static OL_Result _AddRef(
    const JSON_Object* self_)
{
    JSONObject* self = (JSONObject*)self_;

    if (!self || self->magic != OBJECT_MAGIC)
        return OL_Result_BadParameter;

    if (self->refCount == 0)
        return OL_Result_Failed;

    /* Increment the reference count */
    self->refCount++;

    return OL_Result_Ok;
}

static OL_Result _Release(
    JSON_Object* self_)
{
    JSONObject* self = (JSONObject*)self_;
    size_t i;

    /* Check the parameters */
    if (!self || self->magic != OBJECT_MAGIC)
        return OL_Result_BadParameter;

    DEBUG_ASSERT(self->refCount != 0);

    /* Decrement the reference count */
    if (--self->refCount != 0)
        return OL_Result_Ok;

    /* Destruct each JSONObject.pairs[i] */
    for (i = 0; i < self->count; i++)
    {
        PairDestruct(&self->pairs[i], &self->alloc);
    }

    /* Free JSONObject.pairs[] array */
    AllocPut(&self->alloc, self->pairs);

    /* Clear JSONObject.magic (to detect subsequent invalid 'self' pointer use) */
    self->magic = 0xDDDDDDDD;

    /* Free the object structure */
    Free(self_);

    return OL_Result_Ok;
}

static size_t _Count(
    const JSON_Object* self_)
{
    const JSONObject* self = (const JSONObject*)self_;

    if (!self || self->magic != OBJECT_MAGIC)
        return (size_t)-1;

    return self->count;
}

static OL_Result _Add(
    JSON_Object* self_,
    const char* name,
    const JSON_Value* value,
    unsigned int flags)
{
    JSONObject* self = (JSONObject*)self_;
    size_t nameLen;
    unsigned int nameCode;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC || !name || !name[0] || !value)
        return OL_Result_BadParameter;

    /* Check for a valid navigation link name */
    if (value->type == OL_Type_NavigationLink && 
        !_IsValidNavigationLinkName(name))
    {
        return OL_Result_InvalidName;
    }

    /* Add object-level flags */
    flags |= self->flags;

    /* Compute nameLen */
    nameLen = NameLen(name, flags);

    /* Compute nameCode */
    nameCode = StrCode(name, nameLen);

    /* Reject if a property with that name already exists */
    if (!(self->flags & OL_FLAG_ALLOW_DUPLICATES))
    {
        if (_Find(self, name, nameCode) != (size_t)-1)
            return OL_Result_AlreadyExists;
    }

    /* Add new pair to end of array */
    {
        size_t capacity;

        /* If no more space, allocate space for a new pair */
        if (self->count == self->capacity)
        {
            Pair* pairs;

            if (self->capacity == 0)
                capacity = OBJECT_MIN_CAPACITY;
            else
                capacity = self->capacity * 2;

            /* Allocate memory */
            if (AllocResize(
                &self->alloc,
                self->pairs,
                capacity * sizeof(Pair),
                self->capacity * sizeof(Pair),
                (void**)&pairs))
            {
                return OL_Result_Failed;
            }

            self->pairs = pairs;
            self->capacity = capacity;
        }

        /* Construct the new pair */
        if (value->type == JSON_Type_String &&
            (flags & JSON_FLAG_LENGTH_NAME) &&
            (flags & JSON_FLAG_STATIC_NAME) &&
            (flags & JSON_FLAG_STATIC_VALUE))
        {
            PairConstructStringSpecial(&self->pairs[self->count], name, 
                nameCode, value);
        }
        else if (PairConstruct(
            &self->pairs[self->count],
            name, 
            nameLen, 
            nameCode, 
            value, 
            flags, 
            &self->alloc) != 0)
        {
            return OL_Result_Failed;
        }

        self->count++;
    }

    return OL_Result_Ok;
}

static OL_Result _Set(
    JSON_Object* self_, 
    const char* name,
    const JSON_Value* value,
    unsigned int flags)
{
    JSONObject* self = (JSONObject*)self_;
    unsigned int nameCode;
    size_t pos;
    Pair* pair;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC || !name || !name[0] || !value)
        return OL_Result_BadParameter;

    /* Add object-level flags */
    flags |= self->flags;

    /* Compute nameCode */
    nameCode = StrCode(name, NameLen(name, flags));

    /* Reject if property not found */
    if ((pos = _Find(self, name, nameCode)) == (size_t)-1)
        return OL_Result_NotFound;

    pair = &self->pairs[pos];

    /* Set Pair.value and Pair.type */
    if ((pair->value.type == JSON_Type_String) &&
        (pair->flags & JSON_FLAG_STATIC_NAME) &&
        (pair->flags & JSON_FLAG_STATIC_VALUE) &&
        (value->type == JSON_Type_String) &&
        (flags & JSON_FLAG_STATIC_NAME) &&
        (flags & JSON_FLAG_STATIC_VALUE))
    {
        PairSetStringSpecial(pair, value, &self->alloc);
    }
    else if (PairSet(pair, value, flags, &self->alloc) != 0)
    {
        return OL_Result_Failed;
    }

    return OL_Result_Ok;
}

static OL_Result _Get(
    const JSON_Object* self_, 
    const char* name,
    JSON_Value* value,
    unsigned int* flags_)
{
    const JSONObject* self = (const JSONObject*)self_;
    unsigned int nameCode;
    size_t pos;
    unsigned int flags = flags_ ? *flags_ : 0;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC || !name || !name[0])
        return OL_Result_BadParameter;

    /* Add object-level flags */
    flags |= self->flags;

    /* Compute nameCode */
    nameCode = StrCode(name, NameLen(name, flags));

    /* Reject if property not found */
    if ((pos = _Find(self, name, nameCode)) == (size_t)-1)
        return OL_Result_NotFound;

    /* Set 'value' parameter */
    if (value)
    {
        OL_Result r; 

        if ((r = PairGet(&self->pairs[pos], value, flags_, 
            (Alloc*)&self->alloc)) != OL_Result_Ok)
            return r;
    }

    return OL_Result_Ok;
}

static OL_Result _Remove(
    JSON_Object* self_, 
    const char* name,
    unsigned int flags)
{
    JSONObject* self = (JSONObject*)self_;
    unsigned int nameCode;
    size_t pos;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC || !name || !name[0])
        return OL_Result_BadParameter;

    /* Add object-level flags */
    flags |= self->flags;

    /* Compute nameCode */
    nameCode = StrCode(name, NameLen(name, flags));

    /* Reject if property not found */
    if ((pos = _Find(self, name, nameCode)) == (size_t)-1)
        return OL_Result_NotFound;

    /* Destruct the given pair */
    PairDestruct(&self->pairs[pos], &self->alloc);

    /* Remove the pair from the array */
    {
        size_t r = self->count - pos - 1;

        if (r)
            memmove(&self->pairs[pos], &self->pairs[pos+1], r * sizeof(Pair));

        self->count--;
    }

    return OL_Result_Ok;
}

static OL_Result _SetAt(
    JSON_Object* self_, 
    size_t pos,
    const JSON_Value* value,
    unsigned int flags)
{
    JSONObject* self = (JSONObject*)self_;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC || !value)
        return OL_Result_BadParameter;

    /* Add object-level flags */
    flags |= self->flags;

    /* Fail if 'pos' is out of bounds */
    if (pos >= self->count)
        return OL_Result_OutOfBounds;

    /* Set Pair.value and Pair.type */
    if (PairSet(&self->pairs[pos], value, flags, &self->alloc) != 0)
        return OL_Result_Failed;

    return OL_Result_Ok;
}

static OL_Result _GetAt(
    const JSON_Object* self_, 
    size_t pos,
    const char** name,
    JSON_Value* value,
    unsigned int* flags)
{
    const JSONObject* self = (const JSONObject*)self_;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC)
        return OL_Result_BadParameter;

    /* Fail if 'pos' is out of bounds */
    if (pos >= self->count)
        return OL_Result_OutOfBounds;

    /* Set 'name' parameter */
    if (name)
        *name = self->pairs[pos].name;

    /* Set 'value' parameter */
    if (value)
    {
        OL_Result r; 

        if ((r = PairGet(&self->pairs[pos], value, flags,
            (Alloc*)&self->alloc) != OL_Result_Ok))
            return r;
    }

    return OL_Result_Ok;
}

static OL_Result _RemoveAt(
    JSON_Object* self_, 
    size_t pos,
    unsigned int flags)
{
    JSONObject* self = (JSONObject*)self_;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC)
        return OL_Result_BadParameter;

    /* Add object-level flags */
    flags |= self->flags;

    /* Fail if 'pos' is out of bounds */
    if (pos >= self->count)
        return OL_Result_OutOfBounds;

    /* Destruct the given pair */
    PairDestruct(&self->pairs[pos], &self->alloc);

    /* Remove the pair from the array */
    {
        size_t r = self->count - pos - 1;

        if (r)
            memmove(&self->pairs[pos], &self->pairs[pos+1], r * sizeof(Pair));

        self->count--;
    }

    return OL_Result_Ok;
}

static OL_Result _Print(
    const JSON_Object* self_,
    size_t indent)
{
    OL_Result r;
    OutStream outStream;

    OutStreamInit(&outStream);

    r = JSON_Object_Serialize(self_, &outStream.base, indent);

    if (r != OL_Result_Ok)
        goto done;

    printf("%.*s\n", (int)outStream.out->size, outStream.out->data);

    r = OL_Result_Ok;

done:
    OutStreamDestroy(&outStream);
    return r;
}

static JSON_Object* _Clone(
    const JSON_Object* self_);

#if 0
static OL_Result _Clear(
    JSON_Object* self_)
{
    JSONObject* self = (JSONObject*)self_;
    size_t i;

    /* Check the parameters */
    if (!self || self->magic != OBJECT_MAGIC)
        return OL_Result_BadParameter;

    DEBUG_ASSERT(self->refCount != 0);

    /* Destruct each JSONObject.pairs[i] */
    for (i = 0; i < self->count; i++)
    {
        PairDestruct(&self->pairs[i], &self->alloc);
    }

    /* Free JSONObject.pairs[] array */
    AllocPut(&self->alloc, self->pairs);

    self->pairs = NULL;
    self->count = 0;
    self->capacity = 0;
    self->flags = 0;

    return OL_Result_Ok;
}
#endif

static OL_Result _Clear(
    JSON_Object* self_)
{
    JSONObject* self = (JSONObject*)self_;
    size_t i;

    /* Check the parameters */
    if (!self || self->magic != OBJECT_MAGIC)
        return OL_Result_BadParameter;

    DEBUG_ASSERT(self->refCount != 0);

    /* Destruct each JSONObject.pairs[i] */
    for (i = 0; i < self->count; i++)
    {
        PairDestruct(&self->pairs[i], &self->alloc);
    }

    /* ATTN.B: why is this block necessary to prevent memory leaks? */
    {
        size_t allocBufSize;
        size_t n;

        /* Free JSONObject.pairs[] array */
        AllocPut(&self->alloc, self->pairs);
        
        /* Align size to next multiple of 8 */
        n = ((sizeof(JSONObject) + 7) & ~7);

        /* Compute allocBufSize */
        allocBufSize = (sizeof(Pair) * OBJECT_MIN_CAPACITY) + 1024;

        /* Initialize JSONObject.alloc */
        AllocInit(&self->alloc, (char*)self + n, allocBufSize);

        /* Set JSONObject.pairs */
        self->pairs = NULL;

        /* Set JSONObject.count */
        self->count = 0;

        /* Set JSONObject.capacity */
        self->capacity = 0;
    }

    /* Set JSONObject.flags */
    self->flags = 0;

    return OL_Result_Ok;
}

static OL_Result _SetFlags(
    JSON_Object* self_,
    unsigned int flags)
{
    JSONObject* self = (JSONObject*)self_;
    unsigned int f = 0;

    if (!self || self->magic != OBJECT_MAGIC)
        return OL_Result_BadParameter;

    if (flags & JSON_FLAG_ALLOW_DUPLICATES)
    {
        f |= JSON_FLAG_ALLOW_DUPLICATES;
        flags &= ~JSON_FLAG_ALLOW_DUPLICATES;
    }

    if (flags & JSON_FLAG_STATIC_VALUE)
    {
        f |= JSON_FLAG_STATIC_VALUE;
        flags &= ~JSON_FLAG_STATIC_VALUE;
    }

    if (flags & JSON_FLAG_STATIC_NAME)
    {
        f |= JSON_FLAG_STATIC_NAME;
        flags &= ~JSON_FLAG_STATIC_NAME;
    }

    if (flags & JSON_FLAG_LENGTH_NAME)
    {
        f |= JSON_FLAG_LENGTH_NAME;
        flags &= ~JSON_FLAG_LENGTH_NAME;
    }

    /* If any unconsumed flags */
    if (flags)
        return OL_Result_Failed;

    self->flags = f;
    return OL_Result_Ok;
}

extern OL_Result Object_Deserialize(
    JSON_Object* self,
    JSON_Char* data,
    size_t size,
    size_t* offset);

JSON_ObjectFT __JSON_Object_ft =
{
    _AddRef,
    _Release,
    _Clone,
    _Clear,
    _SetFlags,
    _Count,
    _Add,
    _Set,
    _Get,
    _Remove,
    _SetAt,
    _GetAt,
    _RemoveAt,
    _Print,
    Object_Serialize,
    Object_Deserialize
};

static JSON_Object* _Clone(
    const JSON_Object* self_)
{
    const JSONObject* self = (const JSONObject*)self_;
    JSONObject* newObject;
    const size_t ALLOCBUFSIZE = 1024;
    size_t n;
    size_t i;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC)
        return NULL;
    
    /* Align size to next multiple of 8 */
    n = ((sizeof(JSONObject) + 7) & ~7);

    /* Allocate the memory (self + alignment + extra bytes) */
    if (!(newObject = (JSONObject*)Malloc(n + ALLOCBUFSIZE)))
        return NULL;

    /* Set JSONObject.ft */
    newObject->base.ft = &__JSON_Object_ft;

    /* Set JSONObject.magic */
    newObject->magic = OBJECT_MAGIC;

    /* Set JSONObject.refCount */
    newObject->refCount = 1;

    /* Initialize JSONObject.alloc */
    AllocInit(&newObject->alloc, (char*)newObject + n, ALLOCBUFSIZE);

    /* Set JSONObject.count */
    newObject->count = 0;

    /* Allocate JSONObject.pairs[] */
    if (!(newObject->pairs = AllocGet(
        &newObject->alloc,
        self->capacity * sizeof(Pair))))
    {
        _Release(&newObject->base);
        return NULL;
    }

    /* Set JSONObject.capacity */
    newObject->capacity = self->capacity;

    /* Construct JSONObject.pairs[] */
    for (i = 0; i < self->count; i++)
    {
        const Pair* pair = &self->pairs[i];

        if (PairConstruct(
            &newObject->pairs[i], 
            pair->name,
            pair->nameLen,
            pair->nameCode,
            &pair->value,
            pair->flags,
            &newObject->alloc) != 0)
        {
            _Release(&newObject->base);
            return NULL;
        }

        newObject->count++;
    }

    return &newObject->base;
}

JSON_Object* JSON_Object_New()
{
    JSONObject* self;
    size_t allocBufSize;
    size_t n;
    
    /* Align size to next multiple of 8 */
    n = ((sizeof(JSONObject) + 7) & ~7);

    /* Compute allocBufSize */
    allocBufSize = (sizeof(Pair) * OBJECT_MIN_CAPACITY) + 1024;

    /* Allocate the memory (self + alignment + extra bytes) */
    if (!(self = (JSONObject*)Malloc(n + allocBufSize)))
        return NULL;

    _Construct(self, n, allocBufSize);

    return &self->base;
}
