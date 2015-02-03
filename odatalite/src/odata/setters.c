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
#include <limits.h>
#include <base/str.h>
#include <base/base64.h>
#include "setters.h"
#include "types.h"
#include "format.h"
#include "uri.h"
#include "uriparser.h"
#include "alloc.h"

static int _NullSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs,
    unsigned int flags,
    Alloc* alloc)
{
    lhs->type = OL_Type_Null;
    return 0;
}

static int _BooleanSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = JSON_Type_Null;
        return 0;
    }

    lhs->type = OL_Type_Boolean;
    lhs->u.boolean = rhs->u.boolean;
    return 0;
}

static int _Int64Setter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = JSON_Type_Null;
        return 0;
    }

    lhs->type = OL_Type_Int64;
    lhs->u.integer = rhs->u.int64;
    return 0;
}

static int _DoubleSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;
    const char* str = NULL;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    if (rhs->u.double_ == INFINITY)
        str = "INF";
    else if (rhs->u.double_ == -INFINITY)
        str = "-INF";
    else if (rhs->u.double_ == NAN)
        str = "NaN";
    else
    {
        lhs->type = JSON_Type_Real;
        lhs->u.real = rhs->u.double_;
        return 0;
    }

    if (!(lhs->u.string = StrdupAF(str, alloc, flags)))
        return -1;

    lhs->type = OL_Type_String;
    return 0;
}

static int _StringSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs,
    unsigned int flags,
    Alloc* alloc)
{
    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    lhs->type = OL_Type_String;

    if (!(lhs->u.string = StrdupAF(rhs->u.string, alloc, flags)))
        return -1;

    return 0;
}

static int _ObjectSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs,
    unsigned int flags,
    Alloc* alloc)
{
    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    if (JSON_Object_AddRef(rhs->u.object) != OL_Result_Ok)
        return -1;

    lhs->type = JSON_Type_Object;
    lhs->u.object = rhs->u.object;
    return 0;
}

static int _ArraySetter(
    JSON_Value* lhs,
    const JSON_Value* rhs,
    unsigned int flags,
    Alloc* alloc)
{
    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    if (JSON_Array_AddRef(rhs->u.array) != OL_Result_Ok)
        return -1;

    lhs->type = JSON_Type_Array;
    lhs->u.array = rhs->u.array;
    return 0;
}

static int _ByteSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    lhs->type = JSON_Type_Integer;
    lhs->u.integer = rhs->u.byte;
    return 0;
}

static int _SByteSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    lhs->type = JSON_Type_Integer;
    lhs->u.integer = rhs->u.sByte;
    return 0;
}

static int _Int16Setter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    lhs->type = JSON_Type_Integer;
    lhs->u.integer = rhs->u.int16;
    return 0;
}

static int _Int32Setter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    lhs->type = JSON_Type_Integer;
    lhs->u.integer = rhs->u.int32;
    return 0;
}

static int _SingleSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    JSON_Value rhs;
    rhs.type = OL_Type_Double;
    rhs.u.real = ((OL_Value*)rhs_)->u.single;
    return _DoubleSetter(lhs, &rhs, flags, alloc);
}

static int _DecimalSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    /* ATTN.A: implement this */
    return -1;
}

static int _BinarySetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    OL_Value* rhs = (OL_Value*)rhs_;
    OL_Binary x;
    size_t r;
    size_t n;
    Base64EncState state = BASE64ENCSTATE_INITIALIZER;
    char buf[128];
    char* str;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    x = rhs->u.binary;

    if (x.size && !x.data)
        return -1;

    /* Round size to next multiple of 3 */
    r = ((x.size + 2) / 3) * 3;

    /* Calculate allocation size (4 bytes output for every 3 bytes input) */
    n = (r / 3) * 4;

    /* Allocate the string (leave room for zero terminator) */
    if (!(str = MallocA(n+1, alloc)))
        return -1;

    /* Zero terminate the string */
    *str = '\0';

    /* Encode the string */
    if (x.size)
    {
        size_t m = 0;
        int rr;

        while ((rr = Base64Enc(&state, x.data, x.size, buf, sizeof(buf))) > 0)
        {
            buf[rr] = '\0';
            strcat(str + m, buf);
            m += rr;
        }

        /* Remove '=' padding */
        {
            char* end = str + m;

            while (end != str && end[-1] == '=')
                *--end = '\0';
        }
    }

    lhs->type = JSON_Type_String;
    lhs->u.string = str;
    return 0;
}

