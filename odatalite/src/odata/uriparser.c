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
#include "uriparser.h"
#include <stdlib.h>
#include <base/format.h>
#include <base/str.h>
#include <base/chars.h>
#include <base/parse.h>
#include <base/iprintf.h>
#include <base/array.h>
#include "uri.h"
#include "chars.h"
#include "serialize.h"
#include "setters.h"
#include "types.h"
#include "return.h"

/*
**==============================================================================
**
** Examples:
**     service/Items(OrderID=1,ItemNo=2)
**     https://host/service/Orders(1)/Items(OrderID=1,ItemNo=2)
**     service/Orders(1)/Items(OrderID=1,ItemNo=2)
**     service/Categories(1)/Products/$ref
**     service/Products(0)/Category/$ref
**     service/Customers/Model.VipCustomer
**     service/Customers(1)/Products
**     http://host/service/People('O''Neil')
**     http://host/service/People(%27O%27%27Neil%27) 
**     http://host/service/People%28%27O%27%27Neil%27%29
**     http://host/service/Categories('Smartphone%2FTablet')
**     http://host/service/$metadata
**     http://host/service/$batch
**     http://host/service/ProductsByCategoryId(categoryId=2)
**     http://host/service/Products/Model.MostExpensive()
**     http://host/service/Products/$count
**     http://host/service/Customers/Model.VipCustomer
**     http://host/service/Pictures('Sunset4321299432')/$value
**
**==============================================================================
*/

int URIExpandEscapes(char* str)
{
    /* OPT: 658,549,483,481,471,470,465 */
    char* p = str;
    char* dest;

    /* Skip over initial sequence of non-percent characters */
    {
        while (IsNotPercentOrZero(*p))
            p++;

        dest = p;
    }

    /* Expand escape sequencees */
    while (*p)
    {
        /* (*p == '%' || *p == '\0') */
        {
            if (!p[1] || HexStr2ToChar(&p[1], dest) != 0)
                RETURN(-1);

            p += 3;
            dest++;
        }

        /* Copy over a sequence of non-percent characters */
        {
            char* start = p;

            while (IsNotPercentOrZero(*p))
                p++;

            if (p != start)
            {
                memmove(dest, start, p - start);
                dest += p - start;
            }
        }
    }

    *dest = '\0';
    return 0;
}

/*
**==============================================================================
**
** Example: 
**     https://host/odata/Orders(1)/Items(OrderID=1,ItemNo=2)
**
** 
** BNF:
**    keyPredicate     = simpleKey / compoundKey
**    simpleKey        = OPEN keyPropertyValue CLOSE
**    compoundKey      = OPEN keyValuePair *( COMMA keyValuePair ) CLOSE
**    keyValuePair     = 
**        ( primitiveKeyProperty / keyPropertyAlias ) EQ keyPropertyValue
**    keyPropertyValue = primitiveLiteral
**    keyPropertyAlias = serviceIdentifier
**
**==============================================================================
*/

/* Examples: 'Hello', 12345, true, false */
static char* _ParseLiteral(URIKey* key, char* p)
{
    key->flags = OL_FLAG_STATIC_NAME|OL_FLAG_STATIC_VALUE;
    key->name = NULL;

    if (*p == '\'')
    {
        /* string */
        /* ATTN.B: handle escaped semiquote (two semiquotes) */
        const char* start = ++p;

        while (*p && *p != '\'')
            p++;

        if (*p != '\'')
            RETURN(NULL);

        *p++ = '\0';
        key->value = OL_StringValue(start);
    }
    else if (*p == '-' || isdigit(*p))
    {
        /* number */
        /* ATTN.B: support decimal notation */
        signed long long x;
        char* end;

        x = strtoll(p, &end, 10);
        p = end;
        key->value = OL_Int64Value(x);
    }
    else if (Strncmp(p, STRLIT("true")) == 0 && !IsToken(p[4]))
    {
        /* true */
        p += STRN("true");
        key->value = OL_BooleanValue(OL_TRUE);
    }
    else if (Strncmp(p, STRLIT("false")) == 0 && !IsToken(p[5]))
    {
        /* false */
        p += STRN("false");
        key->value = OL_BooleanValue(OL_FALSE);
    }

    return p;
}

