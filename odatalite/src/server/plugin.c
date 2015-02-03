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
#include "plugin.h"
#include "defaultplugin.h"
#include <base/find.h>
#include <base/str.h>
#include <base/path.h>
#include <base/file.h>
#include <base/format.h>
#include <base/http.h>
#include <base/plugininfo.h>
#include <base/shlib.h>
#include <base/log.h>
#include <plugins/odata/odataplugin.h>

static PluginInfo _builtinPlugin0 =
{
    "Default",
    PHIT_METHOD_GET,
    STRLIT("/"),
    NULL,
    0,
    &__defaultPlugin 
};

static PluginInfo _builtinPlugin1 =
{
    "Default",
    PHIT_METHOD_GET,
    STRLIT("/files/*"),
    NULL,
    0,
    &__defaultPlugin
};

static PluginInfo _builtinPlugin2 =
{
    "OData",
    HTTP_METHOD_ANY,
    STRLIT("/odata/*"),
    STRLIT("/odata/webpage"),
    &__odataPlugin.base 
};

PluginInfo* __plugins[MAX_PLUGINS] =
{
    &_builtinPlugin0,
    &_builtinPlugin1,
    &_builtinPlugin2
};

size_t __nplugins = NUM_BUILTIN_PLUGINS;

/* Returns 0 if uri matches pattern */
static int _MatchURI(
    const char* pattern, 
    size_t patternLen,
    const char* uri)
{
    if (patternLen < 2)
        return strcmp(pattern, uri);

    if (pattern[patternLen-2] == '/' && pattern[patternLen-1] == '*')
    {
        if (strncmp(pattern, uri, patternLen - 2) == 0)
            return 0;

        /* Try without the leading slash */
        if (patternLen >= 3 && pattern[0] == '/')
        {
            if (strncmp(pattern+1, uri, patternLen - 3) == 0)
                return 0;
        }
    }
    else
    {
        if (strcmp(pattern, uri) == 0)
            return 0;

        /* Try without the leading slash */
        if (strcmp(pattern+1, uri) == 0)
            return 0;
    }

    /* No match */
    return -1;
}

static int _LoadPlugin(PluginInfo* info)
{
    void* handle = NULL;
    void* sym;
    PHIT_MainProc proc;
    char err[1024];
    char path[MAX_PATH_SIZE];
    char root[MAX_PATH_SIZE];
    char libname[MAX_PATH_SIZE];

    /* Get full path of the library */
    if (!MakePath(ID_PLUGIN_LIBDIR, root))
    {
        LOGW(("MakePath(ID_PLUGIN_LIBDIR) failed"));
        return -1;
    }

    /* Expand to full shared library name */
    if (MakeShlibName(libname, info->libname) != 0)
    {
        LOGE(("MakeShlibName()"));
        return -1;
    }

    /* Find the shared library */
    if (FindFile(path, root, libname) != 0)
    {
        LOGW(("cannot find %s under %s", libname, root));
        return -1;
    }

    /* Open shared library */
    if (!(handle = ShlibOpen(path)))
    {
        ShlibErr(err, sizeof(err));
        LOGW(("failed to load: %s: %s", path, err));
        goto failed;
    }

    /* Find symbol */
    if (!(sym = ShlibSym(handle, "PHIT_Main")))
    {
        ShlibErr(err, sizeof(err));
        LOGW(("%s:PHIT_Main() not found: %s", path, err));
        goto failed;
    }

    /* Do this to avoid warning about conversion */
    memcpy(&proc, &sym, sizeof(sym));

    /* Invoke the entry point to get the plugin instance */
    if (!(info->plugin = (*proc)()))
    {
        LOGW(("%s:PHIT_Main() returned NULL", path));
        goto failed;
    }

    /* Invoke the plugin's Load() method */
    if (!(info->plugin->Load))
    {
        LOGW(("%s: plugin has NULL load method", path));
        goto failed;
    }

    (*info->plugin->Load)(info->plugin);

    info->shlib = handle;
    info->loaded = 1;
    return 0;

failed:

    if (handle)
        ShlibClose(handle);

    return -1;
}

PHIT_Plugin* PluginLookup(
    PHIT_Method method,
    const char* uri)
{
    size_t i;

    for (i = 0; i < __nplugins; i++)
    {
        PluginInfo* info = __plugins[i];

        if (info->method == HTTP_METHOD_ANY || method == info->method)
        {
            if (_MatchURI(info->uri, info->uriLen, uri) == 0)
            {
                if (i < NUM_BUILTIN_PLUGINS)
                {
                    if (!info->loaded)
                    {
                        DEBUG_ASSERT(info->plugin->Load);
                        (*info->plugin->Load)(info->plugin);
                        info->loaded = 1;
                    }
                }
                else
                {
                    if (!info->plugin)
                    {
                        if (_LoadPlugin(info) != 0)
                        {
                            return NULL;
                        }
                    }
                }

                return __plugins[i]->plugin;
            }
        }
    }

    /* Not found */
    return NULL;
}

int PluginLoad(
    char* error,
    size_t errorSize)
{
    char path[MAX_PATH_SIZE];
    size_t newSize;

    MakePath(ID_PLUGINS_CONF, path);

    newSize = PluginInfoLoad(
        path,
        __plugins,
        MAX_PATH_SIZE,
        __nplugins,
        error,
        errorSize);

    if (newSize == (size_t)-1)
        return -1;

    __nplugins = newSize;
    return 0;
}

/* Unload all plugins */
void PluginUnload()
{
    size_t i;

    /* Unload the built-in plugins */
    for (i = 0; i < NUM_BUILTIN_PLUGINS; i++)
    {
        PluginInfo* info = __plugins[i];

        /* Invoke the plugin's Unload() method */
        if (info->plugin && info->plugin->Unload)
        {
            (*info->plugin->Unload)(info->plugin);
        }

        info->loaded = 0;
    }

    /* Unload the dynamic plugins */
    for (i = NUM_BUILTIN_PLUGINS; i < __nplugins; i++)
    {
        PluginInfo* info = __plugins[i];

        /* Invoke the plugin's Unload() method */
        if (info->plugin && info->plugin->Unload)
        {
            (*info->plugin->Unload)(info->plugin);
        }

        /* PluginInfo.shlib */
        if (info->shlib)
            ShlibClose(info->shlib);

        info->loaded = 0;

        /* PluginInfo.uri & PluginInfo.libname */
        PluginInfoRelease(&info, 1);
    }

    __nplugins = NUM_BUILTIN_PLUGINS;
}
