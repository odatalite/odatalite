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

int Strncaseeq(const char* s1, const char* s2, size_t n)
{
    /*HOTSOPT*/

    while (n >= 4)
    {
        if (((s1[0] - s2[0]) && (tolower(s1[0]) - tolower(s2[0]))) ||
            ((s1[1] - s2[1]) && (tolower(s1[1]) - tolower(s2[1]))) ||
            ((s1[2] - s2[2]) && (tolower(s1[2]) - tolower(s2[2]))) ||
            ((s1[3] - s2[3]) && (tolower(s1[3]) - tolower(s2[3]))))
        {
            return -1;
        }

        n -= 4;
        s1 += 4;
        s2 += 4;
    }

    while (n--)
    {
        if (((s1[0] - s2[0]) && (tolower(s1[0]) - tolower(s2[0]))))
        {
            return -1;
        }

        s1++;
        s2++;
    }

    /* Equal */
    return 0;
}

int StrcmpSuffix(
    const char* str,
    const char* suffix)
{
    size_t nstr = strlen(str);
    size_t nsuffix = strlen(suffix);

    if (nsuffix > nstr)
        return -1;

    return strcmp(str + nstr - nsuffix, suffix);
}

unsigned long long MakeStr8(const char* str)
{
    return MakeStr8Fast(str);
}

int Streqn(
    const char* s1,
    const char* s2,
    size_t n)
{
    size_t m = n / sizeof(int);
    const int* p1 = (const int*)s1;
    const int* p2 = (const int*)s2;

    while (m)
    {
        if (*p1 != *p2)
            return -1;
        m--;
        p1++;
        p2++;
    }

    s1 = (const char*)p1;
    s2 = (const char*)p2;
    n -= m * sizeof(int);

    while (n)
    {
        if (*s1 != *s2)
            return -1;

        n--;
        s1++;
        s2++;
    }

    return 0;
}

char* StripOuterSpaces(char* str)
{
    char* end = str + strlen(str);

    while (end != str && isspace(end[-1]))
        *--end = '\0';

    while (*str && isspace(*str))
        str++;

    return str;
}

char* Strnstr(const char* str, const char* s, size_t n)
{
    const char* p;

    for (p = str; *p; p++)
    {
        if (*p == s[0] && strncmp(p, s, n) == 0)
            return (char*)p;
    }

    return NULL;
}

char* StrtokTrim(
    StrtokState* state,
    char* str,
    const char* delim)
{
    char* p = Strtok(state, str, delim);

    if (p)
        return StripOuterSpaces(p);

    return p;
}

size_t Strtoks(
    char* str,
    const char* delim,
    char** toks,
    size_t ntoks)
{
    StrtokState state;
    char* p;
    size_t n = 0;

    for (p = Strtok(&state, str, delim); p; p = Strtok(&state, NULL, delim))
    {
        if (n == ntoks)
            return (size_t)-1;

        toks[n++] = p;
    }

    return n;
}
