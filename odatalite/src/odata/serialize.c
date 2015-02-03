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
#define _GNU_SOURCE
#include <common.h>
#include <base/buf.h>
#include "json.h"
#include "pair.h"
#include "jsonobject.h"
#include "chars.h"
#include "jsonarray.h"
#include <math.h>
#include <base/str.h>
#include <base/dump.h>
#include <base/iprintf.h>
#include "getters.h"
#include "setters.h"
#include "destructors.h"
#include "serialize.h"
#include "outstream.h"
#include "format.h"
#include "odatamacros.h"

static void _SerializeReal(Buf* out, double x)
{
    char buf[32];
    int n = sprintf(buf, "%E", x);
    BufCat(out, buf, (size_t)n);
}

#define SMALL

static void _SerializeEscChar(Buf* out, char x)
{
    char buf[6];
    size_t n = 2;

    buf[0] = '\\';

    switch (x)
    {
        case '"':
            buf[1] = '"';
            break;
        case '\\':
            buf[1] = '\\';
            break;
        case '\b':
            buf[1] = 'b';
            break;
        case '\f':
            buf[1] = 'f';
            break;
        case '\n':
            buf[1] = 'n';
            break;
        case '\r':
            buf[1] = 'r';
            break;
        case '\t':
            buf[1] = 't';
            break;
        default:
        {
            /* \uXXXX */
            buf[1] = 'u';
            buf[2] = '0';
            buf[3] = '0';
            buf[4] = __hexNibbleToChar[(x >>  4) & 0x0000000F];
            buf[5] = __hexNibbleToChar[(x >>  0) & 0x0000000F];
            n = 6;
            break;
        }
    }

    BufCat(out, buf, n);
}

ALWAYS_INLINE void _SerializeNamePlusColonSpace(
    Buf* out, 
    const char* name,
    size_t nameLen)
{
    size_t size = out->size + nameLen + 4;

    if (BufReserve(out, size) == 0)
    {
        char* p = &out->data[out->size];
        p[0] = '"';
        memcpy(&p[1], name, nameLen);
        p[nameLen+1] = '"';
        p[nameLen+2] = ':';
        p[nameLen+3] = ' ';
        out->size = size;
    }
}

void _SerializeEscapedChars(Buf* out, const char* str)
{
    const char* start = str;

    for (;;)
    {
        const char* p = start;

        /* Skip over non-escape characters (will stop on zero-terminator) */
        while (!IsEsc(*p))
            p++;

        /* Serialize accumulated non-escape characters */
        if (p != start)
            BufCat(out, start, p - start);

        if (*p == '\0')
            break;

        /* Serialize the escape character */
        _SerializeEscChar(out, *p);
        start = p + 1;
    }
}

ALWAYS_INLINE void _SerializeString(Buf* out, const char* str)
{
    const char* p = str;

    while (!IsEsc(p[0]) && !IsEsc(p[1]) && !IsEsc(p[2]) && !IsEsc(p[3]))
        p += 4;

    while (!IsEsc(*p))
        p++;

    if (*p)
    {
        BufCatCh(out, '"');
        BufCat(out, str, p - str);
        _SerializeEscapedChars(out, p);
        BufCatCh(out, '"');
    }
    else
    {
        BufCatQuotedString(out, str, p - str);
    }
}

ALWAYS_INLINE void _Indent(Buf* out, size_t depth)
{
    BufSet(out, ' ', depth * 2);
}

OL_Result __SerializeArray(
    Buf* out,
    const JSON_Value* v,
    size_t depth,
    OL_MetadataType metadataType);

OL_Result SerializeElement(
    Buf* out,
    const JSON_Value* v,
    size_t depth,
    OL_MetadataType metadataType)
{
    switch (v->type)
    {
        case JSON_Type_Null:
        {
            BufCat(out, STRLIT("null"));
            break;
        }
        case JSON_Type_Boolean:
        {
            if (v->u.boolean)
                BufCat(out, STRLIT("true"));
            else
                BufCat(out, STRLIT("false"));
            break;
        }
        case JSON_Type_Integer:
        {
            char buf[22];
            size_t size;
            const char* s = SLongLongToStr(buf, v->u.integer, &size);
            BufCat(out, s, size);
            break;
        }
        case JSON_Type_Real:
        {
            _SerializeReal(out, v->u.real);
            break;
        }
        case JSON_Type_String:
        {
            _SerializeString(out, v->u.string);
            break;
        }
        case JSON_Type_Object:
        {
            SerializeObject((JSONObject*)v->u.object, NULL, out, depth, 0,
                metadataType, NULL);
            break;
        }
        case JSON_Type_Array:
        {
            __SerializeArray(out, v, depth, metadataType);
        }
        default:
            break;
    }

    return OL_Result_Ok;
}

