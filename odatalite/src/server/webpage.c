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
#include <phit.h>
#include <base/buf.h>
#include <base/str.h>
#include <base/html.h>
#include <base/http.h>
#include <base/path.h>
#include <base/role.h>
#include "plugin.h"
#include "options.h"
#include "context.h"
#include "connection.h"

/* Make this a little smaller by suppressing inlining */
#define BufCat BufCatNoInline

#if defined(ENABLE_WEBPAGES)

static void _SendBackgroundGifFile(PHIT_Context* context)
{
    char path[MAX_PATH_SIZE];

    MakePath2(ID_DATADIR, path, "background.gif");
    HTMLPostFile(context, path, "image/gif");
}

static const char* _MethodNameOf(int method)
{
    if (method == -1)
        return "ANY";

    return HTTPMethodNameOf(method);
}

static void _FormatPath(
    Buf* out, 
    const char* name,
    PathID id)
{
    char path[MAX_PATH_SIZE];
    BufFmt(out, "<li><b>%s</b>=%s</li>", name, MakePath(id, path));
}

static void _FormatWebPage(
    Buf* out,
    Connection* connection)
{
    size_t i;

    DEBUG_ASSERT(connection);

    BufCatShareFile(out, "preamble.html");

    BufCat(out, STRLIT("<h1>The PHIT Web Server</h1>"));

    /* Plugins */
    {
        BufCat(out, STRLIT("<hr>"));
        BufCat(out, STRLIT("<h2>Plugins:</h2>"));
        BufCat(out, STRLIT(
            "<table width=100% border=0 cellspacing=0 cellpadding=5>"));
        BufCat(out, STRLIT("<tr bgcolor=#777777>"));

        HTMLPutTH(out, "Name");
        HTMLPutTH(out, "Method");
        HTMLPutTH(out, "URI");
        HTMLPutTH(out, "Library");
        HTMLPutTH(out, "Link");

        BufCat(out, STRLIT("</tr>"));

        for (i = 0; i < __nplugins; i++)
        {
            const PluginInfo* p = __plugins[i];
            {
                BufFmt(out, "<tr bgcolor=\"%s\">", 
                    (i % 2) ? "#DDDDDDDD" : "lightyellow");

                HTMLPutTD(out, p->name);
                HTMLPutTD(out, _MethodNameOf(p->method));
                HTMLPutTD(out, p->uri);
                HTMLPutTD(out, Strnull(p->libname));

                if (p->linkLen == 0)
                {
                    HTMLPutTD(out, "");
                }
                else
                {
                    BufFmt(out, "<td><a href=\"%s\">%s</a></td>", p->link, 
                        p->link);
                }
                BufCat(out, STRLIT("</tr>"));
            }
        }

        BufCat(out, STRLIT("</table>"));
    }

    /* Identify */
    {
        BufCat(out, STRLIT("<h2>Identity:</h2>"));
        BufCat(out, STRLIT("<ul>"));

        BufFmt(out, "<li><b>User: </b>%s</li>", connection->user);

        BufFmt(out, "<li><b>Role: </b>%s</li>", RoleName(connection->role));

        BufCat(out, STRLIT("</ul>"));
    }

    /* Heap Usage */
    {
        AllocStats stats;

        GetAllocStats(&stats);

        BufFmt(out,
            "<h2>Heap Usage:</h2>"
            "<ul>"
            "<li><b>Total: </b>%lu</li>"
            "<li><b>Peak: </b>%lu</li>"
            "<li><b>Allocations: </b>%lu</li>"
            "<li><b>Deallocations: </b>%lu</li>"
            "</ul>", 
            stats.bytesAllocated,
            stats.maxBytesAllocated,
            stats.numAllocs,
            stats.numAllocs);
    }

    /* Files */
    {
        BufCat(out, STRLIT("<h2>Files:</h2>"));
        BufCat(out, STRLIT("<ul>"));

        BufCat(out, STRLIT(
            "<li><a href=\"/files/phit.log\">phit.log</a></li>"));

        BufCat(out, STRLIT(
            "<li><a href=\"/files/plugins.conf\">plugins.conf</a></li>"));

        BufCat(out, STRLIT(
            "<li><a href=\"/files/phitd.conf\">phitd.conf</a></li>"));

        BufCat(out, STRLIT(
            "<li><a href=\"/files/roles.conf\">roles.conf</a></li>"));

        BufCat(out, STRLIT("</ul>"));
    }

    /* Paths */
    {
        BufCat(out, STRLIT("<h2>Paths:</h2>"));
        BufCat(out, STRLIT("<ul>"));

        _FormatPath(out, "SOCKFILE", ID_SOCKFILE);
        _FormatPath(out, "PIDFILE", ID_PIDFILE);
        _FormatPath(out, "AUTHDIR", ID_AUTHDIR);
        _FormatPath(out, "LOGFILE", ID_LOGFILE);
        _FormatPath(out, "RECVLOG", ID_RECVLOG);
        _FormatPath(out, "SENDLOG", ID_SENDLOG);
        _FormatPath(out, "PLUGGINSCONF", ID_PLUGINS_CONF);
        _FormatPath(out, "PROVIDERSCONF", ID_PROVIDERS_CONF);
        _FormatPath(out, "ROLESCONF", ID_ROLES_CONF);
        _FormatPath(out, "LIBDIR", ID_LIBDIR);

        BufCat(out, STRLIT("</ul>"));
    }

    /* Endpoints */
    {
        BufCat(out, STRLIT("<h2>Endpoints:</h2>"));
        BufCat(out, STRLIT("<ul>"));

        BufFmt(out, "<li><b>TCP Port: </b>%u</li>", g_options.port);
        BufFmt(out, "<li><b>UDS Path: </b>%s</li>", g_options.sockfile);

        BufCat(out, STRLIT("</ul>"));
    }

    BufCat(out, STRLIT("<br>"));
    BufCatShareFile(out, "postamble.html");

    BufCatCh(out, '\0');
}

