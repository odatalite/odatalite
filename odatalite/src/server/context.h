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
#ifndef _context_h
#define _context_h

#include "common.h"
#include <phit.h>
#include <base/alloc.h>
#include <base/buf.h>

typedef struct _Connection Connection;

#define DETAIL_SIZE 128

typedef struct _Context
{
    /* Base type */
    PHIT_Context base;

    /* Back pointer to the connection */
    Connection* connection;

    /* Plugin for this context */
    PHIT_Plugin* plugin;

    /* Whether client accepts chunked encoding */
    int acceptChunkedEncoding;

    /* Whether to use chunked encoding or not */
    int chunkedEncoding;

    /* Whether plugin has posted end-of-headers */
    int postedEOH;

    /* Whether plugin has posted end-of-content */
    int postedEOC;

    /* Data set by the plugin */
    void* pluginData;

    /* Status code from the PostStatusLine() method */
    PHIT_StatusCode statusCode;
}
Context;

void ContextInit(
    Context* self,
    Connection* connection);

void ContextReset(
    Context* self);

void ContextDestroy(
    Context* self);

#endif /* _context_h */
