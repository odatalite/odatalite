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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
# include <stdlib.h>
# include <sys/types.h>
# include <pwd.h>
# include <base/str.h>
# include <base/path.h>
#endif

#include "auth.h"

#if defined(ENABLE_LOCAL_AUTH)

uid_t AuthGetUID(
    const char* name)
{
    struct passwd pwbuf;
    char buf[1024];
    struct passwd* pw;

    if (getpwnam_r(name, &pwbuf, buf, sizeof(buf), &pw) != 0 || !pw)
        return -1;

    return pw->pw_uid;
}

static void _GenerateRandomData(
    char data[AUTH_DATA_SIZE+1])
{
    static int seeded;
    size_t i;
    char* p = data;

    if (!seeded)
    {
        srand(time(NULL));
        seeded = 1;
    }

    for (i = 0; i < AUTH_DATA_SIZE/2; i++)
    {
        UCharToHexStr(p, (unsigned char)(rand() % 256));
        p += 2;
    }

    p[0] = '\0';
}

static int _FormatFileName(
    uid_t uid,
    char path[MAX_PATH_SIZE])
{
    static unsigned int counter;
    char name[USERNAME_SIZE];

    counter++;

    if (AuthGetUserName(uid, name) != 0)
        return -1;

    {
        int n;
        char buf[MAX_PATH_SIZE];

        n = Snprintf(path, MAX_PATH_SIZE, "%s/%s.%u", 
            MakePath(ID_AUTHDIR, buf), name, counter);

        if (n >= MAX_PATH_SIZE)
            return -1;
    }

    return 0;
}

static int _CreateFile(
    uid_t uid,
    const char* path,
    const char data[AUTH_DATA_SIZE+1])
{
    int fd;

    unlink(path);

    if ((fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR)) == -1)
        return -1;

    if (write(fd, data, AUTH_DATA_SIZE) != (int)AUTH_DATA_SIZE)
    {
        goto failed;
    }

    if (fchown(fd, uid, -1) != 0)
    {
        goto failed;
    }

    close(fd);
    return 0;

failed:
    close(fd);
    unlink(path);
    return -1;
}

int AuthCreateFile(
    uid_t uid, 
    char path[MAX_PATH_SIZE],
    char data[AUTH_DATA_SIZE+1])
{
    /* Format the file name: <AUTH_DIR>/<USERNAME>.<COUNTER> */
    if (_FormatFileName(uid, path) != 0)
        return -1;

    /* Generate random */
    _GenerateRandomData(data);

    /* Create the file */
    if (_CreateFile(uid, path, data) != 0)
        return -1;

    return 0;
}

#endif /* defined(ENABLE_LOCAL_AUTH) */

/* Suppress warning that compilation unit is empty */
int __authserver_c;
