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
#include "role.h"
#include "alloc.h"
#include "parse.h"
#include "str.h"

static void _Dump(Role* role)
{
    size_t i;

    for (i = 0; i < role->nusers; i++)
    {
        printf("%s", role->users[i]);

        if (i + 1 != role->nusers)
            putchar(' ');
    }

    putchar('\n');
}

void RoleDump()
{
    printf("guests: ");
    _Dump(&__roles[PHIT_ROLE_GUEST-1]);

    printf("operators: ");
    _Dump(&__roles[PHIT_ROLE_OPERATOR-1]);

    printf("admins: ");
    _Dump(&__roles[PHIT_ROLE_ADMIN-1]);
}
