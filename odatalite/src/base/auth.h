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
#ifndef _phitd_auth_h
#define _phitd_auth_h

#include "common.h"

#if defined(HAVE_POSIX)
# include <unistd.h>
# include <sys/types.h>
#endif

# define AUTH_DATA_SIZE 64

typedef enum _AuthState
{
    AUTH_START,
    AUTH_PENDING,
    AUTH_ALLOWED,
    AUTH_DENIED
}
AuthState;

#if defined(ENABLE_LOCAL_AUTH)

int AuthCreateFile(
    uid_t uid, 
    char path[MAX_PATH_SIZE],
    char data[AUTH_DATA_SIZE+1]);

int AuthLoadFile(
    const char* path,
    char data[AUTH_DATA_SIZE+1]);

uid_t AuthGetUID(
    const char* name);

int AuthGetUserName(
    uid_t uid,
    char name[USERNAME_SIZE]);

#endif /* defined(ENABLE_LOCAL_AUTH) */

#endif /* _phitd_auth_h */
