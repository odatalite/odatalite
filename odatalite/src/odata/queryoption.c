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
#include <common.h>
#include "queryoption.h"

const char* _queryOptionStrings[] =
{
#if 0
    "\006filter" + 1,
    "\006expand" + 1,
    "\006select" + 1,
    "\007orderby" + 1,
    "\003top" + 1,
    "\004skip" + 1,
    "\005count" + 1,
    "\006search" + 1,
    "\006format" + 1
#else
    "filter",
    "expand",
    "select",
    "orderby",
    "top",
    "skip",
    "count",
    "search",
    "format"
#endif
};

const char* QueryOptionToStr(unsigned int queryOption)
{
    unsigned int n = 0;

    while (queryOption)
    {
        n++;
        queryOption >>= 1;
    }

    n--;

    if (n >= ARRSIZE(_queryOptionStrings))
        return "unknown";

    return _queryOptionStrings[n];
}
