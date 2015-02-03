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
#include <base/shlib.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    Shlib* shlib;

    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "Usage: %s path [symbol]\n", argv[0]);
        exit(1);
    }

    if (!(shlib = ShlibOpen(argv[1])))
    {
        char err[2048];
        ShlibErr(err, sizeof(err));
        fprintf(stderr, "%s: %s\n", argv[0], err);
        exit(1);
    }

    if (argc == 3)
    {
        void* sym = ShlibSym(shlib, argv[2]);

        if (!sym)
        {
            char err[2048];
            ShlibErr(err, sizeof(err));
            fprintf(stderr, "%s: %s\n", argv[0], err);
            exit(1);
        }
    }

    ShlibClose(shlib);
    return 0;
}
