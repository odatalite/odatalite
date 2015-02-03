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
#include "ptrarray.h"
#include "alloc.h"
#include <stdlib.h>

int PtrArray_Construct(
    PtrArray* self,
    size_t capacity,
    void (*destructor)(void*))
{
    if (capacity == 0)
        capacity = 1;

    self->size = 0;
    self->capacity = capacity;
    self->destructor = destructor;

    self->data = (void**)Malloc(self->capacity * sizeof(void*));

    if (!self->data)
        return -1;

    return 0;
}

void PtrArray_Destruct(
    PtrArray* self)
{
    if (self->destructor)
    {
        size_t i;

        for (i = 0; i < self->size; i++)
            (*self->destructor)(self->data[i]);

        self->destructor = NULL;
    }

    if (self->data)
    {
        Free(self->data);
        self->data = NULL;
    }
}

int PtrArray_Append(
    PtrArray* self, 
    void* element)
{
    if (self->size == self->capacity)
    {
        void** data;
        size_t capacity = self->capacity * 2;

        if (!(data = (void**)Realloc(self->data, capacity * sizeof(void*))))
            return -1;

        self->capacity = capacity;
        self->data = data;
    }

    self->data[self->size++] = element;
    return 0;
}
