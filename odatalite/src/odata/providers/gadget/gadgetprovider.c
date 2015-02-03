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

#define D(X) X

typedef struct _Gadget
{
    OL_Int64 Id;
    const char* Color;
    const char* Model;
    OL_Int32 WeigthInGrams;
    OL_Date ManufacturingDate;
    OL_Int64 SerialNumber;
}
Gadget;

static Gadget _gadgets[] =
{
    {
        1, /* Id */
        "Red", /* Color */
        "M3403", /* Model */
        765, /* WeigthInGrams */
        { 2014, 1, 13 }, /* ManufacturingDate */
        847574657 /* SerialNumber */
    },
    {
        2, /* Id */
        "Cyan", /* Color */
        "M3303", /* Model */
        531, /* WeigthInGrams */
        { 2014, 1, 14 }, /* ManufacturingDate */
        143547848 /* SerialNumber */
    },
    {
        3, /* Id */
        "Blue", /* Color */
        "M2403", /* Model */
        765, /* WeigthInGrams */
        { 2014, 1, 15 }, /* ManufacturingDate */
        847574657 /* SerialNumber */
    },
    {
        4, /* Id */
        "Green", /* Color */
        "M1313", /* Model */
        531, /* WeigthInGrams */
        { 2014, 1, 16 }, /* ManufacturingDate */
        143547848 /* SerialNumber */
    },
    {
        5, /* Id */
        "Amber", /* Color */
        "M2313", /* Model */
        776, /* WeigthInGrams */
        { 2012, 2, 31 }, /* ManufacturingDate */
        949547849 /* SerialNumber */
    },
    {
        6, /* Id */
        "White", /* Color */
        "M9911", /* Model */
        472, /* WeigthInGrams */
        { 2013, 2, 12 }, /* ManufacturingDate */
        141541811 /* SerialNumber */
    },
    {
        7, /* Id */
        "Pink", /* Color */
        "M4911", /* Model */
        474, /* WeigthInGrams */
        { 2014, 2, 1 }, /* ManufacturingDate */
        242241811 /* SerialNumber */
    },
    {
        8, /* Id */
        "Orange", /* Color */
        "M5483", /* Model */
        301, /* WeigthInGrams */
        { 2014, 9, 10 }, /* ManufacturingDate */
        398763154 /* SerialNumber */
    },
    {
        9, /* Id */
        "Black", /* Color */
        "M1413", /* Model */
        201, /* WeigthInGrams */
        { 2014, 10, 2 }, /* ManufacturingDate */
        498513154 /* SerialNumber */
    },
    {
        10, /* Id */
        "Lime", /* Color */
        "M2413", /* Model */
        334, /* WeigthInGrams */
        { 2014, 8, 12 }, /* ManufacturingDate */
        123654898 /* SerialNumber */
    },
    {
        11, /* Id */
        "Red", /* Color */
        "M3403", /* Model */
        765, /* WeigthInGrams */
        { 2014, 1, 13 }, /* ManufacturingDate */
        847574657 /* SerialNumber */
    },
    {
        12, /* Id */
        "Cyan", /* Color */
        "M3303", /* Model */
        531, /* WeigthInGrams */
        { 2014, 1, 14 }, /* ManufacturingDate */
        143547848 /* SerialNumber */
    },
    {
        13, /* Id */
        "Blue", /* Color */
        "M2403", /* Model */
        765, /* WeigthInGrams */
        { 2014, 1, 15 }, /* ManufacturingDate */
        847574657 /* SerialNumber */
    },
    {
        14, /* Id */
        "Green", /* Color */
        "M1313", /* Model */
        531, /* WeigthInGrams */
        { 2014, 1, 16 }, /* ManufacturingDate */
        143547848 /* SerialNumber */
    },
    {
        15, /* Id */
        "Amber", /* Color */
        "M2313", /* Model */
        776, /* WeigthInGrams */
        { 2012, 2, 31 }, /* ManufacturingDate */
        949547849 /* SerialNumber */
    },
    {
        16, /* Id */
        "White", /* Color */
        "M9911", /* Model */
        472, /* WeigthInGrams */
        { 2013, 2, 12 }, /* ManufacturingDate */
        141541811 /* SerialNumber */
    },
    {
        17, /* Id */
        "Pink", /* Color */
        "M4911", /* Model */
        474, /* WeigthInGrams */
        { 2014, 2, 1 }, /* ManufacturingDate */
        242241811 /* SerialNumber */
    },
    {
        18, /* Id */
        "Orange", /* Color */
        "M5483", /* Model */
        301, /* WeigthInGrams */
        { 2014, 9, 10 }, /* ManufacturingDate */
        398763154 /* SerialNumber */
    },
    {
        19, /* Id */
        "Black", /* Color */
        "M1413", /* Model */
        201, /* WeigthInGrams */
        { 2014, 10, 2 }, /* ManufacturingDate */
        498513154 /* SerialNumber */
    },
    {
        20, /* Id */
        "Lime", /* Color */
        "M2413", /* Model */
        334, /* WeigthInGrams */
        { 2014, 8, 12 }, /* ManufacturingDate */
        123654898 /* SerialNumber */
    }
};

