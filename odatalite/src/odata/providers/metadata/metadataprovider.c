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
#include <sys/types.h>
#include <dirent.h>
#include <base/format.h>
#include <odata/odata.h>

extern const EDMX_Edmx ServiceRoot_Edmx;

#define D(X) X

typedef struct _Provider 
{
    OL_Provider base;
}
Provider;

static void _Metadata_Load(
    OL_Provider* self,
    OL_Scope* scope)
{
}

static void _Metadata_Unload(
    OL_Provider* self,
    OL_Scope* scope)
{
    free(self);
}

static void _Metadata_Get(
    OL_Provider* self_,
    OL_Scope* scope,
    const OL_URI* uri)
{
    const char* entityType;

    /* Get the entity type of the first path segment */
    if (!(entityType = OL_URI_GetName(uri, 0)))
    {
        OL_Scope_SendResult(scope, OL_Result_Failed);
        return;
    }

    printf("{%s}\n", entityType);

    if (strcmp(entityType, "$metadata") == 0)
    {
        OL_Scope_SendMetadataStruct(scope, &ServiceRoot_Edmx);
        OL_Scope_SendResult(scope, OL_Result_Ok);
    }
    else
    {
        OL_Scope_SendResult(scope, OL_Result_NotSupported);
    }
}

static void _Metadata_Post(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    D( printf("_Metadata_Post()\n"); )
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Metadata_Put(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    D( printf("_Metadata_Put()\n"); )
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Metadata_Patch(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    D( printf("_Metadata_Patch()\n"); )
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Metadata_Delete(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri)
{
    D( printf("_Metadata_Delete()\n"); )
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static OL_ProviderFT _ft =
{
    _Metadata_Load,
    _Metadata_Unload,
    _Metadata_Get,
    _Metadata_Post,
    _Metadata_Put,
    _Metadata_Patch,
    _Metadata_Delete,
};

OL_EXPORT OL_Provider* OL_ProviderEntryPoint()
{
    Provider* self;

    if (!(self = (Provider*)Calloc(1, sizeof(Provider))))
        return NULL;

    self->base.ft = &_ft;

    return &self->base;
}
