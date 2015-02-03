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
#include "disp.h"
#include "plugin.h"
#include <base/log.h>

void DispatchRequest(
    Context* context,
    PHIT_Method method,
    const char* requestURI,
    const PHIT_Headers* headers,
    const char* content,
    size_t contentLength)
{
    PHIT_Plugin* plugin = PluginLookup(
        method,
        requestURI);

    DEBUG_ASSERT(context->base.magic == PHIT_CONTEXT_MAGIC);

    if (!plugin)
    {
        LOGW(("plugin not found: method=%u uri=%s", method, requestURI));

        PHIT_Context_PostStatusLine(
            &context->base, 
            PHIT_STATUSCODE_404_NOT_FOUND,
            PHIT_STATUSMSG_404_NOT_FOUND);

        PHIT_Context_PostHeader(
            &context->base, "Content-Type", "text/html");

        PHIT_Context_PostEOH(&context->base);

        PHIT_Context_PostContent(&context->base, STRLIT(
            "<html>"
              "<head><title>Not Found</title></head>"
              "<body>"
                "404: Not Found"
              "</body>"
            "</html>"));

        PHIT_Context_PostEOC(&context->base);
        return;
    }

    context->plugin = plugin;

    plugin->HandleRequest(
        plugin, 
        &context->base,
        method,
        requestURI,
        headers,
        content,
        contentLength);
}

int DispatchPull(
    Context* context)
{
    PHIT_Plugin* plugin;

    DEBUG_ASSERT(context->base.magic == PHIT_CONTEXT_MAGIC);

    plugin = context->plugin;

    if (!plugin)
        return -1;

    plugin->HandlePull(plugin, &context->base);

    return 0;
}
