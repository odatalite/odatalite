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
#include <math.h>
#include <limits.h>
#include <base/base64.h>
#include <base/str.h>
#include "getters.h"
#include "types.h"

INLINE void _SetNullFlag(unsigned int* flags)
{
    if (flags)
        *flags |= OL_FLAG_NULL;
}

static int _RawGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    size_t typeSize = ODATATypeSizeOf(type);

    /* Handle null */
    if (rhs->type == JSON_Type_Null)
    {
        _SetNullFlag(flags);
        lhs->type = type;
        memset(&lhs->u, 0, typeSize);
        return 0;
    }

    /* Check type */
    if (rhs->type != type)
        return -1;

    /* Set value */
    lhs->type = type;
    memcpy(&lhs->u, &rhs->u, typeSize);

    return 0;
}

static int _DoubleGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;

    /* Handle null */
    if (rhs->type == JSON_Type_Null)
    {
        _SetNullFlag(flags);
        lhs->type = OL_Type_Double;
        lhs->u.double_ = 0;
        return 0;
    }

    /* Handle "Nan" and "Inf" */
    if (rhs->type == JSON_Type_String)
    {
        lhs->type = OL_Type_Double;

        if (!rhs->u.string)
            return -1;

        if (Strncmp(rhs->u.string, STRLIT("INF")) == 0)
        {
            lhs->u.double_ = INFINITY;
            return 0;
        }
        else if (Strncmp(rhs->u.string, STRLIT("-INF")) == 0)
        {
            lhs->u.double_ = -INFINITY;
            return 0;
        }
        else if (Strncmp(rhs->u.string, STRLIT("NaN")) == 0)
        {
            lhs->u.double_ = NAN;
            return 0;
        }

        return -1;
    }

    /* Check type */
    if (rhs->type != JSON_Type_Real)
        return -1;

    /* Set value */
    lhs->type = OL_Type_Double;
    lhs->u.double_ = rhs->u.real;

    return 0;
}

static int _NullGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;

    /* Check type */
    if (rhs->type != JSON_Type_Null)
        return -1;

    /* Set type (null has no value) */
    _SetNullFlag(flags);
    lhs->type = OL_Type_Null;

    return 0;
}

static int _ByteGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    JSON_Value tmp;

    if (_RawGetter(&tmp, rhs, OL_Type_Int64, flags, alloc) != 0)
        return -1;

    /* Check range */
    if (tmp.u.integer < 0 || tmp.u.integer > UCHAR_MAX)
        return -1;

    /* Set value */
    lhs->type = OL_Type_Byte;
    lhs->u.byte = (OL_Byte)tmp.u.integer;

    return 0;
}

static int _SByteGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    JSON_Value tmp;

    if (_RawGetter(&tmp, rhs, OL_Type_Int64, flags, alloc) != 0)
        return -1;

    /* Check range */
    if (tmp.u.integer < SCHAR_MIN || tmp.u.integer > SCHAR_MAX)
        return -1;

    /* Set value */
    lhs->type = OL_Type_SByte;
    lhs->u.sByte = (OL_SByte)tmp.u.integer;

    return 0;
}

static int _Int16Getter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    JSON_Value tmp;

    if (_RawGetter(&tmp, rhs, OL_Type_Int64, flags, alloc) != 0)
        return -1;

    /* Check range */
    if (tmp.u.integer < SHRT_MIN || tmp.u.integer > SHRT_MAX)
        return -1;

    /* Set value */
    lhs->type = OL_Type_Int16;
    lhs->u.int16 = (OL_Int16)tmp.u.integer;

    return 0;
}

static int _Int32Getter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    JSON_Value tmp;

    if (_RawGetter(&tmp, rhs, OL_Type_Int64, flags, alloc) != 0)
        return -1;

    /* Check range */
    if (tmp.u.integer < INT_MIN || tmp.u.integer > INT_MAX)
        return -1;

    /* Set value */
    lhs->type = OL_Type_Int32;
    lhs->u.int32 = (OL_Int32)tmp.u.integer;

    return 0;
}

static int _SingleGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    JSON_Value tmp;

    if (_DoubleGetter(&tmp, rhs, OL_Type_Double, flags, alloc) != 0)
        return -1;

    lhs->type = OL_Type_Single;
    lhs->u.single = (float)tmp.u.real;

    return 0;
}

