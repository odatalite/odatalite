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
#include "client.h"
#include <base/addr.h>
#include <base/sock.h>
#include <base/selector.h>
#include <base/buf.h>
#include <base/auth.h>
#include <base/str.h>
#include <base/chars.h>
#include <base/parse.h>
#include <base/http.h>
#include <base/dump.h>

const char* arg0;

#define D(X)

int clientDump;

static void _ReadCallback(
    Selector* selector,
    Client* self)
{
    ssize_t n;
    char buf[4096];

    D( printf("==== _ReadCallback()\n"); )

    n = SockReadN(self->base.sock, buf, sizeof(buf));

    if (clientDump && n > 0)
        Dump(stdout, "RECV", buf, n);

    if (n > 0)
    {
        BufCat(&self->in, buf, n);        
        
        if (self->in.err)
        {
            self->errorCallback(self, "unexpected failure", self->callbackData);
            ClientDelete(self);
            return;
        }

        if (self->httpState == HTTPSTATE_WAITING_FOR_HEADER)
        {
            ssize_t headersLength = 
                HTTPHaveCompleteHeaders(self->in.data, self->in.size);

            if (headersLength == -1)
            {
                self->errorCallback(
                    self, "malformed headers", self->callbackData);
                return;
            }

            if (headersLength > 0)
            {
                if (clientDump)
                {
                    Dump(stdout, "HEADERS", self->in.data, headersLength);
                }

                /* Call begin callback */
                self->beginCallback(self, self->callbackData);

                /* Call callback */
                self->foundEndOfHeadersCallback(
                    self,
                    self->in.data,
                    headersLength,
                    self->callbackData);

                if (HTTPResponseParse(
                    &self->httpResponse,
                    self->in.data,
                    headersLength) != 0)
                {
                    self->errorCallback(
                        self, "bad http response header", self->callbackData);
                    return;
                }

                if (!self->httpResponse.headers.contentLength.found &&
                    !self->httpResponse.headers.transferEncoding.chunked &&
                    self->httpResponse.statusCode 
                        != PHIT_STATUSCODE_204_NO_CONTENT)
                {
                    self->errorCallback(
                        self, "missing Content-Length", self->callbackData);
                }

                D( HTTPResponseDump(&self->httpResponse); )

                /* Call headers callback */
                self->headersCallback(
                    self,
                    self->httpResponse.statusCode,
                    self->httpResponse.statusMsg,
                    &self->httpResponse.headers,
                    self->callbackData);

                BufRemove(&self->in, 0, headersLength);

                if (self->httpResponse.statusCode ==
                    PHIT_STATUSCODE_204_NO_CONTENT)
                {
                    /* Call end callback */
                    self->endCallback(self, self->callbackData);
                    self->httpState = HTTPSTATE_WAITING_FOR_HEADER;
                }
                else
                {
                    self->httpState = HTTPSTATE_WAITING_FOR_CONTENT;
                }
            }
        }

        if (self->httpState == HTTPSTATE_WAITING_FOR_CONTENT)
        {
            if (self->httpResponse.headers.transferEncoding.chunked)
            {
                /* ATTN: assuming fixed-size chunks markers */
                /* Dispatch chunk-by-chunk */
                for (;;)
                {
                    size_t chunkOffset;
                    size_t chunkSize;
                    int r;
#if 0
                    Dump(stdout, "TMP", self->in.data, self->in.size);
#endif

                    /* Check whether we have a complete chunk */
                    r = HTTPHaveCompleteChunk(self->in.data, self->in.size,
                        &chunkOffset, &chunkSize);

                    /* Check for malformed chunk prefix */
                    if (r == -1)
                    {
                        self->errorCallback( self, "malformed chunk prefix",
                            self->callbackData);
                        return;
                    }

                    /* Return if not enough data for a complete chunk yet */
                    if (r == 0)
                        return;

                    /* If this is the final empty chunk */
                    if (chunkSize == 0)
                    {
                        if (clientDump)
                            Dump(stdout, "CHUNK", NULL, 0);

                        /* Remove empty chunk */
                        BufRemove(&self->in, 0, chunkOffset);

                        if (self->httpResponse.headers.trailer.size)
                        {
                            self->httpState = HTTPSTATE_WAITING_FOR_TRAILER;
                            goto trailer;
                        }
                        else
                        {
                            self->httpState = HTTPSTATE_WAITING_FOR_HEADER;
                            self->endCallback(self, self->callbackData);
                            return;
                        }
                    }

                    /* Remove chunk prefix */
                    BufRemove(&self->in, 0, chunkOffset);

                    /* Remove chunk suffix */
                    BufRemove(&self->in, chunkSize, HTTPGetChunkSuffixSize());

                    if (clientDump)
                        Dump(stdout, "CHUNK", self->in.data, chunkSize);

                    /* Dispatch all items in this chunk */
                    self->contentCallback(
                        self, 
                        self->in.data, 
                        chunkSize,
                        self->callbackData);

                    /* Remove the consumed bytes */
                    BufRemove(&self->in, 0, chunkSize);
                }
            }
            else
            {
                size_t n;
                size_t r;

                /* Use 'Content-Length' header */
                n = (size_t)self->httpResponse.headers.contentLength.value;
                r = (n < self->in.size) ? n : self->in.size;

                /* Dispatch non-zero content */
                if (r)
                {
                    /* Dispatch the content */
                    self->contentCallback(
                        self, 
                        self->in.data, 
                        r,
                        self->callbackData);

                    /* Remove the consumed bytes */
                    BufRemove(&self->in, 0, r);

                    /* Update the content length */
                    self->httpResponse.headers.contentLength.value -= r;
                }

                /* Check whether all content has been exhausted */
                if (self->httpResponse.headers.contentLength.value == 0)
                {
                    self->httpState = HTTPSTATE_WAITING_FOR_HEADER;
                    self->endCallback(self, self->callbackData);
                    return;
                }
            }
        }

trailer:

        if (self->httpState == HTTPSTATE_WAITING_FOR_TRAILER)
        {
            ssize_t trailersLength = 
                HTTPHaveCompleteTrailers(
                self->in.data, 
                self->in.size,
                self->httpResponse.headers.trailer.size);

            if (trailersLength == -1)
            {
                self->errorCallback(
                    self,
                    "malformed trailers",
                    self->callbackData);
                return;
            }

            if (trailersLength > 0)
            {
                if (clientDump)
                    Dump(stdout, "TRAILERS", self->in.data, trailersLength);

                if (HTTPTrailersParse(
                    &self->httpTrailers,
                    self->httpResponse.headers.trailer.size,
                    self->in.data,
                    trailersLength) != 0)
                {
                    self->errorCallback(
                        self,
                        "bad http trailers",
                        self->callbackData);
                    return;
                }

                /* Dispatch trailers */
                self->trailersCallback(
                    self,
                    &self->httpTrailers.headers,
                    self->callbackData);


                /* Remove trailers */
                BufRemove(&self->in, 0, trailersLength);
                self->httpState = HTTPSTATE_WAITING_FOR_HEADER;
                self->endCallback(self, self->callbackData);
            }
        }
    }
}

