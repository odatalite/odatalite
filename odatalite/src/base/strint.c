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
#include <limits.h>
#include "str.h"

void UIntToStrZeroPadded(
    char *buf,
    size_t paddedSize,
    unsigned int x)
{
    size_t n;
    char tmp[11];
    char* s = (char*)UIntToStr(tmp, x, &n);

    if (n > paddedSize)
    {
        memcpy(buf, s + n - paddedSize, paddedSize + 1);
        return;
    }
    else if (n == paddedSize)
    {
        memcpy(buf, s, paddedSize + 1);
    }
    else
    {
        size_t r = paddedSize - n;
        memset(buf, '0', r);
        memcpy(buf + r, s, n + 1);
    }
}

void ULongLongToStrZeroPadded(
    char *buf,
    size_t paddedSize,
    unsigned long long x)
{
    size_t n;
    char tmp[21];
    char* s = (char*)ULongLongToStr(tmp, x, &n);

    if (n > paddedSize)
    {
        memcpy(buf, s + n - paddedSize, paddedSize + 1);
        return;
    }
    else if (n == paddedSize)
    {
        memcpy(buf, s, paddedSize + 1);
    }
    else
    {
        size_t r = paddedSize - n;
        memset(buf, '0', r);
        memcpy(buf + r, s, n + 1);
    }
}

const char* UIntToStr(
    char buf[11], 
    unsigned int x, 
    size_t* size)
{
    char* p;

    p = &buf[10];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    if (size)
        *size = &buf[10] - p;

    return p;
}

const char* SIntToStr(
    char buf[12], 
    int x, 
    size_t* size)
{
    char* p;
    int neg;

    if (x == INT_MIN)
    {
        strcpy(buf, "-2147483648");
        *size = 11;
        return buf;
    }

    if (x < 0)
    {
        x = -x;
        neg = 1;
    }
    else
        neg = 0;

    p = (char*)UIntToStr(buf+1, (unsigned int)x, size);

    if (neg)
    {
        *--p = '-';
        (*size)++;
    }

    return p;
}

const char* ULongToStr(
    char buf[21], 
    unsigned long x, 
    size_t* size)
{
    char* p;        
        
    p = &buf[20];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    if (size)
        *size = &buf[20] - p;

    return p;
}

const char* ULongLongToStr(
    char buf[21], 
    unsigned long long x, 
    size_t* size)
{
    char* p;

    p = &buf[20];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    if (size)
        *size = &buf[20] - p;

    return p;
}

const char* SLongLongToStr(
    char buf[22], 
    long long x, 
    size_t* size)
{
    char* p;
    int neg;

    if (x == LLONG_MIN)
    {
        strcpy(buf, "-9223372036854775808");
        *size = 20;
        return buf;
    }

    if (x < 0)
    {
        x = -x;
        neg = 1;
    }
    else
        neg = 0;

    p = (char*)ULongLongToStr(buf+1, (unsigned int)x, size);

    if (neg)
    {
        *--p = '-';
        (*size)++;
    }

    return p;
}

int StrToInt(const char* s, int* x)
{
    char* end;
    long tmp;

    tmp = strtol(s, &end, 10);

    if (*end != '\0' || tmp < INT_MIN || tmp > INT_MAX)
        return -1;

    *x = (int)tmp;
    return 0;
}

int StrToUInt(const char* s, unsigned int* x)
{
    char* end;
    unsigned long tmp;

    tmp = strtoul(s, &end, 10);

    if (*end != '\0' || tmp > UINT_MAX)
        return -1;

    *x = (unsigned int)tmp;
    return 0;
}

int StrToULong(const char* s, unsigned long* x)
{
    char* end;

    *x = strtoul(s, &end, 10);

    if (*end != '\0')
        return -1;

    return 0;
}

int StrToUShort(const char* s, unsigned short* x)
{
    char* end;
    unsigned long tmp;

    tmp = strtoul(s, &end, 10);

    if (*end != '\0' || tmp > USHRT_MAX)
        return -1;

    *x = (unsigned short)tmp;
    return 0;
}
