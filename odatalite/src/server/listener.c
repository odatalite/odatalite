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
#include <stdio.h>
#include "listener.h"
#include "connection.h"
#include <base/log.h>

static void _ListenerCallback(
    Selector* selector,
    Handler* handler,
    unsigned int mask)
{
    Listener* self = (Listener*)handler;

    if (mask & SELECTOR_READ)
    {
        Sock sock;
        Addr addr;

        sock = SockAccept(self->base.sock, &addr);

        if (sock != -1)
        {
            Connection* conn = ConnectionNew(selector, self->addrType, sock);
            (void)conn;
        }

        if (self->addrType == ADDR_INET)
        {
            SockSetNoDelay(sock, 1);
        }
    }

    if (mask & SELECTOR_DESTROY)
    {
        ListenerDestroy(self);
    }
}

int ListenerInit(
    Listener* self,
    Selector* selector, 
    const char* sockname,
    unsigned short port)
{
    Addr addr;
    Sock sock;

    LOGD(("ListenerInit(%p)", self));

    memset(self, 0, sizeof(Listener));

#if defined(HAVE_POSIX)
    if (sockname)
        AddrInitUnix(&addr, sockname);
    else
#endif
        AddrInitInetAny(&addr, port);

    if ((sock = SockCreateListener(&addr)) == -1)
        return -1;

    SockSetBlocking(sock, 0);

    if (addr.type == ADDR_INET)
        SockSetNoDelay(sock, 1);

    self->base.sock = sock;
    self->base.mask = SELECTOR_READ;
    self->base.callback = _ListenerCallback;
    self->selector = selector;
    SelectorAddHandler(selector, &self->base);

#if defined(HAVE_POSIX)
    if (sockname)
        self->addrType = ADDR_UNIX;
    else
#endif
        self->addrType = ADDR_INET;

    if (sockname)
        LOGI(("Listening on %s", sockname));
    else
        LOGI(("Listening on %u", port));

    return 0;
}

void ListenerDestroy(
    Listener* self)
{
    LOGD(("ListenerDestroy(%p)", self));

    SelectorRemoveHandler(self->selector, &self->base);
    SockClose(self->base.sock);
}
