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
#ifndef __phit_paths_h
#define __phit_paths_h

#include "common.h"
#include "alloc.h"

typedef enum _PathID
{
    ID_SOCKFILE,
    ID_PIDFILE,
    ID_AUTHDIR,
    ID_LOGFILE,
    ID_RECVLOG,
    ID_SENDLOG,
    ID_PHITD_CONF,
    ID_PLUGINS_CONF,
    ID_ROLES_CONF,
    ID_PROVIDERS_CONF,
    ID_DATADIR,
    ID_LIBDIR,
    ID_PLUGIN_LIBDIR,
}
PathID;

const char* GetPrefix();

const char* MakePath(
    PathID id, 
    char buf[MAX_PATH_SIZE]);

const char* MakePath2(
    PathID id, 
    char buf[MAX_PATH_SIZE],
    const char* basename);

/* Split path into segments, return # of segments or SIZEMAX on failure */
size_t SplitPath(
    char* path,
    const char* segments[],
    size_t nsegments);

int JoinPath(
    const char* const* path,
    int npath,
    char buf[MAX_PATH_SIZE]);

void DumpPaths();

int MakeAbsolutePath(
    char buf[MAX_PATH_SIZE],
    const char* path);

int NormalizePath(
    char path[MAX_PATH_SIZE]);

int Rootname(
    char path[MAX_PATH_SIZE]);

const char* Basename(
    const char* path);

#endif /* __phit_paths_h */