static const size_t _ngadgets = OL_ARRAYSIZE(_gadgets);

static OL_Result _SendGadget(
    OL_Scope* scope,
    const Gadget* gadget)
{
    OL_Object* obj;

    if (!(obj = OL_Scope_NewObject(scope)))
        return OL_Result_Failed;

    OL_Object_AddInt64(obj, "Id", gadget->Id);
    OL_Object_AddString(obj, "Color", gadget->Color);
    OL_Object_AddString(obj, "Model", gadget->Model);
    OL_Object_AddInt32(obj, "WeigthInGrams", gadget->WeigthInGrams);
    OL_Object_AddDate(obj, "ManufacturingDate", gadget->ManufacturingDate);
    OL_Object_AddInt64(obj, "SerialNumber", gadget->SerialNumber);

    OL_Scope_SendEntity(scope, obj);
    OL_Object_Release(obj);

    return OL_Result_Ok;
}

typedef struct _Provider 
{
    OL_Provider base;

    /* Number of elements sent so far */
    unsigned long count;

    /* Handle the $top query option */
    unsigned long top;

    /* Handle the $skip query option */
    unsigned long skip;

    /* Whether $count option was present */
    OL_Boolean countOption;
}
Provider;

static void _Gadget_Load(
    OL_Provider* self,
    OL_Scope* scope)
{
}

static void _Gadget_Unload(
    OL_Provider* self,
    OL_Scope* scope)
{
    free(self);
}

#define BATCH_SIZE 10