static int _DecimalGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    /* ATTN.A: implement this! */
    return -1;
}

static int _BinaryGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    OL_Binary x;

    /* Handle null */
    if (rhs->type == JSON_Type_Null)
    {
        _SetNullFlag(flags);
        lhs->type = OL_Type_Binary;
        lhs->u.binary.size = 0;
        lhs->u.binary.data = NULL;
        return 0;
    }

    /* Check type */
    if (rhs->type != JSON_Type_String || !rhs->u.string)
        return -1;

    /* Convert string to binary type */
    {
        Base64DecState state = BASE64DECSTATE_INITIALIZER;
        size_t n = strlen(rhs->u.string);
        size_t r;
        size_t d;
        char* data;

        /* Allocate enough memory with room for '=' padding */
        if (!(data = AllocGet(alloc, n + 1 + 3)))
            return -1;

        /* Copy the string */
        memcpy(data, rhs->u.string, n + 1);

        /* Round to next multiple of 4 */
        r = ((n + 3) / 4) * 4;

        /* Calculate delta between r and n (number of '=' pad characters) */
        d = r - n;

        /* Pad end of the string with '=' characters up to multiple of 4 */
        if (d)
        {
            memset(data + n, '=', d);
            n += d;
            data[n] = '\0';
        }

        /* Convert from base64 to binary in place */
        if ((n = Base64Dec(&state, data, n, data, n)) == 0)
            return -1;

        /* Terminate in case caller treats it like a zero-terminated string */
        data[n] = '\0';

        /* Allocate memory to hold binary data */
        x.data = data;
        x.size = n;
    }

    /* Set value */
    lhs->type = OL_Type_Binary;
    lhs->u.binary = x;

    return 0;
}

static int _DateGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    OL_Date x;

    /* Handle null */
    if (rhs->type == JSON_Type_Null)
    {
        _SetNullFlag(flags);
        lhs->type = OL_Type_Date;
        memset(&lhs->u.date, 0, sizeof(lhs->u.date));
        return 0;
    }

    /* Check type */
    if (rhs->type != JSON_Type_String || !rhs->u.string)
        return -1;

    /* Convert */
    {
        int n;

        n = sscanf(rhs->u.string, "%04u-%02u-%02u", &x.year, &x.month, &x.day);

        if (n != 3)
            return -1;

    }

    /* Check range */
    {
        if (x.month > 12)
            return -1;

        if (x.day > 31)
            return -1;
    }

    /* Set value */
    lhs->type = OL_Type_Date;
    lhs->u.date = x;

    return 0;
}

static int _TimeOfDayGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    OL_TimeOfDay x;

    /* Handle null */
    if (rhs->type == JSON_Type_Null)
    {
        _SetNullFlag(flags);
        lhs->type = OL_Type_TimeOfDay;
        memset(&lhs->u.timeOfDay, 0, sizeof(lhs->u.timeOfDay));
        return 0;
    }

    /* Check type */
    if (rhs->type != JSON_Type_String || !rhs->u.string)
        return -1;

    /* Convert */
    {
        memset(&x, 0, sizeof(x));

        int n = sscanf(rhs->u.string, "%02u:%02u:%02u.%llu",
            &x.hour, &x.minute, &x.second, &x.fractionalSecond);

        /* second and msec are optional */
        if (n < 2)
            return -1;
    }

    /* Check range */
    {
        if (x.hour > 24)
            return -1;

        if (x.minute > 60)
            return -1;

        if (x.second > 60)
            return -1;
    }

    /* Set value */
    lhs->type = OL_Type_TimeOfDay;
    lhs->u.timeOfDay = x;

    return 0;
}

