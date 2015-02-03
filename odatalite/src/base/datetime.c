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

#include "common.h"

#if defined(HAVE_POSIX)
# include <sys/time.h>
#endif

#include "datetime.h"

unsigned long long Time()
{
#if defined(_MSC_VER)
    FILETIME ft;
    ULARGE_INTEGER tmp;

    GetSystemTimeAsFileTime(&ft);
    tmp.u.LowPart = ft.dwLowDateTime;
    tmp.u.HighPart = ft.dwHighDateTime;
    tmp.QuadPart -= 0X19DB1DED53E8000;
    return (unsigned long long)(tmp.QuadPart / (UINT64)10);
#else
    /* Combine into one structure (to elminate need for two memset calls) */
    typedef struct _TimeInfo
    {
        struct timeval tv;
        struct timezone tz;
    }
    TimeInfo;
    TimeInfo ti;
    memset(&ti, 0, sizeof(ti));

    if (gettimeofday(&ti.tv, &ti.tz) != 0)
        return (unsigned long long)-1;

    return (unsigned long long)ti.tv.tv_sec * 
        (unsigned long long)1000000 + (unsigned long long)ti.tv.tv_usec;

    return 0;
#endif
}
