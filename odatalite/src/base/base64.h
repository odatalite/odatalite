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
#ifndef _phit_base64_h
#define _phit_base64_h

#include "common.h"
#include <sys/types.h>

typedef struct _Base64EncState
{
    int state;

    /* Input buffer */
    const unsigned char* data;
    size_t size;

    /* Offset into output buffer */
    size_t offset;

    /* Holds base-64 characters already encoded */
    unsigned char chars[4];

    /* Number of characters encoded */
    size_t numEncoded;

    /* Non-zero when characters are all encoded */
    int finished;
}
Base64EncState;

#define BASE64ENCSTATE_INITIALIZER { 0, NULL, 0, 0, { 0, 0, 0, 0 }, 0, 0 }

size_t Base64Enc(
    Base64EncState* state,
    const void* data,
    size_t size,
    char* dataOut,
    size_t sizeOut);

typedef struct _Base64DecState
{
    int state;
    unsigned char* data;
    size_t size;
    unsigned char* end;
    size_t n;
    unsigned char chars[4];
}
Base64DecState;

#define BASE64DECSTATE_INITIALIZER { 0, NULL, 0, NULL, 0, { 0, 0, 0, 0 } }

int Base64Dec(
    Base64DecState* state,
    const char* data,
    size_t size,
    void* dataOut,
    size_t sizeOut);

#endif /* _phit_base64_h */
