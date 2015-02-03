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
#ifndef _alloc_h
#define _alloc_h

#include "common.h"

/*
**==============================================================================
**
** Allocator
**
**==============================================================================
*/

#if defined(ENABLE_ALLOCATOR)

typedef struct _AllocStats
{
    unsigned long bytesAllocated;
    unsigned long maxBytesAllocated;
    unsigned long numAllocs;
    unsigned long numFrees;
}
AllocStats;

void GetAllocStats(AllocStats* stats);

INLINE unsigned long GetBytesAllocated()
{
    AllocStats stats;
    GetAllocStats(&stats);
    return stats.bytesAllocated;
}

void AllocPrintStats(const char* msg);

void AllocPrintStatsAssert();

void* Malloc(size_t size);

void* Calloc(size_t count, size_t size);

void* Realloc(void* ptr, size_t size);

void Free(void* ptr);

char* Strdup(const char* str);

#else /* defined(ENABLE_ALLOCATOR) */

#define Malloc malloc
#define Calloc calloc
#define Realloc realloc
#define Free free

INLINE char* Strdup(const char* str)
{
    extern char* strdup(const char* str);
    return strdup(str);
}

#endif /* defined(ENABLE_ALLOCATOR) */

int Resize(
    void* ptr, 
    size_t newSize, 
    size_t oldSize, 
    void** ptrOut);

void* Memdup(const void* data, size_t size);

/*
**==============================================================================
**
** Alloc
**
**==============================================================================
*/

#if defined(ENABLE_STATIC_BUFFERS)
# define ALLOC_INITIALIZER { NULL, 0, 0 }
#else
# define ALLOC_INITIALIZER { 0 }
#endif

typedef struct _Alloc
{
#if defined(ENABLE_STATIC_BUFFERS)
    char* data;
    size_t size;
    size_t offset;
#else
    ptrdiff_t dummy;
#endif
}
Alloc;

INLINE void AllocInit(
    Alloc* self,
    void* data,
    size_t size)
{
#if defined(ENABLE_STATIC_BUFFERS)
    self->data = (char*)data;
    self->size = size;

    /* Align offset on an 8 byte boundary */
    self->offset = (unsigned long long)((ptrdiff_t)data) % 8;
#endif
}

ALWAYS_INLINE void* AllocGet(
    Alloc* self,
    size_t size)
{
#if defined(ENABLE_STATIC_BUFFERS)
    if (self->offset + size <= self->size)
    {
        void* ptr = self->data + self->offset;

        /* Align next allocation on 8 byte boundary */
        self->offset += (size + 7) & ~7;

        return ptr;
    }
#endif

    return Malloc(size);
}

int AllocResize(
    Alloc* self,
    void* ptr,
    size_t newSize,
    size_t oldSize,
    void** ptrOut);

ALWAYS_INLINE void AllocPut(
    Alloc* self,
    void* ptr)
{
#if defined(ENABLE_STATIC_BUFFERS)
    char* p = (char*)ptr;

    if (p >= self->data && p < (self->data + self->size))
    {
        return;
    }
#endif

    Free(ptr);
}

void* AllocMemdup(
    Alloc* self,
    const void* data,
    size_t size);

ALWAYS_INLINE char* AllocStrdup(
    Alloc* self,
    const char* str)
{
    return (char*)AllocMemdup(self, str, strlen(str)+1);
}

#endif /* _alloc_h */
