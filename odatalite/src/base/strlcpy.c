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
#include "str.h"

size_t Strlcpy(
    char* dest,
    const char* src,
    size_t size)
{
#if 0
    const char* start = src;

    if (size)
    {
        char* end = dest + size - 1;

        while (*src && dest != end)
            *dest++ = (char)*src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    DEBUG_ASSERT(src - start < size);

    return src - start;
#else

    size_t nsrc = strlen(src); /* length of src */

    if (nsrc < size)
    {
        memcpy(dest, src, nsrc+1);
    }
    else if (nsrc > size)
    {
        memcpy(dest, src, size-1);
        dest[size-1] = '\0';
    }

    return nsrc;

#endif
}

size_t Strlcpy2(
    char* dest,
    const char* s1,
    const char* s2,
    size_t size)
{
    size_t n;

    if ((n = Strlcpy(dest, s1, size)) >= size)
        return n + strlen(s2);

    return Strlcat(dest, s2, size);
}

size_t Strlcpy3(
    char* dest,
    const char* s1,
    const char* s2,
    const char* s3,
    size_t size)
{
    size_t n;

    if ((n = Strlcpy2(dest, s1, s2, size)) >= size)
        return n + strlen(s3);

    return Strlcat(dest, s3, size);
}
