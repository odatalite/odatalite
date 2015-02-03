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
#define _GNU_SOURCE
#include <stdlib.h>
#include <base/format.h>
#include <base/str.h>
#include <base/chars.h>
#include <base/parse.h>
#include <base/iprintf.h>
#include <base/array.h>
#include "uri.h"
#include "chars.h"
#include "serialize.h"
#include "setters.h"
#include "types.h"
#include "uriparser.h"
#include "odatamacros.h"
#include "return.h"

#define URI_MAGIC 0x8800ABCB
#define URI_PAIR_CAPACITY 4
#define URI_ELEMENT_CAPACITY 8

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

static void _DestructElements(URI* self)
{
    size_t i;

    /* Destruct each segment */
    for (i = 0; i < self->segments.size; i++)
    {
        URISegment* segment = &self->segments.data[i];
        size_t j;

        /* Destruct each key of this segment */
        for (j = 0; j < segment->keysSize; j++)
        {
            URIKey* p = &segment->keys[j];

            if (!(p->flags & OL_FLAG_STATIC_NAME))
                AllocPut(&self->alloc, p->name);

            if (!(p->flags & OL_FLAG_STATIC_VALUE))
            {
                ValueDestructor dtor = GetDestructor(p->value.type);

                if (dtor)
                    (*dtor)((JSON_Value*)&p->value, p->flags, &self->alloc);
            }
        }

        /* Free Array.keys[] */
        AllocPut(&self->alloc, segment->keys);
    }
}

/*
**==============================================================================
**
** URI Methods
**
**==============================================================================
*/

void __OL_URI_Destruct(
    URIWithAllocBuf* self_)
{
    URI* self = (URI*)self_;

    /* Destruct the keys */
    _DestructElements(self);

    /* Free Array.segments[] */
    AllocPut(&self->alloc, self->segments.data);

    /* Clear URI.magic (to detect subsequent invalid 'self' pointer use) */
    self->magic = 0xDDDDDDDD;
}

static OL_Result _URI_AddRef(
    const OL_URI* self_)
{
    URI* self = (URI*)self_;

    /* Check parameters */
    if (!self || self->magic != URI_MAGIC)
        RETURN(OL_Result_BadParameter);

    /* Check refCount */
    if (self->refCount == 0)
        RETURN(OL_Result_Failed);

    /* Increment the reference count */
    self->refCount++;

    RETURN(OL_Result_Ok);
}

static OL_Result _URI_Release(
    OL_URI* self_)
{
    URI* self = (URI*)self_;

    /* Check the parameters */
    if (!self || self->magic != URI_MAGIC)
        RETURN(OL_Result_BadParameter);

    DEBUG_ASSERT(self->refCount != 0);

    /* Decrement the reference count */
    if (--self->refCount != 0)
        RETURN(OL_Result_Ok);

    __OL_URI_Destruct((URIWithAllocBuf*)self);

    /* Free the array structure */
    Free(self);

    RETURN(OL_Result_Ok);
}

