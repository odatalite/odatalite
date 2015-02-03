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
#include <string.h>

#include "http.h"
#include "parse.h"
#include "str.h"
#include "chars.h"
#include "dump.h"

# define T(X)

const char* __HTTPMethodNames[10] =
{
    "\003GET" + 1,
    "\003PUT" + 1,
    "\005PATCH" + 1,
    "\006DELETE" + 1,
    "\004POST" + 1,
    "\006M-POST" + 1,
    "\004HEAD" + 1,
    "\005TRACE" + 1,
    "\007CONNECT" + 1,
    "\007OPTIONS" + 1
};

static int _AppendHeader(
    PHIT_Header* headers,
    size_t* nheaders,
    const char* name,
    const char* value)
{
    if (*nheaders == HEADERS_BUFSIZE)
        return -1;

    headers[*nheaders].name = name;
    headers[*nheaders].value = value;
    (*nheaders)++;

    return 0;
}

static int _HTTPParseContentLength(
    PHIT_Headers* headers,
    char* data,
    size_t size)
{
    char* end;
    headers->contentLength.found = 1;
    headers->contentLength.value = strtoul(data, &end, 10);
    return data == end ? -1 : 0;
}

/*
    parameter = attribute "=" value
    attribute = token
    value = token | quoted-string
    token = 1*<any CHAR except CTLs or separators>
*/
static char* _ParseHTTPParameter(
    char* p,
    PHIT_HTTPParameter* param)
{
    /* Get the name */
    {
        char* start;
        char* end;

        while (IsLWS(*p))
            p++;

        if (!*p)
            return p;

        start = p;

        while (IsHTTPToken(*p))
            p++;

        if (p == start)
            return NULL;

        end = p;

        while (IsLWS(*p))
            p++;

        if (*p++ != '=')
            return NULL;

        *end = '\0';
        param->name = start;
    }

    /* Get the value */
    {
        char* start;
        char* end;

        while (IsLWS(*p))
            p++;

        if (!*p)
            return NULL;

        if (*p == '"')
        {
            start = ++p;

            while (*p && *p != '"')
                p++;

            if (*p != '"')
                return NULL;

            end = p++;
        }
        else
        {
            start = p;

            while (IsHTTPToken(*p))
                p++;

            if (p == start)
                return NULL;

            end = p;
        }

        while (IsLWS(*p))
            p++;

        if (*p && *p++ != ';')
            return NULL;

        *end = '\0';
        param->value = start;
    }

    return p;
}

/*
    Content-Type = "Content-Type" ":" media-type
    media-type = type "/" subtype *( ";" parameter )
    type = token
    subtype = token
*/
static int _HTTPParseContentType(
    PHIT_Headers* headers,
    HTTPBuf* buf,
    char* data,
    size_t size)
{
    char* p = data;

    /* Found */
    headers->contentType.found = 1;

    /* Get the 'type' */
    {
        char* start;
        char* end;

        while (IsLWS(*p))
            p++;

        start = p;

        while (IsHTTPToken(*p))
            p++;

        if (p == start)
            return -1;

        end = p;

        while (IsLWS(*p))
            p++;

        if (*p++ != '/')
            return -1;

        *end = '\0';
        headers->contentType.mediaType = start;
    }

    /* Get the 'subtype' */
    {
        char* start;
        char* end;

        while (IsLWS(*p))
            p++;

        start = p;

        while (IsHTTPToken(*p))
            p++;

        if (p == start)
            return -1;

        end = p;

        while (IsLWS(*p))
            p++;

        if (*p && *p++ != ';')
            return -1;

        *end = '\0';
        headers->contentType.mediaSubType = start;
    }

    /* Get each parameter */
    while (*p)
    {
        PHIT_HTTPParameter param;

        memset(&param, 0, sizeof(param));

        if (!(p = _ParseHTTPParameter(p, &param)))
            return -1;

        if (headers->contentType.nparameters == 
            PHIT_ARRAY_SIZE(buf->contentTypeParameters))
        {
            return -1;
        }

        buf->contentTypeParameters[headers->contentType.nparameters] = param;
        headers->contentType.parameters = buf->contentTypeParameters;
        headers->contentType.nparameters++;
    }

    return 0;
}

const char* PHIT_HeadersFind(
    const PHIT_Headers* self,
    const char* name,
    size_t len)
{
    size_t i;

    for (i = 0; i < self->nheaders; i++)
    {
        const char* s = self->headers[i].name;

        if (Strncaseeq(s, name, len) == 0 && s[len] == '\0')
            return self->headers[i].value;
    }

    /* Not found! */
    return NULL;
}

