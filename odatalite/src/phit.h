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
#ifndef _phit_phit_h
#define _phit_phit_h

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
**==============================================================================
**
** PHIT_EXPORT
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define PHIT_EXPORT __declspec(dllexport)
# define PHIT_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
# define PHIT_EXPORT __attribute__((visibility("default")))
# define PHIT_IMPORT /* empty */
#elif defined(sun)
# define PHIT_EXPORT __global
# define PHIT_IMPORT /* empty */
#else
# define PHIT_EXPORT
# define PHIT_IMPORT
#endif

/*
**==============================================================================
**
** PHIT_INLINE
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define PHIT_INLINE static __inline
#elif defined(__GNUC__)
# define PHIT_INLINE static __inline
#elif defined(sun)
# define PHIT_INLINE static inline
#elif defined(__PPC)
# define PHIT_INLINE __inline__
#else
# define PHIT_INLINE static __inline
#endif

/*
**==============================================================================
**
** PHIT_ARRAY_SIZE()
**
**==============================================================================
*/

#define PHIT_ARRAY_SIZE(ARR) (sizeof(ARR) / sizeof(ARR[0]))

/*
**==============================================================================
**
** PHIT_Method
**
**==============================================================================
*/

typedef enum _PHIT_Method
{
    PHIT_METHOD_GET,
    PHIT_METHOD_PUT,
    PHIT_METHOD_PATCH,
    PHIT_METHOD_DELETE,
    PHIT_METHOD_POST,
    PHIT_METHOD_MPOST,
    PHIT_METHOD_HEAD,
    PHIT_METHOD_TRACE,
    PHIT_METHOD_CONNECT,
    PHIT_METHOD_OPTIONS
}
PHIT_Method;

/*
**==============================================================================
**
** PHIT_StatusCode
**
**==============================================================================
*/

typedef enum _PHIT_StatusCode
{
    /* Informational */
    PHIT_STATUSCODE_100_CONTINUE = 100,
    PHIT_STATUSCODE_101_SWITCHING_PROTOCOLS = 101,

    /* Successful */
    PHIT_STATUSCODE_200_OK = 200,
    PHIT_STATUSCODE_201_CREATED = 201,
    PHIT_STATUSCODE_202_ACCEPTED = 202,
    PHIT_STATUSCODE_203_NON_AUTHORITATIVE_INFORMATION = 203,
    PHIT_STATUSCODE_204_NO_CONTENT = 204,
    PHIT_STATUSCODE_205_RESET_CONTENT = 205,
    PHIT_STATUSCODE_206_PARTIAL_CONTENT = 206,

    /* Redirection */
    PHIT_STATUSCODE_300_MULTIPLE_CHOICES = 300,
    PHIT_STATUSCODE_301_MOVED_PERMANENTLY = 301,
    PHIT_STATUSCODE_302_FOUND = 302,
    PHIT_STATUSCODE_303_SEE_OTHER = 303,
    PHIT_STATUSCODE_304_NOT_MODIFIED = 304,
    PHIT_STATUSCODE_305_USE_PROXY = 305,
    PHIT_STATUSCODE_306_UNUSED = 306,
    PHIT_STATUSCODE_307_TEMPORARY_REDIRECT = 307,

    /* Client Error */
    PHIT_STATUSCODE_400_BAD_REQUEST = 400,
    PHIT_STATUSCODE_401_UNAUTHORIZED = 401,
    PHIT_STATUSCODE_402_PAYMENT_REQUIRED = 402,
    PHIT_STATUSCODE_403_FORBIDDEN = 403,
    PHIT_STATUSCODE_404_NOT_FOUND = 404,
    PHIT_STATUSCODE_405_METHOD_NOT_ALLOWED = 405,
    PHIT_STATUSCODE_406_NOT_ACCEPTABLE = 406,
    PHIT_STATUSCODE_407_PROXY_AUTHENTICATION_REQUIRED = 407,
    PHIT_STATUSCODE_408_REQUEST_TIMEOUT = 408,
    PHIT_STATUSCODE_409_CONFLICT = 409,
    PHIT_STATUSCODE_410_GONE = 410,
    PHIT_STATUSCODE_411_LENGTH_REQUIRED = 411,
    PHIT_STATUSCODE_412_PRECONDITION_FAILED = 412,
    PHIT_STATUSCODE_413_REQUEST_ENTITY_TOO_LARGE = 413,
    PHIT_STATUSCODE_414_REQUEST_URI_TOO_LONG = 414,
    PHIT_STATUSCODE_415_UNSUPPORTED_MEDIA_TYPE = 415,
    PHIT_STATUSCODE_416_REQUEST_RANGE_NOT_SATISFIABLE = 416,
    PHIT_STATUSCODE_417_EXPECTATION_FAILED = 417,

    /* Server Error */
    PHIT_STATUSCODE_500_INTERNAL_SERVER_ERROR = 500,
    PHIT_STATUSCODE_501_NOT_IMPLEMENTED = 501,
    PHIT_STATUSCODE_502_BAD_GATEWAY = 502,
    PHIT_STATUSCODE_503_SERVICE_UNAVAILABLE = 503,
    PHIT_STATUSCODE_504_GATEWAY_TIMEOUT = 504,
    PHIT_STATUSCODE_505_HTTP_VERSION_NOT_SUPPORTED = 505
}
PHIT_StatusCode;

