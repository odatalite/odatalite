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
#include <stdio.h>
#include "selector.h"

/*
**==============================================================================
**
** Local options:
**
**==============================================================================
*/

#if 0
# define CHECK_DUPLICATE_ADDS
#endif

#if 0
# define ENABLE_EXCEPTIONS
#endif

/*
**==============================================================================
**
** _FindHandler()
**
**==============================================================================
*/

static size_t _FindHandler(Selector* self, Handler* handler)
{
    size_t i;

    for (i = 0; i < self->nhandlers; i++)
    {
        if (self->handlers[i] == handler)
            return i;
    }

    return (size_t)-1;
}

/*
**==============================================================================
**
** _DispatchNextSelection()
**
**==============================================================================
*/

static int _DispatchNextSelection(
    Selector* self)
{
    /* Dispatch each active handler */
    for (; self->index < self->nselections; self->index++)
    {
        Selection* sel = &self->selections[self->index];

        /* If handler not already removed, then dispatch it */
        if (sel->mask)
        {
            (*sel->handler->callback)(self, sel->handler, sel->mask);
            self->index++;
            return 1;
        }
    }

    return 0;
}

void SelectorInit(
    Selector* self)
{
    memset(self, 0, sizeof(Selector));
    FD_ZERO(&self->rset);
    FD_ZERO(&self->wset);
#if defined(ENABLE_EXCEPTIONS)
    FD_ZERO(&self->eset);
#endif
}

/*
**==============================================================================
**
** SelectorAddHandler()
**
**==============================================================================
*/

int SelectorAddHandler(
    Selector* self,
    Handler* handler)
{
    if (self->nhandlers == MAX_HANDLERS)
        return -1;

#if defined(CHECK_DUPLICATE_ADDS)
    if (_FindHandler(self, handler) != (size_t)-1)
        return -1;
#endif


#if defined(USE_FDSET_INTERNALS)
    handler->__fdelt = __FDELT(handler->sock);
    handler->__fdmask = __FDMASK(handler->sock);
#endif

    self->handlers[self->nhandlers++] = handler;

    DEBUG_ASSERT(_FindHandler(self, handler) != (size_t)-1);

    return 0;
}

/*
**==============================================================================
**
** SelectorRemoveHandler()
**
**==============================================================================
*/

int SelectorRemoveHandler(
    Selector* self,
    Handler* handler)
{
    size_t i;
    size_t pos;

    /* Remove from the handler list */
    {
        if ((pos = _FindHandler(self, handler)) == (size_t)-1)
            return -1;

        self->handlers[pos] = self->handlers[self->nhandlers-1];
        self->nhandlers--;
    }

    DEBUG_ASSERT(_FindHandler(self, handler) == (size_t)-1);

    /* Mark as dead in the selection list */
    for (i = 0; i < self->nselections; i++)
    {
        if (self->selections[i].handler == handler)
        {
            /* Make this into a dead selection (will not be dispatched) */
            self->selections[i].mask = 0;
            break;
        }
    }

    /* Not found */
    return -1;
}

/*
**==============================================================================
**
** SelectorRun()
**
**==============================================================================
*/

int SelectorRun(
    Selector* self,
    long sec,
    long usec)
{
    /*HOTSPOT*/
    int n = 0;
    size_t i;
    struct timeval tv;
    struct timeval* ptv = NULL;
    int totalBits;

    /* Dispatch the next selection if any */
    if (_DispatchNextSelection(self) == 1)
        return 1;

    /* Clear the selections array */
    self->index = 0;
    self->nselections = 0;

    /* Initialize timeout pointer (possibly null) */
    if (sec != -1)
    {
        tv.tv_sec = sec;
        tv.tv_usec = usec;
        ptv = &tv;
    }

    /* Set up descriptor sets */
    for (i = 0; i < self->nhandlers; i++)
    {
        const Handler* p = self->handlers[i];

        if (p->mask & SELECTOR_READ)
        {
            /*HOTSPOT*/
            HANDLER_SET(p, &self->rset);
        }

        if (p->mask & SELECTOR_WRITE)
        {
            /*HOTSPOT*/
            HANDLER_SET(p, &self->wset);
        }

#if defined(ENABLE_EXCEPTIONS)
        if (p->mask & SELECTOR_EXCEPTION)
            HANDLER_SET(p, &self->eset);
#endif

        /* Note that first argument to select() is ingored on Windows */
#if !defined(_MSC_VER)
        if (p->sock > n)
            n = p->sock;
#endif
    }

    /* Perform select */
    {
#if defined(ENABLE_EXCEPTIONS)
        totalBits = select(n + 1, &self->rset, &self->wset, &self->eset, ptv);
#else
        totalBits = select(n + 1, &self->rset, &self->wset, NULL, ptv);
#endif
        if (totalBits < 1)
        {
            /* Failed: totalBits==-1 or Timeout: totalBits==0 */
            return totalBits;
        }
    }

    /* Build an array of selections to be dispatched. Work backwards
     * since experience shows that higher-numbered descriptors tend
     * be busier (since the listener is usually a lower numbered
     * descriptor).
     */

    for (i = self->nhandlers; totalBits && i > 0; i--)
    {
        Handler* p = self->handlers[i-1];
        unsigned int mask = 0;

        if ((p->mask & SELECTOR_WRITE) && HANDLER_ISSET(p, &self->wset))
        {
            mask |= SELECTOR_WRITE;
            HANDLER_CLR(p, &self->wset);
            totalBits--;
        }

        if (totalBits && (p->mask & SELECTOR_READ) && HANDLER_ISSET(p, &self->rset))
        {
            mask |= SELECTOR_READ;
            HANDLER_CLR(p, &self->rset);
            totalBits--;
        }

#if defined(ENABLE_EXCEPTIONS)
        if (totalBits && (p->mask & SELECTOR_EXCEPTION) && HANDLER_ISSET(p, &self->eset))
        {
            mask |= SELECTOR_EXCEPTION;
            HANDLER_CLR(p, &self->eset);
            totalBits--;
        }
#endif

        if (mask)
        {
            self->selections[self->nselections].handler = p;
            self->selections[self->nselections].mask = mask;
            self->nselections++;
        }
    }

    /* Dispatch the next selection if any */
    return _DispatchNextSelection(self);
}

/*
**==============================================================================
**
** SelectorDestroy>()
**
**==============================================================================
*/

void SelectorDestroy(
    Selector* self)
{
    size_t i;

    self->nselections = 0;

    for (i = 0; i < self->nhandlers; i++)
    {
        self->selections[self->nselections].handler = self->handlers[i];
        self->selections[self->nselections].mask = SELECTOR_DESTROY;
        self->nselections++;
    }

    for (i = 0; i < self->nselections; i++)
    {
        Selection* sel = &self->selections[i];
        (*sel->handler->callback)(self, sel->handler, sel->mask);
    }
}
