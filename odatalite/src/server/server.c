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
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <stdarg.h>
#include <base/addr.h>
#include <base/sock.h>
#include <base/selector.h>
#include <base/process.h>
#include <base/pidfile.h>
#include <base/cleanup.h>
#include <base/err.h>
#include <base/pam.h>
#include <base/path.h>
#include <base/role.h>
#include <base/log.h>
#include <base/alloc.h>
#include <base/getopt.h>
#include <base/conffile.h>
#include <base/format.h>
#include "listener.h"
#include "connection.h"
#include "options.h"
#include "help.h"
#include "plugin.h"

Options g_options;

static const char* arg0;


static int _ConfFileCallback(
    const char* path,
    unsigned int line,
    char** fields,
    size_t nfields,
    void* data,
    char* err,
    size_t errSize)
{
    Options* options = (Options*)data;
    const char* name;
    const char* value;

    if (nfields != 2)
    {
        Snprintf(err, errSize, "%s(%u): expected 2 fields", path, line);
        return -1;
    }

    name = fields[0];
    value = fields[1];

    if (strcmp(name, "port") == 0)
    {
        return StrToUShort(value, &options->port);
    }
    else if (strcmp(name, "noauth") == 0)
    {
        return StrToBool(value, &options->noauth);
    }
    else if (strcmp(name, "nodaemonize") == 0)
    {
        return StrToBool(value, &options->nodaemonize);
    }
    else if (strcmp(name, "dump") == 0)
    {
        return StrToBool(value, &options->dump);
    }
    else if (strcmp(name, "sockfile") == 0)
    {
        Strlcpy(options->sockfileBuf, value, sizeof(options->sockfileBuf));
        options->sockfile = options->sockfileBuf;
        return 0;
    }
    else if (strcmp(name, "loglevel") == 0)
    {
        return LogLevelFromString(value, &__logLevel);
    }
#if defined(ENABLE_SOCKTRACE)
    else if (strcmp(name, "logsockio") == 0)
    {
        return StrToBool(value, &__sockLog);
    }
#endif
    else if (strcmp(name, "logtostdout") == 0)
    {
        unsigned char flag;

        if (StrToBool(value, &flag) != 0)
            return -1;

        if (flag)
            LogSetStream(stdout);

        return 0;
    }

    Snprintf(err, errSize, "%s(%u): unknown option", path, line);
    return -1;
}

static void _GetConfFileOptions()
{
    char path[MAX_PATH_SIZE];
    char err[256];

    MakePath(ID_PHITD_CONF, path);

    if (access(path, R_OK) == 0 &&
        ConfFileLoad(
            path, "=", _ConfFileCallback, &g_options, err, sizeof(err)) != 0)
    {
        Err("%s", err);
    }
}

