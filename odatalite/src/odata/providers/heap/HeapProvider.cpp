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
#include <cstdio>
#include <cstdlib>
#include "HeapProvider.h"
#include <new>
#include "strings.h"
#include <base/alloc.h>
#include <plugins/odata/options.h>

#define D(X)

using namespace odata;

void HeapProvider::Load(odata::Scope& scope)
{
    D( printf("=== HeapProvider::Load()\n"); )
}

void HeapProvider::Unload(odata::Scope& scope)
{
    D( printf("=== HeapProvider::Unload()\n"); )

    /* Avoid calling 'operator delete()' (requires standard C++ library */
    this->~HeapProvider();
    free(this);
}

void HeapProvider::Get(
    odata::Scope& scope,
    const odata::URI& uri)
{
    const char* func;

    D( printf("=== HeapProvider::Get()\n"); )
    D( uri.Print(); )

    if (uri.Count() != 1)
    {
        scope.SendResult(OL_Result_NotSupported);
        return;
    }

    if (!(func = uri.GetName(0)))
    {
        scope.SendResult(OL_Result_Failed, "invalid URI");
        return;
    }

    if (strcmp(func, "GetHeapUsage") == 0)
    {
#if defined(ENABLE_DEBUG) && defined(ENABLE_ALLOCATOR)
        AllocStats stats;

        if (!scope.GetOption( OPTION_ALLOCSTATS, &stats, sizeof(stats)))
        {
            scope.SendResult(OL_Result_Failed, "GetOption() failed");
            return;
        }

        Object o = scope.NewObject();
        o.AddInt64("BytesAllocated", stats.bytesAllocated);
        o.AddInt64("MaxBytesAllocated", stats.maxBytesAllocated);
        o.AddInt64("NumAllocs", stats.numAllocs);
        o.AddInt64("NumFrees", stats.numFrees);
        scope.SendEntity(o);
        scope.SendResult(OL_Result_Ok);
        return;
#endif
    }

    scope.SendResult(OL_Result_NotSupported);
}

extern "C" OL_EXPORT OL_Provider* OL_ProviderEntryPoint()
{
    D( printf("=== OL_ProviderEntryPoint()\n"); )

    /* Avoid calling 'operator new()' (requires standard C++ library */
    HeapProvider* self = (HeapProvider*)calloc(1, sizeof(HeapProvider));
    new(self) HeapProvider();

    return (OL_Provider*)self;
}
