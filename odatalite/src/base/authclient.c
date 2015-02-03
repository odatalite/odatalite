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
# include <fcntl.h>
#endif

#include "auth.h"

#if defined(ENABLE_LOCAL_AUTH)

int AuthLoadFile(
    const char* path,
    char data[AUTH_DATA_SIZE+1])
{
    int fd;

    if ((fd = open(path, O_RDONLY)) == -1)
        return -1;

    if (read(fd, data, AUTH_DATA_SIZE) != AUTH_DATA_SIZE)
    {
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}

#endif /* defined(ENABLE_LOCAL_AUTH) */

/* Suppress warning that compilation unit is empty */
int __authclient_c;