static void _GetOptions(Options* options, int* argc, char** argv)
{
    GetOptState gos = GETOPTSTATE_INITIALIZER;
    int opt;

    while ((opt = GetOpt(&gos, *argc, argv, "hfp:u:isg:o:a:l:SkDPR")) != -1)
    {
        switch (opt)
        {
            case 'h':
            {
                PrintHelp(arg0);
                exit(0);
            }
            case 'p':
            {
                if (StrToUShort(gos.optarg, &options->port) != 0)
                    Err("invalid arg: -%c %s", opt, gos.optarg);

                break;
            }
            case 'u':
            {
                options->sockfile = gos.optarg;
                break;
            }
            case 'f':
            {
                options->nodaemonize = 1;
                break;
            }
#if defined(ENABLE_PIDFILE)
            case 's':
            {
                options->stop = 1;
                break;
            }
#endif /* defined(ENABLE_PIDFILE) */
            case 'P':
            {
                options->paths = 1;
                break;
            }
            case 'R':
            {
                options->roles = 1;
                break;
            }
#if defined(ENABLE_LOGGING)
            case 'l':
            {
                if (LogLevelFromString(gos.optarg, &__logLevel) != 0)
                    Err("invalid arg: -%c %s", opt, gos.optarg);

                break;
            }
            case 'S':
            {
                LogSetStream(stdout);
                break;
            }
#endif /* defined(ENABLE_LOGGING) */
#if defined(ENABLE_ROLES)
            case 'g':
            {
                if (RoleAddUser(PHIT_ROLE_GUEST, gos.optarg) != 0)
                    Err("invalid username: -%c %s", opt, gos.optarg);

                break;
            }
            case 'o':
            {
                if (RoleAddUser(PHIT_ROLE_OPERATOR, gos.optarg) != 0)
                    Err("invalid username: -%c %s", opt, gos.optarg);

                break;
            }
            case 'a':
            {
                if (RoleAddUser(PHIT_ROLE_ADMIN, gos.optarg) != 0)
                    Err("invalid username: -%c %s", opt, gos.optarg);

                break;
            }
#endif /* defined(ENABLE_ROLES) */
#if defined(ENABLE_SOCKTRACE)
            case 'k':
            {
                __sockLog = 1;
                break;
            }
#endif /* defined(ENABLE_SOCKTRACE) */
            case 'i':
            {
                options->noauth = 1;
                break;
            }
#if defined(ENABLE_DEBUG)
            case 'D':
            {
                options->dump = 1;
                break;
            }
#endif /* defined(ENABLE_DEBUG) */
            case ':':
            {
                Err("missing option argument: -%c", gos.optopt);
            }
            case '?':
            {
                Err("unknown option: -%c", gos.optopt);
            }
            default:
            {
                Err("unknown option: -%c", opt);
            }
        }
    }

    *argc = gos.optind;
}

static int _terminated = 0;

static void _HandleSIGTERM(int sig)
{
    _terminated = 1;
}

#if defined(ENABLE_PIDFILE)
static int _StopServer()
{
    if (PIDFileIsRunning() != 0)
    {
        if (errno == EPERM || errno == EACCES)
            Err("permission denied");

        Err("not running");
        exit(1);
    }

    if (PIDFileSignal(SIGTERM) != 0)
    {
        Err("failed");
        exit(1);
    }

    printf("%s: stopped\n", arg0);
    exit(0);
}
#endif /* defined(ENABLE_PIDFILE) */

