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
#include "format.h"
#include "cleanup.h"
#include "str.h"
#include "conffile.h"

const char* __roleNames[] =
{
    "none",
    "guest",
    "operator",
    "admin"
};

Role __roles[NUM_ROLES];

static PHIT_Role _StrToRole(
    const char* str)
{
    size_t i;

    for (i = 0; i < ARRSIZE(__roleNames); i++)
    {
        if (strcmp(str, __roleNames[i]) == 0)
            return (PHIT_Role)i;
    }

    return PHIT_ROLE_NONE;
}

static Alloc _alloc = ALLOC_INITIALIZER;

static void _CleanupCallback(CleanupHandler* handler)
{
    size_t i;

    for (i = 0; i < NUM_ROLES; i++)
    {
        Role* role = &__roles[i];
        size_t j;

        for (j = 0; j < role->nusers; j++)
            AllocPut(&_alloc, role->users[j]);

        AllocPut(&_alloc, role->users);
    }
}

static CleanupHandler _cleanupHandler;

static int _Append(
    Role* role,
    const char* user_)
{
    char* user;

    if (!_cleanupHandler.callback)
    {
        _cleanupHandler.callback = _CleanupCallback;
        AddCleanupHandler(&_cleanupHandler);
    }

    if (!(user = AllocStrdup(&_alloc, user_)))
        return -1;

    if (AllocResize(
        &_alloc, 
        (void*)role->users, 
        sizeof(char*) * (role->nusers+1), 
        sizeof(char*) * role->nusers,
        (void**)&role->users) != 0)
    {
        return -1;
    }

    role->users[role->nusers++] = user;
    return 0;
}

int RoleAddUser(
    PHIT_Role role,
    const char* user)
{
    if (role == PHIT_ROLE_NONE)
        return -1;

    if (user[0] != '*' && ParseToken(user) == user)
        return -1;

    if (_Append(&__roles[role-1], user) != 0)
        return -1;

    return 0;
}

static int _FindUserOrWildcard(
    Role* role,
    const char* user)
{
    size_t i;

    for (i = 0; i < role->nusers; i++)
    {
        const char* tmpUser = role->users[i];

        /* Look for wildcard */
        if (tmpUser[0] == '*' && tmpUser[1] == '\0')
            return 0;

        /* Check user now */
        if (Streq(tmpUser, user) == 0)
            return 0;
    }

    return -1;
}

PHIT_Role RoleResolve(
    const char* user)
{
    size_t i;

    for (i = 3; i > 0; i--)
    {
        if (_FindUserOrWildcard(&__roles[i-1], user) == 0)
            return (PHIT_Role)i;
    }

    return PHIT_ROLE_NONE;
}

static int _ConfFileCallback(
    const char* path,
    unsigned int line,
    char** fields,
    size_t nfields,
    void* data,
    char* err,
    size_t errSize)
{
    PHIT_Role role;

    if (nfields != 2)
        return -1;

    /* Check username */
    if (*fields[0] == '\0')
    {
        Snprintf(err, errSize, "%s(%u): missing user", path, line);
        return -1;
    }

    /* Check role */
    if ((role = _StrToRole(fields[1])) == PHIT_ROLE_NONE)
    {
        Snprintf(err, errSize, "%s(%u): unknown role", path, line);
        return -1;
    }

    /* Add the new role */
    if (RoleAddUser(role, fields[0]) != 0)
    {
        Snprintf(err, errSize, "%s(%u): add failed", path, line);
        return -1;
    }

    return 0;
}

int RolesLoad(
    const char* path,
    char* err,
    size_t errSize)
{
    return ConfFileLoad(path, ":", _ConfFileCallback, NULL, err, errSize);
}
