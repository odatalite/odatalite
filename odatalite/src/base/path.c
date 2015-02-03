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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "path.h"
#include "str.h"
#include "env.h"
#include "cleanup.h"

typedef struct _PathEntry
{
    const char* lhs;
    const char* rhs;
}
PathEntry;

static PathEntry _entries[] =
{
    { RUNSTATEDIR, "/phitd.sock" },
    { RUNSTATEDIR, "/phitd.pid" },
    { LOCALSTATEDIR, "/phitauth/" },
    { LOCALSTATEDIR, "/log/phit.log" },
    { LOCALSTATEDIR, "/log/phitrecv.log" },
    { LOCALSTATEDIR, "/log/phitsend.log" },
    { SYSCONFDIR, "/phit/phitd.conf" },
    { SYSCONFDIR, "/phit/plugins.conf" },
    { SYSCONFDIR, "/phit/roles.conf" },
    { SYSCONFDIR, "/phit/providers.conf" },
    { DATAROOTDIR, "/phit" },
    { LIBDIR, NULL }, /* ID_LIBDIR */
    { LIBDIR, NULL } /* ID_PLUGIN_LIBDIR */
};

/* Points to heap memory or PREFIX macro */
static const char* _prefix;

static int _runningFromSourceDirectory = 0;

const char* GetPrefix()
{
    if (!_prefix)
    {
        if ((_prefix = GetEnv("PHIT_PREFIX")))
        {
            char path[MAX_PATH_SIZE];

            Strlcpy2(path, _prefix, "/configure.ac", sizeof(path));

            if (access(path, F_OK) == 0)
                _runningFromSourceDirectory = 1;
        }
        else
        {
            _prefix = PREFIX;
        }
    }

    return _prefix;
}

const char* MakePath(
    PathID id, 
    char buf[MAX_PATH_SIZE])
{
    const PathEntry* ent = &_entries[id];

    /* Copy prefix */
    if (Strlcpy(buf, GetPrefix(), MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    /* If running from source directory */
    if (_runningFromSourceDirectory && id == ID_PLUGIN_LIBDIR)
        return buf;

    /* Copy the LHS */
    {
        const char* p;

        /* Skip over "${prefix}" or "${exec_prefix}" */
        {
            p = ent->lhs;

            if (p[0] == '$' && p[1] == '{')
            {
                for (p += 2; *p && *p != '}'; p++)
                    ;

                if (*p == '}')
                    p++;
            }
        }

        if (Strlcat(buf, p, MAX_PATH_SIZE) >= MAX_PATH_SIZE)
            return NULL;
    }

    /* Copy the RHS */
    if (ent->rhs && Strlcat(buf, ent->rhs, MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    return buf;
}

const char* MakePath2(
    PathID id, 
    char buf[MAX_PATH_SIZE],
    const char* basename)
{
    if (!MakePath(id, buf))
        return NULL;

    if (Strlcat2(buf, "/", basename, MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    return buf;
}

int MakeAbsolutePath(
    char buf[MAX_PATH_SIZE],
    const char* path)
{
    char cwd[MAX_PATH_SIZE];

    if (path[0] != '/')
    {
        if (getcwd(cwd, sizeof(cwd)) == (char*)0)
            return -1;

        if (Strlcpy2(buf, cwd, "/", MAX_PATH_SIZE) >= MAX_PATH_SIZE)
            return -1;
    }

    if (Strlcat(buf, path, MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return -1;

    return 0;
}

int NormalizePath(
    char path[MAX_PATH_SIZE])
{
    char cwd[MAX_PATH_SIZE];

    if (getcwd(cwd, sizeof(cwd)) == (char*)0)
        return -1;

    if (chdir(path) != 0)
        return -1;

    if (getcwd(path, MAX_PATH_SIZE) == (char*)0)
        return -1;

    if (chdir(cwd))
        return -1;

    return 0;
}

int Rootname(
    char path[MAX_PATH_SIZE])
{
    char* p;

    if ((p = strrchr(path, '/')) && p != path)
        *p = '\0';

    return NormalizePath(path);
}

const char* Basename(
    const char* path)
{
    const char* p;

    if ((p = strrchr(path, '/')))
        return p + 1;

    return path;
}
