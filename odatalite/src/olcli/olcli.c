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
static size_t s_repeats = 0;
static int s_done = 0;
#define AUTHORIZATION_LINE_SIZE 1024
char s_authLine[AUTHORIZATION_LINE_SIZE] = { '\0' };

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

#define OLCLI_HEADERS_TRACE_FILE "olcli.headers"
#define OLCLI_CONTENT_TRACE_FILE "olcli.content"

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
        if (!(os = fopen(OLCLI_HEADERS_TRACE_FILE, "a")))
            Err("failed to open '%s'", OLCLI_HEADERS_TRACE_FILE);

        if (fwrite(headers, 1, headersLength, os) != headersLength)
            Err("failed to write '%s'", OLCLI_HEADERS_TRACE_FILE);

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

#if 0
    if (statusCode != 200)
    {
        printf("%lu %s\n", statusCode, statusMsg);
    }
#endif
}

static void _ClientContentCallback(
    Client* self, 
    const char* content, 
    size_t fileSize,
    void* callbackData)
{
    D( printf("=== _ClientContentCallback()\n"); )

    if (!g_options.quiet)
    {
        printf("%.*s", (int)fileSize, content);
    }

    if (g_options.trace)
    {
        FILE* os;

        if (!(os = fopen(OLCLI_CONTENT_TRACE_FILE, "a")))
            Err("failed to open '%s'", OLCLI_CONTENT_TRACE_FILE);

        if (fwrite(content, 1, fileSize, os) != fileSize)
            Err("failed to write '%s'", OLCLI_CONTENT_TRACE_FILE);

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
        s_done = 1;
        return; 
    }

#if 0
    /* Post the request */
    if (ClientPostRequest(s_client, request, requestSize) != 0)
    {
        Err("ClientPostRequest() failed");
    }
#endif
}

const char* arg0;

static const char HELP[] = "\n\
Usage: %s SUBCOMMAND [OPTIONS]\n\
\n\
WHERE:\n\
    SUBCOMMAND is get, post, put, patch, delete\n\
\n\
OPTIONS:\n\
    -h          Print this help message\n\
    -H HOST     Connect to this host (default %s)\n\
    -P PORT     Connect on this port (default %u)\n\
    -s PATH     Connect on this Unix domain socket (default %s)\n\
    -u USERNAME Authenticate as this user\n\
    -q          Quiet\n\
    -i          Ignore authentication\n\
    -t          Trace responses (creates olcli.headers and olcli.content)\n\
    -m TYPE     Metadata type: none/minimal/full\n\
\n";