static OL_URI* _URI_Clone(
    const OL_URI* self_)
{
    const URI* self = (const URI*)self_;
    URI* newURI;
    size_t i;

    /* Check parameters */
    if (!self || self->magic != URI_MAGIC)
        RETURN(NULL);
    
    /* Allocate the memory (self + alignment + extra bytes) */
    if (!(newURI = (URI*)Malloc(sizeof(URIWithAllocBuf))))
        RETURN(NULL);

    __OL_URI_Construct((URIWithAllocBuf*)newURI);

    /* Allocate URI.segments[] */
    if (!(newURI->segments.data = AllocGet(
        &newURI->alloc,
        self->segments.capacity * sizeof(URISegment))))
    {
        _URI_Release(&newURI->base);
        RETURN(NULL);
    }

    /* Set URI.count */
    newURI->segments.size = 0;

    /* Set URI.capacity */
    newURI->segments.capacity = self->segments.capacity;

    /* Copy URI.segments[] */
    for (i = 0; i < self->segments.size; i++)
    {
        size_t j;

        for (j = 0; j < self->segments.data[i].keysSize; j++)
        {
            URIKey* p = &newURI->segments.data[i].keys[j];
            const URIKey* q = &self->segments.data[i].keys[j];

            /* URIElem.flags */
            p->flags = 0;

            /* Copy URIKey.name */
            if (q->flags & OL_FLAG_STATIC_NAME)
            {
                p->name = q->name;
                p->flags |= OL_FLAG_STATIC_NAME;
            }
            else
                p->name = AllocStrdup(&newURI->alloc, q->name);

            /* Copy URIKey.value */
            if (q->flags & OL_FLAG_STATIC_VALUE)
            {
                p->value = q->value;
                p->flags |= OL_FLAG_STATIC_VALUE;
            }
            else
            {
                ValueSetter setter = GetSetter(p->value.type);

                if (!setter)
                {
                    _URI_Release(&newURI->base);
                    RETURN(NULL);
                }

                if ((*setter)(
                    (JSON_Value*)&p->value, 
                    (const JSON_Value*)&q->value, 
                    0, 
                    &newURI->alloc) != 0)
                {
                    _URI_Release(&newURI->base);
                    RETURN(NULL);
                }
            }

            newURI->segments.data[i].keysSize++;
        }

        /* URI.count */
        newURI->segments.size++;
    }

    RETURN(&newURI->base);
}

static OL_Result _URI_Clear(
    OL_URI* self_)
{
    URI* self = (URI*)self_;

    /* Check the parameters */
    if (!self || self->magic != URI_MAGIC)
        RETURN(OL_Result_BadParameter);

    DEBUG_ASSERT(self->refCount != 0);

    /* Destruct the keys (but leave the 'segments' allocation) */
    _DestructElements(self);

    /* URI.segments */
    self->segments.size = 0;

    /* URI.queryOptions */
    self->queryOptions = 0;

    RETURN(OL_Result_Ok);
}

static OL_Result _URI_SetFlags(
    OL_URI* self_,
    unsigned int flags)
{
    URI* self = (URI*)self_;
    unsigned int f = 0;

    /* Check parameters */
    if (!self || self->magic != URI_MAGIC)
        RETURN(OL_Result_BadParameter);

    /* Extract the valid flags */
    if (flags & OL_FLAG_STATIC_VALUE)
    {
        f |= OL_FLAG_STATIC_VALUE;
        flags &= ~OL_FLAG_STATIC_VALUE;
    }

    /* If any unconsumed flags */
    if (flags)
        RETURN(OL_Result_Failed);

    self->flags = f;
    RETURN(OL_Result_Ok);
}

static size_t _URI_Count(
    const OL_URI* self_)
{
    /* Check parameters */
    const URI* self = (const URI*)self_;

    if (!self || self->magic != URI_MAGIC)
        RETURN((size_t)-1);

    RETURN(self->segments.size);
}

static size_t _URI_KeyCount(
    const OL_URI* self_,
    size_t index)
{
    /* Check parameters */
    const URI* self = (const URI*)self_;
    const URISegment* segment;

    /* ATTN.A: dangerous to return -1 for error */
    if (!self || self->magic != URI_MAGIC)
        RETURN(0);

    if (index >= self->segments.size)
        RETURN(0);

    segment = &self->segments.data[index];

    RETURN(segment->keysSize);
}

const OL_Char* _URI_GetName(
    const OL_URI* self_,
    size_t index)
{
    /* Check parameters */
    const URI* self = (const URI*)self_;
    const URISegment* segment;

    if (!self || self->magic != URI_MAGIC)
        RETURN(NULL);

    if (index >= self->segments.size)
        RETURN(NULL);

    segment = &self->segments.data[index];

    RETURN(segment->name);
}

