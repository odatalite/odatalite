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
#include "common.h"

#if defined(HAVE_POSIX)
# include <unistd.h>
# include <sys/types.h>
# include <pwd.h>
#endif

#include "str.h"
#include "user.h"

int GetCurrentUserName(
    char name[USERNAME_SIZE])
{
    struct passwd pwbuf;
    char buf[1024];
    struct passwd* pw;

    if (getpwuid_r(getuid(), &pwbuf, buf, sizeof(buf), &pw) != 0 || !pw)
        return -1;

    if (Strlcpy(name, pw->pw_name, USERNAME_SIZE) >= USERNAME_SIZE)
        return -1;

    return 0;
}
