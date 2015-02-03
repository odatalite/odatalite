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
#include <ctype.h>
#include <string.h>

const char* arg0;

void ProcessFile(const char* path)
{
    FILE* is = fopen(path, "rb");
    char buf[1024];
    size_t n;

    if (!is)
    {
        fprintf(stderr, "%s: failed to open %s", arg0, path);
        exit(1);
    }

    printf("/* %s */\n", path);
    printf("static const char DATA[] =\n");
    printf("{\n");
    printf("    \n");

    while ((n = fread(buf, 1, sizeof(buf), is)) > 0)
    {
        size_t i;

        for (i = 0; i < n; i++)
        {
            printf("0x%02X", (unsigned char)buf[i]);

            if (i + 1 != n)
                printf(", ");

            if ((i + 1) % 8 == 0)
                printf("\n    ");
        }
    }

    printf("\n");
    printf("};\n");

    fclose(is);
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s FILENAME\n", arg0);
        exit(1);
    }

    ProcessFile(argv[1]);

    return 0;
}
