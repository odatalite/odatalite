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
#include "chars.h"
#include <base/chars.h>
#include <base/buf.h>
#include <base/dump.h>
#include <base/str.h>
#include "return.h"
#include "jsonparser.h"

#define JSON_PARSER_MAGIC 0x3748f2de

INLINE OL_Result _Call(
    JSON_Parser* self,
    JSON_Reason reason,
    JSON_Type type,
    const JSON_Union* un)
{
    return self->callback(self, reason, type, un, self->callbackData);
}

static OL_Result _GetString(JSON_Parser* self, char** str)
{
    char* start = self->ptr;
    char* p = start;
    const char* end = self->end;
    int escaped = 0;

    /* Save the start of the string */
    *str = p;

    /* Find the closing quote */
    while (p != end && *p != '"')
    {
        if (*p++ == '\\')
        {
            escaped = 1;

            if (*p == 'u')
            {
                if (end - p < 4)
                    RETURN(OL_Result_EndOfFile);
                p += 4;
            }
            else
            {
                if (p == end)
                    RETURN(OL_Result_EndOfFile);
                p++;
            }
        }
    }

    if (p == end || *p != '"')
        RETURN(OL_Result_EndOfFile);

    /* Update the stream */
    self->ptr += p - start + 1;

    /* Overwrite the '"' character */
    *p = '\0';
    end = p;

    /* ATTN.B: store length (end-p) to str[-1] */

    /* Process escaped characters (if any) */
    if (escaped)
    {
        p = start;

        while (*p)
        {
            /* Handled escaped characters */
            if (*p == '\\')
            {
                p++;

                if (!*p)
                    RETURN(OL_Result_EndOfFile);

                switch (*p)
                {
                    case '"':
                        p[-1] = '"';
                        memmove(p, p + 1, end - p);
                        end--;
                        break;
                    case '\\':
                        p[-1] = '\\';
                        memmove(p, p + 1, end - p);
                        end--;
                        break;
                    case 'b':
                        p[-1] = '\b';
                        memmove(p, p + 1, end - p);
                        end--;
                        break;
                    case 'f':
                        p[-1] = '\f';
                        memmove(p, p + 1, end - p);
                        end--;
                        break;
                    case 'n':
                        p[-1] = '\n';
                        memmove(p, p + 1, end - p);
                        end--;
                        break;
                    case 'r':
                        p[-1] = '\r';
                        memmove(p, p + 1, end - p);
                        end--;
                        break;
                    case 't':
                        p[-1] = '\t';
                        memmove(p, p + 1, end - p);
                        end--;
                        break;
                    case 'u':
                    {
                        unsigned int x;

                        p++;

                        /* Expecting 4 hex digits: XXXX */
                        if (end - p < 4)
                            RETURN(OL_Result_EndOfFile);

                        if (HexStr4ToUint(p, &x) != 0)
                            RETURN(OL_Result_SyntaxError);

                        if (x >= 256)
                        {
                            /* ATTN.B: UTF-8 not supported yet! */
                            RETURN(OL_Result_NotSupported);
                        }

                        /* Overwrite '\' character */
                        p[-2] = x;

                        /* Remove "uXXXX" */
                        memmove(p - 1, p + 4, end - p - 3);

                        p = p - 1;
                        end -= 5;
                        break;
                    }
                    default:
                        RETURN(OL_Result_Failed);
                }
            }
            else
            {
                p++;
            }
        }
    }

#if 0
    Dump(stdout, "GETSTRING", *str, strlen(*str));
#endif

    return OL_Result_Ok;
}

static OL_Result _GetValue(
    JSON_Parser* self);

static OL_Result _GetArray(
    JSON_Parser* self)
{
    OL_Result r;
    JSON_Char c;

    /* array = begin-array [ value *( value-separator value ) ] end-array */
    for (;;)
    {
        /* Skip whitespace */
        while (self->ptr != self->end && isspace(*self->ptr))
            self->ptr++;

        /* Fail if output exhausted */
        if (self->ptr == self->end)
            RETURN(OL_Result_EndOfFile);

        /* Read the next character */
        c = *self->ptr++;

        if (c == ',')
        {
            continue;
        }
        else if (c == ']')
        {
            break;
        }
        else
        {
            self->ptr--;

            if ((r = _GetValue(self)) != OL_Result_Ok)
            {
                RETURN(r);
            }
        }
    }

    return OL_Result_Ok;
}

static OL_Result _GetNumber(
    JSON_Parser* self,
    JSON_Type* type,
    JSON_Union* un)
{
    JSON_Char c;
    int isInteger = 1;
    char* end;
    const char* start = self->ptr;

    /* Skip over any characters that can comprise a number */
    while (self->ptr != self->end && IsNumberChar(*self->ptr))
    {
        c = *self->ptr;
        self->ptr++;

        if (IsDecimalOrExponent(c))
            isInteger = 0;
    }

    if (isInteger)
    {
        *type = JSON_Type_Integer;
        un->integer = strtoll(start, &end, 10);
    }
    else
    {
        *type = JSON_Type_Real;
        un->real = strtod(start, &end);
    }

    if (!end || end != self->ptr)
        RETURN(OL_Result_SyntaxError);

    return OL_Result_Ok;
}

INLINE int _Expect(JSON_Parser* self, const char* str, size_t len)
{
    if (self->end - self->ptr >= len && memcmp(self->ptr, str, len) == 0)
    {
        self->ptr += len;
        return 0;
    }

    return -1;
}

static OL_Result _GetObject(
    JSON_Parser* self);

