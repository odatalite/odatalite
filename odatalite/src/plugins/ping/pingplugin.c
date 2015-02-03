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
#include <base/html.h>

static void _Load(
    PHIT_Plugin* plugin)
{
}

static void _Unload(
    PHIT_Plugin* plugin)
{
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
    const char DATA[] = 
        "<h1>Ping Plugin</h1>"
        "<hr>"
        "<br>"
        "<b>PHIT is alive!</b>";

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

static void _HandlePull(
    PHIT_Plugin* plugin,
    PHIT_Context* context)
{
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