static void _GetOpts(int* argc, char** argv)
{
    GetOptState gos = GETOPTSTATE_INITIALIZER;
    int opt;

    while ((opt = GetOpt(&gos, *argc, argv, "hH:P:s:u:qr:itm:")) != -1)
    {
        switch (opt)
        {
            case 'h':
            {
                g_options.help = 1;
                return;
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
            case 't':
            {
                g_options.trace = 1;
                break;
            }
            case 'm':
            {
                if (strcmp(gos.optarg, "none") != 0 &&
                    strcmp(gos.optarg, "minimal") != 0 &&
                    strcmp(gos.optarg, "full") != 0)
                {
                    Err("invalid arg: -%c %s", opt, gos.optarg);
                }

                g_options.metadata = gos.optarg;
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

void ProcessGet(
    int argc, 
    const char* argv[],
    Selector* selector)
{
    Buf buf = BUF_INITIALIZER;

    /* Check args */
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s get URI\n", argv[0]);
        exit(1);
    }

    /* Build the request */
    {
        BufFmt(&buf,
            "GET %s\r\n"
            "OData-Version: 4.0\r\n"
            "Accept: application/json;odata.metadata=%s\r\n",
            argv[2],
            g_options.metadata);

        if (*s_authLine)
        {
            BufCatStr(&buf, s_authLine);
            BufCatStr(&buf, "\r\n");
        }

        BufCatStr(&buf, "\r\n");
    }

    /* Post the request */
    if (ClientPostRequest(s_client, buf.data, buf.size) != 0)
    {
        Err("failed to post the request");
    }

    /* Run the main loop */
    while (!s_done)
    {
        SelectorRun(selector, 1, 0);
    }

    /* Free the request */
    BufDestroy(&buf);
}

void ProcessSubcommand(
    int argc, 
    const char* argv[],
    Selector* selector)
{
    Buf buf = BUF_INITIALIZER;
    const char* httpMethod = NULL;
    int needContent = 0;
    const char* path = NULL;
    size_t fileSize = 0;

    /* Resolve HTTP method to use and whether content is needed */
    if (strcmp(argv[1], "get") == 0)
    {
        httpMethod = "GET";
    }
    else if (strcmp(argv[1], "post") == 0)
    {
        httpMethod = "POST";
        needContent = 1;
    }
    else if (strcmp(argv[1], "put") == 0)
    {
        httpMethod = "PUT";
        needContent = 1;
    }
    else if (strcmp(argv[1], "patch") == 0)
    {
        httpMethod = "PATCH";
        needContent = 1;
    }
    else if (strcmp(argv[1], "delete") == 0)
    {
        httpMethod = "DELETE";
    }
    else
    {
        Err("unknown subcommand: %s", argv[1]);
    }

    /* Check args */
    if (needContent)
    {
        if (argc != 4)
        {
            fprintf(stderr, "Usage: %s %s URI FILENAME\n", argv[0], argv[1]);
            exit(1);
        }

        path = argv[3];
    }
    else
    {
        if (argc != 3)
        {
            fprintf(stderr, "Usage: %s %s URI\n", argv[0], argv[1]);
            exit(1);
        }
    }

    /* Get the content length */
    if (path)
    {
        if ((fileSize = FileSize(path)) == (size_t)-1)
            Err("file not found: %s", path);
    }

    /* Build the request */
    {
        BufFmt(&buf,
            "%s %s\r\n"
            "OData-Version: 4.0\r\n"
            "Accept: application/json;odata.metadata=%s\r\n",
            httpMethod,
            argv[2],
            g_options.metadata);

        if (fileSize)
        {
            BufFmt(&buf, "Content-Length: %lu\r\n", (unsigned long)fileSize);
        }

        if (*s_authLine)
        {
            BufCatStr(&buf, s_authLine);
            BufCatStr(&buf, "\r\n");
        }

        BufCatStr(&buf, "\r\n");
    }

    /* Append file if any */
    if (path && BufCatFile(&buf, path) != 0)
    {
        Err("BufCatFile() failed");
    }

    /* Post the request */
    if (ClientPostRequest(s_client, buf.data, buf.size) != 0)
    {
        Err("failed to post the request");
    }

    /* Run the main loop */
    while (!s_done)
    {
        SelectorRun(selector, 1, 0);
    }

    /* Free the request */
    BufDestroy(&buf);
}

int main(int argc, const char* argv[])
{
    Selector selector;
    const unsigned short PORT = 8888;
    const char* HOST = "127.0.0.1";
    const char* password = NULL;
    char userBuffer[USERNAME_SIZE];
    char sockfileBuf[MAX_PATH_SIZE];
    CallbackData callbackData;

    arg0 = argv[0];
    ErrSetArg0(arg0);

    /* Set the default options */
    memset(&g_options, 0, sizeof(Options));
    g_options.sockname = MakePath(ID_SOCKFILE, sockfileBuf);
    g_options.port = PORT;
    g_options.metadata = "minimal";

    /* Set the repeat default */
    g_options.repeat = 1;

    /* Get command line options */
    _GetOpts(&argc, (char**)argv);

    /* Print help? */
    if (g_options.help)
    {
        printf(HELP, arg0, HOST, PORT, g_options.sockname);
        exit(1);
    }

    /* Check arguments */
    if (argc < 2)
    {
        fprintf(stderr, "Use -h for help\n");
        exit(1);
    }

    /* Remove the trace files */
    if (g_options.trace)
    {
        unlink(OLCLI_HEADERS_TRACE_FILE);
        unlink(OLCLI_CONTENT_TRACE_FILE);
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
        if (FormatAuthorizationLine(s_authLine, g_options.user, password) != 0)
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

    /* Process the request */
    ProcessSubcommand(argc, argv, &selector);

    /* Shutdown the socket layer */
    SockStop();

    return 0;
}