static int _ParseTokenList(
    char* data,
    const char** buf,
    size_t maxBufSize,
    size_t* bufSizeOut)
{
    char* p = data;

    for (;;)
    {
        char* start = p;

        /* Skip over LWS and commas */
        while (IsLWS(*p) || *p == ',')
            p++;

        /* Null terminate */
        if (p != start)
            *start = '\0';

        if (!*p)
            break;

        start = p;

        /* Skip over token characters */
        while (IsHTTPToken(*p))
            p++;

        if (p == start)
        {
            return -1;
        }

        /* Append trailer to list */
        {
            if (*bufSizeOut == maxBufSize)
                return -1;

            buf[(*bufSizeOut)++] = start;
        }

        if (!*p)
            break;
    }

    return 0;
}

int PHIT_HeadersParse(
    PHIT_Headers* self,
    HTTPBuf* buf,
    char* data,
    size_t size)
{
    /*HOTSPOT*/
    char* p = data;
    size_t n = size;
    char* crlf;
    char* start;
    int foundContentType = 0;
    int foundTE = 0;

    memset(self, 0, sizeof(*self));
    memset(buf, 0, sizeof(*buf));

    while (n)
    {
        char c = toupper(*p);

        start = p;

        /* Find the <CR><LF> sequence */
        if (!(crlf = (char*)FindCRLF(p, n)))
            return -1;

        /* Break out on empty lines */
        if (p == crlf)
        {
            p = (crlf + 2);
            n -= (p - start);
            break;
        }

        /* Null-terminate the line */
        *crlf = '\0';

        /* Match the header */
        if (!foundContentType && c == 'C' &&
            Strncaseeq(p, STRLIT("Content-Type:")) == 0)
        {
            p += STRN("Content-Type:");

            if (_HTTPParseContentType(self, buf, p, crlf - p) != 0)
                return -1;

            foundContentType = 1;
        }
        else if (c == 'C' && Strncaseeq(p, STRLIT("Content-Length:")) == 0)
        {
            p += STRN("Content-Length:");

            if (_HTTPParseContentLength(self, p, crlf - p) != 0)
            {
                return -1;
            }
        }
        else if (!foundTE &&
            ((p[0] == 'T' && p[1] == 'E' && p[2] == ':') ||
            Strncaseeq(p, STRLIT("TE:")) == 0))
        {
            p += STRN("TE:");

            self->te.found = 1;

            for (; *p; p++)
            {
                if (StrncaseeqProbable(p, STRLIT("chunked")) == 0)
                {
                    self->te.chunked = 1;
                    p += STRN("chunked");
                }

                if (StrncaseeqProbable(p, STRLIT("trailers")) == 0)
                {
                    self->te.trailers = 1;
                    p += STRN("trailers");
                }
            }

            foundTE = 1;
        }
        else if (c == 'T' && Strncaseeq(p, STRLIT("Transfer-Encoding:")) == 0)
        {
            p += STRN("Transfer-Encoding:");

            self->transferEncoding.found = 1;

            for (; *p; p++)
            {
                if (StrncaseeqProbable(p, STRLIT("chunked")) == 0)
                {
                    self->transferEncoding.chunked = 1;
                    p += STRN("chunked");
                }
            }
        }
        else if (c == 'U' && Strncaseeq(p, STRLIT("User-Agent:")) == 0)
        {
            p += STRN("User-Agent:");
            self->userAgent.found = 1;
            self->userAgent.value = TrimLeadingAndTrailingLWS(p, crlf - p);
        }
        else if (c == 'H' && Strncaseeq(p, STRLIT("Host:")) == 0)
        {
            p += STRN("Host:");
            self->host.found = 1;
            self->host.value = TrimLeadingAndTrailingLWS(p, crlf - p);
        }
        else if (c == 'A' && Strncaseeq(p, STRLIT("Authorization:")) == 0)
        {
            p += STRN("Authorization:");
            p = TrimLeadingAndTrailingLWS(p, crlf - p);

            self->authorization.found = 1;

            if (Strncaseeq(p, STRLIT("Basic")) == 0)
            {
                p += STRN("Basic");
                self->authorization.type = PHIT_AUTHORIZATIONTYPE_BASIC;

                while (IsLWS(*p))
                    p++;

                self->authorization.credentials = p;
            }
            else
            {
                self->authorization.type = PHIT_AUTHORIZATIONTYPE_UNKNOWN;
            }
        }
        else if (c == 'T' && Strncaseeq(p, STRLIT("Trailer:")) == 0)
        {
            p += STRN("Trailer:");
            self->trailer.found = 1;

            if (_ParseTokenList(p, buf->trailersBuf, TRAILERS_BUFSIZE,
                &buf->trailersBufSize) == 0)
            {
                self->trailer.data = buf->trailersBuf;
                self->trailer.size = buf->trailersBufSize;
            }
            else
            {
                /* ATTN: ignore error */
            }
        }
        else
        {
            /* Process a generic header */
            while (*p && *p != ':')
                p++;

            /* Expect a colon */
            if (*p != ':')
                return -1;

            /* Null terminate the header */
            *p++ = '\0';

            /* Skip linear whitespace */
            while (IsLWS(*p))
                p++;

            _AppendHeader(buf->headersBuf, &buf->headersBufSize, start, p);
        }

        p = (crlf + 2);
        n -= (p - start);
    }

    /* Check whether we consumed all the bytes */
    DEBUG_ASSERT(n == 0);

    self->headers = buf->headersBuf;
    self->nheaders = buf->headersBufSize;

    return 0;
}

