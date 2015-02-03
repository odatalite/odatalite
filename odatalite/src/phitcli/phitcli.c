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
#include <client/client.h>
#include <base/str.h>
#include <base/err.h>
#include <base/base64.h>
#include <base/path.h>
#include <base/getopt.h>
#include <base/str.h>
#include <base/buf.h>
#include <base/user.h>
#include <base/file.h>
#include <stdarg.h>
#include <limits.h>
#include "options.h"

#define D(X)

Options g_options;

static Client* s_client;
static char* s_request;
static size_t s_requestSize;
static size_t s_repeats = 0;

static void _Terminate(Client* client, int code)
{
    Selector* selector = client->selector;
    ClientDelete(client);

    if (selector)
        SelectorDestroy(selector);

    exit(code);
}

typedef struct _CallbackData
{
    int dummy;
}
CallbackData;

static void _ClientBeginCallback(
    Client* self,
    void* callbackData)
{
    D( printf("=== _ClientBeginCallback()\n"); )
}

static void _ClientErrorCallback(
    Client* self,
    const char* message,
    void* callbackData)
{
    printf("=== _ClientErrorCallback(): %s\n", message);

    _Terminate(self, 1);
}

#define PHIT_HEADERS_TRACE_FILE "phit.headers"
#define PHIT_CONTENT_TRACE_FILE "phit.content"

static void _ClientFoundEndOfHeadersCallback(
    Client* self, 
    const char* headers, 
    size_t headersLength,
    void* callbackData)
{
    FILE* os;

    D( printf("=== _ClientFoundEndOfHeadersCallback(): %s\n", message); )

    if (!g_options.quiet)
    {
        printf("%.*s", (int)headersLength, headers);
    }

    if (g_options.trace)
    {
        if (!(os = fopen(PHIT_HEADERS_TRACE_FILE, "a")))
            Err("failed to open '%s'", PHIT_HEADERS_TRACE_FILE);

        if (fwrite(headers, 1, headersLength, os) != headersLength)
            Err("failed to write '%s'", PHIT_HEADERS_TRACE_FILE);

        fclose(os);
    }
}

static void _ClientHeadersCallback(
    Client* self,
    unsigned long statusCode,
    const char* statusMsg,
    PHIT_Headers* headers,
    void* callbackData)
{
    D( printf("=== _ClientHeadersCallback()\n"); )

    if (statusCode != 200)
    {
        printf("Failed: HTTP Status Code: %lu\n", statusCode);
    }
}

static void _ClientContentCallback(
    Client* self, 
    const char* content, 
    size_t contentLength,
    void* callbackData)
{
    D( printf("=== _ClientContentCallback()\n"); )

    if (!g_options.quiet)
    {
        printf("%.*s", (int)contentLength, content);
    }

    if (g_options.trace)
    {
        FILE* os;

        if (!(os = fopen(PHIT_CONTENT_TRACE_FILE, "a")))
            Err("failed to open '%s'", PHIT_CONTENT_TRACE_FILE);

        if (fwrite(content, 1, contentLength, os) != contentLength)
            Err("failed to write '%s'", PHIT_CONTENT_TRACE_FILE);

        fclose(os);
    }
}

static void _ClientTrailersCallback(
    Client* self,
    PHIT_Headers* trailers,
    void* callbackData)
{
    D( printf("=== _ClientTrailersCallback()\n"); )
    PHIT_HeadersDump(trailers, 0);
}

static void _ClientEndCallback(
    Client* self,
    void* callbackData)
{
    D( printf("=== _ClientEndCallback()\n"); )

    if (!g_options.quiet)
        printf("\n");

    s_repeats++;

    if (s_repeats == g_options.repeat)
    {
        exit(0);
    }

    /* Post the request */
    if (ClientPostRequest(s_client, s_request, s_requestSize) != 0)
    {
        Err("ClientPostRequest() failed");
    }
}

const char* arg0;

static const char HELP[] = "\n\
Usage: %s [OPTIONS] PATH\n\
\n\
WHERE:\n\
    PATH is a file containing an HTTP request.\n\
\n\
OPTIONS:\n\
    -h          Print this help message\n\
    -H HOST     Connect to this host\n\
    -P PORT     Connect on this port\n\
    -s PATH     Connect on this Unix domain socket\n\
    -u USERNAME Authenticate as this user\n\
    -q          Quiet\n\
    -r N        Repeat the request N times\n\
    -i          Ignore authentication\n\
    -D          Dump incoming and outgoing messages to stdout\n\
    -H PATH     Send message response headers to this file\n\
    -C PATH     Send message response content to this file\n\
    -t          Trace responses to phit.headers and phit.content\n\
\n";

