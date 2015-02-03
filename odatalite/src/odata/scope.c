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
#include <base/alloc.h>
#include "odata.h"
#include "scope.h"
#include "uri.h"
#include "jsonarray.h"
#include "jsonobject.h"

#define CONTEXT_MIN_CAPACITY 2048

static OL_Result _AddRef(
    const OL_Scope* self_)
{
    Scope* self = (Scope*)self_;

    if (!self || self->magic != CONTEXT_MAGIC)
        return OL_Result_BadParameter;

    if (self->refCount == 0)
        return OL_Result_Failed;

    /* Increment the reference count */
    self->refCount++;

    return OL_Result_Ok;
}

static OL_Result _Release(
    OL_Scope* self_)
{
    Scope* self = (Scope*)self_;
    size_t i;

    /* Check the parameters */
    if (!self || self->magic != CONTEXT_MAGIC)
        return OL_Result_BadParameter;

    /* Decrement reference count */
    if (--self->refCount != 0)
        return OL_Result_Ok;

    /* Release Scope.uris */
    {
        for (i = 0; i < self->uris.size; i++)
            OL_Object_Release((OL_Object*)self->uris.data[i]);

        PtrArray_Destruct(&self->uris);
    }

    /* Release Scope.arrays */
    {
        for (i = 0; i < self->arrays.size; i++)
            OL_Array_Release((OL_Array*)self->arrays.data[i]);

        PtrArray_Destruct(&self->arrays);
    }

    /* Release Scope.objects */
    {
        for (i = 0; i < self->objects.size; i++)
            OL_Object_Release((OL_Object*)self->objects.data[i]);

        PtrArray_Destruct(&self->objects);
    }

    /* Release Scope.providerData */
    if (self->providerDataDestructor)
        (*self->providerDataDestructor)(self->providerData);

    /* Free the uri cache */
    for (i = 0; i < self->uriCacheSize; i++)
        OL_URI_Release(self->uriCache[i]);

    /* Free the array cache */
    for (i = 0; i < self->arrayCacheSize; i++)
        OL_Array_Release(self->arrayCache[i]);

    /* Free the object cache */
    for (i = 0; i < self->objectCacheSize; i++)
        OL_Object_Release(self->objectCache[i]);

    /* Free the requestURI */
    if (self->requestURI)
        Free(self->requestURI);

    /* Clear Scope.magic */
    self->magic = 0xDDDDDDDD;

    /* Free the scope structure */
    Free(self);

    return OL_Result_Ok;
}

static OL_Result _Clear(
    OL_Scope* self_)
{
    Scope* self = (Scope*)self_;

    /* Check the parameters */
    if (!self || self->magic != CONTEXT_MAGIC)
        return OL_Result_BadParameter;

    /* Free all the objects or add some to the cache */
    {
        size_t i;

        for (i = 0; i < self->objects.size; i++)
        {
            OL_Object* object = (OL_Object*)self->objects.data[i];
#if defined(ENABLE_DEBUG)
            extern JSON_ObjectFT __JSON_Object_ft;
#endif

            DEBUG_ASSERT(object->ft == (void*)&__JSON_Object_ft);

            if (self->objectCacheSize != CONTEXT_OBJECT_CACHE_SIZE &&
                ((JSONObject*)object)->refCount == 1)
            {
                OL_Object_Clear(object);
                self->objectCache[self->objectCacheSize++] = object;
            }
            else
            {
                OL_Object_Release(object);
            }
        }

        self->objects.size = 0;
    }

    /* Free all the arrays or add some to the cache */
    {
        size_t i;

        for (i = 0; i < self->arrays.size; i++)
        {
            OL_Array* array = (OL_Array*)self->arrays.data[i];

            if (self->arrayCacheSize != CONTEXT_ARRAY_CACHE_SIZE &&
                ((JSONArray*)array)->refCount == 1)
            {
                OL_Array_Clear(array);
                self->arrayCache[self->arrayCacheSize++] = array;
            }
            else
            {
                OL_Array_Release(array);
            }
        }

        self->arrays.size = 0;
    }

    /* Free all the URIs or add some to the cache */
    {
        size_t i;

        for (i = 0; i < self->uris.size; i++)
        {
            OL_URI* uri = (OL_URI*)self->uris.data[i];

            if (self->uriCacheSize != CONTEXT_URI_CACHE_SIZE &&
                ((URI*)uri)->refCount == 1)
            {
                OL_URI_Clear(uri);
                self->uriCache[self->uriCacheSize++] = uri;
            }
            else
            {
                OL_URI_Release(uri);
            }
        }

        self->uris.size = 0;
    }

    return OL_Result_Ok;
}

