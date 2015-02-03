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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

const char* arg0;

static int IsBinaryFile(const char* path)
{
    FILE* is;
    int c;
    
    if (!(is = fopen(path, "rb")))
    {
        fprintf(stderr, "%s: warning: cannot open '%s'\n", arg0, path);
        return 0;
    }

    while ((c = fgetc(is)) != EOF)
    {
        if (c >= 128)
        {
            fclose(is);
            return 1;
        }
    }

    fclose(is);
    return 0;
}

static void Run(const char* root)
{
    char* dirs[1024];
    size_t ndirs = 0;
    struct dirent* ent;
    DIR* dir;
    size_t i;

    /* Open directory */
    if (!(dir = opendir(root)))
    {
        fprintf(stderr, "%s: warning: failed to open directory: %s\n", 
            arg0, root);
        return;
    }

    /* Scan directory, looking for binary files */
    while ((ent = readdir(dir)))
    {
        char path[1024];
        struct stat st;

        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        *path = '\0';
        strncat(path, root, sizeof(path) - 1);
        strncat(path, "/", sizeof(path) - 1 - strlen(root));
        strncat(path, ent->d_name, sizeof(path) - 1 - strlen(root) - 1);

        if (stat(path, &st) != 0)
        {
            fprintf(stderr, "%s: warning: failed to stat: %s\n", 
                arg0, path);
            continue;
        }

        if (st.st_mode & S_IFDIR)
        {
            if (ndirs == sizeof(dirs) / sizeof(dirs[0])) 
            {
                fprintf(stderr, "%s: too many directories: > %u\n", arg0, 
                    (unsigned int)(sizeof(dirs) / sizeof(dirs[0])));
                exit(1);
            }
            dirs[ndirs++] = strdup(path);
        }
        else
        {
            if (IsBinaryFile(path))
            {
                printf("%s\n", path);
            }
        }
    }

    /* Close directory */
    closedir(dir);

    /* Scan child directories */
    for (i = 0; i < ndirs; i++)
    {
        Run(dirs[i]);
        free(dirs[i]);
    }
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(1);
    }

    Run(".");

    return 0;
}
