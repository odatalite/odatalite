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
#include "providers.h"
#include <base/find.h>
#include <odata/odata.h>
#include <odata/providerentry.h>
#include <base/path.h>
#include <base/log.h>
#include <base/str.h>

ProviderEntry** __entries;
size_t __entriesSize;

static int _LoadProvider(ProviderEntry* entry)
{
    char root[MAX_PATH_SIZE];
    char path[MAX_PATH_SIZE];
    char libname[MAX_PATH_SIZE];
    OL_ProviderEntryPointProc proc;

    /* Get full path of the library */
    if (!MakePath(ID_PLUGIN_LIBDIR, root))
    {
        LOGW(("MakePath(ID_PLUGIN_LIBDIR) failed"));
        return -1;
    }

    /* Expand to full shared library name */
    if (MakeShlibName(libname, entry->libname) != 0)
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

    /* Open the shared library */
    if (!(entry->shlib = ShlibOpen(path)))
    {
        char err[256];
        ShlibErr(err, sizeof(err));

        LOGW(("failed to load provider library %s: %s", path, err));
        return -1;
    }

    /* Find provider entry point */
    if (!(proc = ShlibSym(entry->shlib, OL_PROVIDERENTRYPOINT)))
    {
        LOGW(("failed to find provider entry point: %s.%s", path,
            OL_PROVIDERENTRYPOINT));
        return -1;
    }

    /* Call provider entry point */
    if (!(entry->provider = (*proc)()))
    {
        LOGW(("failed to call provider entry point: %s.%s()", path,
            OL_PROVIDERENTRYPOINT));
        return -1;
    }

    /* Call the provider Load() */
    {
        OL_Scope* context;

        if (!(context = __OL_Scope_New()))
        {
            LOGW(("failed to create context: %s(%d)", __FILE__, __LINE__));
            return -1;
        }

        /* ATTN: handle PostResult() */

        (*entry->provider->ft->Load)(entry->provider, context);

        OL_Scope_Release(context);
    }

    return 0;
}

int ProvidersLoad()
{
    char buf[MAX_PATH_SIZE];
    char err[512];
    size_t i;

    if (ProviderEntryLoadFile(
        MakePath(ID_PROVIDERS_CONF, buf),
        &__entries,
        &__entriesSize,
        err,
        sizeof(err)) != 0)
    {
        LOGW(("failed to load %s: %s", buf, err));
        return -1;
    }

    for (i = 0; i < __entriesSize; i++)
    {
        ProviderEntry* entry = __entries[i];
        _LoadProvider(entry);
    }

    return 0;
}

static size_t _MatchSegments(
    const Path* path,
    const URI* uri)
{
    size_t i = 0; /* path-segment index */
    size_t j = 0; /* uri-segment index */
    size_t n = 0; /* number of matching segments */

    /* Skip over "/" element if any */
    {
        if (path->nsegments == 0)
            return SIZEMAX;

        if (strcmp(path->segments[0], "/") == 0)
            i++;
    }

    /* Compare 'uri' and 'path' segments */
    for (; i < path->nsegments && j < uri->segments.size; i++, j++)
    {
        if (strcmp(path->segments[i], uri->segments.data[j].name) != 0)
            break;

        n++;
    }

    /* Return number of matching segments */
    return n;
}

ProviderEntry* FindProviderEntry(
    const URI* uri,
    size_t* numMatchingSegments)
{
    ProviderEntry* entry = NULL;
    *numMatchingSegments = 0;

    /* Find provider entry for this URI with the longest URI match */
    {
        size_t i;
        size_t j;

        for (i = 0; i < __entriesSize; i++)
        {
            ProviderEntry* e = __entries[i];

            for (j = 0; j < e->paths.size; j++)
            {
                const Path* path = &e->paths.data[j];
                size_t r = _MatchSegments(path, uri);

                if (r == SIZEMAX)
                    return NULL;

                if (r > *numMatchingSegments)
                {
                    *numMatchingSegments = r;
                    entry = e;

                    if (r == uri->segments.size)
                        return entry;
                }
                else if (r == 0 && !entry)
                {
                    /* Check for root provider */
                    if (path->nsegments == 1 && 
                        strcmp(path->segments[0], "/")  == 0)
                    {
                        entry = e;
                    }
                }
            }
        }
    }

    return entry;
}

static int _ProviderUnload(ProviderEntry* entry)
{
    /* Call the provider Unload() */
    {
        OL_Scope* context;

        if (!(context = __OL_Scope_New()))
        {
            LOGW(("failed to create context: %s(%d)", __FILE__, __LINE__));
            return -1;
        }

        /* ATTN: handle PostResult() */

        (*entry->provider->ft->Unload)(entry->provider, context);

        OL_Scope_Release(context);
    }

    /* Close the shared library */
    ShlibClose(entry->shlib);

    return 0;
}

int ProvidersUnload()
{
    size_t i;

    for (i = 0; i < __entriesSize; i++)
    {
        ProviderEntry* entry = __entries[i];
        _ProviderUnload(entry);
        ProviderEntryDelete(entry);
    }

    Free(__entries);
    __entries = NULL;
    __entriesSize = 0;

    return 0;
}
