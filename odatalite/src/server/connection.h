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
#ifndef _connection_h
#define _connection_h

#include <stdlib.h>
#include <base/alloc.h>
#include <base/buf.h>
#include <base/sock.h>
#include <base/selector.h>
#include <base/auth.h>
#include <base/addr.h>
#include <base/http.h>
#include "context.h"

#if defined(ENABLE_STATIC_BUFFERS)
# define INBUF_CAPACITY 1024
# define OUTBUF_CAPACITY 1024
#else
# define INBUF_CAPACITY 1
# define OUTBUF_CAPACITY 1
#endif

#define USE_CMD

#define IN_BUF_SIZE 4096

#define CONNECTION_MAGIC 0x69027113

struct _Connection
{
    Handler base;

    unsigned int magic;

    /* Whether this connection is Unix or Internet socket */
    AddrType addrType;

    /* Authentication */
    AuthState authState;

    /* Back-pointer to selector */
    Selector* selector;

    /* Input buffer */
    Buf in;
    Alloc inAlloc;
    char inBuffer[IN_BUF_SIZE];

    /* Interim buffer (eventually copied to wbuf) */
    Buf out;
    Alloc outAlloc;
    char outBuffer[1024];

    /* Write buffer (all writes done directly from this buffer) */
    Buf wbuf;
    Alloc wbufAlloc;
    char wbufBuffer[1024];

    /* Offset to the the HTTP content (right after HTTP header) */
    size_t headerLength;

    /* Provider invocation context */
    Context context;

    /* Authenticated user */
    char user[USERNAME_SIZE];

    /* Authenticated role */
    PHIT_Role role;

    /* HTTP fields */
    HTTPState httpState;
    HTTPRequest httpRequest;

    /* Whether this is the final chunk */
    int chunkFinal;

#if 0
    /* Currently plugin (null means none loaded) */
    PHIT_Plugin* plugin;
#endif
};

Connection* ConnectionNew(
    Selector* selector, 
    AddrType addrType,
    Sock sock);

void ConnectionDelete(
    Connection* self);

#endif /* _connection_h */
