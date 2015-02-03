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
#ifndef _phit_role_h
#define _phit_role_h

#include "common.h"
#include "conffile.h"
#include <phit.h>

/* The number of roles (admin, operator, guest) */
#define NUM_ROLES 3

typedef struct _Role
{
    char** users;
    size_t nusers;
}
Role;

extern Role __roles[NUM_ROLES];

extern const char* __roleNames[];

int RoleAddUser(
    PHIT_Role role,
    const char* user);

PHIT_Role RoleResolve(
    const char* user);

INLINE const char* RoleName(PHIT_Role role)
{
    return __roleNames[(unsigned int)role];
}

int RolesLoad(
    const char* path,
    char* err,
    size_t errSize);

void RoleDump();

#endif /* _phit_role_h */
