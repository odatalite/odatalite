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
#ifndef _buf_h
#define _buf_h

#include <stdarg.h>
#include "common.h"
#include "alloc.h"

#define BUF_INITIALIZER { NULL, NULL, 0, 0, 0 }

typedef struct _Buf
{
    Alloc* alloc;
    char* data;
    size_t size;
    size_t capacity;

    /* -1 if Buf object is in an error state */
    int err;
}
Buf;

void BufRaiseErr(Buf* self);

void BufInit(
    Buf* self,
    Alloc* alloc);

void BufDestroy(
    Buf* self);

ALWAYS_INLINE void BufClear(
    Buf* self)
{
    self->size = 0;
    self->err = 0;
}

int __BufReserve(
    Buf* self,
    size_t capacity);

ALWAYS_INLINE int BufReserve(
    Buf* self,
    size_t capacity)
{
    if (capacity <= self->capacity)
        return 0;

    return __BufReserve(self, capacity);
}

void __BufCat(
    Buf* self,
    const char* data,
    size_t size);

ALWAYS_INLINE void BufCat(
    Buf* self,
    const char* data,
    size_t size)
{
    size_t n = self->size + size;

    if (n > self->capacity)
    {
        __BufCat(self, data, size);
        return;
    }

    memcpy(self->data + self->size, data, size);
    self->size = n;
}

void BufCatNoInline(
    Buf* self,
    const char* data,
    size_t size);

ALWAYS_INLINE void BufCatStr(
    Buf* self,
    const char* data)
{
    BufCat(self, data, strlen(data));
}

void BufCatQuotedString(
    Buf* self,
    const char* str,
    size_t len);

ALWAYS_INLINE void BufCatCh(
    Buf* self,
    char c)
{
    if (self->size != self->capacity)
    {
        self->data[self->size++] = c;
        return;
    }

    BufCat(self, &c, 1);
}

void __BufCatCh2(
    Buf* self,
    char c1,
    char c2);

ALWAYS_INLINE void BufCatCh2(
    Buf* self,
    char c1,
    char c2)
{
    if (self->size + 2 > self->capacity)
    {
        __BufCatCh2(self, c1, c2);
        return;
    }

    self->data[self->size++] = c1;
    self->data[self->size++] = c2;
}

ALWAYS_INLINE void BufSet(
    Buf* self,
    char c,
    size_t size)
{
    /*HOTSOPT*/
    size_t n = self->size + size;

    if (n > self->capacity)
    {
        if (__BufReserve(self, n) != 0)
            return;
    }

    memset(self->data + self->size, c, size);
    self->size = n;
}

void BufRemove(
    Buf* self,
    size_t offset,
    size_t size);

int BufFmtV(Buf* self, const char* format, va_list ap);

PRINTF_FORMAT(2, 3)
int BufFmt(Buf* self, const char* format, ...);

/* Zero-terminate this buffer without increasing its size */
INLINE void BufZeroTerminate(Buf* self)
{
    if (self->size + 1 > self->capacity)
    {
        if (__BufReserve(self, self->size + 1) != 0)
            return;
    }

    self->data[self->size] = '\0';
}

#define BufDefine(NAME, SIZE) \
    Alloc alloc##NAME; \
    char allocBuf##NAME[SIZE]; \
    Buf buf; \
    AllocInit(&alloc##NAME, allocBuf##NAME, sizeof(allocBuf##NAME)); \
    BufInit(&NAME, &alloc##NAME)

int BufCatFile(Buf* self, const char* path);

/* Cat the file in the /share/phit directory */
int BufCatShareFile(Buf* self, const char* basename);

void BufCat2(
    Buf* self,
    const char* s1,
    size_t n1,
    const char* s2,
    size_t n2);

void BufCat3(
    Buf* self,
    const char* s1,
    size_t n1,
    const char* s2,
    size_t n2,
    const char* s3,
    size_t n3);

void BufCat4(
    Buf* self,
    const char* s1,
    size_t n1,
    const char* s2,
    size_t n2,
    const char* s3,
    size_t n3,
    const char* s4,
    size_t n4);

#endif /* _buf_h */
