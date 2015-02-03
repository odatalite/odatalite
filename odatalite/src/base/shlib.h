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
#ifndef _phit_base_shlib_h
#define _phit_base_shlib_h

#include "common.h"

#if defined(HAVE_POSIX)
# include <dlfcn.h>
#else
# include <windows.h>
#endif

#include "alloc.h"
#include "str.h"

typedef struct _Shlib Shlib;

Shlib* ShlibOpen(const char* path);

INLINE int ShlibClose(Shlib* self)
{
#if defined(HAVE_POSIX)
    return dlclose(self);
#else
    return FreeLibrary((HMODULE)self) ? 0 : -1;
#endif
}


INLINE void* ShlibSym(
    Shlib* self,
    const char* symbol)
{
#if defined(_MSC_VER)
# pragma warning(disable:4054)
# pragma warning(disable:4055)

    FARPROC result;
    result = GetProcAddress((HMODULE)self, symbol);
    return (void*)result;
#else
    return dlsym(self, symbol);
#endif
}

INLINE size_t ShlibErr(char* buf, size_t bufSize)
{
#if defined(_MSC_VER)
    char* err = NULL;
    size_t r;

    if (!FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER|
        FORMAT_MESSAGE_FROM_SYSTEM|
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&err,
        0,
        NULL))
    {
        return 0;
    }

    r = Strlcpy(buf, err, bufSize);
    LocalFree(err);
    return r;
#else

    char* err;

    if (!(err = dlerror()))
        return 0;

    return Strlcpy(buf, err, bufSize);
#endif
}

INLINE int MakeShlibName(
    char buf[MAX_PATH_SIZE], 
    const char* libname)
{
    if (Strlcpy3(
        buf, 
        SHLIB_PREFIX, 
        libname, 
        SHLIB_SUFFIX, 
        MAX_PATH_SIZE) >= MAX_PATH_SIZE)
    {
	return -1;
    }

    return 0;
}

#endif /* _phit_base_shlib_h */