static OL_Result _URI_GetKey(
    const OL_URI* self_, 
    size_t index,
    const OL_Char* name,
    OL_Value* value)
{
    const URI* self = (const URI*)self_;
    const URISegment* segment;

    /* Check parameters */
    if (!self || self->magic != URI_MAGIC || !name)
        RETURN(OL_Result_BadParameter);

    /* Check that 'index' is within boudns */
    if (index >= self->segments.size)
        RETURN(OL_Result_OutOfBounds);

    /* Get the N-th segment */
    segment = &self->segments.data[index];

    /* Optimize for "$[0-9]" case */
    if (name[0] == '$' && isdigit(name[1]) && name[2] == '\0')
    {
        size_t i = name[1] - '0';

        if (i >= segment->keysSize)
            RETURN(OL_Result_NotFound);

        if (value)
        {
            ValueAssignUnpadded(
                (JSON_Value*)value, 
                (JSON_Value*)&segment->keys[i].value);
        }

        RETURN(OL_Result_Ok);
    }

    /* Check for key name */
    {
        size_t i;

        for (i = 0; i < segment->keysSize; i++)
        {
            const URIKey* key = &segment->keys[i];

            if (strcmp(key->name, name) == 0)
            {
                if (value)
                    ValueAssignUnpadded(
                        (JSON_Value*)value, (JSON_Value*)&key->value);

                RETURN(OL_Result_Ok);
            }
        }
    }

    RETURN(OL_Result_NotFound);
}

static OL_Result _URI_GetKeyAt(
    const OL_URI* self_, 
    size_t index,
    size_t offset,
    const OL_Char** name,
    OL_Value* value)
{
    const URI* self = (const URI*)self_;
    const URISegment* segment;

    /* Check parameters */
    if (!self || self->magic != URI_MAGIC)
        RETURN(OL_Result_BadParameter);

    /* Check that 'index' is within boudns */
    if (index >= self->segments.size)
        RETURN(OL_Result_OutOfBounds);

    segment = &self->segments.data[index];

    /* Check bounds error on keys */
    if (offset >= segment->keysSize)
        RETURN(OL_Result_OutOfBounds);

    /* Get the key */
    {
        const URIKey* key = &segment->keys[offset];

        if (name)
            *name = key->name;

        if (value)
            ValueAssignUnpadded((JSON_Value*)value, (JSON_Value*)&key->value);
    }

    RETURN(OL_Result_Ok);
}

static OL_Result _URI_Parse(
    OL_URI* self_,
    char* uri,
    char* err,
    size_t errSize)
{
    URI* self = (URI*)self_;

    if (!self || self->magic != URI_MAGIC || !uri || !err)
        RETURN(OL_Result_BadParameter);

    RETURN(URIParse(self, uri, err, errSize));
}

static OL_Result _URI_Format(
    const OL_URI* self_,
    char* buf,
    size_t size)
{
    URI* self = (URI*)self_;
    size_t i;
    size_t j;

    if (!self || self->magic != URI_MAGIC || !buf)
        RETURN(OL_Result_Failed);

    if (Strlcpy(buf, "odata", size) >= size)
        RETURN(OL_Result_Failed);

    if (self->segments.size == 0)
        RETURN(OL_Result_Ok);

    if (Strlcat(buf, "/", size) >= size)
        RETURN(OL_Result_Failed);

    for (i = 0; i < self->segments.size; i++)
    {
        const URISegment* segment = &self->segments.data[i];

        if (Strlcat(buf, segment->name, size) >= size)
            RETURN(OL_Result_Failed);

        if (segment->keysSize)
        {
            if (Strlcat(buf, "(", size) >= size)
                RETURN(OL_Result_Failed);

            for (j = 0; j < segment->keysSize; j++)
            {
                const URIKey* key = &segment->keys[j];
                FormatValue(buf, size, &key->value);

                if (j + 1 != segment->keysSize)
                {
                    if (Strlcat(buf, ",", size) >= size)
                        RETURN(OL_Result_Failed);
                }
            }

            if (Strlcat(buf, ")", size) >= size)
                RETURN(OL_Result_Failed);
        }

        if (i + 1 != self->segments.size)
        {
            if (Strlcat(buf, "/", size) >= size)
                RETURN(OL_Result_Failed);
        }
    }

    RETURN(OL_Result_Ok);
}

