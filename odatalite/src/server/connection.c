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
#include "common.h"

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#if defined(HAVE_POSIX)
#include <sys/types.h>
#include <sys/socket.h>
#endif

#include <base/str.h>
#include <base/pam.h>
#include <base/chars.h>
#include <base/log.h>
#include <base/role.h>
#include <base/parse.h>
#include <base/http.h>
#include <base/dump.h>
#include <base/base64.h>
#include "connection.h"
#include "disp.h"
#include "context.h"
#include "options.h"
#include "phit.h"

INLINE void _SolicitReads(Connection* self)
{
    self->base.mask |= SELECTOR_READ;
}

INLINE void _UnsolicitReads(Connection* self)
{
    self->base.mask &= ~SELECTOR_READ;
}

INLINE void _SolicitWrites(Connection* self)
{
    self->base.mask |= SELECTOR_WRITE;
}

INLINE void _UnsolicitWrites(Connection* self)
{
    self->base.mask &= ~SELECTOR_WRITE;
}

void __EnterWaitingForHeader(
    Connection* self)
{
    self->httpState = HTTPSTATE_WAITING_FOR_HEADER;
    self->chunkFinal = 0;
    _SolicitReads(self);
}

static void _HandleRequest(
    Selector* selector,
    Connection* self,
    const char* content,
    size_t contentLength)
{
    DEBUG_ASSERT(self->authState == AUTH_ALLOWED);

    ContextReset(&self->context);

    DispatchRequest(
        &self->context,
        self->httpRequest.method,
        self->httpRequest.uri,
        &self->httpRequest.headers,
        content,
        contentLength);

    if (self->context.acceptChunkedEncoding)
    {
        /* Needed to initiate pull operations */
        _SolicitWrites(self);
    }

    return;
}

#if defined(ENABLE_PAM_AUTH)
static int _AuthHTTPBasic(
    HTTPRequest* headers,
    PHIT_Role* role)
{
    /* The authroization header must be present */
    if (!headers->headers.authorization.found)
        goto AccessDenied;

    /* The authorization type must be basic */
    if (headers->headers.authorization.type != PHIT_AUTHORIZATIONTYPE_BASIC)
        goto AccessDenied;

    /* The credentials are either in value or username+password */
    if (!headers->headers.authorization.credentials &&
        (!headers->username || !headers->password))
    {
        goto AccessDenied;
    }

    /* Decode the <USERNAME>:<PASSWORD> in place */
    if (headers->headers.authorization.credentials)
    {
        size_t n;
        size_t len;
        Base64DecState s = BASE64DECSTATE_INITIALIZER;
        char* colon;
        char* credentials;

        credentials = (char*)headers->headers.authorization.credentials;

        len = strlen(headers->headers.authorization.credentials);

        n = Base64Dec(
            &s, 
            credentials,
            len, 
            credentials,
            len);

        if (n == -1 || n >= len)
            goto AccessDenied;

        /* Split "<USERNAME>:<PASSWORD>" into 'username' and 'password' */

        credentials[n] = '\0';
        headers->username = credentials;

        if (!(colon = strchr(credentials, ':')))
            goto AccessDenied;

        *colon = '\0';
        headers->password = colon + 1;
    }

#if 0
    printf("username{%s}\n", headers->authorization.username);
    printf("password{%s}\n", headers->authorization.password);
#endif


    /* Use PAM to authenticate the request */
    if (PAMAuth(headers->username, headers->password) != 0)
    {
        LOGW(("PAM authentication failed: %s", headers->username));
        goto AccessDenied;;
    }

# if defined(ENABLE_ROLES)

    /* Resolve the role for this user */
    {
        *role = RoleResolve(headers->username);

        if (*role == PHIT_ROLE_NONE)
        {
            LOGW(("Role authentication failed: %s", headers->username));
            goto AccessDenied;
        }

        LOGI(("authenticated %s as %s", headers->username, RoleName(*role)));
    }

# endif /* defined(ENABLE_ROLES) */

    /* ATTN: scrub the password here! */

    return 0;

AccessDenied:

    LOGW(("Access denied: %s", Strnull(headers->username)));
    return -1;
}
#endif /* defined(ENABLE_PAM_AUTH) */

