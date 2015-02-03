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
#ifndef _addr_h
#define _addr_h

#include "common.h"
#include <string.h>

#if defined(_MSC_VER)
# include <winsock2.h>
#else
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netinet/tcp.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/un.h>
#endif

#if defined(_MSC_VER)
typedef int socklen_t;
#endif

#if defined(_MSC_VER)
typedef unsigned long in_addr_t;
#endif


typedef enum _AddrType
{
    ADDR_INET = 0,
    ADDR_UNIX = 1
}
AddrType;

typedef struct _Addr
{
    union 
    {
        struct sockaddr_in in;
#if defined(HAVE_POSIX)
        struct sockaddr_un un;
#endif
    }
    u;
    AddrType type;
    socklen_t length;
}
Addr;

INLINE void AddrInitInetAny(
    Addr* self,
    unsigned short port)
{
    memset((char*)self, 0, sizeof(*self));
    self->u.in.sin_family = AF_INET;
    self->u.in.sin_addr.s_addr = htonl(INADDR_ANY);
    self->u.in.sin_port = htons(port);
    self->type = ADDR_INET;
    self->length = sizeof(self->u.in);
}

int AddrInitInet(
    Addr* self,
    const char* host,
    unsigned short port);

#if defined(HAVE_POSIX)
int AddrInitUnix(
    Addr* self,
    const char* path);
#endif

#endif /* _addr_h */
