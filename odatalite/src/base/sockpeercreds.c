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
#include "sock.h"

#if defined(__APPLE__)
# define PEERCRED LOCAL_PEERCRED
#else
# define PEERCRED SO_PEERCRED
#endif

#if defined(ENABLE_LOCAL_AUTH)

int SockGetPeerCreds(
    Sock sock,
    uid_t* uid,
    gid_t* gid)
{
    struct ucred uc;
    socklen_t len = sizeof(struct ucred);

    if (getsockopt(sock, SOL_SOCKET, PEERCRED, &uc, &len) != 0)
    {
        /* This may fail on platforms that don't support SO_PEERCRED */
        return -1;
    }

#if defined(__APPLE__)
    if (uid)
        *uid = uc.cr_uid;
    if (gid)
        *gid = uc.cr_rgid;
#else
    if (uid)
        *uid = uc.uid;
    if (gid)
        *gid = uc.gid;
#endif

    return 0;
}

#endif /* defined(ENABLE_LOCAL_AUTH) */

/* Expand to full shared library name */
int __sockpeercreds_h;