static void _HandleHTTPRequest(
    Selector* selector,
    Connection* self)
{
    ssize_t requestLength = 0;

    if (self->httpState == HTTPSTATE_WAITING_FOR_HEADER)
    {
        ssize_t headersLength = HTTPHaveCompleteHeaders(
            self->in.data, self->in.size);

        if (headersLength == -1)
        {
            LOGW(("malformed request headers"));
            goto disconnect;
        }

        if (headersLength > 0)
        {
#if 0
            if (g_options.dump)
                Dump(stdout, "HTTP.HEADER", self->in.data, headersLength);
#endif

            /* Unsolicit reads during request processing */
            _UnsolicitReads(self);

            /* parse the HTTP request headers */
            if (HTTPRequestParse(
                &self->httpRequest,
                self->in.data, 
                headersLength) != 0)
            {
                LOGW(("HTTP request parsing failed"));
                goto disconnect;
            }

            /* Save content length (if any) */
            requestLength = (size_t)headersLength + 
                self->httpRequest.headers.contentLength.value;

            /* Use chunked encoding if "TE: chunked" present */
            if (self->httpRequest.headers.te.found &&
                self->httpRequest.headers.te.chunked)
            {
                self->context.acceptChunkedEncoding = 1;
            }

#if 0
            if (g_options.dump)
                HTTPRequestDump(&self->httpRequest);
#endif

            /* If user not authenticated yet */
            if (self->authState == AUTH_START)
            {
                /* ATTN: authenticate each request (for proxies)? */

# if defined(ENABLE_PAM_AUTH)
                /* Authenticate the client */
                if (_AuthHTTPBasic(&self->httpRequest, &self->role) != 0)
                {
                    goto denied;
                }

                Strlcpy(self->user, self->httpRequest.username, 
                    sizeof(self->user));

# endif /* defined(ENABLE_PAM_AUTH) */

                self->authState = AUTH_ALLOWED;

                LOGD(("Access allowed: %s", 
                    self->httpRequest.headers.authorization.credentials));
            }

            /* Save the length of the HTTP header */
            self->headerLength = headersLength;

            self->httpState = HTTPSTATE_WAITING_FOR_CONTENT;
            /* Fall through to HTTPSTATE_WAITING_FOR_CONTENT case below */
        }
    }

    if (self->httpState == HTTPSTATE_WAITING_FOR_CONTENT)
    {
        /* If all the content has arrived */
        if (self->httpRequest.headers.contentLength.value <= 
            self->in.size - self->headerLength)
        {
            size_t endOffset = self->headerLength + 
                self->httpRequest.headers.contentLength.value;

            if (g_options.dump)
            {
                Dump(stdout, "HTTP.CONTENT", 
                    self->in.data + self->headerLength,
                    self->httpRequest.headers.contentLength.value);
            }

            self->chunkFinal = 0;

            /* Handle the command */
            _HandleRequest(
                selector, 
                self,
                self->in.data + self->headerLength,
                self->httpRequest.headers.contentLength.value);

            /* Remove HTTP header and associated content */
            BufRemove(&self->in, 0, endOffset);

            /* Now wait for response header to be sent. */
            self->httpState = HTTPSTATE_SENDING_RESPONSE_HEADER;
        }
    }

    return;

# if defined(ENABLE_PAM_AUTH)
denied:

    if (requestLength)
        BufRemove(&self->in, 0, requestLength);

    BufClear(&self->wbuf);
    HTTPFormatAccessDeniedResponse(&self->wbuf);
    _SolicitWrites(self);

    return;

# endif /* defined(ENABLE_PAM_AUTH) */

disconnect:

    LOGW(("forcibly closing connection"));
    ConnectionDelete(self);
}

static int _ReadCallback(
    Selector* selector,
    Connection* self)
{
    ssize_t r;
    char buf[IN_BUF_SIZE];

    DEBUG_ASSERT(self->magic = CONNECTION_MAGIC);

    r = SockReadN(self->base.sock, buf, sizeof(buf));

    if (r > 0)
    {
        if (g_options.dump)
            Dump(stdout, "RECV", buf, (size_t)r);

        BufCat(&self->in, buf, r);

        if (self->in.err)
        {
            ConnectionDelete(self);
            return -1;
        }

        _HandleHTTPRequest(selector, self);
    }
    else if (r == -1 && (errno == EWOULDBLOCK || errno == EAGAIN))
    {
        /* Ignore */
    }
    else
    {
        ConnectionDelete(self);
        return -1;
    }

    return 0;
}

static int _NeedToWrite(Connection* self)
{
    return self->wbuf.size != 0 || self->out.size != 0;
}