static OL_Result _Reset(
    OL_Scope* self_)
{
    Scope* self = (Scope*)self_;

    /* Check the parameters */
    if (!self || self->magic != CONTEXT_MAGIC)
        return OL_Result_BadParameter;

    _Clear(self_);

    self->privateData = NULL;
    self->providerData = NULL;
    self->providerDataDestructor = NULL;
    self->httpStatusCode = 0;
    self->httpStatusMsg = NULL;
    self->error = 0;

    self->postHTTPPreamble = 0;
    self->postBeginEntitySet = 0;
    self->postEntity = 0;
    self->postEndEntitySet = 0;
    self->postValue = 0;
    self->postResult = 0;
    self->postMetadata = 0;

    if (self->requestURI)
    {
        Free(self->requestURI);
        self->requestURI = NULL;
    }

    self->contextURI[0] = '\0';
    self->version = 0;
    self->phitContext = NULL;

    /* Reset paging variables */
    self->count = 0;
    self->top = ULONG_MAX;
    self->skip = 0;

    self->unmatchedSegmentName = NULL;

    self->isCountRequest = 0;

    self->uriQueryOptions = 0;

    return OL_Result_Ok;
}

static OL_Array* _NewArray(
    const OL_Scope* self_)
{
    Scope* self = (Scope*)self_;
    OL_Array* array;

    if (!self || self->magic != CONTEXT_MAGIC)
        return NULL;

    if (self->arrayCacheSize)
    {
        array = self->arrayCache[--self->arrayCacheSize];
    }
    else if (!(array = __OL_Array_New()))
    {
        return NULL;
    }

    DEBUG_ASSERT(((JSONArray*)array)->refCount == 1);

    if (PtrArray_Append(&self->arrays, array) != 0)
    {
        OL_Array_Release(array);
        return NULL;
    }

    OL_Array_AddRef(array);
    DEBUG_ASSERT(((JSONArray*)array)->refCount == 2);

    return array;
}

static OL_URI* _NewURI(
    const OL_Scope* self_)
{
    Scope* self = (Scope*)self_;
    OL_URI* uri;

    if (!self || self->magic != CONTEXT_MAGIC)
        return NULL;

    if (self->uriCacheSize)
    {
        uri = self->uriCache[--self->uriCacheSize];
    }
    else if (!(uri = __OL_URI_New()))
    {
        return NULL;
    }

    DEBUG_ASSERT(((URI*)uri)->refCount == 1);

    if (PtrArray_Append(&self->uris, uri) != 0)
    {
        OL_URI_Release(uri);
        return NULL;
    }

    OL_URI_AddRef(uri);
    DEBUG_ASSERT(((URI*)uri)->refCount == 2);

    return uri;
}

static OL_Object* _NewObject(
    const OL_Scope* self_)
{
    Scope* self = (Scope*)self_;
    OL_Object* object;

    if (!self || self->magic != CONTEXT_MAGIC)
        return NULL;

    if (self->objectCacheSize)
    {
        object = self->objectCache[--self->objectCacheSize];
    }
    else if (!(object = __OL_Object_New()))
    {
        return NULL;
    }

    DEBUG_ASSERT(((JSONObject*)object)->refCount == 1);

    if (PtrArray_Append(&self->objects, object) != 0)
    {
        OL_Object_Release(object);
        return NULL;
    }

    OL_Object_AddRef(object);
    DEBUG_ASSERT(((JSONObject*)object)->refCount == 2);

    return object;
}

static void _SetProviderData(
    OL_Scope* self_,
    void* ptr,
    void (*destructor)(void* ptr))
{
    Scope* self = (Scope*)self_;

    DEBUG_ASSERT(self->magic == CONTEXT_MAGIC);

    if (self->providerDataDestructor)
        (*self->providerDataDestructor)(self->providerData);

    self->providerData = ptr;
    self->providerDataDestructor = destructor;
}

static void* _GetProviderData(
    OL_Scope* self_)
{
    Scope* self = (Scope*)self_;

    DEBUG_ASSERT(self->magic == CONTEXT_MAGIC);

    return self->providerData;
}

static OL_ScopeFT _ft =
{
    _AddRef,
    _Release,
    _Clear,
    _Reset,
    _NewURI,
    _NewArray,
    _NewObject,
    NULL, /* SendBeginEntitySet, */
    NULL, /* SendEntity, */
    NULL, /* SendEndEntitySet, */
    NULL, /* SendResult, */
    NULL, /* SendMetadataStruct */
    NULL, /* SendMetadataXML */
    _SetProviderData,
    _GetProviderData,
    NULL, /* GetOption */
};

OL_Scope* __OL_Scope_New()
{
    Scope* self;

    if (!(self = (Scope*)Calloc(1, sizeof(Scope))))
        return NULL;

    self->base.ft = &_ft;
    self->magic = CONTEXT_MAGIC;
    self->refCount = 1;

    /* ATTN.C: use self->alloc here! */
    if (PtrArray_Construct(&self->uris, 8, NULL) != 0)
    {
        Free(self);
        return NULL;
    }

    /* ATTN.C: use self->alloc here! */
    if (PtrArray_Construct(&self->arrays, 8, NULL) != 0)
    {
        PtrArray_Destruct(&self->uris);
        Free(self);
        return NULL;
    }

    /* ATTN.C: use self->alloc here! */
    if (PtrArray_Construct(&self->objects, 8, NULL) != 0)
    {
        PtrArray_Destruct(&self->uris);
        PtrArray_Destruct(&self->arrays);
        Free(self);
        return NULL;
    }

    self->metadataType = OL_MetadataType_Minimal;

    self->top = ULONG_MAX;

    return &self->base;
}
