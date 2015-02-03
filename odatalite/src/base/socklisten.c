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
#include "sock.h"
#include "str.h"

Sock SockCreateListener(
    const Addr* addr)
{
    Sock sock;

    if ((sock = SockCreate(addr->type)) == -1)
    {
        return -1;
    }

    if (SockReuseAddr(sock, 1) != 0)
    {
        goto failed;
    }

#if defined(HAVE_POSIX)
    if (addr->type == ADDR_UNIX)
        unlink(addr->u.un.sun_path);
#endif

    if (SockBind(sock, addr) != 0)
    {
        goto failed;
    }

#if defined(HAVE_POSIX)
    if (addr->type == ADDR_UNIX)
    {
        /* Allow non-root users to connect */
        if (chmod(addr->u.un.sun_path, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|
            S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH) != 0)
        {
            goto failed;
        }
    }
#endif

    if (SockListen(sock) != 0)
    {
        goto failed;
    }

    return sock;

failed:
    SockClose(sock);
    return -1;
}