static ssize_t _Send(
    Connection* self)
{
    ssize_t n = 0;

    /* If the write buffer is empty, then build the next HTTP chunk */
    if (self->out.size > 0 && self->wbuf.size == 0)
    {
        BufCat(&self->wbuf, self->out.data, self->out.size);

        /* Clear the output buffer */
        BufClear(&self->out);

        /* If the final chunk, then write null chunk and status header */
        if (self->chunkFinal)
        {
            __EnterWaitingForHeader(self);
        }
    }
    else if (self->out.size == 0 && self->chunkFinal)
    {
        /* For case when there is nothing between HTTP header and trailer */
        /* ATTN: not confident about this */
        __EnterWaitingForHeader(self);
    }

    /* If no data to write, return */
    if (self->out.size == 0 && self->wbuf.size == 0)
    {
        /* Nothing written */
        return 0;
    }

    /* Write what is in the write buffer */
    if ((n = SockWriteN(self->base.sock, self->wbuf.data, self->wbuf.size)) > 0)
    {
        if (g_options.dump)
            Dump(stdout, "SEND", self->wbuf.data, (size_t)n);

        BufRemove(&self->wbuf, 0, (size_t)n);

        return n;
    }
    else if (n == -1 && (errno != EWOULDBLOCK && errno != EAGAIN))
    {
        return 0;
    }

    return -1;
}

static int _WriteCallback(
    Selector* selector,
    Connection* self)
{
    ssize_t n = 0;


    DEBUG_ASSERT(self->magic = CONNECTION_MAGIC);

    if (self->context.plugin && !_NeedToWrite(self))
    {
        static const size_t MAX_OUTBUF_SIZE = 4*1024;

        while (self->out.size < MAX_OUTBUF_SIZE && !self->context.postedEOC)
        {
            if (DispatchPull(&self->context) != 0)
            {
                /* ATTN: how do we report errors to HTTP client */
                __EnterWaitingForHeader(self);
                /* ATTN: how will trailer be written if we unsolic here? */
                _UnsolicitWrites(self);
                return 0;
            }
        }
    }

    DEBUG_ASSERT(self->magic = CONNECTION_MAGIC);

    /* If nothing to write, then return */
    if (!_NeedToWrite(self))
    {
        _UnsolicitWrites(self);
        return 0;
    }

    if ((n = _Send(self)) == -1)
    {
        ConnectionDelete(self);
        return -1;
    }

    if (n > 0)
    {
        if (!_NeedToWrite(self) && !self->context.plugin)
        {
            _UnsolicitWrites(self);
        }
    }

    /* If there's nothing left to write, then listen for reads again */
    _SolicitReads(self);
    return 0;
}

static void _Callback(
    Selector* selector,
    Handler* handler, 
    unsigned int mask)
{
    Connection* conn = (Connection*)handler;

    DEBUG_ASSERT(conn->magic = CONNECTION_MAGIC);

    if (mask & SELECTOR_READ)
    {
        if (_ReadCallback(selector, conn) == -1)
            return;
    }

    if (mask & SELECTOR_WRITE)
    {
        if (_WriteCallback(selector, conn) == -1)
            return;
    }

    if (mask & SELECTOR_DESTROY)
    {
        ConnectionDelete(conn);
    }
}

Connection* ConnectionNew(
    Selector* selector, 
    AddrType addrType,
    Sock sock)
{
    Connection* self;
    
    if (!(self = (Connection*)Calloc(1, sizeof(Connection))))
        return NULL;

    self->magic = CONNECTION_MAGIC;

    self->addrType = addrType;

#if defined(ENABLE_PAM_AUTH)
    self->authState = AUTH_START;
#else
    self->authState = AUTH_ALLOWED;
#endif

    self->authState = AUTH_START;

    if (g_options.noauth)
    {
        self->authState = AUTH_ALLOWED;
    }

    AllocInit(&self->inAlloc, self->inBuffer, sizeof(self->inBuffer));
    AllocInit(&self->outAlloc, self->outBuffer, sizeof(self->outBuffer));

    LOGD(("ConnectionNew(%p)", self));

    BufInit(&self->in, &self->inAlloc);
    BufInit(&self->out, &self->outAlloc);
    BufInit(&self->wbuf, &self->wbufAlloc);

    SockSetBlocking(sock, 0);
    self->base.sock = sock;
    self->base.mask = SELECTOR_READ;
    self->base.callback = _Callback;
    self->selector = selector;
    SelectorAddHandler(selector, &self->base);
    ContextInit(&self->context, self);

    return self;
}

void ConnectionDelete(
    Connection* self)
{
    LOGD(("ConnectionDelete(%p)", self));

    SelectorRemoveHandler(self->selector, &self->base);
    SockClose(self->base.sock);
    BufDestroy(&self->in);
    BufDestroy(&self->out);
    BufDestroy(&self->wbuf);
    ContextDestroy(&self->context);

    self->magic = 0xDDDDDDDD;
    Free(self);
}
