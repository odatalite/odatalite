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
#include "providerentry.h"
#include <base/format.h>
#include <base/path.h>
#include <base/file.h>
#include <base/ptrarray.h>
#include <base/str.h>
#include <base/conffile.h>
#include <base/array.h>

static void _ProviderEntryDestructor(void* ptr)
{
    ProviderEntryDelete((ProviderEntry*)ptr);
}

static int _ConfFileCallback(
    const char* path,
    unsigned int line,
    char** fields,
    size_t nfields,
    void* callbackData,
    char* err,
    size_t errSize)
{
    PtrArray* entries = (PtrArray*)callbackData;
    ProviderEntry* info;

    /* Need 3 fields */
    if (nfields != 3)
        return -1;

    /* Allocate ProviderEntry */
    if (!(info = (ProviderEntry*)Calloc(1, sizeof(ProviderEntry))))
        goto OutOfMemory;

    /* Append ProviderEntry to entries */
    if (PtrArray_Append(entries, info) != 0)
        goto OutOfMemory;

    /* Get ProviderEntry.libname */
    {
        if (*fields[0] == '\0')
        {
            Snprintf(err, errSize, "%s(%u): missing libname", path, (int)line);
            goto Failed;
        }

        if (!(info->libname = Strdup(fields[0])))
            goto OutOfMemory;
    }

    /* Get ProviderEntry.paths */
    {
        StrtokState sts;
        char* p = fields[1];

        for (p = StrtokTrim(&sts, p, ","); 
            p; 
            p = StrtokTrim(&sts, NULL, ","))
        {
            Path tmp;

            if (!*p)
            {
                Snprintf(err, errSize, "%s(%u): bad URI", path, (int)line);
                goto Failed;
            }

            if (!(tmp.buf = Strdup(p)))
                goto OutOfMemory;

            if (!(tmp.path = Strdup(p)))
            {
                Free(tmp.buf);
                goto OutOfMemory;
            }

            tmp.nsegments = SplitPath(tmp.buf, tmp.segments, MAX_SEGMENTS);

            if (tmp.nsegments == SIZEMAX)
            {
                Free(tmp.buf);
                Free(tmp.path);
                goto OutOfMemory;
            }

            if (ArrayAppend((Array*)&info->paths, &tmp, sizeof(tmp), NULL) != 0)
            {
                Free(tmp.buf);
                Free(tmp.path);
                goto OutOfMemory;
            }
        }
    }

    /* Get ProviderEntry.queryOptions */
    {
        char* toks[16];
        char* p = fields[2];
        size_t n;
        size_t i;

        if ((n = Strtoks(p, ",", toks, ARRSIZE(toks))) == (size_t)-1)
        {
            Snprintf(err, errSize, "%s(%u): overflow", path, (int)line);
            goto Failed;
        }

        info->queryOptions = 0;

        for (i = 0; i < n; i++)
        {
            if (strcmp(toks[i], "top") == 0)
                info->queryOptions |= OL_QUERY_OPTION_TOP;
            else if (strcmp(toks[i], "skip") == 0)
                info->queryOptions |= OL_QUERY_OPTION_SKIP;
            else if (strcmp(toks[i], "count") == 0)
                info->queryOptions |= OL_QUERY_OPTION_COUNT;
            else
            {
                Snprintf(err, errSize, "%s(%u): unsuppoted query option: %s", 
                    path, (int)line, toks[i]);
                goto Failed;
            }
        }
    }

    return 0;

OutOfMemory:
    Snprintf(err, errSize, "%s(%u): out of memory", path, (int)line);

Failed:
    return -1;
}

int ProviderEntryLoadFile(
    const char* path,
    ProviderEntry*** entriesOut,
    size_t* entriesSizeOut,
    char* err,
    size_t errSize)
{
    PtrArray entries;

    /* Initialize entries */
    *entriesOut = NULL;
    *entriesSizeOut = 0;

    /* Initialize PtrArray */
    if (PtrArray_Construct(&entries, 8, _ProviderEntryDestructor) != 0)
        return -1;

    if (ConfFileLoad(path, ":", _ConfFileCallback, &entries, err, errSize) != 0)
        return -1;

    *entriesOut = (ProviderEntry**)entries.data;
    *entriesSizeOut = entries.size;

    return 0;
}

void ProviderEntryDelete(
    ProviderEntry* self)
{
    size_t i;

    Free(self->libname);

    for (i = 0; i < self->paths.size; i++)
    {
        Free(self->paths.data[i].buf);
        Free(self->paths.data[i].path);
    }

    Free(self->paths.data);
    Free(self);
}
