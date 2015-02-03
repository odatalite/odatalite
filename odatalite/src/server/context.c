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
#include <base/buf.h>
#include <base/dump.h>
#include <base/log.h>
#include "context.h"
#include "connection.h"
#include "contextoptions.h"

static void _PostStatusLine(
    PHIT_Context* context,
    PHIT_StatusCode statusCode,
    const char* statusMsg)
{
    Context* self = (Context*)context;
    Buf* wbuf;

    DEBUG_ASSERT(context->magic == PHIT_CONTEXT_MAGIC);

    wbuf = &self->connection->wbuf;

    /* Save status code to make various decisions later */
    self->statusCode = statusCode;

    /* Example: HTTP/1.1 200 OK<CR><LF> */
    BufCat(wbuf, STRLIT("HTTP/1.1 "));

    /* Write the status code */
    {
        char buf[UIntToStrBufSize];
        size_t size;
        const char* str = UIntToStr(buf, statusCode, &size);
        BufCat(wbuf, str , size);
    }

    BufCatCh(wbuf, ' ');
    BufCatStr(wbuf, statusMsg);
    BufCat(wbuf, STRLIT("\r\n"));
}

static void _PostHeaderAux(
    PHIT_Context* context,
    const char* name,
    size_t nameLen,
    const char* value,
    size_t valueLen)
{
    Context* self = (Context*)context;
    Buf* wbuf;

    DEBUG_ASSERT(context->magic == PHIT_CONTEXT_MAGIC);

    wbuf = &self->connection->wbuf;
    nameLen = strlen(name);
    valueLen = strlen(value);

    BufCat(wbuf, name, nameLen);
    BufCat(wbuf, STRLIT(": "));
    BufCat(wbuf, value, valueLen);
    BufCat(wbuf, STRLIT("\r\n"));
}

static void _PostHeader(
    PHIT_Context* context,
    const char* name,
    const char* value)
{
    return _PostHeaderAux(
        context, name, strlen(name), value, strlen(value));
}

static void _PostHeaderUL(
    PHIT_Context* context,
    const char* name,
    unsigned long x)
{
    char buf[ULongToStrBufSize];
    const char* value;
    size_t valueLen;

    value = ULongToStr(buf, x, &valueLen);
    _PostHeaderAux(context, name, strlen(name), value, valueLen);
}

static void _PostTrailerField(
    PHIT_Context* context,
    const char* name,
    const char* value)
{
    Context* self = (Context*)context;
    Buf* out;
    size_t nameLen;
    size_t valueLen;

    DEBUG_ASSERT(context->magic == PHIT_CONTEXT_MAGIC);

    out = &self->connection->out;
    nameLen = strlen(name);
    valueLen = strlen(value);

    BufCat(out, name, nameLen);
    BufCat(out, STRLIT(": "));
    BufCat(out, value, valueLen);
    BufCat(out, STRLIT("\r\n"));
}

static void _PostEOH(
    PHIT_Context* context)
{
    Context* self = (Context*)context;
    Buf* wbuf;

    DEBUG_ASSERT(context->magic == PHIT_CONTEXT_MAGIC);

    wbuf = &self->connection->wbuf;

    /* If no "Content-Length" header, then use chunked encoding */
    if (self->acceptChunkedEncoding &&
        self->statusCode != PHIT_STATUSCODE_204_NO_CONTENT)
    {
        BufCat(wbuf, STRLIT("Transfer-Encoding: chunked\r\n"));
        self->chunkedEncoding = 1;
        self->connection->base.mask |= SELECTOR_WRITE;
    }

    self->postedEOH = 1;

    if (self->chunkedEncoding)
        BufCat(wbuf, STRLIT("\r\n"));
}

static void _PostContent(
    PHIT_Context* context,
    const char* data,
    size_t size)
{
    Context* self = (Context*)context;
    Buf* out;

    DEBUG_ASSERT(context->magic == PHIT_CONTEXT_MAGIC);

    out = &self->connection->out;

    if (data && size)
    {
        /* Write chunk prefix */
        if (self->chunkedEncoding)
            HTTPFormatChunk(out, data, size);
        else
            BufCat(out, data, size);
    }
}

