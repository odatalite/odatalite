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
#ifndef _selector_h
#define _selector_h

#include "common.h"

#if defined(_MSC_VER)
# include <winsock2.h>
#else
# include <unistd.h>
# include <errno.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
#endif

#include <string.h>
#include "common.h"
#include "addr.h"
#include "sock.h"

/*
**==============================================================================
**
** USE_FDSET_INTERNALS
**
**==============================================================================
*/

#if defined(__GNUC__) && \
    defined(__FDELT) && \
    defined(__FDMASK) && \
    defined(__FDS_BITS)
# define USE_FDSET_INTERNALS
#endif

/*
**==============================================================================
**
** SELECTOR_READ
** SELECTOR_WRITE
** SELECTOR_EXCEPTION
** SELECTOR_DESTROY
**
**==============================================================================
*/

#define SELECTOR_READ (1 << 0)
#define SELECTOR_WRITE (1 << 1)
#define SELECTOR_EXCEPTION (1 << 2)
#define SELECTOR_DESTROY (1 << 3)

/*
**==============================================================================
**
** MAX_HANDLERS
**
**==============================================================================
*/

#define MAX_HANDLERS FD_SETSIZE

/*
**==============================================================================
**
** HandlerCallback
**
**==============================================================================
*/

typedef struct _Selector Selector;
typedef struct _Handler Handler;

typedef void (*HandlerCallback)(
    struct _Selector* selector,
    struct _Handler* handler, 
    unsigned int mask);

/*
**==============================================================================
**
** Handler
**
**==============================================================================
*/

struct _Handler
{
    /* ATTN: Sock should be 'int' since it can be used for fd's */
    /* Socket to watch */
    Sock sock;

#if defined(USE_FDSET_INTERNALS)
    unsigned long __fdelt;
    unsigned long __fdmask;
#endif

    /* Event to watch for (see SELECTOR_*) */
    unsigned int mask;

    /* Callback to be invoked on an event */
    HandlerCallback callback;
};

#if defined(USE_FDSET_INTERNALS)
# define HANDLER_SET(h, set) (__FDS_BITS(set)[h->__fdelt] |= h->__fdmask)
# define HANDLER_CLR(h, set) (__FDS_BITS(set)[h->__fdelt] &= ~h->__fdmask)
# define HANDLER_ISSET(h, set) (__FDS_BITS(set)[h->__fdelt] & h->__fdmask)
#else
# define HANDLER_SET(h, set) FD_SET(h->sock, set)
# define HANDLER_CLR(h, set) FD_CLR(h->sock, set)
# define HANDLER_ISSET(h, set) FD_ISSET(h->sock, set)
#endif

/*
**==============================================================================
**
** Selection
**
**==============================================================================
*/

typedef struct _Selection
{
    Handler* handler;
    unsigned int mask;
}
Selection;

/*
**==============================================================================
**
** Selector
**
**==============================================================================
*/

struct _Selector
{
    Handler* handlers[MAX_HANDLERS];
    size_t nhandlers;

    Selection selections[MAX_HANDLERS];
    size_t nselections;
    size_t index;

    fd_set rset;
    fd_set wset;
#if defined(ENABLE_EXCEPTIONS)
    fd_set eset;
#endif
};

void SelectorInit(
    Selector* self);

int SelectorAddHandler(
    Selector* self,
    Handler* handler);

int SelectorRemoveHandler(
    Selector* self,
    Handler* handler);

int SelectorRun(
    Selector* self,
    long sec,
    long usec);

void SelectorDestroy(
    Selector* self);

#endif /* _selector_h */
