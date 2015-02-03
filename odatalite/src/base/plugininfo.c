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
#include "plugininfo.h"
#include "alloc.h"
#include "str.h"
#include "path.h"
#include "file.h"
#include "format.h"
#include "http.h"
#include "conffile.h"

typedef struct _CallbackData
{
    PluginInfo** array;
    size_t arraySize;
    size_t arrayOffset;
    size_t arrayEnd;
}
CallbackData;

static int _ConfFileCallback(
    const char* path,
    unsigned int line,
    char** fields,
    size_t nfields,
    void* data,
    char* err,
    size_t errSize)
{
    PluginInfo* info;
    CallbackData* cd = (CallbackData*)data;

    /* Expecting 5 fields */
    if (nfields != 5)
    {
        Snprintf(err, errSize, "%s(%u): expected 5 fields", path, line);
        return -1;
    }

    /* Check for array overflow */
    if (cd->arrayEnd == cd->arraySize)
    {
        Snprintf(err, errSize, "%s(%u): overflow", path, line);
        return -1;
    }

    /* Allocate a new zero-initialized array entry */
    if (!(info = (PluginInfo*)Calloc(1, sizeof(PluginInfo))))
    {
        Snprintf(err, errSize, "%s(%u): out of memory", path, line);
        return -1;
    }

    /* Insert new array entry */
    cd->array[cd->arrayEnd++] = info;

    /* PluginInfo.name */
    {
        if (!(info->name = Strdup(fields[0])))
        {
            Snprintf(err, errSize, "%s(%u): out of memory", path, line);
            return -1;
        }

        if (*info->name == '\0')
        {
            Snprintf(err, errSize, "%s(%u): missing plugin name", path, line);
            return -1;
        }
    }

    /* PluginInfo.method */
    {
        PHIT_Method method;
        const char* end;

        /* Parse the method (could be '*') */
        if (fields[1][0] == '*' && fields[1][1] == '\0')
        {
            method = HTTP_METHOD_ANY;
        }
        else if (!(end = ParseHTTPMethod(fields[1], &method)) || *end)
        {
            Snprintf(err, errSize, "%s(%u): unknown method", path, line);
            return -1;
        }

        info->method = method;
    }

    /* PluginInfo.uri */
    {
        if (!(info->uri = Strdup(fields[2])))
        {
            Snprintf(err, errSize, "%s(%u): out of memory", path, line);
            return -1;
        }

        if (*info->uri == '\0')
        {
            Snprintf(err, errSize, "%s(%u): missing URI", path, line);
            return -1;
        }

        info->uriLen = strlen(info->uri);
    }

    /* PluginInfo.libname */
    {
        if (!(info->libname = Strdup(fields[3])))
        {
            Snprintf(err, errSize, "%s(%u): out of memory", path, line);
            return -1;
        }

        if (*info->libname == '\0')
        {
            Snprintf(err, errSize, "%s(%u): missing URI", path, line);
            return -1;
        }
    }

    /* PluginInfo.link */
    {
        if (!(info->link = Strdup(fields[4])))
        {
            Snprintf(err, errSize, "%s(%u): out of memory", path, line);
            return -1;
        }

        info->linkLen = strlen(info->link);
    }

    return 0;
}

size_t PluginInfoLoad(
    const char* path,
    PluginInfo** array,
    size_t arraySize,
    size_t arrayOffset,
    char* err,
    size_t errSize)
{
    CallbackData cd;

    cd.array = array;
    cd.arraySize = arraySize;
    cd.arrayOffset = arrayOffset;
    cd.arrayEnd = arrayOffset;
    
    if (ConfFileLoad(path, ":", _ConfFileCallback, &cd, err, errSize) != 0)
    {
        PluginInfoRelease(cd.array + cd.arrayOffset, 
            cd.arraySize - cd.arrayOffset);
        return -1;
    }

    return cd.arrayEnd;
}

void PluginInfoRelease(
    PluginInfo** array,
    size_t arraySize)
{
    size_t i;

    for (i = 0; i < arraySize; i++)
    {
        Free(array[i]->name);
        Free(array[i]->uri);
        Free(array[i]->libname);
        Free(array[i]->link);
        Free(array[i]);
    }
}
