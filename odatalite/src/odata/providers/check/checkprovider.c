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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base/format.h>
#include <odata/odata.h>

#include "strings.h"

#define D(X)

typedef struct _Provider 
{
    OL_Provider base;
}
Provider;

static void _Check_Load(
    OL_Provider* self,
    OL_Scope* scope)
{
    D( printf("=== _Check_Load\n"); )
}

static void _Check_Unload(
    OL_Provider* self,
    OL_Scope* scope)
{
    D( printf("=== _Check_Unload\n"); )
    free(self);
}

static void _Check_Get(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri)
{
    const char* func = NULL;

    D( printf("=== _Check_Get\n"); )
    D ( OL_URI_Print(uri, 0); )

    if (OL_URI_Count(uri) != 1)
    {
        OL_Scope_SendResult(scope, OL_Result_NotSupported);
        return;
    }

    if (!(func = OL_URI_GetName(uri, 0)))
    {
        OL_Scope_SendResult(scope, OL_Result_Failed);
        return;
    }

    if (strcmp(func, "Check") != 0)
    {
        OL_Scope_SendResult(scope, OL_Result_NotSupported);
        return;
    }

    {
        OL_Value v;

        OL_Object* obj = OL_Scope_NewObject(scope);
        OL_Object_AddString(obj, "Message", "ok");
        v = OL_GuidValue(0x1F9E824A,0xB1E8,0x4078,0x9475,0x897E,0x3987127A);
        OL_Object_Add(obj, "GUID", &v);

        OL_Scope_SendEntity(scope, obj);
        OL_Scope_SendResult(scope, OL_Result_Ok);
        OL_Object_Release(obj);
        return;
    }
}

static void _Check_Post(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Check_Put(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Check_Patch(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Check_Delete(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri)
{
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static OL_ProviderFT _ft =
{
    _Check_Load,
    _Check_Unload,
    _Check_Get,
    _Check_Post,
    _Check_Put,
    _Check_Patch,
    _Check_Delete,
};

OL_EXPORT OL_Provider* OL_ProviderEntryPoint()
{
    Provider* self;

    if (!(self = (Provider*)malloc(sizeof(Provider))))
        return NULL;

    self->base.ft = &_ft;

    return &self->base;
}
