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
#include "conffile.h"
#include "format.h"
#include "file.h"
#include "parse.h"
#include "str.h"

#define MAX_FIELDS 8

int ConfFileLoad(
    const char* path,
    const char* delim,
    ConfFileCallback callback,
    void* data,
    char* err,
    size_t errSize)
{
    FILE* is;
    char buf[1024];
    unsigned int line;

    /* Open file */
    if (!(is = Fopen(path, "r")))
    {
        Snprintf(err, errSize, "%s: open failed", path);
        return -1;
    }

    /* Read line-by-line */
    for (line = 1; fgets(buf, sizeof(buf), is); line++)
    {
        char* p = buf;
        char* fields[MAX_FIELDS];
        size_t nfields = 0;
        StrtokState sts;

        /* Remove leading whitespace */
        while (isspace(*p))
            p++;

        /* Skip comments and blank lines */
        if (*p == '#' || *p == '\0')
            continue;

        /* Split the line into tokens */
        for (p = Strtok(&sts, buf, delim); p; p = Strtok(&sts, NULL, delim))
        {
            if (nfields == MAX_FIELDS)
            {
                Snprintf(err, errSize, "%s(%u): overflow", path, line);
                fclose(is);
                return -1;
            }

            fields[nfields++] = StripOuterSpaces(p);
            *err = '\0';

        }

        if (callback(path, line, fields, nfields, data, err, errSize) != 0)
        {
            if (*err == '\0')
                Snprintf(err, errSize, "%s(%u): failed", path, line);

            fclose(is);
            return -1;
        }
    }

    /* If read failed */
    if (!feof(is))
    {
        Snprintf(err, errSize, "%s: read failed", path);
        fclose(is);
        return -1;
    }

    fclose(is);
    return 0;
}
