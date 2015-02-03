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
#ifndef _test_h
#define _test_h

#include "common.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
**==============================================================================
**
** __numFailed;
** __numFailed;
**
**==============================================================================
*/

static unsigned int __numPassed = 0;
static unsigned int __numFailed = 0;

/*
**==============================================================================
**
** BEGINTEST()
**
**==============================================================================
*/

ALWAYS_INLINE void __BeginTest(const char* name)
{
#if 0
    printf("=== %s...", name);
#endif
}

#define BEGINTEST(NAME) \
    void NAME() \
    { \
        __BeginTest(#NAME); \

/*
**==============================================================================
**
** ENDTEST()
**
**==============================================================================
*/

ALWAYS_INLINE void __EndTestPassed(const char* name)
{
    __numPassed++;
#if 0
    printf("PASSED\n");
#endif
}

ALWAYS_INLINE void __EndTestFailed(const char* name)
{
    __numFailed++;
}

#define ENDTEST(NAME)  \
    goto EndTestPassed; /* suppress defined but not used warning */ \
    EndTestPassed: \
        __EndTestPassed(#NAME); \
        return; \
    goto EndTestFailed; /* suppress defined but not used warning */ \
    EndTestFailed: \
        __EndTestFailed(#NAME); \
        return; \
    }

/*
**==============================================================================
**
** TEST
**
**==============================================================================
*/

ALWAYS_INLINE void __Test(const char* file, size_t line, const char* cond)
{
    printf("FAILED\n");
    fprintf(stderr, "TEST: %s(%d): %s\n", file, (int)line, cond);
}

#define TEST(COND) \
    do \
    { \
        if (!(COND)) \
        { \
            __Test(__FILE__, __LINE__, #COND); \
            goto EndTestFailed; \
        } \
        break; \
    } \
    while (0)

/*
**==============================================================================
**
** PrintTestSummary()
**
**==============================================================================
*/

ALWAYS_INLINE void PrintTestSummary()
{
    if (__numFailed)
    {
        printf("*** Failed %u tests\n", __numFailed);
        exit(1);
    }
}

#endif /* _test_h */
