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
#include <odata/odatamacros.h>
#include <cstdio>
#include <cstdlib>
#include "FrogProvider.h"
#include <new>
#include "strings.h"

#define D(X)

using namespace odata;

/* Overload operator new to remove dependency on C++ library */
void* operator new(size_t size)
{
    return malloc(size);
}

/* Overload operator delete to remove dependency on C++ library */
void operator delete(void* p)
{
    free(p);
}

Object FrogProvider::MakeKermit(Scope& scope)
{
#if defined(USE_CACHE)
    if (m_kermit)
        return *m_kermit;
#endif

    Object frog = scope.NewObject();

    frog.SetFlags(OL_FLAG_STATIC_NAME|OL_FLAG_LENGTH_NAME|OL_FLAG_STATIC_VALUE|
        OL_FLAG_ALLOW_DUPLICATES);

    frog.Add(Frog_Id, OL_GuidValue(
        0x1C6D09D2, 0xF1B6, 0x43F1, 0xB30B, 0xF774, 0x7822A29B));
    frog.AddString(Frog_UserName, "kermit");
    frog.AddString(Frog_First, "Kermit");
    frog.AddString(Frog_Last, "Frog");
    frog.AddString(Frog_Color, "Green");
    frog.AddDate(Frog_Birthdate, Date(1955, 12, 3));

    frog.AddNavigationLink(Frog_Friend, "Frogs('willie')");

    {
        Array arr = scope.NewArray();
        arr.AppendDate(Date(2015, 12, 31));
        arr.AppendDate(Date(2015, 12, 24));
        arr.AppendDate(Date(2015, 12, 25));
        frog.AddArray(Frog_Holidays, arr);
    }

#if defined(USE_CACHE)
    m_kermit = new Object(frog);
#endif

    return frog;
}

Object FrogProvider::MakeWillie(Scope& scope)
{
#if defined(USE_CACHE)
    if (m_willie)
        return *m_willie;
#endif

    Object frog = scope.NewObject();

    frog.SetFlags(OL_FLAG_STATIC_NAME|OL_FLAG_LENGTH_NAME|OL_FLAG_STATIC_VALUE|
        OL_FLAG_ALLOW_DUPLICATES);

    frog.Add(Frog_Id, OL_GuidValue(
        0X7C1D0F49, 0X0DF2, 0X4EB9, 0X8566, 0X7DFD, 0XB4283E46));
    frog.AddString(Frog_UserName, "willie");
    frog.AddString(Frog_First, "William");
    frog.AddString(Frog_Last, "Frog");
    frog.AddString(Frog_Color, "Red");
    frog.AddDate(Frog_Birthdate, Date(2006, 3, 1));

#if defined(USE_CACHE)
    m_willie = new Object(frog);
#endif

    return frog;
}

Object FrogProvider::MakeFreddy(Scope& scope)
{
#if defined(USE_CACHE)
    if (m_freddy)
        return *m_freddy;
#endif

    Object frog = scope.NewObject();

    frog.SetFlags(OL_FLAG_STATIC_NAME|OL_FLAG_LENGTH_NAME|OL_FLAG_STATIC_VALUE|
        OL_FLAG_ALLOW_DUPLICATES);

    frog.Add(Frog_Id, OL_GuidValue(
        0x430BAEEB, 0x3192, 0x46E9, 0xA244, 0x79F3, 0xD68CA03A));
    frog.AddString(Frog_UserName, "freddy");
    frog.AddString(Frog_First, "Frederick");
    frog.AddString(Frog_Last, "Frog");
    frog.AddString(Frog_Color, "Blue");
    frog.AddDate(Frog_Birthdate, Date(1991, 8, 3));

#if defined(USE_CACHE)
    m_freddy = new Object(frog);
#endif

    return frog;
}

FrogProvider::FrogProvider()
{
#if defined(USE_CACHE)
    m_kermit = 0;
    m_willie = 0;
    m_freddy = 0;
#endif
}

void FrogProvider::Load(odata::Scope& scope)
{
    D( printf("=== FrogProvider::Load()\n"); )
}

void FrogProvider::Unload(odata::Scope& scope)
{
    D( printf("=== FrogProvider::Unload()\n"); )

    if (m_kermit)
    {
        delete m_kermit;
        m_kermit = 0;
    }

    if (m_willie)
    {
        delete m_willie;
        m_willie = 0;
    }

    if (m_freddy)
    {
        delete m_freddy;
        m_freddy = 0;
    }

    /* Avoid calling 'operator delete()' (requires standard C++ library */
    this->~FrogProvider();
    free(this);
}

void FrogProvider::Get(
    odata::Scope& scope,
    const odata::URI& uri)
{
    const char* entityName;
    const char* userName;
    const char* role = 0;

    D( printf("=== FrogProvider::Get()\n"); )
    D( uri.Print(); )

    /* Get the user role */
    if (!scope.GetOption(OL_Scope_Option_Role, &role, sizeof(role)))
    {
        scope.SendResult(OL_Result_Failed);
        return;
    }

    D( printf("FrogProvider::Get(): role=%s\n", role); )

    if (!(entityName = uri.GetName(0)) || strcmp(entityName, "Frogs") != 0)
    {
        scope.SendResult(OL_Result_NotSupported);
        return;
    }

    if (uri.Count() < 1)
    {
        scope.SendResult(OL_Result_NotSupported);
        return;
    }

    if (uri.GetKeyString(0, "$0", userName))
    {
        if (strcmp(userName, "kermit") == 0)
        {
            scope.SendEntity(MakeKermit(scope));
            scope.SendResult(OL_Result_Ok);
        }
        else if (strcmp(userName, "willie") == 0)
        {
            scope.SendEntity(MakeWillie(scope));
            scope.SendResult(OL_Result_Ok);
        }
        else if (strcmp(userName, "freddy") == 0)
        {
            scope.SendEntity(MakeFreddy(scope));
            scope.SendResult(OL_Result_Ok);
        }
        else
        {
            scope.SendResult(OL_Result_NotFound,
                "Frog.UserName='%s'", userName);
            return;
        }
    }
    else if (uri.KeyCount(0) == 0)
    {
        scope.SendBeginEntitySet();
        {
            scope.SendEntity(MakeKermit(scope));
            scope.SendEntity(MakeWillie(scope));
            scope.SendEntity(MakeFreddy(scope));
        }
        scope.SendEndEntitySet();
        scope.SendResult(OL_Result_Ok);
        return;
    }

    scope.SendResult(OL_Result_NotSupported);
}

extern "C" OL_EXPORT OL_Provider* OL_ProviderEntryPoint()
{
    D( printf("=== OL_ProviderEntryPoint()\n"); )

    FrogProvider* self = new FrogProvider();

    return (OL_Provider*)self;
}