static unsigned int _URI_GetQueryOptionFlags(
    const OL_URI* self_)
{
    URI* self = (URI*)self_;

    if (!self || self->magic != URI_MAGIC)
        RETURN(OL_Result_BadParameter);

    RETURN(self->queryOptions);
}

static unsigned int _URI_GetQueryOption(
    const OL_URI* self_,
    unsigned int option,
    void* value,
    size_t valueSize)
{
    URI* self = (URI*)self_;

    if (!self || self->magic != URI_MAGIC || !value)
        RETURN(OL_Result_BadParameter);

    switch (option)
    {
        case OL_QUERY_OPTION_COUNT:
        {
            if (self->queryOptions & OL_QUERY_OPTION_TOP)
            {
                const OL_Boolean flag = OL_TRUE;

                if (valueSize != sizeof(OL_Boolean))
                    RETURN(OL_Result_BadParameter);

                memcpy(value, &flag, valueSize);
                RETURN(OL_Result_Ok);
            }
            break;
        }
        case OL_QUERY_OPTION_TOP:
        {
            if (self->queryOptions & OL_QUERY_OPTION_TOP)
            {
                if (valueSize != sizeof(self->queryOptionTop))
                    RETURN(OL_Result_BadParameter);

                memcpy(value, &self->queryOptionTop, valueSize);
                RETURN(OL_Result_Ok);
            }
            break;
        }
        case OL_QUERY_OPTION_SKIP:
        {
            if (self->queryOptions & OL_QUERY_OPTION_SKIP)
            {
                if (valueSize != sizeof(self->queryOptionSkip))
                    RETURN(OL_Result_BadParameter);

                memcpy(value, &self->queryOptionSkip, valueSize);
                RETURN(OL_Result_Ok);
            }
            break;
        }
        case OL_QUERY_OPTION_SKIPTOKEN:
        {
            if (self->queryOptions & OL_QUERY_OPTION_SKIPTOKEN)
            {
                if (valueSize != sizeof(self->queryOptionSkiptoken))
                    RETURN(OL_Result_BadParameter);

                memcpy(value, &self->queryOptionSkiptoken, valueSize);
                RETURN(OL_Result_Ok);
            }
            break;
        }
    }

    RETURN(OL_Result_NotFound);
}