static int _DateTimeOffsetGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    OL_DateTimeOffset x;

    /* Handle null */
    if (rhs->type == JSON_Type_Null)
    {
        _SetNullFlag(flags);
        lhs->type = OL_Type_DateTimeOffset;
        memset(&lhs->u.dateTimeOffset, 0, sizeof(lhs->u.dateTimeOffset));
        return 0;
    }

    /* Check type */
    if (rhs->type != JSON_Type_String || !rhs->u.string)
        return -1;

    /* Convert */
    {
        int n;

        memset(&x, 0, sizeof(x));

        n = sscanf(rhs->u.string, "%04u-%02u-%02uT%02u:%02u:%02u.%12lluZ",
            &x.year, &x.month, &x.day, &x.hour, &x.minute, &x.second, 
            &x.fractionalSecond);

        /* Note: second and msec are optional */
        if (n < 5)
            return -1;
    }

    /* Check range */
    {
        if (x.month > 12)
            return -1;

        if (x.day > 31)
            return -1;

        if (x.hour > 24)
            return -1;

        if (x.minute > 60)
            return -1;

        if (x.second > 60)
            return -1;
    }

    /* Set value */
    lhs->type = OL_Type_DateTimeOffset;
    lhs->u.dateTimeOffset = x;

    return 0;
}

static int _DurationGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    OL_Duration x;

    /* Handle null */
    if (rhs->type == JSON_Type_Null)
    {
        _SetNullFlag(flags);
        lhs->type = OL_Type_Duration;
        memset(&lhs->u.duration, 0, sizeof(lhs->u.duration));
        return 0;
    }

    /* Check type */
    if (rhs->type != JSON_Type_String || !rhs->u.string)
        return -1;

    /* Convert */
    {
        char sign = '+';
        const char* str = rhs->u.string;
        int n;

        memset(&x, 0, sizeof(x));

        /* Get the optional sign */
        if (str[0] == '-' || str[0] == '+')
        {
            sign = str[0];
            str++;
        }

        n = sscanf(str,  "P%uD" "T" "%uH" "%uM" "%u.%12lluS",
            &x.days, &x.hour, &x.minute, &x.second, &x.fractionalSecond);

        /* Must at least read 1 item */
        if (n < 1)
            return -1;

        x.negative = (sign == '-') ? OL_TRUE : OL_FALSE;
    }

    /* Set value */
    lhs->type = OL_Type_Duration;
    lhs->u.duration = x;

    return 0;
}

static int _GuidGetter(
    JSON_Value* lhs_,
    const JSON_Value* rhs,
    unsigned short type,
    unsigned int* flags,
    Alloc* alloc)
{
    OL_Value* lhs = (OL_Value*)lhs_;
    unsigned int data1;
    unsigned int data2;
    unsigned int data3;
    unsigned int data4;
    unsigned int data5;
    unsigned int data6;

    /* Handle null */
    if (rhs->type == JSON_Type_Null)
    {
        _SetNullFlag(flags);
        lhs->type = OL_Type_Guid;
        memset(&lhs->u.guid, 0, sizeof(lhs->u.guid));
        return 0;
    }

    /* Check type */
    if (rhs->type != JSON_Type_String || !rhs->u.string)
        return -1;

    /* Convert */
    {
        int n = sscanf(rhs->u.string, "%08X-%04X-%04X-%04X-%04X%08X",
            &data1, &data2, &data3, &data4, &data5, &data6);

        if (n != 6)
            return -1;
    }

    /* Set value */
    lhs->type = OL_Type_Guid;
    lhs->u.guid.data1 = data1;
    lhs->u.guid.data2 = data2;
    lhs->u.guid.data3 = data3;
    lhs->u.guid.data4 = data4;
    lhs->u.guid.data5 = data5;
    lhs->u.guid.data6 = data6;

    return 0;
}

ValueGetter __getters[] =
{
    _NullGetter, /* Null */
    _RawGetter, /* Boolean */
    _RawGetter, /* Int64 */
    _DoubleGetter, /* Double */
    _RawGetter, /* String */
    _RawGetter, /* Object */
    _RawGetter, /* Array */
    _ByteGetter, /* Byte */
    _SByteGetter, /* SByte */
    _Int16Getter, /* Int16 */
    _Int32Getter, /* Int32 */
    _SingleGetter, /* Single */
    _DecimalGetter, /* Decimal */
    _BinaryGetter, /* Binary */
    _DateGetter, /* Date */
    _TimeOfDayGetter, /* TimeOfDay */
    _DateTimeOffsetGetter, /* DateTimeOffset */
    _DurationGetter, /* Duration */
    _GuidGetter, /* Guid */
    _RawGetter, /* NavigationLink */
    _RawGetter, /* AssociationLink */
};