static void _GetOpts(int* argc, char** argv)
{
    GetOptState gos = GETOPTSTATE_INITIALIZER;
    int opt;

    while ((opt = GetOpt(&gos, *argc, argv, "hH:P:s:u:qr:iDt")) != -1)
    {
        switch (opt)
        {
            case 'h':
            {
                printf(HELP, arg0);
                exit(0);
            }
            case 'q':
            {
                g_options.quiet = 1;
                break;
            }
            case 'P':
            {
                unsigned long x;
                char* end = NULL;

                x = strtoul(gos.optarg, &end, 10);

                if (*end != '\0' || x > USHRT_MAX)
                    Err("invalid arg: -%c %s", opt, gos.optarg);

                g_options.port = (unsigned short)x;
                break;
            }
            case 'H':
            {
                g_options.host = gos.optarg;
                break;
            }
            case 's':
            {
                g_options.sockname = gos.optarg;
                break;
            }
            case 'u':
            {
                g_options.user = gos.optarg;
                break;
            }
            case 'r':
            {
                long x;
                char* end = NULL;

                x = strtol(gos.optarg, &end, 10);

                if (*end != '\0' || x < 0 || x > INT_MAX)
                    Err("invalid arg: -%c %s", opt, gos.optarg);

                g_options.repeat = (int)x;
                break;
            }
            case 'i':
            {
                g_options.ignoreAuth = 1;
                break;
            }
            case 'D':
            {
                g_options.dump = 1;
                break;
            }
            case 't':
            {
                g_options.trace = 1;
                break;
            }
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

#define AUTHORIZATION_LINE_SIZE 256

int FormatAuthorizationLine(
    char buf[AUTHORIZATION_LINE_SIZE],
    const char* username,
    const char* password)
{
    char tmp[64];
    char b64[128];
    Base64EncState state = BASE64ENCSTATE_INITIALIZER;
    size_t n;

    Strlcpy3(tmp, g_options.user, ":", password, sizeof(tmp));

    n = Base64Enc(&state, tmp, strlen(tmp), b64, sizeof(b64));

    if (n <= 0)
        return -1;

    b64[n] = '\0';
    Strlcpy2(buf, "Authorization: Basic ", b64, AUTHORIZATION_LINE_SIZE);

    return 0;
}

int BuildRequestFromFile(
    const char* path,
    const char* authLine,
    char** data,
    size_t* size)
{
    FILE* is;
    char line[1024];
    Buf buf = BUF_INITIALIZER;
    int foundEOF = 0;

    if (!(is = fopen(path, "rb")))
        return -1;

    while (fgets(line, sizeof(line), is))
    {
        if (!foundEOF && strcmp(line, "\r\n") == 0)
        {
            if (authLine && *authLine)
            {
                BufCatStr(&buf, authLine);
                BufCatStr(&buf, "\r\n");
            }

            foundEOF = 1;
        }
        BufCatStr(&buf, line);
    }

    *data = buf.data;
    *size = buf.size;

    fclose(is);
    return 0;
}

int main(int argc, const char* argv[])
{
    Selector selector;
    const unsigned short PORT = 8888;
    const char* password = NULL;
    char userBuffer[USERNAME_SIZE];
    char sockfileBuf[MAX_PATH_SIZE];
    CallbackData callbackData;
    char authLine[AUTHORIZATION_LINE_SIZE] = { '\0' };

    arg0 = argv[0];
    ErrSetArg0(arg0);

    /* Set the default options */
    memset(&g_options, 0, sizeof(Options));
    g_options.sockname = MakePath(ID_SOCKFILE, sockfileBuf);
    g_options.port = PORT;

    /* Set the repeat default */
    g_options.repeat = 1;

    /* Get command line options */
    _GetOpts(&argc, (char**)argv);

    /* Check arguments */
    if (argc != 2)
    {
        fprintf(stderr, "Use -h for help\n");
        exit(1);
    }

    /* Remove the trace files */
    if (g_options.trace)
    {
        unlink(PHIT_HEADERS_TRACE_FILE);
        unlink(PHIT_CONTENT_TRACE_FILE);
    }

#if defined(HAVE_POSIX)
    /* Ignore SIGPIPE */
    signal(SIGPIPE, SIG_IGN);
#endif

    /* Resolve the user (if not already given with -u option */
    if (!g_options.user)
    {
        if (GetCurrentUserName(userBuffer) != 0)
            Err("failed to resolve the current user name");

        g_options.user = userBuffer;
    }

    /* Initialize the selector */
    SelectorInit(&selector);

#if defined(ENABLE_PAM_AUTH)

    if (!g_options.ignoreAuth)
    {
        password = getpass("Password: ");

        if (!password)
            Err("invalid password");

        /* Create the HTTP "Authorization:" header line */
        if (FormatAuthorizationLine(authLine, g_options.user, password) != 0)
            Err("FormatAuthorizationLine() failed");
    }

#endif /* defined(ENABLE_PAM_AUTH) */

    /* ATTN: use string locator for both Unix and Inet sockets */

#if !defined(HAVE_POSIX)
    if (!g_options.host)
        g_options.host = "127.0.0.1";
#endif

    /* Initialize the sockets layer */
    SockStart();

    /* Initialize the callback data */
    memset(&callbackData, 0, sizeof(CallbackData));

    /* Create handler */
    if (!(s_client = ClientNew(
        &selector, 
        g_options.sockname, 
        g_options.host, 
        g_options.port, 
        g_options.user,
        password,
        _ClientBeginCallback,
        _ClientErrorCallback,
        _ClientFoundEndOfHeadersCallback,
        _ClientHeadersCallback,
        _ClientContentCallback,
        _ClientTrailersCallback,
        _ClientEndCallback,
        &callbackData)))
    {
        Err("failed to connect");
        exit(1);
    }
    
    /* Build the request from the file and the auth-line */
    if (BuildRequestFromFile(argv[1], authLine, 
        &s_request, &s_requestSize) != 0)
    {
        Err("failed to read '%s'\n", argv[1]);
    }

    /* Post the request */
    if (ClientPostRequest(s_client, s_request, s_requestSize) != 0)
    {
        Err("failed to post the request");
    }

    /* Run the main loop */
    for (;;)
    {
        SelectorRun(&selector, 1, 0);
    }

    /* Shutdown the socket layer */
    SockStop();

    /* Free the file memory block */
    Free(s_request);

    return 0;
}
