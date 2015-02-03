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
#include "buf.h"
#include "parse.h"
#include "chars.h"

#define T(X)

/* ATTN: use BufFmt to collapse all these redundant sphitngs */

#if 0
int HTTPFormatHTMLWelcomeMessage(Buf* out)
{
#   define CONTENT "<html><body><h2>PHIT</h2></body></html>"
    BufCat(out, STRLIT("HTTP/1.1 200 OK\r\n"));
    BufCat(out, STRLIT("Content-Type: text/html\r\n"));
    BufFmt(out, "Content-Length: %lu\r\n\r\n", (unsigned long)STRN(CONTENT));
    BufCat(out, STRLIT(CONTENT));
    return 0;
#   undef CONTENT
}
#endif

const char* ParseHTTPMethod(
    const char* str,
    PHIT_Method* method)
{
    size_t i;

    for (i = 0; i < ARRSIZE(__HTTPMethodNames); i++)
    {
        const char* s = __HTTPMethodNames[i];

        if (Strncmp(str, s, s[-1]) == 0)
        {
            *method = (PHIT_Method)i;
            return str + s[-1];
        }
    }

    return NULL;
}

int HTTPRequestParse(
    HTTPRequest* self,
    char* data,
    size_t size)
{
    /*HOTSPOT*/
    char* p = data;
    size_t n = size;
    char* crlf;

    memset(self, 0, sizeof(*self));

    if (!(crlf = (char*)FindCRLF(p, n)))
        return -1;

    *crlf = '\0';

    /* Parse the start line */
    {
        /* Example: "M-POST / HTTP/1.1<CR><LF>" */

        /* parse the HTTP method name */
        if (!(p = (char*)ParseHTTPMethod(p, &self->method)))
            return -1;

        /* Expect space after method */
        if (!IsLWS(*p++))
            return -1;

        /* Skip whitespace leading up to URI */
        {
            while (IsLWS(*p))
                p++;

            if (!*p)
                return -1;
        }

        /* Get the URI */
        {
            self->uri = p;

            while (*p && !IsLWS(*p))
                p++;

            *p = '\0';
        }

        /* Ignore remainder of request line */
    }

    p = crlf + 2;
    n -= (p - data);

    if (PHIT_HeadersParse(&self->headers, &self->buf, p, n) != 0)
    {
        return -1;
    }

#if  0
    /* Handle custom headers */
    self->phitCommand = (char*)PHIT_HeadersFind(
        &self->headers, STRLIT("PHIT-Command"));
#endif

    return 0;
}
