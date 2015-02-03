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
#include "format.h"

int Snprintf(
    char* buffer,
    size_t size,
    const char* format,
    ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = Vsnprintf(buffer, size, format, ap);
    va_end(ap);

    return r;
}

size_t Format_12llu(char* buf, unsigned long long x)
{
    size_t size;
    char tmp[21];
    const char* s = ULongLongToStr(tmp, x, &size);

    if (size < 12)
    {
        memcpy(buf, s, size+1);
        return size;
    }
    else
    {
        /* Truncate size-12 digits */
        memcpy(buf, s + size - 12, 13);
        return 12;
    }
}