static char* _ParseQueryOptionValueULong(
    char* p,
    size_t len,
    unsigned long* value,
    char* err,
    size_t errSize)
{
    char* end;

    *value = strtoul(p + len, &end, 10);

    if (end == p)
    {
        Snprintf(err, errSize, "invalid value for %.*s", (int)len, p);
        return NULL;
    }

    return end;
}

static OL_Result _ParseQueryOption(
    URI* uri, 
    char** pInOut,
    char* err,
    size_t errSize)
{
    char* p = *pInOut;

    if (Strncmp(p, STRLIT("$top=")) == 0)
    {
        uri->queryOptions |= OL_QUERY_OPTION_TOP;

        if (!(p = _ParseQueryOptionValueULong(
            p,
            STRN("$top="),
            &uri->queryOptionTop,
            err, 
            errSize)))
        {
            return OL_Result_SyntaxError;
        }
    }
    else if (Strncmp(p, STRLIT("$skip=")) == 0)
    {
        uri->queryOptions |= OL_QUERY_OPTION_SKIP;

        if (!(p = _ParseQueryOptionValueULong(
            p,
            STRN("$skip="),
            &uri->queryOptionSkip,
            err, 
            errSize)))
        {
            return OL_Result_SyntaxError;
        }
    }
    else if (Strncmp(p, STRLIT("$skiptoken=")) == 0)
    {
        p += STRN("$skiptoken=");
        uri->queryOptions |= OL_QUERY_OPTION_SKIPTOKEN;
        uri->queryOptionSkiptoken = p;

        /* Skiptoken always last in URI */
        while (*p)
            p++;
    }
    else
    {
        Snprintf(err, errSize, "unsupported query option: %s", p);
        return OL_Result_NotSupported;
    }

    *pInOut = p;
    return OL_Result_Ok;
}

static OL_Result _ParseKeyPredicate(
    URISegment* segment, 
    Alloc* alloc,
    char** pInOut,
    int expectClosingParen)
{
    char* p = *pInOut;
    size_t index = 0;

    /* For each key */
    for (;;)
    {
        URIKey* key;
        char* start;

        /* Skip whitespace */
        while (isspace(*p))
            p++;

        /* End of key predicate? */
        if (!expectClosingParen && (*p == '\0' || *p == '/'))
            return OL_Result_Ok;

        /* Premature end of input */
        if (!*p)
            RETURN(OL_Result_SyntaxError);

        /* If empty parameter list */
        if (*p == ')')
        {
            p++;
            *pInOut = p;
            return OL_Result_Ok;
        }

        /* Check for overflow */
        if (segment->keysSize == segment->keysCapacity)
        {
            if (ArrayReserve(
                (Array*)segment, 
                segment->keysSize + 1,
                sizeof(URIKey),
                URI_PAIR_CAPACITY,
                alloc) != 0) {
                RETURN(OL_Result_Failed);
            }
        }

        /* Initialize the key */
        key = &segment->keys[segment->keysSize++];

        /* Don't free any memory later since it belongs to the buffer */
        key->flags = OL_FLAG_STATIC_NAME|OL_FLAG_STATIC_VALUE;

        /* Parse literal */
        {
            start = p;

            if (!(p = _ParseLiteral(key, p)))
                RETURN(OL_Result_Failed);
        }

        /* Attempt to recognize an identifier=value */
        if (p == start)
        {
            char* startIdent;
            char* endIdent;

            /* Parse identifier */
            {
                startIdent = p;

                if ((p = (char*)ParseIdent(p)) == startIdent)
                    RETURN(OL_Result_Failed);

                endIdent = p;
            }

            /* Skip spaces */
            while (isspace(*p))
                p++;

            /* Expect '=' */
            if (*p++ != '=')
                RETURN(OL_Result_Failed);

            /* Skip spaces */
            while (isspace(*p))
                p++;

            if (!*p)
                RETURN(OL_Result_Failed);

            /* Parse literal */
            {
                char* start = p;
                
                if (!(p = _ParseLiteral(key, p)))
                    RETURN(OL_Result_Failed);

                /* If it was not a literal */
                if (p == start)
                    RETURN(OL_Result_Failed);
            }

            key->name = startIdent;
            *endIdent = '\0';
        }
        else
        {
            /* Set name to '$0' through '$N' */
            static const char* _names = "$0\0$1\0$2\0$3\0$4\0$5\0$6\0$7\0$8";
            key->name = (char*)&_names[index*3];
        }

        /* Search for either comma or closing paren */
        {
            while (isspace(*p))
                p++;

            if (!expectClosingParen && (*p == '\0' || *p == '/'))
                break;

            if (*p == ')')
            {
                p++;
                break;
            }

            if (*p != ',')
                RETURN(OL_Result_Failed);

            p++;
        }

        index++;
    }

    *pInOut = p;

    return OL_Result_Ok;
}

