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

size_t Strlcat(
    char* dest,
    const char* src,
    size_t size)
{
    size_t ndest = strlen(dest); /* length of dest */
    size_t nsrc = strlen(src); /* length of src */
    size_t rem = size - ndest - 1; /* bytes remaining in buffer (w/o '\0') */
    size_t ncopy = nsrc < rem ? nsrc : rem; /* bytes to copy (w/o '\0') */

    /* Copy if there is more than just a zero terminator */
    if (ncopy)
    {
        memcpy(dest + ndest, src, ncopy);
        dest[ndest + ncopy] = '\0';
    }

    return ndest + nsrc;
}

size_t Strlcat2(
    char* dest,
    const char* s1,
    const char* s2,
    size_t size)
{
    size_t n;

    if ((n = Strlcat(dest, s1, size)) >= size)
        return n + strlen(s2);

    return Strlcat(dest, s2, size);
}

size_t Strlcat3(
    char* dest,
    const char* s1,
    const char* s2,
    const char* s3,
    size_t size)
{
    size_t n;

    if ((n = Strlcat2(dest, s1, s2, size)) >= size)
        return n + strlen(s3);

    return Strlcat(dest, s3, size);
}
