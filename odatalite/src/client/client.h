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
#ifndef _phit_client_h
#define _phit_client_h

#include <stddef.h>
#include <base/auth.h>
#include <base/http.h>
#include <base/selector.h>

typedef struct _Client Client;

typedef void (*ClientBeginCallback)(
    Client* self,
    void* callbackData);

typedef void (*ClientErrorCallback)(
    Client* self,
    const char* message,
    void* callbackData);

typedef void (*ClientFoundEndOfHeadersCallback)(
    Client* self, 
    const char* headers, 
    size_t headersLength,
    void* callbackData);

typedef void (*ClientHeadersCallback)(
    Client* self,
    unsigned long statusCode,
    const char* statusMsg,
    PHIT_Headers* header,
    void* callbackData);

typedef void (*ClientContentCallback)(
    Client* self, 
    const char* content, 
    size_t contentLength,
    void* callbackData);

typedef void (*ClientTrailersCallback)(
    Client* self,
    PHIT_Headers* trailers,
    void* callbackData);

typedef void (*ClientEndCallback)(
    Client* self,
    void* callbackData);

struct _Client
{
    Handler base;
    Selector* selector;
    Buf in;
    Buf out;
    ClientBeginCallback beginCallback;
    ClientErrorCallback errorCallback;
    ClientFoundEndOfHeadersCallback foundEndOfHeadersCallback;
    ClientHeadersCallback headersCallback;
    ClientContentCallback contentCallback;
    ClientTrailersCallback trailersCallback;
    ClientEndCallback endCallback;
    void* callbackData;

    HTTPResponse httpResponse;
    HTTPTrailers httpTrailers;
    HTTPState httpState;

    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
};

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
    void* callbackData);

void ClientDelete(
    Client* self);

int ClientPostRequest(
    Client* self,
    const char* request,
    size_t requestSize);

/* Set to non-zero to get client dumps */
extern int clientDump;

#endif /* _phit_client_h */

