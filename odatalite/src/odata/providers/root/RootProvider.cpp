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
#include "RootProvider.h"
#include <new>
#include "strings.h"

#define D(X)

using namespace odata;

void RootProvider::Load(odata::Scope& scope)
{
    D( printf("=== RootProvider::Load()\n"); )
}

void RootProvider::Unload(odata::Scope& scope)
{
    D( printf("=== RootProvider::Unload()\n"); )

    /* Avoid calling 'operator delete()' (requires standard C++ library */
    this->~RootProvider();
    free(this);
}

/*
    {
        "EntitySets": [
            "Customers",
            "Orders",
            "OrderDetails"
        ]
    }

*/

void RootProvider::Get(
    odata::Scope& scope,
    const odata::URI& uri)
{
    D( printf("=== RootProvider::Get()\n"); )
    D( uri.Print(); )

    if (uri.Count() == 0)
    {
        Object obj = scope.NewObject();
        Array arr = scope.NewArray();
        arr.AppendString("Person");
        arr.AppendString("Frogs");
        arr.AppendString("Presidents");
        arr.AppendString("Gadgets");
        obj.AddArray("EntitySets", arr);

        scope.SendEntity(obj);
        scope.SendResult(OL_Result_Ok);
        return;
    }

    scope.SendResult(OL_Result_NotFound);
}

extern "C" OL_EXPORT OL_Provider* OL_ProviderEntryPoint()
{
    D( printf("=== OL_ProviderEntryPoint()\n"); )

    /* Avoid calling 'operator new()' (requires standard C++ library */
    RootProvider* self = (RootProvider*)calloc(1, sizeof(RootProvider));
    new(self) RootProvider();

    return (OL_Provider*)self;
}
