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
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/wait.h>
#endif

#include "str.h"
#include "pam.h"

#if defined(ENABLE_PAM_AUTH)

#if 1
# include <security/pam_appl.h>
#else
# include <pam/pam_appl.h>
#endif

static int _PAMAuthCallback(
    int nmessages,
    const struct pam_message** messages,
    struct pam_response** resp,
    void* applicationData)
{
    const char* password = (const char*)applicationData;
    int i;

    /* Fail if no messages */
    if (nmessages <= 0)
        return PAM_CONV_ERR;

    /* Allocate the responses */
    if (!(*resp = (struct pam_response*)calloc(nmessages, sizeof(**resp))))
        return PAM_BUF_ERR;

    /* Copy the password to the resp messages */
    for (i = 0; i < nmessages; i++)
    {
        if (messages[i]->msg_style == PAM_PROMPT_ECHO_OFF)
        {
            resp[i]->resp = (char*)malloc(PAM_MAX_MSG_SIZE);
            Strlcpy(resp[i]->resp, password, PAM_MAX_MSG_SIZE);
            resp[i]->resp_retcode = 0;
        }
        else
            return PAM_CONV_ERR;
    }

    return PAM_SUCCESS;
}

static int _PAMCheckUser(
    const char* user, 
    const char* password)
{
    struct pam_conv conv;
    pam_handle_t* t = NULL;
    int r = 0;

    memset(&conv, 0, sizeof(conv));

    /* Work around callback signature incompatibilities across platforms */
    {
#if 0
        void** convptr = (void**)&conv.conv;
        *convptr = _PAMAuthCallback;
#else
        conv.conv = _PAMAuthCallback;
#endif
    }
    conv.appdata_ptr = (void*)password;

    if (pam_start("phit", user, &conv, &t) != PAM_SUCCESS)
        return -1;

    if (pam_authenticate(t, 0) != PAM_SUCCESS)
    {
        r = -1;
        goto done;
    }

    if (pam_acct_mgmt(t, 0) != PAM_SUCCESS)
    {
        r = -1;
        goto done;
    }

done:
    pam_end(t, 0);
    return r;
}

#if defined(ENABLE_PAM_FORKING)

static void _CloseAllBut(int fd)
{
    int n;
    int i;
    const int SIZE = 2500;
    const int OFFSET = STDERR_FILENO + 1;

    /* Limit in case getdtablesize() returns something huge (2^64) */
    if ((n = getdtablesize()) < 0 || n > SIZE)
        n = SIZE;

    for (i = OFFSET; i < n; ++i)
    {
        if (i != fd)
            close(i);
    }
}

static pid_t _PAMFork(
    int* fd,
    const char* user, 
    const char* password)
{
    int s[2];
    int child;

    /* create communication pipe */
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, s) != 0)
        return -1;

    child = fork();

    if (child < 0)
    {
        /* Failed */
        close(s[0]);
        close(s[1]);
        return -1;
    }
    else if (child > 0)
    {
        /* Inside Parent */
        close(s[1]);
        *fd = s[0];
        return child;
    }
    else
    {
        int r;

        /* Inside Child */

        /* Close all open file descriptors but the given socket */
        _CloseAllBut(s[1]);

        /* Authenticate the user (and write result to the pipe) */
        r = _PAMCheckUser(user, password);
        write(s[1], &r, sizeof(r));
        close(s[1]);

        /* Exit the child process */
        _exit(0);
    }
}

#endif /* defined(ENABLE_PAM_FORKING) */

int PAMAuth(
    const char* user, 
    const char* password)
{
#if defined(ENABLE_PAM_FORKING)

    int fd;
    pid_t child;
    int n;
    int r;

    if ((child = _PAMFork(&fd, user, password)) == -1)
        return -1;

    while ((n = read(fd, &r, sizeof(int))) == -1 && errno == EINTR)
        ;

    if (n != sizeof(int))
        return -1;

    close(fd);
    waitpid(child, NULL, WNOHANG);

    return r;

#else /* defined(ENABLE_PAM_FORKING) */

    return _PAMCheckUser(user, password);

#endif /* defined(ENABLE_PAM_FORKING) */
}

#endif /* defined(ENABLE_PAM_AUTH) */
