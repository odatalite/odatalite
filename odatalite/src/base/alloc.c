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
#include <assert.h>
#include "alloc.h"
#include "roundpow2.h"

#if 0
# define ENABLE_FILLING
# define ENABLE_CLEARING
#endif

/*
**==============================================================================
**
** Allocator
**
**==============================================================================
*/

#if defined(ENABLE_ALLOCATOR)

# define MEMMAGIC 0X6C2A018E

static AllocStats _allocStats;

typedef struct _MemHeader
{
    unsigned int magic;
    unsigned int size;
}
MemHeader;

void GetAllocStats(AllocStats* stats)
{
    *stats = _allocStats;
}

void* _Alloc(size_t size)
{
    MemHeader* h;

#if 0
    {
        AllocPrintStats("_Alloc");
        printf("_Alloc(%u)\n", (int)size);
    }
#endif

    if (!(h = malloc(sizeof(MemHeader) + size)))
        return NULL;

    h->magic = MEMMAGIC;
    h->size = size;

    _allocStats.bytesAllocated += size;

    if (_allocStats.bytesAllocated > _allocStats.maxBytesAllocated)
    {
        _allocStats.maxBytesAllocated = _allocStats.bytesAllocated;
    }

    _allocStats.numAllocs++;

#if defined(ENABLE_FILLING)
    memset(h + 1, 0xAA, size);
#endif

    return h + 1;
}

void* Malloc(size_t size)
{
# if defined(ENABLE_ALLOC_TRACE)
    printf("=== Malloc(%u)\n", (unsigned int)size);
# endif

    return _Alloc(size);
}

void* Calloc(size_t count, size_t size)
{
    void* ptr;

# if defined(ENABLE_ALLOC_TRACE)
    printf("=== Calloc(%u, %u)\n", (unsigned int)count, (unsigned int)size);
# endif

    if (!(ptr = _Alloc(count * size)))
        return NULL;

    return memset(ptr, 0, count * size);
}

void* Realloc(void* ptr, size_t size)
{
    MemHeader* h;

# if defined(ENABLE_ALLOC_TRACE)
    printf("=== Realloc(%p, %u)\n", ptr, (unsigned int)size);
# endif

    if (!ptr)
        return Malloc(size);

    h = (MemHeader*)ptr - 1;
    DEBUG_ASSERT(h->magic == MEMMAGIC);

    if (!(h = realloc(h, sizeof(MemHeader) + size)))
    {
        return NULL;
    }

    _allocStats.bytesAllocated -= h->size;
    _allocStats.bytesAllocated += size;

    if (_allocStats.bytesAllocated > _allocStats.maxBytesAllocated)
        _allocStats.maxBytesAllocated = _allocStats.bytesAllocated;

#if defined(ENABLE_FILLING)
    if (size > h->size)
        memset((char*)(h + 1) + h->size, 0xAA, size - h->size);
#endif

    h->size = size;
    return h + 1;
}

void Free(void* ptr)
{
    MemHeader* h;

    if (!ptr)
        return;

    h = (MemHeader*)ptr - 1;
    DEBUG_ASSERT(h->magic == MEMMAGIC);

    _allocStats.bytesAllocated -= h->size;
    _allocStats.numFrees++;

#if defined(ENABLE_CLEARING)
    memset(h, 0xDD, sizeof(MemHeader) + h->size);
#endif

    free(h);
}

char* Strdup(const char* str)
{
    size_t len;
    char* result;

    len = strlen(str);

    if (!(result = (char*)Malloc(len + 1)))
        return NULL;

    return memcpy(result, str, len + 1);
}

#endif /* defined(ENABLE_ALLOCATOR) */

int Resize(void* ptr, size_t newSize, size_t oldSize, void** ptrOut)
{
    void* p;
    
    if (!(p = Realloc(ptr, newSize)))
        return -1;

    *ptrOut = p;
    return 0;
}

void* Memdup(const void* data, size_t size)
{
    void* p = Malloc(size);

    if (!p)
        return NULL;

    return memcpy(p, data, size);
}

/*
**==============================================================================
**
** Alloc
**
**==============================================================================
*/

int AllocResize(
    Alloc* self,
    void* ptr,
    size_t newSize,
    size_t oldSize,
    void** ptrOut)
{
    /* ATTN: can this check be removed later */
    if (!self)
        return Resize(ptr, newSize, oldSize, ptrOut);

#if defined(ENABLE_STATIC_BUFFERS)

    if (!ptr)
    {
        *ptrOut = AllocGet(self, newSize);
        return 0;
    }

    if ((char*)ptr >= self->data && (char*)ptr < (self->data + self->size))
    {
        if (newSize <= oldSize)
        {
            *ptrOut = ptr;
            return 0;
        }
        else
        {
            void* p;

            if (!(p = Malloc(newSize)))
                return -1;

            *ptrOut = memcpy(p, ptr, oldSize);
            return 0;
        }
    }
#endif /* defined(ENABLE_STATIC_BUFFERS) */

    if (!(ptr = Realloc(ptr, newSize)))
        return -1;

    *ptrOut = ptr;
    return 0;
}

void* AllocMemdup(
    Alloc* self,
    const void* data,
    size_t size)
{
    void* ptr;

    if (!(ptr = (char*)AllocGet(self, size)))
        return NULL;

    return memcpy(ptr, data, size);
}