static void _PostEOC(
    PHIT_Context* context)
{
    Context* self = (Context*)context;
    Buf* out;

    DEBUG_ASSERT(context->magic == PHIT_CONTEXT_MAGIC);

    out = &self->connection->out;

    /* Write content length (in not chunked) */
    if (!self->chunkedEncoding)
    {
        Buf* wbuf = &self->connection->wbuf;
        _PostHeaderUL(context, "Content-Length", out->size);
        BufCat(wbuf, STRLIT("\r\n"));
    }

    /* Write the terminating null chunk */
    if (self->chunkedEncoding)
        BufCat(out, STRLIT("0\r\n"));

    self->plugin = NULL;
    self->postedEOC = 1;
    self->connection->chunkFinal = 1;
    self->connection->base.mask |= SELECTOR_WRITE;
}

void _PostError(
    PHIT_Context* context,
    PHIT_StatusCode statusCode,
    const char* statusMsg,
    const char* detail)
{
    PHIT_Context_PostStatusLine(context, statusCode, statusMsg);
    PHIT_Context_PostHeader(context, "Content-Type", "text/html");
    PHIT_Context_PostEOH(context);

    PHIT_Context_PostContent(context, STRLIT(
        "<html><head></head>"
        "<body>"
        "<h2>"));

    PHIT_Context_PostContent(context, statusMsg, strlen(statusMsg));

    if (detail)
    {
        PHIT_Context_PostContent(context, STRLIT(": "));
        PHIT_Context_PostContent(context, detail, strlen(detail));
    }

    PHIT_Context_PostContent(context, STRLIT(
        "</h2>"
        "</body>"
        "</html>"));

    PHIT_Context_PostEOC(context);
}

static void* _SetPluginData(
    PHIT_Context* context,
    void* pluginData)
{
    Context* self = (Context*)context;
    void* oldPluginData;

    DEBUG_ASSERT(context->magic == PHIT_CONTEXT_MAGIC);

    oldPluginData = self->pluginData;
    self->pluginData = pluginData;
    return oldPluginData;
}

static void* _GetPluginData(
    PHIT_Context* context)
{
    Context* self = (Context*)context;

    DEBUG_ASSERT(context->magic == PHIT_CONTEXT_MAGIC);

    return self->pluginData;
}

static int _GetOption(
    const PHIT_Context* context,
    int option,
    void* value,
    size_t valueSize)
{
    Context* self = (Context*)context;

    if (option == CONTEXT_OPTION_BUF)
    {
        Buf* x;

        if (valueSize < sizeof(x) || !self->connection)
            return -1;

        x = &self->connection->out;
        memcpy(value, &x, sizeof(x));
        return 0;
    }

    if (option == CONTEXT_OPTION_CHUNKED_ENCODING)
    {
        int x = self->chunkedEncoding;

        if (valueSize < sizeof(x))
            return -1;

        memcpy(value, &x, sizeof(x));
        return 0;
    }

    if (option == PHIT_CONTEXT_OPTION_ROLE && self->connection)
    {
        PHIT_Role x = self->connection->role;

        if (valueSize < sizeof(x))
            return -1;

        memcpy(value, &x, sizeof(x));
        return 0;
    }

    /* Unknown option */
    return -1;
}

static PHIT_Context _base =
{
    PHIT_CONTEXT_MAGIC,
    _PostStatusLine,
    _PostHeader,
    _PostHeaderUL,
    _PostTrailerField,
    _PostEOH,
    _PostContent,
    _PostEOC,
    _PostError,
    _SetPluginData,
    _GetPluginData,
    _GetOption
};

void ContextInit(
    Context* self,
    Connection* connection)
{
    memset(self, 0, sizeof(*self));
    self->base = _base;
    self->connection = connection;
    self->connection->base.mask &= ~SELECTOR_WRITE;
}

void ContextReset(
    Context* self)
{
    self->plugin = NULL;
    self->postedEOH = 0;
    self->postedEOC = 0;
    self->connection->base.mask &= ~SELECTOR_WRITE;
}

void ContextDestroy(
    Context* self)
{
    memset(self, 0xDD, sizeof(Context));
}