/* SIZEOPT: 1KB */
static OL_Result _URI_Print(
    const OL_URI* self_,
    size_t indent)
{
    URI* self = (URI*)self_;
    size_t count = _URI_Count(self_);
    size_t i;

    if (count == 0)
        RETURN(OL_Result_Ok);

    Iprintf(indent, "[\n");
    indent++;

    for (i = 0; i < count; i++)
    {
        size_t keyCount = _URI_KeyCount(self_, i);
        size_t j;
        const OL_Char* name;
        OL_Value value;

        /* Print query options */
        if (self->queryOptions)
        {
            size_t n = 0;

            Iprintf(indent, "{\n");
            indent++;

            if (self->queryOptions & OL_QUERY_OPTION_COUNT)
            {
                Iprintf(indent, "\"$count\": true");
                n++;
            }

            if (self->queryOptions & OL_QUERY_OPTION_TOP)
            {
                if (n)
                    printf(",\n");
                Iprintf(indent, "\"$top\": %lu", self->queryOptionTop);
                n++;
            }

            if (self->queryOptions & OL_QUERY_OPTION_SKIP)
            {
                if (n)
                    printf(",\n");
                Iprintf(indent, "\"$skip\": %lu", self->queryOptionSkip);
                n++;
            }

            if (self->queryOptions & OL_QUERY_OPTION_SKIPTOKEN)
            {
                if (n)
                    printf(",\n");
                Iprintf(indent, "\"$skiptoken\": %s", 
                    self->queryOptionSkiptoken);
                n++;
            }

            if (n)
                printf("\n");

            indent--;
            Iprintf(indent, "},\n");
        }

        /* Print the segment */
        {
            Iprintf(indent, "{\n");
            indent++;

            /* Print the segment name */
            Iprintf(indent, "\"name\": \"%s\"", OL_URI_GetName(self_, i));

            /* Print the keys */
            if (keyCount)
            {
                printf(",\n");
                Iprintf(indent, "\"keys\" :\n");
                Iprintf(indent, "{\n");
                indent++;

                for (j = 0; j < keyCount; j++)
                {
                    Buf buf = BUF_INITIALIZER;

                    if (_URI_GetKeyAt(self_, i, j, &name, &value) != 
                        OL_Result_Ok)
                    {
                        BufDestroy(&buf);
                        RETURN(OL_Result_Failed);
                    }

                    Iprintf(indent, "\"%s\": ", name);

                    SerializeElement(&buf, (JSON_Value*)&value, 0, 
                        OL_MetadataType_None);

                    printf("%.*s", (int)buf.size, buf.data);

                    BufDestroy(&buf);

                    if (j + 1 != keyCount)
                        printf(",");

                    printf("\n");
                }

                indent--;
                Iprintf(indent, "}");
            }

            printf("\n");
            indent--;
            Iprintf(indent, "}");

            if (i + 1 != count)
                printf(",");

            printf("\n");
        }
    }

    indent--;
    Iprintf(indent, "]\n");

    RETURN(OL_Result_Ok);
}

void __OL_URI_Construct(URIWithAllocBuf* self_)
{
    URI* self = (URI*)self_;
    
    /* Set URI.ft */
    self->base.ft = &__OL_URI_ft;

    /* Set URI.magic */
    self->magic = URI_MAGIC;

    /* Set URI.refCount */
    self->refCount = 1;

    /* Set URI.flags */
    self->flags = 0;

    /* Set URI.segments */
    memset(&self->segments, 0, sizeof(self->segments));

    /* Set Array.alloc */
    AllocInit(&self->alloc, self_->u.buf, URI_ALLOCBUFSIZE);
}

int URIMakePath(
    const URI* self,
    char path[MAX_PATH_SIZE])
{
    size_t i;

    Strlcpy2(path, self->service, "/", MAX_PATH_SIZE);

    for (i = 0; i < self->segments.size; i++)
    {
        const char* name = self->segments.data[i].name;

        if (Strlcat(path, name, MAX_PATH_SIZE) >= MAX_PATH_SIZE)
            return -1;

        if (i + 1 != self->segments.size)
        {
            if (Strlcat(path, "/", MAX_PATH_SIZE) >= MAX_PATH_SIZE)
                return -1;
        }
    }

    return 0;
}

OL_URI* __OL_URI_New()
{
    URI* self;
    
    /* Allocate array structure with extra bytes */
    if (!(self = (URI*)Calloc(1, sizeof(URIWithAllocBuf))))
        RETURN(NULL);

    __OL_URI_Construct((URIWithAllocBuf*)self);

    RETURN(&self->base);
}

OL_URIFT __OL_URI_ft =
{
    _URI_AddRef,
    _URI_Release,
    _URI_Clone,
    _URI_Clear,
    _URI_SetFlags,
    _URI_Count,
    _URI_KeyCount,
    _URI_GetName,
    _URI_GetKey,
    _URI_GetKeyAt,
    _URI_Parse,
    _URI_Format,
    _URI_GetQueryOptionFlags,
    _URI_GetQueryOption,
    _URI_Print
};