void HandleGetWebPage(
    PHIT_Context* context,
    const char* requestURI)
{
    char buf[MAX_PATH_SIZE];

    if (strcmp(requestURI, "/") == 0)
    {
        Buf buf = BUF_INITIALIZER;

        PHIT_Context_PostStatusLine(
            context, PHIT_STATUSCODE_200_OK, PHIT_STATUSMSG_200_OK);
        PHIT_Context_PostHeader(context, "Content-Type", "text/html");
        PHIT_Context_PostEOH(context);

        _FormatWebPage(&buf, ((Context*)context)->connection);

        PHIT_Context_PostContent(context, buf.data, buf.size);
        PHIT_Context_PostEOC(context);

        BufDestroy(&buf);
    }
    else if (strcmp(requestURI, "/files/phit.log") == 0)
    {
        if (HTMLPostFile(context, MakePath(ID_LOGFILE, buf), "text/plain") != 0)
            goto NotFound;
    }
    else if (strcmp(requestURI, "/files/background.gif") == 0)
    {
        _SendBackgroundGifFile(context);
    }
    else if (strcmp(requestURI, "/files/phitsend.log") == 0)
    {
        if (HTMLPostFile(context, MakePath(ID_SENDLOG, buf), "text/plain") != 0)
            goto NotFound;
    }
    else if (strcmp(requestURI, "/files/phitrecv.log") == 0)
    {
        if (HTMLPostFile(context, MakePath(ID_RECVLOG, buf), "text/plain") != 0)
            goto NotFound;
    }
    else if (strcmp(requestURI, "/files/plugins.conf") == 0)
    {
        MakePath(ID_PLUGINS_CONF, buf);
        if (HTMLPostFile(context, buf, "text/plain") != 0)
            goto NotFound;
    }
    else if (strcmp(requestURI, "/files/phitd.conf") == 0)
    {
        MakePath(ID_PHITD_CONF, buf);
        if (HTMLPostFile(context, buf, "text/plain") != 0)
            goto NotFound;
    }
    else if (strcmp(requestURI, "/files/roles.conf") == 0)
    {
        MakePath(ID_ROLES_CONF, buf);
        if (HTMLPostFile(context, buf, "text/plain") != 0)
            goto NotFound;
    }
    else
    {
        goto NotFound;
    }

    return;

NotFound:

    PHIT_Context_PostError(
        context, 
        PHIT_STATUSCODE_404_NOT_FOUND, 
        PHIT_STATUSMSG_404_NOT_FOUND, 
        requestURI);
}

#endif /* defined(ENABLE_WEBPAGES) */
