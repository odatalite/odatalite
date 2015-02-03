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
#ifndef _phit_base_format_h
#define _phit_base_format_h

#include <stdarg.h>
#include <string.h>
#include "common.h"
#include "str.h"

INLINE int Vsnprintf(
    char* str, 
    size_t size, 
    const char* format, 
    va_list ap)
{
#if defined(_MSC_VER)
    return _vsnprintf_s(str, size, _TRUNCATE, format, ap);
#elif defined(HAVE_VSNPRINTF)
    return vsnprintf(str, size, format, ap);
#else
# error "vsnprintf() defined"
#endif
}

PRINTF_FORMAT(3, 4)
int Snprintf(
    char* buffer,
    size_t size,
    const char* format,
    ...);

/* snprintf(buf, "%u", x) */
ALWAYS_INLINE size_t Format_u(char buf[12], unsigned int x)
{
    char tmp[12];
    size_t size;
    strcpy(buf, UIntToStr(tmp, x, &size));
    return size;
}

/* snprintf(buf, "%02u", x) */
ALWAYS_INLINE size_t Format_02u(char* buf, unsigned int x)
{
    UIntToStrZeroPadded(buf, 2, x);
    return 2;
}

/* snprintf(buf, "%03u", x) */
ALWAYS_INLINE size_t Format_03u(char* buf, unsigned int x)
{
    UIntToStrZeroPadded(buf, 3, x);
    return 3;
}

/* snprintf(buf, "%04u", x) */
ALWAYS_INLINE size_t Format_04u(char* buf, unsigned int x)
{
    UIntToStrZeroPadded(buf, 4, x);
    return 4;
}

/* snprintf(buf, "%12llu", x) */
size_t Format_12llu(char* buf, unsigned long long x);

#endif /* _phit_base_format_h */
