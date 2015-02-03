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
#ifndef _odata_scope_h
#define _odata_scope_h

#include "odata.h"
#include <base/ptrarray.h>
#include <base/buf.h>
#include <phit.h>

#define CONTEXT_MAGIC 0X3B70E3A1

#define CONTEXT_URI_CACHE_SIZE 4
#define CONTEXT_OBJECT_CACHE_SIZE 4
#define CONTEXT_ARRAY_CACHE_SIZE 4

#define MAX_CONTEXT_URI 128

typedef struct _Scope
{
    OL_Scope base;
    unsigned int magic;
    unsigned long refCount;
    PtrArray uris;
    PtrArray arrays;
    PtrArray objects;

    OL_URI* uriCache[CONTEXT_URI_CACHE_SIZE];
    size_t uriCacheSize;;

    OL_Array* arrayCache[CONTEXT_ARRAY_CACHE_SIZE];
    size_t arrayCacheSize;;

    OL_Object* objectCache[CONTEXT_OBJECT_CACHE_SIZE];
    size_t objectCacheSize;

    void* privateData;
    void* providerData;
    void (*providerDataDestructor)(void* ptr);

    /* Serialization buffer */
    Buf* out;

    /* The successful HTTP status code and message to use for this operation */
    unsigned int httpStatusCode;
    const char* httpStatusMsg;

    /* True if scope has entered into an error state */
    OL_Boolean error;

    size_t postHTTPPreamble;
    size_t postBeginEntitySet;
    size_t postEntity;
    size_t postEndEntitySet;
    size_t postValue;
    size_t postResult;
    size_t postMetadata;

    /* Copy of the request URI */
    char* requestURI;

    /* The "@odata.contex" annotation */
    char contextURI[MAX_CONTEXT_URI];

    /* Default: odata.metadata=minimal */
    OL_MetadataType metadataType;

    /* Version of OData (from "OData-Version:" HTTP header) */
    unsigned short version;

    /* Back-pointer to PHIT context */
    PHIT_Context* phitContext;

    /* Paging fields */
    unsigned long count;
    unsigned long top;
    unsigned long skip;

    /* If true, this is a count request (using $count URI segment) */
    OL_Boolean isCountRequest;

    /* Unused (final) URI segment name */
    const char* unmatchedSegmentName;

    /* URI Query options */
    unsigned int uriQueryOptions;
}
Scope;

#endif /* _odata_scope_h */
