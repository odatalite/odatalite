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
#include "common.h"

#if defined(HAVE_POSIX)
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#endif

#include "process.h"

#if defined(HAVE_POSIX)

int ProcessDaemonize()
{
    int pid;

    /* Fork for the first time */
    pid = fork();
    if (pid == -1)
        return -1;

    /* If parent, then exit; let child live on. */
    if (pid > 0)
	exit(0);

    /* Become the session leader (return if this fails) */
    if (setsid() == -1)
        return -1;

    /* Fork a second time */
    if ((pid = fork()) == -1)
	return -1;

    /* If parent (first child), then exit; let second child live one */
    if (pid > 0)
        exit(0);

    /* Close STDIN, STDOUT, and STDERR */
    close(0);
    close(1);
    close(2);

    /* Tie STDIN to /dev/null */
    open("/dev/null", O_RDONLY);

    /* Tie STDOUT to /dev/null */
    open("/dev/null", O_RDWR);

    /* Tie STDERR to /dev/null */
    open("/dev/null", O_RDWR);

    /* Set root directory as current directory */
    chdir("/");

    return 0;
}

#endif /* defined(HAVE_POSIX) */
