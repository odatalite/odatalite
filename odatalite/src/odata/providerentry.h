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
#ifndef _odata_providerentry_h
#define _odata_providerentry_h

#include <odata/odata.h>
#include <base/shlib.h>

#define MAX_SEGMENTS 8

typedef struct _Path
{
    char* buf;
    char* path;
    const char* segments[MAX_SEGMENTS];
    size_t nsegments;
}
Path;

typedef struct _PathArray
{
    Path* data;
    size_t size;
    size_t capacity;
}
PathArray;

typedef struct _ProviderEntry
{
    char* libname;
    PathArray paths;
    unsigned int queryOptions;
    Shlib* shlib;
    OL_Provider* provider;
}
ProviderEntry;

int ProviderEntryLoadFile(
    const char* path,
    ProviderEntry*** entries,
    size_t* entriesSize,
    char* error,
    size_t errorSize);

void ProviderEntryDelete(
    ProviderEntry* self);

void ProviderEntryPrint(
    const ProviderEntry* self);

#endif /* _odata_providerentry_h */
