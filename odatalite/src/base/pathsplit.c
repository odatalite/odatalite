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
#include "path.h"
#include "parse.h"

size_t SplitPath(
    char* path,
    const char* segments[],
    size_t nsegments)
{
    char* p = path;
    size_t n = 0;

    /* The first segments of an absolute path is "/" */
    if (*p == '/')
    {
        segments[n++] = "/";
        p++;
    }

    /* For each segment of the path */
    while (*p)
    {
        char* start;
        char* end;

        start = p;
        {
            while (*p && *p != '/')
                p++;
        }
        end = p;

        if (*p == '/')
            p++;

        /* Ignore consecutive '/' characters */
        if (start == end)
            continue;

        *end = '\0';

        if (n == nsegments)
            return SIZEMAX;

        segments[n++] = start;
    }

    return n;
}
