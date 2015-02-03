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
#ifndef _phit_base_http_h
#define _phit_base_http_h

#include "common.h"

#if defined(HAVE_POSIX)
# include <unistd.h>
#endif

#include "buf.h"
#include "phit.h"
#include "phit.h"
#include "str.h"

#define CHUNK_PREFIX_NULL "00000000\r\n"
#define MIN_CHUNK_PREFIX_SIZE STRN("0\r\n")
#define MAX_CHUNK_PREFIX_SIZE STRN("00000000\r\n")
#define CHUNK_SUFFIX_SIZE STRN("\r\n")

/*
    M-POST /XYZ HTTP/1.1<CR><LF>
    Content-Type: text/plain; charset=utf-8<CR><LF>
    Content-Length: NNNN<CR><LF>
    Connection: Keep-Alive<CR><LF>
    TE: trailers, chunked<CR><LF>
    <CR><LF>

    User-Agent: PHIT<CR><LF>
    Host: <HOST>:<PORT><CR><LF>
    Authorization: Basic ???????????????????????????????<CR><LF>
    <CR><LF>

    HTTP/1.1 200 OK<CR><LF>
    Transfer-Encoding: chunked<CR><LF>
    Content-Type: application/soap+xml;charset=UTF-8<CR><LF>
    <CR><LF>

    M-POST / HTTP/1.1<CR><LF>
    Content-Length: NNN<CR><LF>
    Connection: Keep-Alive<CR><LF> 
    Host: host<CR><LF>
    <CR><LF>

    HTTP/1.1 501 Not Implemented<CR><LF>
    <CR><LF>
*/

typedef enum _HTTPState
{
    HTTPSTATE_WAITING_FOR_HEADER,
    HTTPSTATE_WAITING_FOR_CONTENT,
    HTTPSTATE_WAITING_FOR_TRAILER,
    HTTPSTATE_SENDING_RESPONSE_HEADER
}
HTTPState;


#define HEADERS_BUFSIZE 16
#define TRAILERS_BUFSIZE 8

typedef struct _HTTPBuf
{
    PHIT_Header headersBuf[HEADERS_BUFSIZE];
    size_t headersBufSize;

    const char* trailersBuf[TRAILERS_BUFSIZE];
    size_t trailersBufSize;

    PHIT_HTTPParameter contentTypeParameters[8];
}
HTTPBuf;

int PHIT_HeadersParse(
    PHIT_Headers* self,
    HTTPBuf* buf,
    char* data,
    size_t size);

void PHIT_HeadersDump(
    const PHIT_Headers* self,
    size_t n);

const char* PHIT_HeadersFind(
    const PHIT_Headers* self,
    const char* name,
    size_t len);

typedef struct _HTTPRequest
{
    PHIT_Method method;

    const char* uri;

    PHIT_Headers headers;

    HTTPBuf buf;

#if 0
    char* phitCommand;
#endif

    /* Basic auth results */
    char* username;
    char* password;
}
HTTPRequest;

typedef struct _HTTPResponse
{
    unsigned long statusCode;
    char* statusMsg;

    PHIT_Headers headers;

    HTTPBuf buf;
}
HTTPResponse;

typedef struct _HTTPTrailers
{
    PHIT_Headers headers;

    HTTPBuf buf;
}
HTTPTrailers;

const char* ParseHTTPMethod(
    const char* str,
    PHIT_Method* method);

int HTTPRequestParse(
    HTTPRequest* self,
    char* data,
    size_t size);

int HTTPResponseParse(
    HTTPResponse* self,
    char* data,
    size_t size);

int HTTPTrailersParse(
    HTTPTrailers* self,
    size_t numTrailers,
    char* data,
    size_t size);

void HTTPRequestDump(
    const HTTPRequest* self);

void HTTPResponseDump(
    const HTTPResponse* self);

#if 0
int HTTPFormatHTMLWelcomeMessage(Buf* out);
#endif

#if 0
int HTTPFormatNotImplementedResponse(
    Buf* out);
#endif

int HTTPFormatRequest(
    Buf* out,
    const char* command,
    const char* username,
    const char* password,
    const char* content,
    size_t contentLength);

#if 0
#define __HTTP_CHUNKED_RESPONSE_HEADER \
    "HTTP/1.1 200 OK\r\n" \
    "Content-Type: text/plain\r\n" \
    "Transfer-Encoding: chunked\r\n" \
    "Trailer: PHIT-Status\r\n" \
    "\r\n"
#endif

#if 0
INLINE int HTTPFormatChunkedResponseHeader(
    Buf* out)
{
    return BufCat(out, STRLIT(__HTTP_CHUNKED_RESPONSE_HEADER));
}
#endif

#define __HTTP_ACCESS_DENIED_RESPONSE \
    "HTTP/1.1 401 Access Denied\r\n" \
    "WWW-Authenticate: Basic realm=\"PHIT\"\r\n" \
    "Content-Length: 0\r\n" \
    "\r\n"

INLINE void HTTPFormatAccessDeniedResponse(
    Buf* out)
{
    BufCat(out, STRLIT(__HTTP_ACCESS_DENIED_RESPONSE));
}

#define __HTTP_NOT_IMPLEMENTED_RESPONSE \
    "HTTP/1.1 501 Not Implemented\r\n" \
    "Content-Length: 0\r\n" \
    "\r\n"

INLINE void HTTPFormatNotImplementedResponse(
    Buf* out)
{
    BufCat(out, STRLIT(__HTTP_NOT_IMPLEMENTED_RESPONSE));
}

/* Return size of headers section (or 0 if more data is needed) */
ssize_t HTTPHaveCompleteHeaders(
    char* data,
    size_t size);

/* Return size of headers section (or 0 if more data is needed) */
ssize_t HTTPHaveCompleteTrailers(
    char* data,
    size_t size,
    size_t numTrailers);

INLINE void HTTPFormatNullChunkPrefix(
    Buf* out)
{
    BufCat(out, STRLIT("00000000\r\n"));
}

INLINE void HTTPFormatChunkSuffix(
    Buf* out)
{
    BufCatCh2(out, '\r', '\n');
}

int HTTPFormatChunk(
    Buf* out,
    const char* data,
    size_t size);

INLINE void HTTPFormatNullChunk(
    Buf* out)
{
    /* Write the null chunk: "00000000<CR><LF>" */
    BufCat(out, STRLIT(CHUNK_PREFIX_NULL));
}

/* Return 1 if complete chunk found; 0 if more data needed; -1 on error */
int HTTPHaveCompleteChunk(
    char* data,
    size_t size,
    size_t* chunkOffsetOut,
    size_t* chunkSizeOut);

INLINE ssize_t HTTPGetMinChunkPrefixSize()
{
    return MIN_CHUNK_PREFIX_SIZE;
}

INLINE ssize_t HTTPGetChunkSuffixSize()
{
    return CHUNK_SUFFIX_SIZE;
}

extern const char* __HTTPMethodNames[10];

INLINE const char* HTTPMethodNameOf(PHIT_Method method)
{
    return __HTTPMethodNames[method];
}

#endif /* _phit_base_http_h */
