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
#ifndef _sock_h
#define _sock_h

#include "common.h"

#if defined(_MSC_VER)
# include <winsock2.h>
#else
# include <unistd.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/tcp.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <fcntl.h>
# include <arpa/inet.h>
# include <signal.h>
# include <sys/uio.h>
# include <sys/socket.h>
# include <sys/un.h>
# include <unistd.h>
# include <sys/stat.h>
#endif

#if defined(__APPLE__)
# include <sys/ucred.h>
#endif

#include <string.h>
#include "common.h"
#include "addr.h"

#if defined(_MSC_VER)
# define EINTR WSAEINTR
# define EWOULDBLOCK WSAEWOULDBLOCK
# define EAGAIN 0xFFFFFFFF
#endif


#if defined(_MSC_VER)
# if defined(_WIN64)
typedef unsigned long long Sock;
# else
typedef unsigned int Sock;
# endif
#else
typedef int Sock;
#endif

#if defined(ENABLE_SOCKTRACE)
extern unsigned char __sockLog;
void SockLogClose();
#endif

#if defined(_MSC_VER)
typedef int ssize_t;
#endif

#if defined(HAVE_POSIX)
int __SetFDFlag(
    int fd,
    int flag,
    int value);
#endif /* defined(HAVE_POSIX) */

INLINE int SockStart()
{
#if defined(_MSC_VER)
    {
        WORD version = MAKEWORD(2, 0);
        WSADATA data;
        return WSAStartup(version, &data) == 0 ? 0 : -1;
    }
#else /* _MSC_VER */
    {
        /* ignore PIPE signal */
        signal(SIGPIPE, SIG_IGN);
        return 0;
    }
#endif /* !_MSC_VER */
}

INLINE void SockStop()
{
#if defined(_MSC_VER)
    WSACleanup();
#endif
}

INLINE Sock SockCreate(AddrType type)
{
    if (type == ADDR_INET)
        return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    else if (type == ADDR_UNIX)
        return socket(PF_UNIX, SOCK_STREAM, 0);
    else
        return -1;
}

INLINE int SockClose(
    Sock sock)
{
#if defined(_MSC_VER)
    return closesocket(sock);
#else
    return close(sock);
#endif
}

INLINE int SockBind(
    Sock sock, 
    const Addr* addr)
{
    return bind(sock, (struct sockaddr*)addr, addr->length);
}

INLINE int SockListen(
    Sock sock)
{
    return listen(sock, 15);
}

INLINE Sock SockAccept(
    Sock sock, 
    Addr* addr)
{
    socklen_t addrlen = sizeof(addr->u);
    return accept(sock, (struct sockaddr*)addr, &addrlen);
}

INLINE int SockSetCloseOnExec(
    Sock sock, 
    int closeOnExec)
{
#if defined(_MSC_VER)
    (void)sock;
    (void)closeOnExec;
#else
    return __SetFDFlag(sock, FD_CLOEXEC, closeOnExec);
#endif
}

INLINE int SockConnect(
    Sock sock, 
    const Addr* addr)
{
    return connect(sock, (struct sockaddr*)addr, addr->length);
}

INLINE int SockReuseAddr(
    Sock sock,
    int reuseAddr)
{
    return setsockopt(
        sock, 
        SOL_SOCKET, 
        SO_REUSEADDR, 
        (char*)&reuseAddr, 
        sizeof(reuseAddr));
}

INLINE int SockSetBlocking(
    Sock sock,
    int blocking)
{
#if defined(_MSC_VER)
    int flag = blocking ? 0 : 1;
    return ioctlsocket(sock, FIONBIO, &flag);
#else
    return __SetFDFlag(sock, O_NONBLOCK, blocking);
#endif
}

INLINE int SockGetSndBufSize(Sock sock)
{
    int size = 0;
    socklen_t len = sizeof(size);

    if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&size, &len) != 0)
        return -1;

    return size;
}

INLINE int SockGetRcvBufSize(Sock sock)
{
    int size = 0;
    socklen_t len = sizeof(size);

    if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&size, &len) != 0)
        return -1;

    return size;
}

INLINE int SockSetNoDelay(
    Sock sock,
    int noDelay)
{
    return setsockopt(
        sock,
        IPPROTO_TCP, 
        TCP_NODELAY, 
        (char*)&noDelay, 
        sizeof(noDelay));
}

INLINE int SockGetNoDelay(Sock sock)
{
    int noDelay = 0;
    socklen_t len = sizeof(noDelay);

    if (getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&noDelay, &len) != 0)
        return -1;

    return noDelay;
}

Sock SockCreateListener(
    const Addr* addr);

ssize_t SockRead(
    Sock sock,
    void* data,
    size_t size);

ssize_t SockWrite(
    Sock sock,
    const void* data,
    size_t size);

ssize_t SockReadN(
    Sock sock,
    void* data,
    size_t size);

ssize_t SockWriteN(
    Sock sock,
    const void* data,
    size_t size);

#if defined(ENABLE_LOCAL_AUTH)
int SockGetPeerCreds(
    Sock sock,
    uid_t* uid,
    gid_t* gid);
#endif /* defined(ENABLE_LOCAL_AUTH) */

#if defined(ENABLE_SOCKTRACE)
unsigned long long SockGetBytesSent();
unsigned long long SockGetBytesRecv();
#endif /* ENABLE_SOCKTRACE */

#endif /* _sock_h */
