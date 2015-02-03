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
#define _GNU_SOURCE
#include "find.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "path.h"
#include "str.h"

#define MAX_DIRS 64

int FindFile(
    char path[MAX_PATH_SIZE],
    const char* root,
    const char* name)
{
    char* dirs[MAX_DIRS];
    size_t ndirs = 0;
    struct dirent* ent;
    DIR* dir = NULL;
    size_t i;
    int r = -1;

    /* Open directory */
    if (!(dir = opendir(root)))
        goto done;

    /* Scan directory, looking for binary files */
    while ((ent = readdir(dir)))
    {
        char buf[MAX_PATH_SIZE];
        struct stat st;

        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        Strlcpy3(buf, root, "/", ent->d_name, sizeof(buf));

        if (stat(buf, &st) != 0)
            continue;

        if (st.st_mode & S_IFDIR)
        {
            if (ndirs == sizeof(dirs) / sizeof(dirs[0])) 
                goto done;

            dirs[ndirs++] = Strdup(buf);
        }
        else
        {
            if (strcmp(ent->d_name, name) == 0)
            {
                r = 0;
                Strlcpy(path, buf, MAX_PATH_SIZE);
                goto done;
            }
        }
    }

    /* Close directory */
    closedir(dir);
    dir = NULL;

    /* Scan child directories */
    for (i = 0; i < ndirs; i++)
    {
        if (FindFile(path, dirs[i], name) == 0)
        {
            r = 0;
            goto done;
        }
    }

done:

    /* Close the directory */
    if (dir)
        closedir(dir);

    /* Free any directories */
    for (i = 0; i < ndirs; i++)
        Free(dirs[i]);

    return r;
}
