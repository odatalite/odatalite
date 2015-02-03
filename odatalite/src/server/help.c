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
#include "help.h"

static const char HELP[] = "\n\
Usage: %s [OPTIONS]\n\
\n\
OPTIONS:\n\
    -h                  Print help message\n\
    -f                  Run server in foreground (rather than daemonizing)\n\
    -p PORT             Listen on this port\n\
    -u PATH             Listen on this Unix-domain socket\n\
    -i                  Ignore authentication\n\
    -P                  Print list of path locations\n";

#if defined(ENABLE_PIDFILE)
static const char HELP_PIDFILE[] = "\
    -s                  Stop the server\n";
#endif

#if defined(ENABLE_ROLES)
static const char HELP_ROLES[] = "\
    -g USER             Guest user (repeatable)\n\
    -o USER             Operator user (repeatable)\n\
    -a USER             Admin user (repeatable)\n";
#endif

#if defined(ENABLE_LOGGING)
static const char HELP_LOGGING[] = "\
    -l LEVEL            Log level: FATAL|ERROR|WARNING|INFO|DEBUG|VERBOSE\n\
    -S                  Send log output to standard output\n";
#endif

#if defined(ENABLE_SOCKTRACE)
static const char HELP_SOCKTRACE[] = "\
    -k                  Log soc[k]et I/O (phitsend.log and phitrecv.log)\n";
#endif

#if defined(ENABLE_DEBUG)
static const char HELP_DEBUG[] = "\
    -D                  Dump incoming and outgoing messages to stdout\n";
#endif

void PrintHelp(const char* arg0)
{
    printf(HELP, arg0);

#if defined(ENABLE_PIDFILE)
    printf(HELP_PIDFILE);
#endif

#if defined(ENABLE_ROLES)
    printf(HELP_ROLES);
#endif

#if defined(ENABLE_LOGGING)
    printf(HELP_LOGGING);
#endif

#if defined(ENABLE_SOCKTRACE)
    printf(HELP_SOCKTRACE);
#endif

#if defined(ENABLE_DEBUG)
    printf(HELP_DEBUG);
#endif

    putchar('\n');
}
