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
#include "post.h"
#include <base/buf.h>
#include <odata/result.h>
#include <odata/scope.h>
#include <base/str.h>
#include <odata/odatamacros.h>

const StrLit __metadataV3[] = 
{
    { STRLIT("nometadata") },  
    { STRLIT("minimalmetadata") }, 
    { STRLIT("fullmetadata") }
};

const StrLit __metadataV4[] = 
{ 
    { STRLIT("none") }, 
    { STRLIT("minimal") }, 
    { STRLIT("full") }
};

static void _PostHTTPContentTypeField(
    PHIT_Context* context,
    const char* contentType)
{
    const Scope* scope = (const Scope*)PHIT_Context_GetPluginData(context);
    char buf[128];

    Strlcpy2(buf, contentType, ";", sizeof(buf));

    if (scope)
    {
        if (scope->version == OL_VERSION_4_0)
        {
            Strlcat3(buf, 
                "odata.metadata=", 
                __metadataV4[scope->metadataType].str,
                ";",
                sizeof(buf));
        }
        else if (scope->version == OL_VERSION_3_0)
        {
            Strlcat3(buf, 
                "odata=", 
                __metadataV3[scope->metadataType].str,
                ";",
                sizeof(buf));
        }
    }

    Strlcat(buf, "charset=utf-8", sizeof(buf));

    PHIT_Context_PostHeader(context, "Content-Type", buf);
}

void FormatErrorMessage(
    Buf* out, 
    OL_Result result,
    PHIT_StatusCode* statusCode,
    const char** statusMsg,
    const char* format,
    va_list ap)
{
    switch (result)
    {
        case OL_Result_Failed:
        case OL_Result_BadParameter:
        case OL_Result_SyntaxError:
        case OL_Result_EndOfFile:
        case OL_Result_TypeMismatch:
        case OL_Result_AlreadyExists:
            *statusCode = PHIT_STATUSCODE_400_BAD_REQUEST;
            *statusMsg = PHIT_STATUSMSG_400_BAD_REQUEST;
            break;
        case OL_Result_NotFound:
            *statusCode = PHIT_STATUSCODE_404_NOT_FOUND;
            *statusMsg = PHIT_STATUSMSG_404_NOT_FOUND;
            break;
        case OL_Result_NotSupported:
            *statusCode = PHIT_STATUSCODE_501_NOT_IMPLEMENTED;
            *statusMsg = PHIT_STATUSMSG_501_NOT_IMPLEMENTED;
            break;
        case OL_Result_OutOfBounds:
        case OL_Result_UnknownType:
        case OL_Result_OutOfMemory:
        case OL_Result_InternalError:
        default:
            *statusCode = PHIT_STATUSCODE_500_INTERNAL_SERVER_ERROR;
            *statusMsg = PHIT_STATUSMSG_500_INTERNAL_SERVER_ERROR;
            break;
    }

#   define LF "\n"

    static const char FORMAT[] =
        "{" LF
        "  \"error\": {" LF
        "    \"code\": \"%u\"," LF
        "    \"message\": {" LF
        "      \"lang\": \"en-us\"," LF
        "      \"value\": \"%s: %s\"" LF
        "    }" LF
        "  }" LF
        "}" LF
        ;

    if (format)
    {
        Buf detail = BUF_INITIALIZER;
        BufFmtV(&detail, format, ap);
        BufCatCh(&detail, '\0');
        BufFmt(out, FORMAT, result, ResultToString(result), detail.data);
        BufDestroy(&detail);
    }
    else
    {
        BufFmt(out, FORMAT, result, ResultToString(result), "");
    }
}

void PostErrorV(
    PHIT_Context* context,
    OL_Result result, 
    const char* format, 
    va_list ap)
{
    Buf buf = BUF_INITIALIZER;
    PHIT_StatusCode statusCode;
    const char* statusMsg;

    FormatErrorMessage(&buf, result, &statusCode, &statusMsg, format, ap);
    PostStatusLineAndHeaders(context, statusCode, statusMsg, 
        "application/json");
    PHIT_Context_PostContent(context, buf.data, buf.size);
    BufDestroy(&buf);
    PHIT_Context_PostEOC(context);
}

OL_PRINTF_FORMAT(3, 4)
void PostError(
    PHIT_Context* context,
    OL_Result result, 
    const char* format,
    ...)
{
    if (format)
    {
        va_list ap;
        va_start(ap, format);
        PostErrorV(context, result, format, ap);
        va_end(ap);
    }
    else
    {
        PostErrorV(context, result, NULL, NULL);
    }
}

void PostStatusLineAndHeaders(
    PHIT_Context* context, 
    PHIT_StatusCode statusCode,
    const char* statusMsg,
    const char* contextType)
{
    const Scope* scope = (const Scope*)PHIT_Context_GetPluginData(context);

    PHIT_Context_PostStatusLine(context, statusCode, statusMsg);

    if (statusCode != PHIT_STATUSCODE_204_NO_CONTENT)
    {
        _PostHTTPContentTypeField(context, contextType);

        if (scope)
        {
            if (scope->version == OL_VERSION_4_0)
                PHIT_Context_PostHeader(context, "OData-Version", "4.0");
            else if (scope->version == OL_VERSION_3_0)
                PHIT_Context_PostHeader(context, "DataServiceVersion", "3.0");
        }

        PHIT_Context_PostHeader(context, "Access-Control-Allow-Origin", "*");
        PHIT_Context_PostHeader(context, "Cache-Control", "no-cache");
    }

    PHIT_Context_PostEOH(context);
}

void PostCountResponse(
    PHIT_Context* context, 
    unsigned long count)
{
    char buf[ULongToStrBufSize];
    const char* data;
    size_t size;

    PostStatusLineAndHeaders(context, 
        PHIT_STATUSCODE_200_OK, PHIT_STATUSMSG_200_OK, "text/plain");

    data = ULongToStr(buf, count, &size);
    PHIT_Context_PostContent(context, data, size);
}
