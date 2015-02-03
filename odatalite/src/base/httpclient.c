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
#include "http.h"
#include "str.h"
#include "base64.h"
#include "parse.h"
#include "chars.h"
#include "dump.h"

#define MAX_AUTHORIZATION_VALUE 128

#define T(X)

int HTTPFormatRequest(
    Buf* out,
    const char* command,
    const char* username,
    const char* password,
    const char* content,
    size_t contentLength)
{
    /* ATTN: can any command be sent as an HTTP header? */

    /* Form the value for the "Authorization:" header */
    if (username && *username && password && *password)
    {
        char b64[2*MAX_AUTHORIZATION_VALUE];
        char buf[MAX_AUTHORIZATION_VALUE];
        Base64EncState s = BASE64ENCSTATE_INITIALIZER;
        size_t n;

        /* Build the authorization value */
        {
            n = Strlcpy3(buf, username, ":", password, sizeof(buf));

            if (n >= sizeof(buf))
                return -1;
        }

        /* Encode the authorization value */
        {
            n = Base64Enc(&s, buf, n, b64, sizeof(b64));
        
            if (n >= sizeof(b64))
                return -1;

            b64[n] = '\0';
        }

        if (BufFmt(out,
            "M-POST / HTTP/1.1\r\n"
            "Content-Type: text/plain\r\n"
            "TE: chunked\r\n"
            "Content-Length: %lu\r\n"
            "Authorization: Basic %s\r\n"
            "PHIT-Command: %s\r\n"
            "\r\n", 
            (unsigned long)contentLength,
            b64,
            command) < 0)
        {
            return -1;
        }
    }
    else
    {
        if (BufFmt(out,
            "M-POST / HTTP/1.1\r\n"
            "Content-Type: text/plain\r\n"
            "TE: chunked\r\n"
            "Content-Length: %lu\r\n"
            "PHIT-Command: %s\r\n"
            "\r\n", 
            (unsigned long)contentLength,
            command) < 0)
        {
            return -1;
        }
    }

    BufCat(out, content, contentLength);
    return out->err;
}

int HTTPResponseParse(
    HTTPResponse* self,
    char* data,
    size_t size)
{
    /*HOTSPOT*/
    char* p = data;
    size_t n = size;
    char* crlf;

    memset(self, 0, sizeof(*self));

    if (!(crlf = (char*)FindCRLF(p, n)))
    {
        return -1;
    }

    *crlf = '\0';

    T( printf("LINE{%.*s}\n", (int)(crlf - p), p); )

    /* Parse the start line */
    {
        /* Example: "HTTP/1.1 200 OK" */

        /* Expect "HTTP/1.1" */
        {
            if (Strncmp(p, STRLIT("HTTP/1.1")) != 0)
            {
                return -1;
            }

            p += STRN("HTTP/1.1");
        }

        /* Skip whitespace */
        while (IsLWS(*p))
            p++;

        /* Expect status code */
        {
            char* end;
            self->statusCode = strtoul(p, &end, 10);

            if (end == p)
            {
                return -1;
            }

            p = end;
        }

        /* Skip whitespace */
        while (IsLWS(*p))
            p++;

        /* Get the status message */
        {
            char* start = p;

            while (*p && !IsLWS(*p))
                p++;

            *p = '\0';

            self->statusMsg = start;
        }

        /* Ignore remainder of response line */
    }

    p = crlf + 2;
    n -= (p - data);

    return PHIT_HeadersParse(&self->headers, &self->buf, p, n);
}

int HTTPTrailersParse(
    HTTPTrailers* self,
    size_t numTrailers,
    char* data,
    size_t size)
{
    char* p = data;
    size_t n = size;

    memset(self, 0, sizeof(*self));

    return PHIT_HeadersParse(&self->headers, &self->buf, p, n);
}

ssize_t HTTPHaveCompleteTrailers(
    char* data,
    size_t size,
    size_t numTrailers)
{
    const char* p = data;
    size_t n = size;
    size_t m = 0;

    if (numTrailers == 0)
        return -1;

    while (n)
    {
        const char* crlf = FindCRLF(p, n);
        size_t r;

        if (!crlf)
        {
            /* Need more data */
            return 0;
        }

        r = crlf - p + 2;
        n -= r;
        p += r;

        if (++m == numTrailers)
            break;
    }

    return p - data;
}