/*
**==============================================================================
**
** Status messages
**
**==============================================================================
*/

#define PHIT_STATUSMSG_100_CONTINUE \
    "Continue"

#define PHIT_STATUSMSG_101_SWITCHING_PROTOCOLS \
    "Switching Protocols"

#define PHIT_STATUSMSG_200_OK \
    "OK"

#define PHIT_STATUSMSG_201_CREATED \
    "Created"

#define PHIT_STATUSMSG_202_ACCEPTED \
    "Accepted"

#define PHIT_STATUSMSG_203_NON_AUTHORITATIVE_INFORMATION \
    "Non-Authoritative Information"

#define PHIT_STATUSMSG_204_NO_CONTENT \
    "No Content"

#define PHIT_STATUSMSG_205_RESET_CONTENT \
    "Reset Content"

#define PHIT_STATUSMSG_206_PARTIAL_CONTENT \
    "Partial Content"

#define PHIT_STATUSMSG_300_MULTIPLE_CHOICES \
    "Multiple Choices"

#define PHIT_STATUSMSG_301_MOVED_PERMANENTLY \
    "Moved Permanently"

#define PHIT_STATUSMSG_302_FOUND \
    "Found"

#define PHIT_STATUSMSG_303_SEE_OTHER \
    "See Other"

#define PHIT_STATUSMSG_304_NOT_MODIFIED \
    "Not Modified"

#define PHIT_STATUSMSG_305_USE_PROXY \
    "Use Proxy"

#define PHIT_STATUSMSG_306_UNUSED \
    "Unused"

#define PHIT_STATUSMSG_307_TEMPORARY_REDIRECT \
    "Temporary Redirect"

#define PHIT_STATUSMSG_400_BAD_REQUEST \
    "Bad Request"

#define PHIT_STATUSMSG_401_UNAUTHORIZED \
    "Unauthorized"

#define PHIT_STATUSMSG_402_PAYMENT_REQUIRED \
    "Payment Required"

#define PHIT_STATUSMSG_403_FORBIDDEN \
    "Forbidden"

#define PHIT_STATUSMSG_404_NOT_FOUND \
    "Not Found"

#define PHIT_STATUSMSG_405_METHOD_NOT_ALLOWED \
    "Method Not Allowed"

#define PHIT_STATUSMSG_406_NOT_ACCEPTABLE \
    "Not Acceptable"

#define PHIT_STATUSMSG_407_PROXY_AUTHENTICATION_REQUIRED \
    "Proxy Authentication Required"

#define PHIT_STATUSMSG_408_REQUEST_TIMEOUT \
    "Request Time-out"

#define PHIT_STATUSMSG_409_CONFLICT \
    "Conflict"

#define PHIT_STATUSMSG_410_GONE \
    "Gone"

#define PHIT_STATUSMSG_411_LENGTH_REQUIRED \
    "Length Required"

#define PHIT_STATUSMSG_412_PRECONDITION_FAILED \
    "Precondition Failed"

#define PHIT_STATUSMSG_413_REQUEST_ENTITY_TOO_LARGE \
    "Request Entity Too Large"

#define PHIT_STATUSMSG_414_REQUEST_URI_TOO_LONG \
    "Request-URI Too Large"

#define PHIT_STATUSMSG_415_UNSUPPORTED_MEDIA_TYPE \
    "Unsupported Media Type"