static int _DateSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;
    char* data;
    OL_Date x;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    x = rhs->u.date;

    if (x.year > 9999 || x.month > 12 || x.day > 31)
        return -1;

    if (!(data = MallocA(DateBufSize, alloc)))
        return -1;

    FormatDate(data, &x);
    lhs->type = JSON_Type_String;
    lhs->u.string = data;

    return 0;
}

static int _TimeOfDaySetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;
    char* data;
    OL_TimeOfDay x;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    x = rhs->u.timeOfDay;

    if (!(data = MallocA(TimeOfDayBufSize, alloc)))
        return -1;

    FormatTimeOfDay(data, &x);
    lhs->type = JSON_Type_String;
    lhs->u.string = data;

    return 0;
}

static int _DateTimeOffsetSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;
    char* data;
    OL_DateTimeOffset x;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    x = rhs->u.dateTimeOffset;

    if (!(data = MallocA(DateTimeOffsetBufSize, alloc)))
        return -1;

    FormatDateTimeOffset(data, &x);
    lhs->type = JSON_Type_String;
    lhs->u.string = data;

    return 0;
}

static int _DurationSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;
    char* data;
    OL_Duration x;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    x = rhs->u.duration;

    /* ATTN.C: figure out true size */
    if (!(data = MallocA(DurationBufSize, alloc)))
        return -1;

    FormatDuration(data, &x);
    lhs->type = JSON_Type_String;
    lhs->u.string = data;

    return 0;
}

static int _GuidSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs_,
    unsigned int flags,
    Alloc* alloc)
{
    const OL_Value* rhs = (OL_Value*)rhs_;
    char* data;
    OL_Guid x;

    if (flags & OL_FLAG_NULL)
    {
        lhs->type = OL_Type_Null;
        return 0;
    }

    x = rhs->u.guid;

    if (!(data = MallocA(GuidBufSize, alloc)))
        return -1;

    FormatGuid(data, &x);
    lhs->type = JSON_Type_String;
    lhs->u.string = data;

    return 0;
}

static int _LinkSetter(
    JSON_Value* lhs,
    const JSON_Value* rhs,
    unsigned int flags,
    Alloc* alloc)
{
    URIWithAllocBuf uri;

    if (flags & OL_FLAG_NULL)
        return -1;

    /* Validate the link */
    {
        char buf[128];
        char* str;
        char err[64];
        OL_Result r;

        if (!(str = StrdupBuf(buf, sizeof(buf), rhs->u.string)))
            return -1;

        __OL_URI_Construct(&uri);
        r = URIParse((URI*)&uri, str, err, sizeof(err));
        __OL_URI_Destruct(&uri);

        if (str != buf)
            Free(str);

        if (r != OL_Result_Ok)
            return -1;
    }

    return _StringSetter(lhs, rhs, flags, alloc);
}

ValueSetter __setters[] =
{
    _NullSetter, /* Null */
    _BooleanSetter, /* Boolean */
    _Int64Setter, /* Int64 */
    _DoubleSetter, /* Double */
    _StringSetter, /* String */
    _ObjectSetter, /* Object */
    _ArraySetter, /* Array */
    _ByteSetter, /* Byte */
    _SByteSetter, /* SByte */
    _Int16Setter, /* Int16 */
    _Int32Setter, /* Int32 */
    _SingleSetter, /* Single */
    _DecimalSetter, /* Decimal */
    _BinarySetter, /* Binary */
    _DateSetter, /* Date */
    _TimeOfDaySetter, /* TimeOfDay */
    _DateTimeOffsetSetter, /* DateTimeOffset */
    _DurationSetter, /* Duration */
    _GuidSetter, /* Guid */
    _LinkSetter, /* NavigationLink */
    _LinkSetter, /* AssociationLink */
};
