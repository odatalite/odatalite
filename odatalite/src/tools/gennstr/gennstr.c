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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <base/str.h>

int main(int argc, char** argv)
{
    FILE* is;
    FILE* os;
    char buf[1024];
    int line = 1;
    char basename[1024];
    char path[1024];

    /* Check arguments */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s path\n", argv[0]);
        exit(1);
    }

    /* Open input file */
    if (!(is = fopen(argv[1], "r")) != 0)
    {
        fprintf(stderr, "%s: failed to open '%s'\n", argv[0], argv[1]);
        exit(1);
    }

    /* Form name of output file */
    {
        char* p;

        Strlcpy(path, argv[1], sizeof(path));

        if ((p = strchr(path, '.')))
            *p = '\0';

        Strlcpy(basename, path, sizeof(basename));
        Strlcat(path, ".h", sizeof(path));
    }

    /* Open output file */
    if (!(os = fopen(path, "w")) != 0)
    {
        fprintf(stderr, "%s: failed to open '%s'\n", argv[0], path);
        exit(1);
    }

    /* Print output file preamble */
    fprintf(os, "#ifndef _%s_h\n", basename);
    fprintf(os, "#define _%s_h\n", basename);
    fprintf(os, "\n");

    while (fgets(buf, sizeof(buf), is))
    {
        char* end = buf + strlen(buf);
        char* p;
        char* name;
        char* value;
        size_t len;

        /* Remove trailing whitespace */
        while (end != buf && isspace(end[-1]))
            *--end = '\0';

        /* Split about the ':' character */
        if ((p = strchr(buf, ':')) == NULL)
        {
            fprintf(stderr, "%s: %s(%u): missing ':' character\n",
                argv[0], argv[1], line);
            exit(1);
        }

        *p = '\0';
        name = buf;
        value = p + 1;

        len = strlen(value);

        if (len > 256)
        {
            fprintf(stderr, "%s: %s(%u): string longer than 256 bytes\n",
                argv[0], argv[1], line);
            exit(1);
        }

        fprintf(os, "static const char _%s[] = \"\\%03o%s\";\n", 
            name, (int)len, value);

        fprintf(os, "#define %s (&_%s[1])\n", name, name);

        fprintf(os, "#define %s_Code 0x%08X\n", 
            name, StrCode(value, strlen(value)));

        fprintf(os, "#define %s_Len %u\n", name, (int)strlen(value));

        fprintf(os, "\n");

        line++;
    }

    /* Print output file postamble */
    fprintf(os, "#endif /* _%s_h */\n", basename);

    fclose(is);
    fclose(os);

    printf("Created %s\n", path);

    return 0;
}
