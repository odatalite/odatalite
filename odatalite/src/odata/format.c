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
#include <base/format.h>
#include <base/str.h>
#include "format.h"

void FormatDate(char buf[DateBufSize], const OL_Date* x)
{
    UIntToStrZeroPadded(&buf[0], 4, x->year);
    buf[4] = '-';
    UIntToStrZeroPadded(&buf[5], 2, x->month);
    buf[7] = '-';
    UIntToStrZeroPadded(&buf[8], 2, x->day);
    buf[10] = '\0';
}

size_t FormatTimeOfDay(char buf[TimeOfDayBufSize], const OL_TimeOfDay* x)
{
    size_t n = 0;

    /* hour ":" minute */
    n += Format_02u(&buf[n], x->hour);
    buf[n++] = ':';
    n += Format_02u(&buf[n], x->minute);

    /* [":" second ["." fractionalSeconds]] */
    if (x->second || x->fractionalSecond)
    {
        buf[n++] = ':';
        n += Format_02u(&buf[n], x->second);

        if (x->fractionalSecond)
        {
            buf[n++] = '.';
            n += Format_12llu(&buf[n], x->fractionalSecond);
        }
    }

    return n;
}

size_t FormatDateTimeOffset(
    char buf[DateTimeOffsetBufSize], 
    const OL_DateTimeOffset* x)
{
    size_t n = 0;

    /* year "-" month "-" day "T" hour ":" minute */
    {
        n += Format_04u(&buf[n], x->year);
        buf[n++] = '-';
        n += Format_02u(&buf[n], x->month);
        buf[n++] = '-';
        n += Format_02u(&buf[n], x->day);
        buf[n++] = 'T';
        n += Format_02u(&buf[n], x->hour);
        buf[n++] = ':';
        n += Format_02u(&buf[n], x->minute);
    }

    /* [":" second ["." fractionalSeconds]] */
    if (x->second || x->fractionalSecond)
    {
        buf[n++] = ':';
        n += Format_02u(&buf[n], x->second);

        if (x->fractionalSecond)
        {
            buf[n++] = '.';
            n += Format_12llu(&buf[n], x->fractionalSecond);
        }
    }

    buf[n++] = 'Z';
    buf[n] = '\0';

    /* ATTN.A: implement this: ( "Z" / sign hour ":" minute ) */

    return n;
}

size_t FormatDuration(char buf[128], const OL_Duration* x)
{
    size_t n = 0;

    /* [sign] "P" */
    {
        if (x->negative)
            buf[n++] = '-';

        buf[n++] = 'P';
    }

    /* [1*DIGIT "D"] */
    if (x->days)
    {
        n += Format_u(&buf[n], x->days);
        buf[n++] = 'D';
    }

    /* ["T" [1*DIGIT "H"] [1*DIGIT "M"] [1*DIGIT ["." 1*DIGIT] "S"]] */
    if (x->hour || x->minute || x->second || x->fractionalSecond)
        buf[n++] = 'T';

    /* [1*DIGIT "H"] */
    if (x->hour)
    {
        n += Format_u(&buf[n], x->hour);
        buf[n++] = 'H';
    }

    /* [1*DIGIT "M"] */
    if (x->minute)
    {
        n += Format_u(&buf[n], x->minute);
        buf[n++] = 'M';
    }

    /* [1*DIGIT ["." 1*DIGIT] "S"] */
    if (x->second || x->fractionalSecond)
    {
        if (x->fractionalSecond == 0)
        {
            n += Format_u(&buf[n], x->second);
            buf[n++] = 'S';
        }
        else
        {
            n += Format_u(&buf[n], x->second);
            buf[n++] = '.';
            n += Format_12llu(&buf[n], x->fractionalSecond);
            buf[n++] = 'S';
        }
    }

    buf[n] = '\0';

    return n;
}

void FormatGuid(char buf[GuidBufSize], const OL_Guid* x)
{
    /* AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE */
    /* This version is 10 times faster than sprintf */
    UIntToHexStr8(&buf[0], x->data1);
    buf[8] = '-';
    UShortToHexStr4(&buf[9], x->data2);
    buf[13] = '-';
    UShortToHexStr4(&buf[14], x->data3);
    buf[18] = '-';
    UShortToHexStr4(&buf[19], x->data4);
    buf[23] = '-';
    UShortToHexStr4(&buf[24], x->data5);
    UIntToHexStr8(&buf[28], x->data6);
    buf[36] = '\0';
}
