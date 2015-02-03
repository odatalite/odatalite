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
#ifndef _file_h
#define _file_h

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "common.h"
#include "alloc.h"

EXTERNC_BEGIN

/* Load the file given by 'path' into memory. Upon return '*dataOut' points 
 * to a zero-terminated memory block containing the contents of the file and 
 * '*sizeOut' is this size of this block (excluding the zero-terminator). 
 * If 'alloc' is non null, the memory will be obtained using that allocator.
 * Returns 0 on sucess. If successful, the caller must eventuall free the
 * memory by passing '*dataOut' to AllocPut().
 */
int FileLoad(
    const char* path,
    Alloc* alloc,
    char** dataOut,
    size_t* sizeOut);

INLINE FILE* Fopen(
    const char* path,
    const char* mode)
{
#if defined(_MSC_VER)
    FILE* fp;
    return fopen_s(&fp, path, mode) == 0 ? fp : NULL;
#else
    return fopen(path, mode);
#endif
}

INLINE size_t FileSize(
    const char* path)
{
    struct stat st;

    if (stat(path, &st) != 0)
        return (size_t)-1;

    return (size_t)st.st_size;
}

EXTERNC_END

#endif /* _file_h */
