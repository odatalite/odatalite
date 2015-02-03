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
#include <stdarg.h>
#include "http.h"
#include "iprintf.h"

void PHIT_HeadersDump(
    const PHIT_Headers* self,
    size_t n)
{
    size_t i;

    Iprintf(n, "PHIT_Headers\n");
    Iprintf(n, "{\n");
    n++;

    /* Content-Type: */
    if (self->contentType.found)
    {
        Iprintf(n, "contentType.mediaType={%s}\n", self->contentType.mediaType);
        Iprintf(n, "contentType.mediaSubType={%s}\n", 
            self->contentType.mediaSubType);

        for (i = 0; i < self->contentType.nparameters; i++)
        {
            Iprintf(n, "contentType.param={%s}{%s}\n", 
                self->contentType.parameters[i].name,
                self->contentType.parameters[i].value);
        }
    }

    /* Content-Length: */
    if (self->contentLength.found)
    {
        Iprintf(n, "contentLength={%u}\n", self->contentLength.value);
    }

    /* User-Agent: */
    if (self->userAgent.found)
    {
        Iprintf(n, "userAgent.found={%u}\n", self->userAgent.found);
        Iprintf(n, "userAgent.value={%s}\n", self->userAgent.value);
    }

    /* Host: */
    if (self->host.found)
    {
        Iprintf(n, "host.found={%u}\n", self->host.found);
        Iprintf(n, "host.value={%s}\n", self->host.value);
    }

    /* Authorization: */
    if (self->authorization.found)
    {
        Iprintf(n, "authorization.type={%u}\n", self->authorization.type);
        Iprintf(n, "authorization.value={%s}\n", 
            Strnull(self->authorization.credentials));
    }

    /* TE: */
    if (self->te.found)
    {
        Iprintf(n, "te.trailers={%u}\n", self->te.trailers);
        Iprintf(n, "te.chunked={%u}\n", self->te.chunked);
    }

    /* Transfer-Encoding: */
    if (self->transferEncoding.found)
    {
        Iprintf(n, "transferEncoding.chunked={%u}\n", 
            self->transferEncoding.chunked);
    }

    /* Trailer: */
    if (self->trailer.found)
    {
        Iprintf(n, "trailers.data={");

        for (i = 0; i < self->trailer.size; i++)
        {
            printf("%s", self->trailer.data[i]);

            if (i + 1 != self->trailer.size)
                printf(", ");
        }

        printf("}\n");

        Iprintf(n, "trailer.size={%u}\n", (unsigned int)self->trailer.size);
    }

    for (i = 0; i < self->nheaders; i++)
    {
        Iprintf(n, "%s={%s}\n", self->headers[i].name, self->headers[i].value);
    }

    n--;
    Iprintf(n, "}\n");
}

void HTTPRequestDump(
    const HTTPRequest* self)
{
    size_t n = 0;

    Iprintf(n, "HTTPRequest\n");
    Iprintf(n, "{\n");
    n++;

    Iprintf(n, "method={%u}\n", self->method);
    Iprintf(n, "uri={%s}\n", Strnull(self->uri));

    PHIT_HeadersDump(&self->headers, n);

    n--;
    Iprintf(n, "}\n");
}

void HTTPResponseDump(
    const HTTPResponse* self)
{
    size_t n = 0;

    Iprintf(n, "HTTPResponse\n");
    Iprintf(n, "{\n");
    n++;

    Iprintf(n, "statusCode={%lu}\n", self->statusCode);
    Iprintf(n, "statusMsg={%s}\n", Strnull(self->statusMsg));

    PHIT_HeadersDump(&self->headers, n);

    n--;
    Iprintf(n, "}\n");
}
