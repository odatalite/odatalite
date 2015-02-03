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
# include <sys/errno.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
#endif

#include "pidfile.h"
#include "str.h"
#include "path.h"

#if defined(ENABLE_PIDFILE)

int PIDFileCreate()
{
    int fd;
    char buf[MAX_PATH_SIZE];

    /* Open the PID file */
    if ((fd = open(
        MakePath(ID_PIDFILE, buf), 
        O_WRONLY|O_CREAT|O_TRUNC, 
        0640)) == -1)
    {
        return -1;
    }

    /* Obtain an exclusive lock */
    if (lockf(fd, F_LOCK, 0) != 0)
        goto failed;

    /* Write PID into file */
    {
        char buf[11];
        size_t n;
        char* str = (char*)UIntToStr(buf, getpid(), &n);
        str[n++] = '\n';

        if (write(fd, str, n) != n)
            goto failed;
    }

    return fd;

failed:
    close(fd);
    return -1;
}

int PIDFileDelete()
{
    int pid;
    char buf[MAX_PATH_SIZE];

    /* Only process owner can delete the PID file */
    if ((pid = PIDFileRead()) == -1 || pid != getpid())
        return -1;

    if (unlink(MakePath(ID_PIDFILE, buf)) != 0)
        return -1;

    return 0;
}

int PIDFileRead()
{
    int fd;
    int pid;
    char buf[MAX_PATH_SIZE];
    
    if ((fd = open(MakePath(ID_PIDFILE, buf), O_RDONLY)) == -1)
        return -1;

    /* Read PID from file */
    {
        char buf[11];
        ssize_t n;
        
        if ((n = read(fd, buf, sizeof(buf))) < 1 || n >= sizeof(buf))
            goto failed;

        buf[n] = '\0';

        /* Convert buffer to PID */
        {
            char* end;
            unsigned long x = strtoul(buf, &end, 10);

            if (*end != '\n')
                goto failed;

            pid = (int)x;
        }
    }

    close(fd);
    return pid;

failed:
    close(fd);
    return -1;
}

int PIDFileSignal(int sig)
{
    int pid;

    /* Get PID  form PIDFILE */
    if ((pid = PIDFileRead()) == -1)
        return -1;

    /* Send a SIGTERM to the server */
    if (kill(pid, sig) != 0)
        return -1;

    return 0;
}

int PIDFileIsRunning()
{
    int pid;
    int fd;
    int r;
    char buf[MAX_PATH_SIZE];

    /* Open the PID file for write */
    if ((fd = open(MakePath(ID_PIDFILE, buf), O_WRONLY|O_NONBLOCK, 0640)) == -1)
    {
        return -1;
    }

    /* If able to obtain exclusive write lock, then PID file is stale */
    if ((r = lockf(fd, F_TEST, 0)) == 0)
    {
        unlink(buf);
        close(fd);
        return -1;
    }

    /* Close the file */
    close(fd);

    /* Fail if PIDFILE does not exist */
    if (access(buf, R_OK) == -1)
        return -1;

    /* Read PID form PIDFILE */
    if ((pid = PIDFileRead()) == -1)
        return -1;

    /* Test process to see if it is running */
    if (kill(pid, 0) == -1)
        return -1;

    /* Successful! */
    return 0;
}

#endif /* defined(ENABLE_PIDFILE) */