static void _Gadget_Get(
    OL_Provider* self_,
    OL_Scope* scope,
    const OL_URI* uri)
{
    Provider* self = (Provider*)self_;
    const char* entityType;
    const char* skiptoken = NULL;
    unsigned long nsent = 0;

    D( printf("_Gadget_Get()\n"); )

    /* Initialize top and skip */
    self->skip = 0;
    self->top = UINT_MAX;

    /* Zero elements sent so far */
    self->count = 0;

#if 0
    OL_URI_Print(uri);
#endif

    /* Handle $skiptoken query option */
    if (OL_URI_GetQueryOption(uri, OL_QUERY_OPTION_SKIPTOKEN, &skiptoken, 
        sizeof(skiptoken)) == OL_Result_Ok)
    {
        if (!skiptoken || StrToULong(skiptoken, &self->skip) != 0)
        {
            OL_Scope_SendResultF(scope, OL_Result_Failed, "bad skiptoken");
            return;
        }
    }

    /* Handle $top query option */
    OL_URI_GetQueryOption(uri, OL_QUERY_OPTION_TOP, &self->top, 
        sizeof(self->top));

    /* Handle $skip query option */
    OL_URI_GetQueryOption(uri, OL_QUERY_OPTION_SKIP, &self->skip, 
        sizeof(self->skip));

    if (OL_URI_GetQueryOptionFlags(uri) & OL_QUERY_OPTION_COUNT)
        self->countOption = 1;
    else
        self->countOption = 0;

#if 0
    /* Expecting one entity type in path: service/Gadgets */
    if (OL_URI_Count(uri) != 1)
    {
        OL_Scope_SendResult(scope, OL_Result_Failed);
        return;
    }
#endif

    /* Get the entity type */
    if (!(entityType = OL_URI_GetName(uri, 0)))
    {
        OL_Scope_SendResult(scope, OL_Result_Failed);
        return;
    }

    /* Only supporting Gadgets entity type */
    if (strcmp(entityType, "Gadgets") != 0)
    {
        OL_Scope_SendResultF(scope, OL_Result_NotSupported, "%s", entityType);
        return;
    }

    /* Send all gadgets: service/Gadgets */
    if (OL_URI_KeyCount(uri, 0) == 0)
    {
        size_t i;

        if (self->countOption)
        {
            OL_Object * obj;

            if (!(obj = OL_Scope_NewObject(scope)))
            {
                OL_Scope_SendResult(scope, OL_Result_Failed);
                return;
            }

            OL_Object_AddInt64(obj, "count", _ngadgets);
            OL_Scope_SendEntity(scope, obj);
            OL_Object_Release(obj);
            OL_Scope_SendResult(scope, OL_Result_Ok);
            return;
        }

        OL_Scope_SendBeginEntitySet(scope);

        for (i = 0; i < _ngadgets && nsent < BATCH_SIZE; i++)
        {
            self->count++;

            if (self->count <= self->skip)
                continue;

            if (self->count > self->top)
                break;

            _SendGadget(scope, &_gadgets[i]);
            nsent++;
        }

        /* Send begin-entity-set with (or without) skiptoken */
        if (i < _ngadgets)
        {
            char buf[ULongLongToStrBufSize];
            OL_Scope_SendEndEntitySetWithSkiptoken(scope,
                ULongLongToStr(buf, i, NULL));
        }
        else
        {
            OL_Scope_SendEndEntitySet(scope);
        }

        OL_Scope_SendResult(scope, OL_Result_Ok);
        return;
    }

    /* Send requested gadget: service/Gadgets(1) */
    if (OL_URI_KeyCount(uri, 0) == 1)
    {
        OL_Int64 id;
        size_t i;


        if (OL_URI_GetKeyInt64(uri, 0, "$0", &id) != OL_Result_Ok)
        {
            OL_Scope_SendResult(scope, OL_Result_NotSupported);
            return;
        }

        for (i = 0; i < _ngadgets; i++)
        {
            if (_gadgets[i].Id == id)
            {
                _SendGadget(scope, &_gadgets[i]);
                OL_Scope_SendResult(scope, OL_Result_Ok);
                return;
            }
        }

        OL_Scope_SendResult(scope, OL_Result_NotFound);
        return;
    }

    OL_Scope_SendResult(scope, OL_Result_NotSupported);
}

static void _Gadget_Post(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    D( printf("_Gadget_Post()\n"); )
    OL_Scope_SendEntity(scope, object);
    OL_Scope_SendResult(scope, OL_Result_Ok);
}

static void _Gadget_Put(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    D( printf("_Gadget_Put()\n"); )
    OL_Scope_SendEntity(scope, object);
    OL_Scope_SendResult(scope, OL_Result_Ok);
}

static void _Gadget_Patch(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri,
    const OL_Object* object)
{
    D( printf("_Gadget_Patch()\n"); )

    OL_Scope_SendResult(scope, OL_Result_Ok);
}

static void _Gadget_Delete(
    OL_Provider* self,
    OL_Scope* scope,
    const OL_URI* uri)
{
    D( printf("_Gadget_Delete()\n"); )
    OL_Scope_SendResult(scope, OL_Result_Ok);
}

static OL_ProviderFT _ft =
{
    _Gadget_Load,
    _Gadget_Unload,
    _Gadget_Get,
    _Gadget_Post,
    _Gadget_Put,
    _Gadget_Patch,
    _Gadget_Delete,
};

OL_EXPORT OL_Provider* OL_ProviderEntryPoint()
{
    Provider* self;

    if (!(self = (Provider*)Calloc(1, sizeof(Provider))))
        return NULL;

    self->base.ft = &_ft;

    return &self->base;
}
