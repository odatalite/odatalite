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
#include <stdio.h>
#include <stdarg.h>

#include "buf.h"
#include "str.h"
#include "format.h"
#include "path.h"
#include "file.h"
#include "log.h"

#if defined(__GNUC__)
# define Va_copy  __va_copy
#else
# define Va_copy va_copy
#endif

void BufRaiseErr(Buf* self)
{
    /* This will force capacity to always be insufficient, so that
     * __BufReserve() will always be called which will return an error.
     */
    self->capacity = self->size;
    self->err = -1;
}

void __BufCat(
    Buf* self,
    const char* data,
    size_t size)
{
    size_t n = self->size + size;

    if (__BufReserve(self, self->size + n) != 0)
        return;

    memcpy(self->data + self->size, data, size);
    self->size = n;
}

void BufCatNoInline(
    Buf* self,
    const char* data,
    size_t size)
{
    BufCat(self, data, size);
}

void BufCatQuotedString(
    Buf* self,
    const char* str,
    size_t len)
{
    size_t n = self->size + len + 2;

    if (n > self->capacity)
    {
        if (__BufReserve(self, n) != 0)
            return;
    }

    {
        char* p = self->data + self->size;
        p[0] = '"';
        memcpy(p+1, str, len);
        p[len+1] = '"';
        self->size = n;
    }
}

/* Note: do not call this funciton directly */
int __BufReserve(
    Buf* self,
    size_t capacity)
{
    size_t cap;

    if (self->err)
        return -1;

    cap = self->capacity * 2;

    if (cap < capacity)
    {
        if (capacity)
            cap = capacity;
        else
            cap = 1;
    }

    if (self->alloc)
    {
        if (AllocResize(
            self->alloc, 
            self->data, 
            cap, 
            self->capacity, 
            (void**)&self->data) != 0)
        {
            BufRaiseErr(self);
            return -1;
        }
    }
    else
    {
        void* data = (char*)Realloc(self->data, cap);

        if (!data)
        {
            BufRaiseErr(self);
            return -1;
        }

        self->data = data;
    }

    if (!self->data)
    {
        BufRaiseErr(self);
        return -1;
    }

    self->capacity = cap;

    return 0;
}

void BufInit(
    Buf* self,
    Alloc* alloc)
{
    self->alloc = alloc;

#if defined(ENABLE_STATIC_BUFFERS)
    if (self->alloc)
    {
        self->data = alloc->data;
        self->capacity = alloc->size;
    }
    else
    {
        self->data = NULL;
        self->capacity = 0;
    }
#else /* defined(ENABLE_STATIC_BUFFERS) */
    self->data = NULL;
    self->capacity = 0;
#endif /* defined(ENABLE_STATIC_BUFFERS) */

    self->size = 0;

    self->err = 0;
}

void __BufCatCh2(
    Buf* self,
    char c1,
    char c2)
{
    char str[2];

    str[0] = c1;
    str[1] = c2;
    BufCat(self, str, 2);
}

void BufDestroy(
    Buf* self)
{
    if (self->alloc)
        AllocPut(self->alloc, self->data);
    else
        Free(self->data);
}

int BufFmt(Buf* self, const char* format, ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = BufFmtV(self, format, ap);
    va_end(ap);

    return r;
}

int BufFmtV(Buf* self, const char* format, va_list ap_)
{
    int n;
    static const size_t INITIAL_CAPACITY = 64;

    if (self->err)
        return -1;

    if (self->capacity == 0)
        BufReserve(self, INITIAL_CAPACITY);

    for (;;)
    {
        char* data = self->data + self->size;
        size_t size = self->capacity - self->size;
        va_list ap;

        Va_copy(ap, ap_);

        n = Vsnprintf(data, size, format, ap);

#if defined(__GNUC__)
        if (n < 0)
        {
            va_end(ap);
            BufRaiseErr(self);
            return -1;
        }
#endif

#if defined(_MSC_VER)
        if (n == -1 || (size_t)n >= size)
#else
        if ((size_t)n >= size)
#endif
        {
            /* Double the capacity and try again */
            BufReserve(self, self->capacity * 2);
            va_end(ap);
            continue;
        }

        self->size += (size_t)n;
        va_end(ap);
        break;
    }

    return n;
}

int BufCatFile(Buf* self, const char* path)
{
    FILE* is;
    char buf[512];
    size_t n;
    int r = 0;

    if (self->err)
        return -1;

    if (!(is = Fopen(path, "rb")))
    {
        return -1;
    }

    while ((n = fread(buf, 1, sizeof(buf), is)) > 0)
    {
        BufCat(self, buf, n);

        if (self->err != 0)
        {
            r = -1;
            goto done;
        }
    }

    /* Zero terminate */
    BufCat(self, "\0", 1);

    if (self->err || ferror(is))
    {
        r = -1;
        goto done;
    }

    self->size--;

done:
    fclose(is);
    return r;
}

int BufCatShareFile(Buf* self, const char* basename)
{
    char path[MAX_PATH_SIZE];
    return BufCatFile(self, MakePath2(ID_DATADIR, path, basename));
}

void BufRemove(
    Buf* self,
    size_t offset,
    size_t size)
{
    size_t rem;

    if (self->err)
        return;

    if ((rem = self->size - (offset + size)))
    {
        memmove(self->data + offset, self->data + offset + size, rem);
    }

    self->size -= size;
}

void BufCat2(
    Buf* self,
    const char* s1,
    size_t n1,
    const char* s2,
    size_t n2)
{
    size_t n = n1 + n2;

    if (self->size + n > self->capacity)
    {
        if (__BufReserve(self, self->size + n) != 0)
            return;
    }

    memcpy(self->data + self->size, s1, n1);
    memcpy(self->data + self->size + n1, s2, n2);
    self->size += n;
}

void BufCat3(
    Buf* self,
    const char* s1,
    size_t n1,
    const char* s2,
    size_t n2,
    const char* s3,
    size_t n3)
{
    size_t n = n1 + n2 + n3;

    if (self->size + n > self->capacity)
    {
        if (__BufReserve(self, self->size + n) != 0)
            return;
    }

    memcpy(self->data + self->size, s1, n1);
    memcpy(self->data + self->size + n1, s2, n2);
    memcpy(self->data + self->size + n1 + n2, s3, n3);
    self->size += n;
}

void BufCat4(
    Buf* self,
    const char* s1,
    size_t n1,
    const char* s2,
    size_t n2,
    const char* s3,
    size_t n3,
    const char* s4,
    size_t n4)
{
    size_t n = n1 + n2 + n3 + n4;

    if (self->size + n > self->capacity)
    {
        if (__BufReserve(self, self->size + n) != 0)
            return;
    }

    memcpy(self->data + self->size, s1, n1);
    memcpy(self->data + self->size + n1, s2, n2);
    memcpy(self->data + self->size + n1 + n2, s3, n3);
    memcpy(self->data + self->size + n1 + n2 + n3, s4, n4);
    self->size += n;
}
