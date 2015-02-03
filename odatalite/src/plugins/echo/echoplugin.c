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
#include <phit.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <base/dump.h>
#include <base/html.h>

#define USE_TRAILERS

#define D(X)

typedef struct _PluginData
{
    char* content;
    size_t contentLength;
    size_t contentOffset;
    int chunked;
    int trailers;
}
PluginData;

static void _SendWebPage(
    PHIT_Plugin* plugin,
    PHIT_Context* context)
{
    const char DATA[] =
        "<h1>Echo Plugin</h1>"
        "<hr>"
        "<br>"
        "<form action=\"/echo\" method=\"post\">"
        "<b>Text:</b>"
        "<br>"
        "<input type=\"text\" name=\"text\" size=\"80\">"
        "<input type=\"submit\" value=\"Post\">"
        "</form>\n";

    const size_t SIZE = PHIT_ARRAY_SIZE(DATA) - 1;

    PHIT_Context_PostStatusLine(
        context, PHIT_STATUSCODE_200_OK, PHIT_STATUSMSG_200_OK);
    PHIT_Context_PostHeader(context, "Content-Type", "text/html");
    PHIT_Context_PostEOH(context);

    {
        Buf out = BUF_INITIALIZER;
        BufCatShareFile(&out, "preamble.html");
        PHIT_Context_PostContent(context, out.data, out.size);
        BufDestroy(&out);
    }

    PHIT_Context_PostContent(context, DATA, SIZE);

    {
        Buf out = BUF_INITIALIZER;
        BufCatShareFile(&out, "postamble.html");
        PHIT_Context_PostContent(context, out.data, out.size);
        BufDestroy(&out);
    }

    PHIT_Context_PostEOC(context);
}

static void _PostHTTPError(
    PHIT_Context* context,
    PHIT_StatusCode statusCode,
    const char* message)
{
    static const char S1[] = "<html><body><h2>";
    static size_t N1 = sizeof(S1) - 1;
    static const char S2[] = "</h2></body></html>";
    static size_t N2 = sizeof(S2) - 1;
    size_t len = strlen(message);

    PHIT_Context_PostStatusLine(
        context, PHIT_STATUSCODE_200_OK, PHIT_STATUSMSG_200_OK);
    PHIT_Context_PostHeader(context, "Content-Type", "text/html");
    PHIT_Context_PostHeaderUL(context, "Content-Length", N1 + len + N2);
    PHIT_Context_PostEOH(context);
    PHIT_Context_PostContent(context, S1, N1);
    PHIT_Context_PostContent(context, message, len);
    PHIT_Context_PostContent(context, S2, N2);
    PHIT_Context_PostEOC(context);
}

static void _Load(
    PHIT_Plugin* plugin)
{
    D( printf("=== Echo::Load()\n"); )
}

static void _Unload(
    PHIT_Plugin* plugin)
{
    D( printf("=== Echo::Unload()\n"); )
}

static void _HandleRequest(
    PHIT_Plugin* plugin,
    PHIT_Context* context,
    PHIT_Method method,
    const char* requestURI,
    const PHIT_Headers* headers,
    const char* content,
    size_t contentLength)
{
    PluginData* pluginData;

    D( printf("=== Echo::HandleRequest()\n"); )

    if (method == PHIT_METHOD_GET && strcmp(requestURI, "/echo/webpage") == 0)
    {
        _SendWebPage(plugin, context);
        return;
    }

    if (method != PHIT_METHOD_MPOST && method != PHIT_METHOD_POST)
    {
        _PostHTTPError(
            context, 
            PHIT_STATUSCODE_501_NOT_IMPLEMENTED,
            "This method is not implemented");
        return;
    }

    /* If chunked encoding not supported */
    if (!headers->te.found || !headers->te.chunked)
    {
        PHIT_Context_PostStatusLine(
            context, PHIT_STATUSCODE_200_OK, PHIT_STATUSMSG_200_OK);
        PHIT_Context_PostHeader(context, "Content-Type", 
            "text/plain; charset=utf-8");
        PHIT_Context_PostHeaderUL(context, "Content-Length", 
            contentLength);
        PHIT_Context_PostEOH(context);
        PHIT_Context_PostContent(context, content, contentLength);
        PHIT_Context_PostEOC(context);
        return;
    }

    /* Allocate the callback data */
    if (!(pluginData = (PluginData*)malloc(sizeof(PluginData))))
    {
        _PostHTTPError(
            context, 
            PHIT_STATUSCODE_500_INTERNAL_SERVER_ERROR,
            "malloc() failed");
        return;
    }

    /* Set PluginData.trailers */
    pluginData->trailers = headers->te.trailers;

    /* Copy the content into the plugin data */
    {
        char* p = (char*)malloc(contentLength);

        if (!p)
        {
            free(pluginData);
            _PostHTTPError(
                context, 
                PHIT_STATUSCODE_500_INTERNAL_SERVER_ERROR,
                "malloc() failed");
            return;
        }

        memcpy(p, content, contentLength);

        pluginData->content = p;
        pluginData->contentLength = contentLength;
        pluginData->contentOffset = 0;
        PHIT_Context_SetPluginData(context, pluginData);
    }

    /* Post stauts line and header fields */
    PHIT_Context_PostStatusLine(
        context, PHIT_STATUSCODE_200_OK, PHIT_STATUSMSG_200_OK);
    PHIT_Context_PostHeader(context, "Content-Type", 
        "text/plain; charset=utf-8");

#if defined(USE_TRAILERS)
    if (headers->te.trailers)
        PHIT_Context_PostHeader(context, "Trailer", "Trailer1,Trailer2");
#endif

    PHIT_Context_PostEOH(context);
}

static void _HandlePull(
    PHIT_Plugin* plugin,
    PHIT_Context* context)
{
    PluginData* pluginData;
    size_t rem;
    size_t len;

    D( printf("=== Echo::HandlePull()\n"); )

    pluginData = (PluginData*)PHIT_Context_GetPluginData(context);
    assert(pluginData);

    /* Calculate remaing content to be written */
    rem = pluginData->contentLength - pluginData->contentOffset;

    /* Calculate a random number of bytes to be written */
    if ((len = (rand() % 32) + 13) > rem)
        len = rem;

    /* Post the content */
    PHIT_Context_PostContent(
        context, 
        pluginData->content + pluginData->contentOffset,
        len);

    /* Update the offset */
    pluginData->contentOffset += len;

#if 0
    printf("LEN{%d}\n", (int)pluginData->contentLength);
    printf("OFF{%d}\n", (int)pluginData->contentOffset);
#endif

    /* If content is exhausted, post end-of-content */
    if (pluginData->contentOffset == pluginData->contentLength)
    {
        PHIT_Context_PostEOC(context);

        if (pluginData->trailers)
        {
#if defined(USE_TRAILERS)
            PHIT_Context_PostTrailerField(context, "Trailer1", "value1");
            PHIT_Context_PostTrailerField(context, "Trailer2", "value2");
#endif
        }
        free(pluginData->content);
        free(pluginData);
    }
}

static PHIT_Plugin _plugin =
{
    _Load,
    _Unload,
    _HandleRequest,
    _HandlePull
};

PHIT_EXPORT PHIT_Plugin* PHIT_Main()
{
    return &_plugin;
}
