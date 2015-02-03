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
#include "html.h"
#include "file.h"
#include "path.h"
#include "log.h"

int HTMLPostFile(
    PHIT_Context* context, 
    const char* path,
    const char* contentType)
{
    char* data;
    size_t size;

    if (FileLoad(path, NULL, &data, &size) != 0)
    {
        LOGW(("HTMLPostFile(%s) failed", path));
        return -1;
    }

    PHIT_Context_PostStatusLine(
        context, PHIT_STATUSCODE_200_OK, PHIT_STATUSMSG_200_OK);
    PHIT_Context_PostHeader(context, "Content-Type", contentType);
    PHIT_Context_PostEOH(context);
    PHIT_Context_PostContent(context, data, size);
    PHIT_Context_PostEOC(context);

    Free(data);

    return 0;
}

void HTMLPutTH(Buf* out, const char* str)
{
    BufFmt(out, "<th align=left>%s</th>", str);
}

void HTMLPutTD(Buf* out, const char* str)
{
    BufFmt(out, "<td>%s</td>", str);
}
