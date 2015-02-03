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
#include "webpage.h"
#include <base/buf.h>
#include <base/str.h>
#include <base/html.h>
#include <odata/queryoption.h>
#include "providers.h"

void PostWebPage(
    PHIT_Plugin* plugin,
    PHIT_Context* context)
{
    Buf out = BUF_INITIALIZER;

    BufCatShareFile(&out, "preamble.html");

    BufCat(&out, STRLIT("<h1>ODataLite Plugin</h1>"));
    BufCat(&out, STRLIT("<hr>"));

    /* Providers */
    {
        size_t i;

        BufCat(&out, STRLIT("<h2>Providers:</h2>"));
        BufCat(&out, STRLIT(
            "<table width=100% border=0 cellspacing=0 cellpadding=5>"));
        BufCat(&out, STRLIT("<tr bgcolor=#777777>"));

        HTMLPutTH(&out, "URIs");
        HTMLPutTH(&out, "Library");
        HTMLPutTH(&out, "Query Options");

        BufCat(&out, STRLIT("</tr>"));

        for (i = 0; i < __entriesSize; i++)
        {
            const ProviderEntry* p = __entries[i];

            if (p)
            {
                BufFmt(&out, "<tr  valign=top bgcolor=\"%s\">",
                    (i % 2) ? "#DDDDDDDD" : "lightyellow");

                /* URIs */
                {
                    size_t j;

                    BufCat(&out, STRLIT("<td>"));

                    for (j = 0; j < p->paths.size; j++)
                    {
                        BufFmt(&out, 
                            "<a "
                            "href=\"javascript:void(0);\" "
                            "onClick=\"GetPage('odata%s'); \">"
                            "<u>%s</u>"
                            "</a><br>\n",
                            p->paths.data[j].path,
                            p->paths.data[j].path);
                    }

                    BufCat(&out, STRLIT("</td>"));
                }

                /* Library */
                HTMLPutTD(&out, p->libname);

                /* Query Options */
                BufCat(&out, STRLIT("<td>"));
                {
                    unsigned int bit;

                    /* Test each bit */
                    for (bit = 0; bit < 32; bit++)
                    {
                        unsigned int mask = 1 << bit;

                        if (mask & p->queryOptions)
                        {
                            BufCatStr(&out, QueryOptionToStr(mask));
                            BufCat(&out, STRLIT("&nbsp;"));
                        }
                    }
                }
                BufCat(&out, STRLIT("</td>"));

                BufCat(&out, STRLIT("</tr>"));
            }
        }

        BufCat(&out, STRLIT("</table>"));
    }

    /* Plain-text query field */
    BufCatShareFile(&out, "odata.html");

    /* Providers.conf */
    {
        BufCat(&out, STRLIT("<h2>Files:</h2>"));
        BufFmt(&out, "<li><a href=\"/odata/%s\">%s</a></li>",
            "providers.conf", "providers.conf");
    }

    /* HTML Postamble */
    BufCatShareFile(&out, "postamble.html");
    BufCatCh(&out, '\0');

    /* Post the response */
    PHIT_Context_PostStatusLine(
        context, PHIT_STATUSCODE_200_OK, PHIT_STATUSMSG_200_OK);
    PHIT_Context_PostHeader(context, "Content-Type", "text/html");
    PHIT_Context_PostHeader(context, "Cache-Control", "no-cache");
    PHIT_Context_PostEOH(context);
    PHIT_Context_PostContent(context, out.data, out.size-1);
    PHIT_Context_PostEOC(context);

    BufDestroy(&out);
}
