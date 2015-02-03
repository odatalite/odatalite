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
#ifndef _phitd_options_h
#define _phitd_options_h

typedef struct _Options
{
    int help;

    /* Port to listen on */
    unsigned short port;

    /* Unix domain sockets files */
    const char* sockfile;
    char sockfileBuf[MAX_PATH_SIZE];

    /* Whether to run in foreground (no daemonize) */
    unsigned char nodaemonize;

    /* Whether to suppress authentication checks */
    unsigned char noauth;

    /* Whether to dump messages to standard output */
    unsigned char dump;

    /* Stop the server */
    int stop;

    /* Print the path location to standard output and exit */
    int paths;

    /* Print the roles to standard output and exit */
    int roles;
}
Options;

extern Options g_options;

#endif /* _phitd_options_h */