/* value = false / null / true / object / array / number / string */
static OL_Result _GetValue(
    JSON_Parser* self)
{
    char c;
    OL_Result r;

    /* Skip whitespace */
    while (self->ptr != self->end && isspace(*self->ptr))
        self->ptr++;

    /* Fail if output exhausted */
    if (self->ptr == self->end)
        RETURN(OL_Result_EndOfFile);

    /* Read the next character */
    c = tolower(*self->ptr++);

    switch (c)
    {
        case 'f':
        {
            JSON_Union un;

            if (_Expect(self, STRLIT("alse")) != 0)
                RETURN(OL_Result_SyntaxError);

            un.boolean = 0;

            if ((r = _Call(
                self,
                JSON_Reason_Value,
                JSON_Type_Boolean,
                &un)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            break;
        }
        case 'n':
        {
            if (_Expect(self, STRLIT("ull")) != 0)
                RETURN(OL_Result_SyntaxError);

            if ((r = _Call(
                self,
                JSON_Reason_Value,
                JSON_Type_Null,
                NULL)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            break;
        }
        case 't':
        {
            JSON_Union un;

            if (_Expect(self, STRLIT("rue")) != 0)
                RETURN(OL_Result_SyntaxError);

            un.boolean = 1;

            if ((r = _Call(
                self,
                JSON_Reason_Value,
                JSON_Type_Boolean,
                &un)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            break;
        }
        case '{':
        {
            if ((r = _GetObject(self)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            break;
        }
        case '[':
        {
            if ((r = _Call(
                self,
                JSON_Reason_BeginArray,
                JSON_Type_Null,
                NULL)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            if ((r = _GetArray(self)) != OL_Result_Ok)
                RETURN(OL_Result_SyntaxError);

            if ((r = _Call(
                self,
                JSON_Reason_EndArray,
                JSON_Type_Null,
                NULL)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            break;
        }
        case '"':
        {
            JSON_Union un;
            
            if ((r = _GetString(self, (char**)&un.string)) != OL_Result_Ok)
                RETURN(OL_Result_SyntaxError);

            if ((r = _Call(
                self,
                JSON_Reason_Value,
                JSON_Type_String,
                &un)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            break;
        }
        default:
        {
            JSON_Type type;
            JSON_Union un;

            self->ptr--;

            if ((r = _GetNumber(self, &type, &un)) != OL_Result_Ok)
                RETURN(OL_Result_SyntaxError);

            if ((r = _Call(
                self,
                JSON_Reason_Value,
                type,
                &un)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            break;
        }
    }

    return OL_Result_Ok;
}

static OL_Result _GetObject(
    JSON_Parser* self)
{
    OL_Result r;
    JSON_Char c;

    if ((r = _Call(
        self,
        JSON_Reason_BeginObject,
        JSON_Type_Null,
        NULL)) != OL_Result_Ok)
    {
        RETURN(r);
    }

    /* Expect: member = string name-separator value */
    for (;;)
    {
        /* Skip whitespace */
        while (self->ptr != self->end && isspace(*self->ptr))
            self->ptr++;

        /* Fail if output exhausted */
        if (self->ptr == self->end)
            RETURN(OL_Result_EndOfFile);

        /* Read the next character */
        c = *self->ptr++;

        if (c == '"')
        {
            JSON_Union un;

            /* Get name */
            if ((r = _GetString(self, (char**)&un.string)) != OL_Result_Ok)
                RETURN(r);

            if ((r = _Call(
                self,
                JSON_Reason_Name,
                JSON_Type_String,
                &un)) != OL_Result_Ok)
            {
                RETURN(r);
            }

            /* Expect: name-separator(':') */
            {
                /* Skip whitespace */
                while (self->ptr != self->end && isspace(*self->ptr))
                    self->ptr++;

                /* Fail if output exhausted */
                if (self->ptr == self->end)
                    RETURN(OL_Result_EndOfFile);

                /* Read the next character */
                c = *self->ptr++;

                if (c != ':')
                    RETURN(OL_Result_SyntaxError);
            }

            /* Expect: value */
            if ((r = _GetValue(self)) != OL_Result_Ok)
                RETURN(r);
        }
        else if (c == '}')
        {
            break;
        }
    }

    if ((r = _Call(
        self,
        JSON_Reason_EndObject,
        JSON_Type_Null,
        NULL)) != OL_Result_Ok)
    {
        RETURN(r);
    }


    return OL_Result_Ok;
}

OL_Result JSON_Parser_Init(
    JSON_Parser* self,
    char* data,
    size_t size,
    JSON_Parser_Callback callback,
    void* callbackData)
{
    if (!self || !data || !size || !callback)
        return OL_Result_BadParameter;

    self->magic = JSON_PARSER_MAGIC;
    self->data = data;
    self->ptr = data;
    self->end = data + size;
    self->callback = callback;
    self->callbackData = callbackData;

    return OL_Result_Ok;
}

extern OL_Result JSON_Parser_Parse(
    JSON_Parser* self)
{
    JSON_Char c;

    /* Check parameters */
    if (!self || self->magic != JSON_PARSER_MAGIC)
        return OL_Result_BadParameter;

    /* Expect '{' */
    {
        /* Skip whitespace */
        while (self->ptr != self->end && isspace(*self->ptr))
            self->ptr++;

        /* Fail if output exhausted */
        if (self->ptr == self->end)
            RETURN(OL_Result_EndOfFile);

        /* Read the next character */
        c = *self->ptr++;

        /* Expect object-begin */
        if (c != '{')
            return OL_Result_SyntaxError;
    }

    return _GetObject(self);
}
