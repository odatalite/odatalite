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
#include "httpstatuscodes.h"
#include <common.h>

static unsigned short _indices[] =
{
    PHIT_STATUSCODE_100_CONTINUE,
    PHIT_STATUSCODE_101_SWITCHING_PROTOCOLS,
    PHIT_STATUSCODE_200_OK,
    PHIT_STATUSCODE_201_CREATED,
    PHIT_STATUSCODE_202_ACCEPTED,
    PHIT_STATUSCODE_203_NON_AUTHORITATIVE_INFORMATION,
    PHIT_STATUSCODE_204_NO_CONTENT,
    PHIT_STATUSCODE_205_RESET_CONTENT,
    PHIT_STATUSCODE_206_PARTIAL_CONTENT,
    PHIT_STATUSCODE_300_MULTIPLE_CHOICES,
    PHIT_STATUSCODE_301_MOVED_PERMANENTLY,
    PHIT_STATUSCODE_302_FOUND,
    PHIT_STATUSCODE_303_SEE_OTHER,
    PHIT_STATUSCODE_304_NOT_MODIFIED,
    PHIT_STATUSCODE_305_USE_PROXY,
    PHIT_STATUSCODE_306_UNUSED,
    PHIT_STATUSCODE_307_TEMPORARY_REDIRECT,
    PHIT_STATUSCODE_400_BAD_REQUEST,
    PHIT_STATUSCODE_401_UNAUTHORIZED,
    PHIT_STATUSCODE_402_PAYMENT_REQUIRED,
    PHIT_STATUSCODE_403_FORBIDDEN,
    PHIT_STATUSCODE_404_NOT_FOUND,
    PHIT_STATUSCODE_405_METHOD_NOT_ALLOWED,
    PHIT_STATUSCODE_406_NOT_ACCEPTABLE,
    PHIT_STATUSCODE_407_PROXY_AUTHENTICATION_REQUIRED,
    PHIT_STATUSCODE_408_REQUEST_TIMEOUT,
    PHIT_STATUSCODE_409_CONFLICT,
    PHIT_STATUSCODE_410_GONE,
    PHIT_STATUSCODE_411_LENGTH_REQUIRED,
    PHIT_STATUSCODE_412_PRECONDITION_FAILED,
    PHIT_STATUSCODE_413_REQUEST_ENTITY_TOO_LARGE,
    PHIT_STATUSCODE_414_REQUEST_URI_TOO_LONG,
    PHIT_STATUSCODE_415_UNSUPPORTED_MEDIA_TYPE,
    PHIT_STATUSCODE_416_REQUEST_RANGE_NOT_SATISFIABLE,
    PHIT_STATUSCODE_417_EXPECTATION_FAILED,
    PHIT_STATUSCODE_500_INTERNAL_SERVER_ERROR,
    PHIT_STATUSCODE_501_NOT_IMPLEMENTED,
    PHIT_STATUSCODE_502_BAD_GATEWAY,
    PHIT_STATUSCODE_503_SERVICE_UNAVAILABLE,
    PHIT_STATUSCODE_504_GATEWAY_TIMEOUT,
    PHIT_STATUSCODE_505_HTTP_VERSION_NOT_SUPPORTED
};

const char* _messages[] =
{
    "Continue",
    "Switching Protocols",
    "OK",
    "Created",
    "Accepted",
    "Non-Authoritative Information",
    "No Content",
    "Reset Content",
    "Partial Content",
    "Multiple Choices",
    "Moved Permanently",
    "Found",
    "See Other",
    "Not Modified",
    "Use Proxy",
    "Unused",
    "Temporary Redirect",
    "Bad Request",
    "Unauthorized",
    "Payment Required",
    "Forbidden",
    "Not Found",
    "Method Not Allowed",
    "Not Acceptable",
    "Proxy Authentication Required",
    "Request Time-out",
    "Conflict",
    "Gone",
    "Length Required",
    "Precondition Failed",
    "Request Entity Too Large",
    "Request-URI Too Large",
    "Unsupported Media Type",
    "Requested range not satisfiable",
    "Expectation Failed",
    "Internal Server Error",
    "Not Implemented",
    "Bad Gateway",
    "Service Unavailable",
    "Gateway Time-out",
    "HTTP Version not supported"
};

const char* GetHTTPStatusMessage(unsigned long statusCode)
{
    size_t i;

    for (i = 0; i < ARRSIZE(_indices); i++)
    {
        if (statusCode == _indices[i])
            return _messages[i];
    }

    return "unknown";
}
