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
#ifndef _phit_parse_h
#define _phit_parse_h

#include "common.h"
#include "alloc.h"
#include "chars.h"

/* Parse a C-style identifier: "[A-Za-a_0-9]+" */
INLINE const char* ParseToken(const char* text)
{
    const char* p = text;

    while (IsToken(*p))
        p++;

    return p;
}

/* Parse a C-style identifier: "[A-Za-z_][A-Za-a_0-9]*" */
INLINE const char* ParseIdent(const char* text)
{
    const char* p = text;

    if (!isalpha(*p) && *p != '_')
        return p;

    return ParseToken(p+1);
}

/* Return a pointer to the first <CR><LF> sequence (or NULL if none) */
const char* FindCRLF(const char* data, size_t size);

/* Return a pointer to the first <CR><LF><CR><LF> sequence (or NULL if none) */
const char* FindCRLFCRLF(const char* data, size_t size);

int ParsePath(
    char* path_,
    Alloc* alloc,
    char*** pathOut,
    int* npathOut);

char* TrimLeadingAndTrailingLWS(
    char* data,
    size_t size);

#endif /* _phit_parse_h */
