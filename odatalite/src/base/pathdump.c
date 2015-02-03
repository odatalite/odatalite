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
#include "path.h"

void DumpPaths()
{
    char buf[MAX_PATH_SIZE];
    printf("SOCKFILE{%s}\n", MakePath(ID_SOCKFILE, buf));
    printf("PIDFILE{%s}\n", MakePath(ID_PIDFILE, buf));
    printf("AUTHDIR{%s}\n", MakePath(ID_AUTHDIR, buf));
    printf("LOGFILE{%s}\n", MakePath(ID_LOGFILE, buf));
    printf("RECVLOG{%s}\n", MakePath(ID_RECVLOG, buf));
    printf("SENDLOG{%s}\n", MakePath(ID_SENDLOG, buf));
    printf("PHITD_CONF{%s}\n", MakePath(ID_PHITD_CONF, buf));
    printf("PLUGINS_CONF{%s}\n", MakePath(ID_PLUGINS_CONF, buf));
    printf("ROLES_CONF{%s}\n", MakePath(ID_ROLES_CONF, buf));
    printf("PROVIDERS_CONF{%s}\n", MakePath(ID_PROVIDERS_CONF, buf));
    printf("DATADIR{%s}\n", MakePath(ID_DATADIR, buf));
    printf("LIBDIR{%s}\n", MakePath(ID_LIBDIR, buf));
    printf("DATADIR{%s}\n", MakePath(ID_DATADIR, buf));
    printf("PLUGIN_LIBDIR{%s}\n", MakePath(ID_PLUGIN_LIBDIR, buf));
}