#define PHIT_STATUSMSG_416_REQUEST_RANGE_NOT_SATISFIABLE \
    "Requested range not satisfiable"

#define PHIT_STATUSMSG_417_EXPECTATION_FAILED \
    "Expectation Failed"

#define PHIT_STATUSMSG_500_INTERNAL_SERVER_ERROR \
    "Internal Server Error"

#define PHIT_STATUSMSG_501_NOT_IMPLEMENTED \
    "Not Implemented"

#define PHIT_STATUSMSG_502_BAD_GATEWAY \
    "Bad Gateway"

#define PHIT_STATUSMSG_503_SERVICE_UNAVAILABLE \
    "Service Unavailable"

#define PHIT_STATUSMSG_504_GATEWAY_TIMEOUT \
    "Gateway Time-out"

#define PHIT_STATUSMSG_505_HTTP_VERSION_NOT_SUPPORTED \
    "HTTP Version not supported"

/*
**==============================================================================
**
** PHIT_Headers
**
**==============================================================================
*/

typedef struct _PHIT_HTTPParameter
{
    const char* name;
    const char* value;
}
PHIT_HTTPParameter;

typedef struct _PHIT_ContentTypeHeader
{
    unsigned char found;
    const char* mediaType;
    const char* mediaSubType;

    const PHIT_HTTPParameter* parameters;
    size_t nparameters;
}
PHIT_ContentTypeHeader;

typedef struct _PHIT_ContentLengthHeader
{
    unsigned char found;
    unsigned int value;
}
PHIT_ContentLengthHeader;

typedef struct _PHIT_UserAgentHeader
{
    unsigned char found;
    const char* value;
}
PHIT_UserAgentHeader;

typedef struct _PHIT_HostHeader
{
    unsigned char found;
    const char* value;
}
PHIT_HostHeader;

typedef enum _PHIT_AuthorizationType
{
    PHIT_AUTHORIZATIONTYPE_NONE,
    PHIT_AUTHORIZATIONTYPE_BASIC,
    PHIT_AUTHORIZATIONTYPE_DIGEST,
    PHIT_AUTHORIZATIONTYPE_UNKNOWN
}
PHIT_AuthorizationType;

typedef struct _PHIT_AuthorizationHeader
{
    unsigned char found;
    PHIT_AuthorizationType type;
    const char* credentials;
}
PHIT_AuthorizationHeader;

typedef struct _PHIT_TEHeader
{
    unsigned char found;
    unsigned char trailers;
    unsigned char chunked;
}
PHIT_TEHeader;

typedef struct _PHIT_TransferEncodingHeader
{
    unsigned char found;
    unsigned char chunked;
}
PHIT_TransferEncodingHeader;

typedef struct _PHIT_TrailerHeader
{
    unsigned char found;
    const char* const* data;
    size_t size;
}
PHIT_TrailerHeader;

typedef struct _PHIT_Header
{
    const char* name;
    const char* value;
}
PHIT_Header;

typedef struct _PHIT_Headers
{
    /* Content-Type: */
    PHIT_ContentTypeHeader contentType;

    /* Content-Length: */
    PHIT_ContentLengthHeader contentLength;

    /* User-Agent: */
    PHIT_UserAgentHeader userAgent;

    /* Host: */
    PHIT_HostHeader host;

    /* Authorization: */
    PHIT_AuthorizationHeader authorization;

    /* TE: */
    PHIT_TEHeader te;

    /* Transfer-Encoding: */
    PHIT_TransferEncodingHeader transferEncoding;

    /* Trailer */
    PHIT_TrailerHeader trailer;

    /* Other headers */
    const PHIT_Header* headers;
    size_t nheaders;
}
PHIT_Headers;

/*
**==============================================================================
**
** PHIT_Role
**
**==============================================================================
*/

typedef enum _PHIT_Role
{
    PHIT_ROLE_NONE,
    PHIT_ROLE_GUEST,
    PHIT_ROLE_OPERATOR,
    PHIT_ROLE_ADMIN
}
PHIT_Role;

/*
**==============================================================================
**
** PHIT_Context
**
**==============================================================================
*/

#define PHIT_CONTEXT_MAGIC 0x6b053d30

typedef struct _PHIT_Context PHIT_Context;

struct _PHIT_Context
{
    /* Magic number */
    unsigned int magic;

    /* Post HTTP status line */
    void (*PostStatusLine)(
        PHIT_Context* context,
        PHIT_StatusCode statusCode,
        const char* statusMsg);

