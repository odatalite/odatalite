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
#define _GNU_SOURCE
#include "sock.h"
#include "path.h"
#include "cleanup.h"
#include "file.h"

#if defined(ENABLE_SOCKTRACE)

unsigned char __sockLog;
static FILE* _sendLog;
static FILE* _recvLog;
static int _logOpenFailed;

static unsigned long long _bytesSent;
static unsigned long long _bytesRecv;

unsigned long long SockGetBytesSent()
{
    return _bytesSent;
}

unsigned long long SockGetBytesRecv()
{
    return _bytesRecv;
}

static void _CleanupCallback(
    CleanupHandler* handler)
{
    SockLogClose();
}

static CleanupHandler _cleanupHandler;

static void _WriteLog(
    FILE** log,
    const char* path,
    const void* data, 
    size_t size)
{
    if (!*log)
    {
        if (_logOpenFailed)
            return;

        if (!(*log = Fopen(path, "wb")))
        {
            _logOpenFailed = 1;
            return;
        }

        if (!_cleanupHandler.callback)
        {
            _cleanupHandler.callback = _CleanupCallback;
            AddCleanupHandler(&_cleanupHandler);
        }
    }

    fwrite(data, 1, size, *log);
    fflush(*log);
}

void SockLogClose()
{
    if (_recvLog)
    {
        fclose(_recvLog);
        _recvLog = NULL;
    }

    if (_sendLog)
    {
        fclose(_sendLog);
        _sendLog = NULL;
    }

    _logOpenFailed = 0;
}

#endif /* defined(ENABLE_SOCKTRACE) */

#if defined(HAVE_POSIX)
int __SetFDFlag(
    int fd,
    int flag,
    int value)
{
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags == -1)
        return -1;

    if (value)
        flags &= ~flag;
    else
        flags |= flag;

    return fcntl(fd, F_SETFL, flags);
}
#endif /* defined(HAVE_POSIX) */

INLINE ssize_t _SockReadInline(
    Sock sock,
    void* data,
    size_t size,
    char buf[MAX_PATH_SIZE])
{
    int n;
#if defined(_MSC_VER)
    while ((n = recv(sock, data, (int)size, 0)) == -1 && errno == EINTR)
        ;
#else
    while ((n = read(sock, data, size)) == -1 && errno == EINTR)
        ;
#endif

#if defined(ENABLE_SOCKTRACE)
    if (n > 0)
    {
        if (__sockLog)
        {
            _WriteLog(&_recvLog, MakePath(ID_RECVLOG, buf), data, n);
        }
        _bytesRecv += n;
    }
#endif

    return (ssize_t)n;
}

INLINE ssize_t _SockWriteInline(
    Sock sock,
    const void* data,
    size_t size,
    char buf[MAX_PATH_SIZE])
{
    int n;
#if defined(_MSC_VER)
    while ((n = send(sock, data, (int)size, 0)) == -1 && errno == EINTR)
        ;
#else
    while ((n = write(sock, data, size)) == -1 && errno == EINTR)
        ;
#endif

#if defined(ENABLE_SOCKTRACE)
    if (n > 0)
    {
        if (__sockLog)
        {
            _WriteLog(&_sendLog, MakePath(ID_SENDLOG, buf), data, n);
        }
        _bytesSent += n;
    }
#endif

    return (ssize_t)n;
}

#if defined(INCLUDE_UNUSED)
ssize_t SockRead(
    Sock sock,
    void* data,
    size_t size)
{
    char buf[MAX_PATH_SIZE];
    return _SockReadInline(sock, data, size, buf);
}
#endif /* defined(INCLUDE_UNUSED) */

#if defined(INCLUDE_UNUSED)
ssize_t SockWrite(
    Sock sock,
    const void* data,
    size_t size)
{
    char buf[MAX_PATH_SIZE];
    return _SockWriteInline(sock, data, size, buf);
}
#endif /* defined(INCLUDE_UNUSED) */

ssize_t SockReadN(
    Sock sock,
    void* data,
    size_t size)
{
    size_t rem = size;
    size_t off = 0;
    char buf[MAX_PATH_SIZE];

    while (rem)
    {
        ssize_t n = _SockReadInline(sock, (char*)data + off, rem, buf);

#if 0
        printf("SockReadN(): %d %d %d\n", sock, (int)n, errno);
#endif

        if (n <= 0)
        {
            return off ? off : n;
        }

        rem -= n;
        off += n;
    }

    return (ssize_t)off;
}

ssize_t SockWriteN(
    Sock sock,
    const void* data,
    size_t size)
{
    size_t rem = size;
    size_t off = 0;
    char buf[MAX_PATH_SIZE];

    DEBUG_ASSERT(size < 1000000);

    while (rem)
    {
        ssize_t n = _SockWriteInline(sock, (char*)data + off, rem, buf);

        if (n <= 0)
        {
            return off ? off : -1;
        }

        rem -= n;
        off += n;
    }

    return (ssize_t)off;
}