OL_Result __SerializeArray(
    Buf* out,
    const JSON_Value* v,
    size_t depth,
    OL_MetadataType metadataType)
{
    size_t i = 0;
    const JSONArray* arr = (JSONArray*)v->u.array;

    BufCatCh2(out, '[', '\n');
    depth++;

    for (i = 0; i < arr->count; i++)
    {
        const JSON_Value* value = &arr->elements[i].value;

        _Indent(out, depth);
        SerializeElement(out, value, depth, metadataType);

        if (i + 1 != arr->count)
            BufCatCh2(out, ',', '\n');
        else
            BufCatCh(out, '\n');
    }

    depth--;
    _Indent(out, depth);
    BufCatCh(out, ']');

    return OL_Result_Ok;
}


ALWAYS_INLINE int NeedOdataTypeAnnotation(unsigned short type)
{
    return type >= OL_Type_Array && type <= OL_Type_Guid;
}

static void _SerializeArrayOdataType(
    Buf* out, 
    const Pair* pair,
    size_t depth)
{
    const char* typeName;
    JSONArray* array = (JSONArray*)pair->value.u.array;

    if (!NeedOdataTypeAnnotation(array->type))
        return;

    /* Get array type */
    if (!(typeName = ODATATypeNameOf(array->type)))
        return;

    /* Put comma and newline after corresponding property */
    BufCatCh2(out, ',', '\n');
    _Indent(out, depth);

    {
        static const char string[] = "@odata.type\": \"Collection(Edm.";
        static size_t const nstring = sizeof(string)-1;
        size_t size;

        /* "Holidays@odata.type" : "Collection(Edm.Date)" */
        size = 1 + pair->nameLen + nstring + 11 + typeName[-1] + 2;

        if (BufReserve(out, size) == 0)
        {
            char* start = out->data + out->size;
            char* p = start;

            *p++ = '"';

            memcpy(p, pair->name, pair->nameLen);
            p += pair->nameLen;

            memcpy(p, string, nstring);
            p += nstring;

            memcpy(p, typeName, typeName[-1]);
            p += typeName[-1];

            *p++ = ')';
            *p++ = '"';

            out->size += p - start;
        }
    }
}

static void _SerializePrimitiveOdataType(
    Buf* out, 
    const Pair* pair,
    size_t depth)
{
    static const char string[] = "@odata.type\": \"Edm.";
    static size_t const nstring = sizeof(string)-1;
    const char* typeName;
    size_t size;

    if (!(typeName = ODATATypeNameOf(pair->type)))
        return;

    /* Put comma and newline after corresponding property */
    BufCatCh2(out, ',', '\n');
    _Indent(out, depth);

    /* "Birthday@odata.type" : "Edm.Date" */
    size = 1 + pair->nameLen + nstring + typeName[-1] + 1;

    if (BufReserve(out, size) == 0)
    {
        char* start = out->data + out->size;
        char* p = start;

        *p++ = '"';

        memcpy(p, pair->name, pair->nameLen);
        p += pair->nameLen;

        memcpy(p, string, nstring);
        p += nstring;

        memcpy(p, typeName, typeName[-1]);
        p += typeName[-1];

        *p++ = '"';

        out->size += p - start;
    }
}

#if 0
void _SerializeOdataType(
    Buf* out, 
    const Pair* pair,
    OL_Type type,
    int isArray,
    size_t depth)
{
    const char* typeName;

    if (!NeedOdataTypeAnnotation(type))
        return;

    /* Get type name */
    if (!(typeName = ODATATypeNameOf(type)))
        return;

    /* Put comma and newline after corresponding property */
    BufCatCh2(out, ',', '\n');
    _Indent(out, depth);

    /* "Holidays@odata.type" :  */
    BufCatCh(out, '"');
    BufCat(out, pair->name, pair->nameLen);
    BufCat(out, STRLIT("@odata.type\": \""));

    if (isArray)
        BufCat(out, STRLIT("Collection("));

    BufCat(out, STRLIT("Edm."));
    BufCat(out, typeName, typeName[-1]);

    if (isArray)
        BufCat(out, STRLIT(")"));

    BufCatCh(out, '"');
}
#endif