ssize_t HTTPHaveCompleteHeaders(
    char* data,
    size_t size)
{
    const char* crlfcrlf = FindCRLFCRLF(data, size);

    if (!crlfcrlf)
    {
        /* Need more data */
        return 0;
    }

    return (crlfcrlf + STRN("\r\n\r\n")) - data;
}

int HTTPFormatChunk(
    Buf* out,
    const char* data,
    size_t size)
{
    /* Reserve space for the chunk (prefix+data+suffix) */
    if (BufReserve(
        out, 
        out->size + MAX_CHUNK_PREFIX_SIZE + size + CHUNK_SUFFIX_SIZE) != 0)
    {
        return -1;
    }

    /* Write the chunk prefix: "HEX<CR><LF>" */
    {
        char buf[10];
        size_t strLen;
        const char* str;
        
        str = UIntToHexStr(buf, size, &strLen);
        buf[8] = '\r';
        buf[9] = '\n';
        strLen += 2;
        memcpy(out->data + out->size, str, strLen);
        out->size += strLen;
    }

    /* Write the data */
    memcpy(out->data + out->size, data, size);
    out->size += size;

    /* Write the chunk suffix: "<CR><LF>" */
    out->data[out->size++] = '\r';
    out->data[out->size++] = '\n';

    return 0;
}

int HTTPHaveCompleteChunk(
    char* data,
    size_t size,
    size_t* chunkOffsetOut,
    size_t* chunkSizeOut)
{
    char xdigits[17];
    size_t i;
    size_t chunkOffset;
    size_t chunkSize;

    /* If no bytes, return now */
    if (!data || !size)
        return 0;

    /* Iterate over leading hex digits */
    for (i = 0; i < size && i < sizeof(xdigits)-1 && isxdigit(data[i]); i++)
        xdigits[i] = data[i];

    /* If no leading hex digits found, fail */
    if (i == 0)
        return -1;

    /* Zero-terminate xdigits */
    xdigits[i] = '\0';

    /* Need 2 more characters for <CR><LF> */
    if (i + 2 > size)
    {
        /* Need more data */
        return 0;
    }

    /* Expect <CR><LF> */
    if (data[i] != '\r' || data[i+1] != '\n')
    {
        /* Bad chunk prefix */
        return -1;
    }

    /* Set offset of chunk */
    chunkOffset = i + 2;

    /* Convert hex string */
    {
        char* end;
        unsigned long x = strtoul(xdigits, &end, 16);

        if (end == xdigits || *end != '\0')
            return -1;

        chunkSize = (size_t)x;
    }

    /* If terminating zero-chunk, then return now */
    if (chunkSize == 0)
    {
        if (chunkOffsetOut)
            *chunkOffsetOut = chunkOffset;

        if (chunkSizeOut)
            *chunkSizeOut = chunkSize;

        return 1;
    }

    /* Do we have enough for a chunk */
    if (chunkOffset + chunkSize + 2 > size)
    {
        /* Need more data */
        return 0;
    }

    /* Check for chunk suffix: <CR><LF> */
    if (data[chunkOffset+chunkSize] != '\r' || 
        data[chunkOffset+chunkSize+1] != '\n')
    {
        return -1;
    }

    /* Set output parameters */

    if (chunkOffsetOut)
        *chunkOffsetOut = chunkOffset;

    if (chunkSizeOut)
        *chunkSizeOut = chunkSize;

    return 1;
}
