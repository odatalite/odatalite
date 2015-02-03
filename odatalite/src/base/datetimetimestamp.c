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
# include <time.h>
#endif

#include "datetime.h"

int GetTimeStamp(char buf[TIMESTAMP_SIZE])
{
#if defined(_MSC_VER)
    {
        SYSTEMTIME systime;
        GetLocalTime(&systime);

        sprintf_s(
            buf,
            TIMESTAMP_SIZE,
            "%02u/%02u/%02u %02u:%02u:%02u",
            systime.wYear,
            systime.wMonth,
            systime.wDay,
            systime.wHour,
            systime.wMinute,
            systime.wSecond);
    }

#else /* defined(_MSC_VER) */

    unsigned long long usec;
    time_t t;
    struct tm tm;

    if ((usec = Time()) == (unsigned long long)-1)
    {
        buf[0] = '\0';
        return -1;
    }

    t = usec / 1000000;

    if (!localtime_r(&t, &tm))
        return -1;

    sprintf(
        buf,
        "%02u/%02u/%02u %02u:%02u:%02u",
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec);

#endif /* defined(_MSC_VER) */

    return 0;
}
