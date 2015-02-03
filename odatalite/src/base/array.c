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
#include "array.h"
#include "alloc.h"
#include "roundpow2.h"

#define MIN_CAPACITY 4

int ArrayReserve(
    Array* self,
    size_t size,
    size_t elemSize,
    size_t minCapacity,
    Alloc* alloc)
{
    void* data;
    size_t capacity = size;

    if (size == 0)
        return -1;

    if (size < minCapacity)
        capacity = minCapacity;
    else
        capacity = RoundPow2(size);

    /* Allocate memory */
    if (AllocResize(
        alloc,
        self->data,
        capacity * elemSize, /* new size */
        self->size * elemSize, /* old size */
        (void**)&data))
    {
        return -1;
    }

    self->data = data;
    self->capacity = capacity;

    return 0;
}

int ArrayAppend(
    Array* self,
    void* element,
    size_t elementSize,
    Alloc* alloc)
{
    if (self->size == self->capacity)
    {
        size_t capacity;
        size_t size = self->size + 1;
        void* data;

        capacity = size < MIN_CAPACITY ? MIN_CAPACITY : RoundPow2(size);

        if (AllocResize(
            alloc,
            self->data,
            capacity * elementSize, /* new capacity */
            self->capacity * elementSize, /* old capacity */
            (void**)&data))
        {
            return -1;
        }

        self->data = data;
        self->capacity = capacity;
    }

    memcpy(
        (char*)self->data + (self->size * elementSize),
        element, 
        elementSize);

    self->size++;

    return 0;
}
