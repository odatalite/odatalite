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
#include "addr.h"
#include "str.h"

int AddrInitInet(
    Addr* self,
    const char* host,
    unsigned short port)
{
    memset(self, 0, sizeof(*self));

    if (isalpha(host[0]))
    {
        struct hostent* ent = gethostbyname((char*)host);

        if (!ent)
            return -1;

        self->u.in.sin_family = ent->h_addrtype;
        memcpy(&self->u.in.sin_addr, ent->h_addr, ent->h_length);
    }
    else
    {
        in_addr_t ip = inet_addr((char*)host);

        if (ip == -1)
            return -1;

        self->u.in.sin_addr.s_addr = ip;
        self->u.in.sin_family = AF_INET;
    }

    self->u.in.sin_port = htons(port);
    self->type = ADDR_INET;
    self->length = sizeof(self->u.in);

    return 0;
}