int main(int argc, char** argv)
{
    const unsigned short PORT = 8888;
    Selector selector;
#if defined(HAVE_POSIX)
    Listener unixListener;
#endif
    Listener inetListener;
    char sockfileBuf[MAX_PATH_SIZE];
#if defined(ENABLE_PIDFILE)
    int pidfile;
    char pidfileBuf[MAX_PATH_SIZE];
#endif /* defined(ENABLE_PIDFILE) */

    arg0 = argv[0];
    ErrSetArg0(arg0);

    /* Set the default options */
    memset(&g_options, 0, sizeof(Options));
    g_options.sockfile = MakePath(ID_SOCKFILE, sockfileBuf);
    g_options.port = PORT;

    /* Set the default options */
#if defined(ENABLE_ROLES)
    /* Load roles.conf */
    {
        char buf[MAX_PATH_SIZE];
        char err[128];

        if (RolesLoad(MakePath(ID_ROLES_CONF, buf), err, sizeof(err)) != 0)
            Err("%s", err);
    }
#endif /* defined(ENABLE_ROLES) */

    /* Set the default options */
    /* Process the configuration file before the command-line options */
    _GetConfFileOptions();

    /* Get command line options */
    _GetOptions(&g_options, &argc, argv);

    /* Dump the paths? */
    if (g_options.paths)
    {
        DumpPaths();
        exit(0);
    }

    /* Dump the roles */
    if (g_options.roles)
    {
        RoleDump();
        exit(0);
    }

#if defined(ENABLE_PAM_AUTH)
    /* Check that the PAM plugin is installed */
    if (access("/etc/pam.d/phit", R_OK) != 0)
    {
        fprintf(stderr, "%s: /etc/pam.d/phit not found\n\n", arg0);
        exit(1);
    }
#endif

    /* Stop the server? */
    if (g_options.stop)
    {
#if defined(ENABLE_PIDFILE)
        _StopServer();
#else
        Err("use kill (-s option is diabled)");
#endif /* defined(ENABLE_PIDFILE) */
    }

    /* Check arguments */
    if (argc != 1)
    {
        fprintf(stderr, "Use -h for help\n");
        exit(1);
    }

#if defined(ENABLE_PIDFILE)
    /* Bail out if server is already running */
    if (PIDFileIsRunning() == 0)
    {
        Err("already running: %s", MakePath(ID_PIDFILE, pidfileBuf));
    }
#endif /* defined(ENABLE_PIDFILE) */

    /* Load the plugins file */
    {
        char error[128];

        if (PluginLoad(error, PHIT_ARRAY_SIZE(error)) != 0)
            Err("%s", error);
    }

    /* Initialize the selector */
    SelectorInit(&selector);

    /* Handle SIGTERM */
    signal(SIGTERM, _HandleSIGTERM);

    /* Ignore SIGPIPE */
#if defined(HAVE_POSIX)
    signal(SIGPIPE, SIG_IGN);
#endif

    /* Initialize the sockets layer */
    {
        int r = SockStart();
        (void)r;
        DEBUG_ASSERT(r == 0);
    }

#if defined(HAVE_POSIX)
    /* Create listener for Unix-domain sockets */
    if (ListenerInit(&unixListener, &selector, g_options.sockfile, 0) != 0)
    {
        char buf[MAX_PATH_SIZE];
        Err("listen failed (uds): %s", MakePath(ID_SOCKFILE, buf));
    }
#endif /* defined(HAVE_POSIX) */

    /* Create listener for internet sockets */
    if (ListenerInit(&inetListener, &selector, NULL, g_options.port) != 0)
    {
        Err("listen failed (inet): port %u", g_options.port);
    }

    /* Daemonize */
#if defined(HAVE_POSIX)
    if (!g_options.nodaemonize)
        ProcessDaemonize();
#endif

#if defined(ENABLE_PIDFILE)
    /* Create PID file (after daemonize) */
    if ((pidfile = PIDFileCreate()) == -1)
    {
        Err("failed to create %s", MakePath(ID_PIDFILE, pidfileBuf));
    }
#endif /* defined(ENABLE_PIDFILE) */

    /* Run the selector */
    while (!_terminated)
    {
        SelectorRun(&selector, 1, 0);
    }

    /* Unload the plugins */
    PluginUnload();

    /* Close and delete the PID file */
#if defined(ENABLE_PIDFILE)
    {
        close(pidfile);

        if (PIDFileDelete() != 0)
        {
            Err("delete failed: %s\n", MakePath(ID_PIDFILE, pidfileBuf));
        }
    }
#endif /* defined(ENABLE_PIDFILE) */

    /* Release the selector (and any surviving handlers) */
    SelectorDestroy(&selector);

    /* Remove the socket file */
#if defined(ENABLE_EXEC_PROVIDERS)
    unlink(MakePath(ID_SOCKFILE, sockfileBuf));
#endif

    /* Shutdown the sockets layer */
    SockStop();

    LOGI(("Terminated"));

    /* Call all cleanup handlers */
    Cleanup();

#if defined(ENABLE_ALLOCATOR)
    /* Print allocation statistics */
    AllocPrintStatsAssert();
#endif

#if defined(ENABLE_SOCKTRACE)
    printf("Bytes sent: %llu\n", SockGetBytesSent());
    printf("Bytes recv: %llu\n", SockGetBytesRecv());
#endif /* ENABLE_SOCKTRACE */

    return 0;
}