    /* Post HTTP header field */
    void (*PostHeader)(
        PHIT_Context* context,
        const char* name,
        const char* value);

    /* Post HTTP header field */
    void (*PostHeaderUL)(
        PHIT_Context* context,
        const char* name,
        unsigned long value);

    /* Post HTTP header field */
    void (*PostTrailerField)(
        PHIT_Context* context,
        const char* name,
        const char* value);

    /* Post end of headers */
    void (*PostEOH)(
        PHIT_Context* context);

    /* Post HTTP content */
    void (*PostContent)(
        PHIT_Context* context,
        const char* data,
        size_t size);

    /* Post end of content */
    void (*PostEOC)(
        PHIT_Context* context);

    /* Post an error message */
    void (*PostError)(
        PHIT_Context* context,
        PHIT_StatusCode statusCode,
        const char* statusMsg,
        const char* detail);

    /* Set client data */
    void* (*SetPluginData)(
        PHIT_Context* context,
        void* pluginData);

    /* Get client data */
    void* (*GetPluginData)(
        PHIT_Context* context);

    /* Get option */
    int (*GetOption)(
        const PHIT_Context* context,
        int option,
        void* value,
        size_t valueSize);
};

PHIT_INLINE void PHIT_Context_PostStatusLine(
    PHIT_Context* context,
    PHIT_StatusCode statusCode,
    const char* statusMsg)
{
    context->PostStatusLine(context, statusCode, statusMsg);
}

PHIT_INLINE void PHIT_Context_PostHeader(
    PHIT_Context* context,
    const char* name,
    const char* value)
{
    context->PostHeader(context, name, value);
}

PHIT_INLINE void PHIT_Context_PostHeaderUL(
    PHIT_Context* context,
    const char* name,
    unsigned long value)
{
    context->PostHeaderUL(context, name, value);
}

PHIT_INLINE void PHIT_Context_PostTrailerField(
    PHIT_Context* context,
    const char* name,
    const char* value)
{
    context->PostTrailerField(context, name, value);
}

PHIT_INLINE void PHIT_Context_PostEOH(
    PHIT_Context* context)
{
    context->PostEOH(context);
}

PHIT_INLINE void PHIT_Context_PostContent(
    PHIT_Context* context,
    const char* data,
    size_t size)
{
    context->PostContent(context, data, size);
}

PHIT_INLINE void PHIT_Context_PostEOC(
    PHIT_Context* context)
{
    context->PostEOC(context);
}

PHIT_INLINE void PHIT_Context_PostError(
    PHIT_Context* context,
    PHIT_StatusCode statusCode,
    const char* statusMsg,
    const char* detail)
{
    context->PostError(context, statusCode, statusMsg, detail);
}

PHIT_INLINE void* PHIT_Context_SetPluginData(
    PHIT_Context* context,
    void* pluginData)
{
    return context->SetPluginData(context, pluginData);
}

PHIT_INLINE void* PHIT_Context_GetPluginData(
    PHIT_Context* context)
{
    return context->GetPluginData(context);
}

PHIT_INLINE int PHIT_Context_GetOption(
    const PHIT_Context* context,
    int option,
    void* value,
    size_t valueSize)
{
    return context->GetOption(context, option, value, valueSize);
}

/*
**==============================================================================
**
** Options supported by PHIT_Context_GetOption()
**
**==============================================================================
*/

#define PHIT_CONTEXT_OPTION_ROLE 1 /* PHIT_Role */

/*
**==============================================================================
**
** PHIT_Plugin
**
**==============================================================================
*/

typedef struct _PHIT_Plugin PHIT_Plugin;

struct _PHIT_Plugin
{
    void (*Load)(
        PHIT_Plugin* plugin);

    void (*Unload)(
        PHIT_Plugin* plugin);

    void (*HandleRequest)(
        PHIT_Plugin* plugin,
        PHIT_Context* context,
        PHIT_Method method,
        const char* requestURI,
        const PHIT_Headers* headers,
        const char* content,
        size_t contentLength);

    void (*HandlePull)(
        PHIT_Plugin* plugin,
        PHIT_Context* context);
};

/*
**==============================================================================
**
** PHIT_MainProc
**
**==============================================================================
*/

typedef PHIT_Plugin* (*PHIT_MainProc)();

#endif /* _phit_phit_h */