/*
**==============================================================================
**
** http://host:port/odata/Categories(1)/Products?$top=2&$orderby=Name
** \____ ServiceRoot ____/\___ ResourcePath ___/\___ QueryOption ___/
**
**==============================================================================
*/

OL_Result URIParse(
    URI* self,
    char* uri,
    char* err,
    size_t errSize)
{
    char* p = uri;
    int foundHttp = 0;
    int foundService = 0;
    char* start;

    DEBUG_ASSERT(self->magic == URI_MAGIC);

    /* Clear if necessary */
    if (self->segments.size)
        OL_URI_Clear(&self->base);

    /* Expand percent encodings */
    if (URIExpandEscapes(p) != 0)
    {
        Snprintf(err, errSize, "invalid percent encoding");
        RETURN(OL_Result_SyntaxError);
    }

    /* Skip over "http://" or "https://" */
    if (Strncmp(p, STRLIT("http://")) == 0)
    {
        foundHttp = 1;
        p += STRN("http://");
    }
    else if (Strncmp(p, STRLIT("https://")) == 0)
    {
        foundHttp = 1;
        p += STRN("https://");
    }

    /* If found "http://" or "https://" */
    if (p != uri)
    {
        /* Skip over host (up to next slash) */
        while (IsNotSlashOrZero(*p))
            p++;

        /* *p is now a slash or a zero-terminator */
        if (!*p)
        {
            Snprintf(err, errSize, "missing path");
            RETURN(OL_Result_SyntaxError);
        }

        p++;

        /* If a second slash folows, then unknown scheme */
        if (*p == '/')
        {
            Snprintf(err, errSize, "unknown scheme: %.*s", (int)(p - uri), uri);
            RETURN(OL_Result_SyntaxError);
        }
    }

    /* Skip over optional slash (e.g., "/odata") */
    if (*p == '/')
        p++;

    /* Skip over resource path */
    for (start = p; *p && *p != '/'; p++)
        ;

    if (p != start)
    {
        size_t n = p - start;

        if (n >= MAX_SERVICE_LEN)
            RETURN(OL_Result_OutOfMemory);

        memcpy(self->service, start, n);
        self->service[n] = '\0';
        self->serviceLen = n;

        foundService = 1;
    }

    if (foundHttp && !foundService)
    {
        Snprintf(err, errSize, "missing service segment");
        RETURN(OL_Result_SyntaxError);
    }

    /* If URI represents just the service document */
    if (*p == '\0')
    {
        if (!foundService)
        {
            Snprintf(err, errSize, "missing service segment");
            RETURN(OL_Result_SyntaxError);
        }

        return OL_Result_Ok;
    }

    /* Expect '/' */
    if (foundService && *p++ != '/')
    {
        Snprintf(err, errSize, "expected '/' after service segment");
        RETURN(OL_Result_SyntaxError);
    }

    /* Process each segment of the resource path */
    while (*p)
    {
        char* start = p;
        URISegment* segment;

        /* Processing key segments cannot be performed here since string
         * keys are ambiguous. For example, these are equivalent:
         *     Persons('jsmith')
         *     Persons/jsmith
         * It's not possible to know whether 'jsmith' is a key or entity set.
         */

        /* Check for $count query option */
        if (Strncmp(p, STRLIT("$count")) == 0)
        {
            self->queryOptions |= OL_QUERY_OPTION_COUNT;
            p += STRN("$count");

            if (*p)
            {
                Snprintf(err, errSize, "extraneous characters after '$count'");
                return -1;
            }

            break;
        }

        /* Check for $value query option */
        if (Strncmp(p, STRLIT("$value")) == 0)
        {
            self->queryOptions |= OL_QUERY_OPTION_VALUE;
            p += STRN("$value");

            if (*p)
            {
                Snprintf(err, errSize, "extraneous characters after '$value'");
                return -1;
            }

            break;
        }

        /* Skip all but these characters: '/' '?' '(' '\0' */
        while (IsNotSlashQuesLeftParenOrZero(*p))
            p++;

        /* Reserve space for a new segment */
        if (self->segments.size == self->segments.capacity)
        {
            if (ArrayReserve(
                (Array*)&self->segments, 
                self->segments.size + 1,
                sizeof(URISegment),
                URI_ELEMENT_CAPACITY,
                &self->alloc) != 0)
            {
                RETURN(OL_Result_Failed);
            }
        }

        /* Initilize the segment */
        segment = &self->segments.data[self->segments.size++];
        segment->keys = NULL;
        segment->keysSize = 0;
        segment->keysCapacity = 0;
        segment->flags = OL_FLAG_STATIC_VALUE;
        segment->name = start;

        /* Check for overflow */
        if (segment->keysSize == segment->keysCapacity)
        {
            if (ArrayReserve(
                (Array*)segment,
                segment->keysSize + 1,
                sizeof(URIKey),
                URI_PAIR_CAPACITY,
                &self->alloc) != 0)
            {
                RETURN(OL_Result_Failed);
            }
        }

        switch (*p)
        {
            case '(':
            {
                *p++ = '\0';

                if (_ParseKeyPredicate(segment, &self->alloc, &p, 1) != 
                    OL_Result_Ok)
                {
                    Snprintf(err, errSize, "invalid key predicate");
                    RETURN(OL_Result_SyntaxError);
                }

                if (*p == '/')
                    p++;

                break;
            }
            case '\0':
            {
                break;
            }
            case '/':
            {
                *p++ = '\0';
                break;
            }
            case '?':
            {
                *p++ = '\0';

                for (;;)
                {
                    OL_Result r;

                    if ((r = _ParseQueryOption(self, &p, err, errSize)))
                        return r;

                    if (!*p)
                        break;

                    if (*p != '&')
                    {
                        Snprintf(err, errSize, 
                            "expected '&' after query option");
                        return OL_Result_SyntaxError;
                    }

                    p++;
                }
                break;
            }
        }
    }

    return OL_Result_Ok;
}