static void _WriteCallback(
    Selector* selector,
    Client* self)
{
    ssize_t n;
    Buf* buf = &self->out;

    D( printf("==== _WriteCallback()\n"); )

    if (buf->size == 0)
    {
        self->base.mask &= ~SELECTOR_WRITE;
        return;
    }

    n = SockWriteN(self->base.sock, buf->data, buf->size);

    if (n > 0)
    {
        if (clientDump)
            Dump(stdout, "SEND", buf->data, buf->size);

        BufRemove(buf, 0, (size_t)n);

        if (buf->size == 0)
            self->base.mask &= ~SELECTOR_WRITE;
    }
    else if (n == -1 && (errno != EWOULDBLOCK && errno != EAGAIN))
    {
        /* Ignore */
    }
    else
    {
        ClientDelete(self);
    }
}

static void _ClientCallback(
    Selector* selector,
    Handler* handler,
    unsigned int mask)
{
    Client* self = (Client*)handler;

    D( printf("_ClientCallback()\n"); )

    if (mask & SELECTOR_READ)
    {
        _ReadCallback(selector, self);
    }

    if (mask & SELECTOR_WRITE)
    {
        _WriteCallback(selector, self);
    }

    if (mask & SELECTOR_DESTROY)
    {
        ClientDelete(self);
    }
}

static int _Connect(
    const Addr* addr)
{
    Sock sock;

    if ((sock = SockCreate(addr->type)) == -1)
        return -1;

    if (SockConnect(sock, addr) != 0)
        goto failed;

    if (SockSetBlocking(sock, 0) != 0)
        return -1;

    return sock;

failed:
    SockClose(sock);
    return -1;
}

Client* ClientNew(
    Selector* selector,
    const char* sockname,
    const char* host,
    unsigned short port,
    const char* username,
    const char* password,
    ClientBeginCallback beginCallback,
    ClientErrorCallback errorCallback,
    ClientFoundEndOfHeadersCallback foundEndOfHeadersCallback,
    ClientHeadersCallback headersCallback,
    ClientContentCallback contentCallback,
    ClientTrailersCallback trailersCallback,
    ClientEndCallback endCallback,
    void* callbackData)
{
    Addr addr;
    Sock sock;
    Client* self;

    if (!errorCallback || !headersCallback || 
        !contentCallback || !trailersCallback)
    {
        return NULL;
    }

    if (host)
    {
        if (AddrInitInet(&addr, host, port) != 0)
            return NULL;
    }
    else
    {
#if defined(HAVE_POSIX)
        if (AddrInitUnix(&addr, sockname) != 0)
#endif
            return NULL;
    }

    if ((sock = _Connect(&addr)) == -1)
        return NULL;

    if (!(self = (Client*)Calloc(1, sizeof(Client))))
    {
        SockClose(sock);
        return NULL;
    }

    self->base.sock = sock;
    self->base.mask = 0;
    self->base.callback = _ClientCallback;
    self->selector = selector;
    self->beginCallback = beginCallback;
    self->errorCallback = errorCallback;
    self->headersCallback = headersCallback;
    self->foundEndOfHeadersCallback = foundEndOfHeadersCallback;
    self->contentCallback = contentCallback;
    self->trailersCallback = trailersCallback;
    self->callbackData = callbackData;
    self->endCallback = endCallback;

    if (SelectorAddHandler(selector, &self->base) != 0)
    {
        ClientDelete(self);
        return NULL;
    }

    /* Save username */
    if (username)
        Strlcpy(self->username, username, sizeof(self->username));

    /* Save password */
    if (password)
        Strlcpy(self->password, password, sizeof(self->password));

    return self;
}

void ClientDelete(
    Client* self)
{
    SelectorRemoveHandler(self->selector, &self->base);
    SockClose(self->base.sock);
    BufDestroy(&self->in);
    BufDestroy(&self->out);
    memset(self, 0xDD, sizeof(Client));
    Free(self);
}

int ClientPostRequest(
    Client* self,
    const char* request,
    size_t requestSize)
{
    BufCat(&self->out, request, requestSize);

    if (self->out.err)
        return -1;

    if (self->out.size)
        self->base.mask = SELECTOR_READ | SELECTOR_WRITE;

    return 0;
}
