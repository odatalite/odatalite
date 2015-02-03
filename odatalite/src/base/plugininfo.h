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
#ifndef _phit_plugininfo_h
#define _phit_plugininfo_h

#include "common.h"
#include "shlib.h"
#include <phit.h>

#define HTTP_METHOD_ANY (-1)

typedef struct _PluginInfo
{
    /* PHIT_Method or HTTP_METHOD_ANY */
    char* name;
    int method;
    char* uri;
    size_t uriLen;
    char* link;
    size_t linkLen;
    PHIT_Plugin* plugin;
    char* libname;
    Shlib* shlib;
    int loaded;
}
PluginInfo;

size_t PluginInfoLoad(
    const char* path,
    PluginInfo** array,
    size_t arraySize,
    size_t arrayOffset,
    char* error,
    size_t errorSize);

void PluginInfoRelease(
    PluginInfo** array,
    size_t arraySize);

#endif /* _phit_plugininfo_h */
