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
#ifndef _odata_format_h
#define _odata_format_h

#include "odata.h"

#define DateBufSize (STRN("9999-12-31") + 1)

#define TimeOfDayBufSize (STRN("24:60:60:999999999999") + 1)

#define DateTimeOffsetBufSize \
    (STRN("7295-95-95T95:95:95.073709551615Z") + 1)

#define DurationBufSize \
    (STRN("-P4294967295DT4294967295H4294967295M4294967295.073709551615S") + 1)

#define GuidBufSize \
    (STRN("AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE") + 1)

/* YYYY-MM-DD */
void FormatDate(
    char buf[DateBufSize], 
    const OL_Date* x);

/* HH ":" MM [":" SS ["." FF]] */
/* "12:30:12.99" */
size_t FormatTimeOfDay(
    char buf[TimeOfDayBufSize], 
    const OL_TimeOfDay* x);

/* YYYY "-" MM "-" DD "T" HH ":" MM [":" SS ["." FF]] */
/* "2014-02-03T12:00:00.00" */
size_t FormatDateTimeOffset(
    char buf[DateTimeOffsetBufSize], 
    const OL_DateTimeOffset* x);

size_t FormatDuration(
    char buf[DurationBufSize], 
    const OL_Duration* x);

/* AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE */
void FormatGuid(
    char buf[GuidBufSize], 
    const OL_Guid* guid);

#endif /* _odata_format_h */
