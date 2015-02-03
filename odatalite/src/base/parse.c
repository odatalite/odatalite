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
#include "parse.h"
#include "chars.h"

/*#undef ENABLE_SPEED_OPTIMIZATIONS*/

#if defined(PHIT_LITTLE_ENDIAN) && defined(PHIT_ONE_BYTE_ALIGNMENT)
# define __CRLF (((unsigned short)'\n' << 8) | (unsigned int)'\r')
# define TESTCRLF(p) (*((unsigned short*)(p)) == __CRLF)
#else
# define TESTCRLF(p) ((p)[0] == '\r' && (p)[1] == '\n')
#endif

const char* FindCRLF(
    const char* data, 
    size_t size)
{
    /*HOTSPOT*/
    const char* p = data;
    size_t n = size - 1;

#if defined(ENABLE_SPEED_OPTIMIZATIONS)

    while (n >= 8)
    {
        if (TESTCRLF(&p[0]))
            return &p[0];
        if (TESTCRLF(&p[1]))
            return &p[1];
        if (TESTCRLF(&p[2]))
            return &p[2];
        if (TESTCRLF(&p[3]))
            return &p[3];
        if (TESTCRLF(&p[4]))
            return &p[4];
        if (TESTCRLF(&p[5]))
            return &p[5];
        if (TESTCRLF(&p[6]))
            return &p[6];
        if (TESTCRLF(&p[7]))
            return &p[7];

        n -= 8;
        p += 8;
    }

    while (n >= 4)
    {
        if (TESTCRLF(&p[0]))
            return &p[0];
        if (TESTCRLF(&p[1]))
            return &p[1];
        if (TESTCRLF(&p[2]))
            return &p[2];
        if (TESTCRLF(&p[3]))
            return &p[3];

        n -= 4;
        p += 4;
    }

    while (n >= 2)
    {
        if (TESTCRLF(&p[0]))
            return &p[0];
        if (TESTCRLF(&p[1]))
            return &p[1];

        n -= 2;
        p += 2;
    }

    while (n >= 1)
    {
        if (TESTCRLF(&p[0]))
            return &p[0];

        n -= 1;
        p += 1;
    }

#else /* defined(ENABLE_SPEED_OPTIMIZATIONS) */

    while (n >= 1)
    {
        if (p[0] == '\r' && p[1] == '\n')
            return &p[0];

        n -= 1;
        p += 1;
    }

#endif /* defined(ENABLE_SPEED_OPTIMIZATIONS) */

    /* Not found */
    return NULL;
}

#if defined(PHIT_LITTLE_ENDIAN) && defined(PHIT_ONE_BYTE_ALIGNMENT)
# define __CRLFCRLF (unsigned int)(('\n'<<24)|('\r'<<16)|('\n'<<8)|'\r')
# define TESTCRLFCRLF(p) (*((unsigned int*)p) == __CRLFCRLF)
#else 
# define TESTCRLFCRLF(p) (p[0]=='\r' && p[1]=='\n' && p[2]=='\r' && p[3]=='\n')
#endif

const char* FindCRLFCRLF(const char* data, size_t size)
{
    const char* p;
    const char* end;

    /* Not found */
    if (size < 4)
        return NULL;

    for (p = data, end = data + size - 3; p < end; )
    {
        if (!IsCRLF(p[3]))
        {
            p += 4;
            continue;
        }

        if (TESTCRLFCRLF(p))
            return p;

        p++;
    }

    /* Not found */
    return NULL;
}

char* TrimLeadingAndTrailingLWS(
    char* data,
    size_t size)
{
    char* start = data;
    char* end = data + size;

    /* Trim leading space */
    while (IsLWS(*start))
        start++;

    /* Trim trailing space */
    while (end != start && IsLWS(end[-1]))
        *--end = '\0';

    return start;
}
