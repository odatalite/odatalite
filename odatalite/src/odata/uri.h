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
#ifndef _odata_uri_h
#define _odata_uri_h

#include <base/alloc.h>
#include "odata.h"

#define URI_MAGIC 0x8800ABCB
#define URI_PAIR_CAPACITY 4
#define URI_ELEMENT_CAPACITY 8
#define URI_ALLOCBUFSIZE (URI_ELEMENT_CAPACITY * sizeof(URISegment) + 512)

typedef struct _URIKey
{
    unsigned int flags;
    char* name;
    OL_Value value;
}
URIKey;

/* Caution: Must have same initial layout as Array defined in <base/array.h> */
typedef struct _URISegment
{
    URIKey* keys;
    size_t keysSize;
    size_t keysCapacity;
    unsigned int flags;
    char* name;
}
URISegment;

/* Caution: Must have same initial layout as Array defined in <base/array.h> */
typedef struct _URISegmentArray
{
    URISegment* data;
    size_t size;
    size_t capacity;
}
URISegmentArray;

#define MAX_SERVICE_LEN 64

typedef struct _URI
{
    OL_URI base;
    unsigned int magic;
    unsigned long refCount;
    unsigned int flags;
    Alloc alloc;
    char service[MAX_SERVICE_LEN];
    size_t serviceLen;
    URISegmentArray segments;

    /* Query options */
    unsigned int queryOptions;
    unsigned long queryOptionTop;
    unsigned long queryOptionSkip;
    const char* queryOptionSkiptoken;
}
URI;

typedef struct _URIWithAllocBuf
{
    URI base;
    union
    {
        unsigned long long alignment1;
        double alignment;
        char buf[URI_ALLOCBUFSIZE];
    }
    u;
}
URIWithAllocBuf;

OL_URI* __OL_URI_New();

void __OL_URI_Construct(URIWithAllocBuf* self_);

void __OL_URI_Destruct(URIWithAllocBuf* self);

extern OL_URIFT __OL_URI_ft;

int URIMakePath(
    const URI* self,
    char path[MAX_PATH_SIZE]);

#endif /* _odata_uri_h */
