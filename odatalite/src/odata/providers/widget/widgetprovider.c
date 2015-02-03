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

#include <odata/odata.h>

OL_Object* MakeWidget(
    OL_Scope* scope,
    long long id,
    const char* color,
    const char* model,
    unsigned int weight)
{
    OL_Object* obj;

    if (!(obj = OL_Scope_NewObject(scope)))
        return NULL;

    OL_Object_AddInt64(obj, "Id", id);
    OL_Object_AddString(obj, "Color", color);
    OL_Object_AddString(obj, "Model", model);
    OL_Object_AddInt32(obj, "Weigth", weight);

    return obj;
}

typedef struct _Provider /* Extends OL_Provider */
{
    OL_Provider base;
    /* Define provider-specific fields here */
}
Provider;

static void _Load(
    OL_Provider* self,
    OL_Scope* scope)
{
}

static void _Unload(
    OL_Provider* self,
    OL_Scope* scope)
{
    free(self);
}

static void _Get(
    OL_Provider* self_,
    OL_Scope* scope,
    const OL_URI* uri)
{
    const char* name;

    /* Expecting one segment after 'service': service/Widgets */
    if (OL_URI_Count(uri) != 1)
    {
        OL_Scope_SendResult(scope, OL_Result_Failed);
        return;
    }

    /* Get the entity type */
    if (!(name = OL_URI_GetName(uri, 0)))
    {
        OL_Scope_SendResult(scope, OL_Result_Failed);
        return;
    }

    /* Fail if entity type name is not 'Widgets' */
    if (strcmp(name, "Widgets") != 0)
    {
        OL_Scope_SendResultF(scope, OL_Result_NotSupported, "%s", name);
        return;
    }

    /* Send all Widgets if no key (e.g.: 'odata/Widgets') */
    if (OL_URI_KeyCount(uri, 0) == 0)
    {
        OL_Object* obj;

        OL_Scope_SendBeginEntitySet(scope);

        /* Send Widgets(1001) */
        {
            if (!(obj = MakeWidget(scope, 1001, "Red", "A1", 55)))
            {
                OL_Scope_SendResult(scope, OL_Result_OutOfMemory);
                return;
            }

            OL_Scope_SendEntity(scope, obj);
            OL_Object_Release(obj);
        }

        /* Send Widgets(1002) */
        {
            if (!(obj = MakeWidget(scope, 1002, "Green", "A2", 65)))
            {
                OL_Scope_SendResult(scope, OL_Result_OutOfMemory);
                return;
            }

            OL_Scope_SendEntity(scope, obj);
            OL_Object_Release(obj);
        }

        OL_Scope_SendEndEntitySet(scope);
        OL_Scope_SendResult(scope, OL_Result_Ok);
        return;
    }

    /* Send one entity if key present (e.g., 'odata/Widgets(1001)') */
    if (OL_URI_KeyCount(uri, 0) == 1)
    {
        OL_Int64 id;
        OL_Object* obj;

        /* Get the key from the URI (e.g., 'odata/Widgets(1001)') */
        if (OL_URI_GetKeyInt64(uri, 0, "$0", &id) != OL_Result_Ok)
        {
            OL_Scope_SendResult(scope, OL_Result_NotSupported);
            return;
        }

        /* Send Widgets(1001) */
        if (id == 1001)
        {
            if (!(obj = MakeWidget(scope, 1001, "Red", "A1", 55)))
            {
                OL_Scope_SendResult(scope, OL_Result_OutOfMemory);
                return;
            }

            OL_Scope_SendEntity(scope, obj);
            OL_Object_Release(obj);
            OL_Scope_SendResult(scope, OL_Result_Ok);
            return;
        }

        /* Send Widgets(1001) */
        if (id == 1002)
        {
            if (!(obj = MakeWidget(scope, 1002, "Green", "A2", 65)))
            {
                OL_Scope_SendResult(scope, OL_Result_OutOfMemory);
                return;
            }

            OL_Scope_SendEntity(scope, obj);
            OL_Object_Release(obj);
            OL_Scope_SendResult(scope, OL_Result_Ok);
            return;
        }

        OL_Scope_SendResult(scope, OL_Result_NotFound);
        return;
    }

    OL_Scope_SendResult(scope, OL_Result_Failed);
}

static void _Post(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Put(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Patch(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Delete(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri)
{
    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static OL_ProviderFT _ft =
{
    _Load,
    _Unload,
    _Get,
    _Post,
    _Put,
    _Patch,
    _Delete,
};

OL_EXPORT OL_Provider* OL_ProviderEntryPoint()
{
    Provider* self;

    /* Allocate the Provider structure */
    if (!(self = (Provider*)calloc(1, sizeof(Provider))))
        return NULL;

    /* Set the function table */
    self->base.ft = &_ft;

    return &self->base;
}
