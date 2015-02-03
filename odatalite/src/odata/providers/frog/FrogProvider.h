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
#ifndef _FrogProvider_h
#define _FrogProvider_h

#include <odata/odatacxx.h>

#if 1
# define USE_CACHE
#endif

class FrogProvider : public odata::Provider
{
public:

    FrogProvider();

    virtual void Load(odata::Scope& scope);

    virtual void Unload(odata::Scope& scope);

    virtual void Get(
        odata::Scope& scope,
        const odata::URI& uri);

    odata::Object MakeKermit(odata::Scope& scope);

    odata::Object MakeWillie(odata::Scope& scope);

    odata::Object MakeFreddy(odata::Scope& scope);

#if defined(USE_CACHE)
    odata::Object* m_kermit;
    odata::Object* m_willie;
    odata::Object* m_freddy;
#endif
};

#endif /* _FrogProvider_h */