int FormatValue(char* buf, size_t size, const OL_Value* value)
{
    switch (value->type)
    {
        case OL_Type_Boolean:
        {
            const char* str = value->u.boolean ? "true" : "false";

            if (Strlcat(buf, str, size) >= size)
                return -1;

            break;
        }
        case OL_Type_String:
        {
            if (Strlcat3(buf, "'", value->u.string, "'", size) >= size)
                return -1;
            break;
        }
        case OL_Type_Int64:
        {
            char tmp[22];
            const char* str = ULongLongToStr(tmp, value->u.int64, NULL);

            if (Strlcat(buf, str, size) >= size)
                return -1;

            break;
        }
        default:
            return -1;
    }

    return 0;
}

OL_Result URIFormatContextURL(
    const URI* self,
    char* buf,
    size_t size)
{
    size_t i;
    size_t j;

    if (self->magic != URI_MAGIC)
        return OL_Result_Failed;

    if (Strlcpy(buf, "odata/$metadata", size) >= size)
        return OL_Result_Failed;

    if (self->segments.size == 0)
        return OL_Result_Ok;

    if (Strlcat(buf, "#", size) >= size)
        return OL_Result_Failed;

    /* If the final segment of path is "$ref" */
    {
        const URISegment* segment = &self->segments.data[self->segments.size-1];

        if (strcmp(segment->name, "$ref") == 0)
            return OL_Result_Ok;
    }

    for (i = 0; i < self->segments.size; i++)
    {
        const URISegment* segment = &self->segments.data[i];

        if (Strlcat(buf, segment->name, size) >= size)
            return OL_Result_Failed;

        if (i + 1 != self->segments.size && segment->keysSize > 0)
        {
            if (Strlcat(buf, "(", size) >= size)
                return OL_Result_Failed;

            for (j = 0; j < segment->keysSize; j++)
            {
                const URIKey* key = &segment->keys[j];
                FormatValue(buf, size, &key->value);

                if (j + 1 != segment->keysSize)
                {
                    if (Strlcat(buf, ",", size) >= size)
                        return OL_Result_Failed;
                }
            }

            if (Strlcat(buf, ")", size) >= size)
                return OL_Result_Failed;
        }

        if (i + 1 != self->segments.size)
        {
            if (Strlcat(buf, "/", size) >= size)
                return OL_Result_Failed;
        }
    }

    return OL_Result_Ok;
}