OL_Result SerializeRawPrimitiveValue(
    Buf* out,
    const OL_Value* value)
{
    switch (value->type)
    {
        case OL_Type_Null:
        {
            BufCat(out, STRLIT("null"));
            return OL_Result_Ok;
        }
        case OL_Type_Boolean:
        case OL_Type_Int64:
        case OL_Type_Double:
        case OL_Type_String:
        {
            return SerializeElement(out, (const JSON_Value*)value, 
                0, OL_MetadataType_None);
        }
        case OL_Type_Object:
        case OL_Type_Array:
        {
            /* Only primitive types supported for this operation */
            return OL_Result_Failed;
        }
        case OL_Type_Byte:
        case OL_Type_SByte:
        case OL_Type_Int16:
        case OL_Type_Int32:
        case OL_Type_Single:
        case OL_Type_Decimal:
        case OL_Type_Binary:
        case OL_Type_Date:
        case OL_Type_TimeOfDay:
        case OL_Type_DateTimeOffset:
        case OL_Type_Duration:
        case OL_Type_Guid:
        case OL_Type_NavigationLink:
        case OL_Type_AssociationLink:
        {
            ValueSetter setter;
            ValueDestructor destructor;
            JSON_Value jvalue;
            unsigned int flags = JSON_FLAG_STATIC_VALUE;

            if (!(setter = GetSetter(value->type)))
                return OL_Result_Failed;

            if (setter(&jvalue, (JSON_Value*)value, flags, NULL) != 0)
                return OL_Result_Failed;

            if (SerializeElement(out, &jvalue, 0, OL_MetadataType_None) !=
                OL_Result_Ok)
            {
                return OL_Result_Failed;
            }

            if (!(destructor = GetDestructor(jvalue.type)))
                return OL_Result_Failed;

            destructor(&jvalue, 0, NULL);
            return OL_Result_Ok;
        }
    }

    /* Unreachable */
    return OL_Result_Failed;
}

static OL_Result _SerializePair(
    Buf* out,
    const Pair* pair,
    size_t depth,
    OL_MetadataType metadataType)
{
    const JSON_Value* v = &pair->value;

    _Indent(out, depth);

    _SerializeNamePlusColonSpace(out, pair->name, pair->nameLen);

    if (pair->value.type == JSON_Type_Null)
    {
        BufCat(out, STRLIT("null"));
        return OL_Result_Ok;
    }

    if (pair->value.type == JSON_Type_Array)
    {
        __SerializeArray(out, v, depth, metadataType);

        if (metadataType == OL_MetadataType_Full)
        {
            _SerializeArrayOdataType(out, pair, depth);
        }
    }
    else
    {
        SerializeElement(out, v, depth, metadataType);

        if (metadataType == OL_MetadataType_Full &&
            NeedOdataTypeAnnotation(pair->type))
        {
            _SerializePrimitiveOdataType(out, pair, depth);
        }
    }

    return OL_Result_Ok;
}

/* Serialize the "@odata.context property */
static void _SerializeContextURI(
    Buf* out,
    const char* contextURI,
    size_t depth,
    size_t numProperties)
{
    _Indent(out, depth);

    BufCat(out, STRLIT("\"@odata.context\": \""));
    BufCatStr(out, contextURI);

    if (numProperties)
        BufCat(out, STRLIT("\",\n"));
    else
        BufCatCh2(out, '"', '\n');
}

OL_Result SerializeObject(
    const JSONObject* self,
    const char* contextURI,
    Buf* out,
    size_t depth,
    int indentOpeningBrace,
    OL_MetadataType metadataType,
    const char* propertyName)
{
    size_t i;

    if (indentOpeningBrace)
        _Indent(out, depth);

    BufCatCh2(out, '{', '\n');

    depth++;

    /* Write the "@odata.context property */
    if (metadataType != OL_MetadataType_None && contextURI)
        _SerializeContextURI(out, contextURI, depth, self->count);

    for (i = 0; i < self->count; i++)
    {
        if (propertyName && strcmp(self->pairs[i].name, propertyName) != 0)
        {
            continue;
        }

        if (_SerializePair(out, &self->pairs[i], depth, 
            metadataType) != OL_Result_Ok)
        {
            return OL_Result_Failed;
        }

        BufCatCh2(out, ',', '\n');
    }

    /* Remove final ',' character (faster than checking in the loop) */
    if (self->count)
    {
        /* Overwrite ',' with '\n' */
        out->size--;
        out->data[out->size-1] = '\n';
    }

    depth--;

    _Indent(out, depth);

    BufCatCh(out, '}');

    return out->err ? OL_Result_Failed : OL_Result_Ok;
}

OL_Result Object_Serialize(
    const JSON_Object* self_,
    JSON_OutStream* outStream,
    size_t depth)
{
    JSONObject* self = (JSONObject*)self_;
    Buf buf = BUF_INITIALIZER;
    Buf* out;
    OL_Result r;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC || !outStream)
        return OL_Result_BadParameter;

    /* Use internal buffer if an OutStream */
    if (outStream->ft == &__OutStreamFT)
        out = ((OutStream*)outStream)->out;
    else
        BufReserve(out = &buf, 4096);

    /* Serialize the object */
    if ((r = SerializeObject(self, NULL, out, depth, 1, 
        OL_MetadataType_Minimal, NULL)) != OL_Result_Ok)
        goto done;

    /* If not an OutSteram, then append data to out-stream */
    if (outStream->ft == &__OutStreamFT)
        r = OL_Result_Ok;
    else
        r = outStream->ft->Put(outStream, out->data, out->size);

done:

    if (outStream->ft != &__OutStreamFT)
        BufDestroy(&buf);

    return r;
}
