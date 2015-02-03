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
#include "destructors.h"

static void _StringDestructor(
    JSON_Value* value,
    unsigned int flags,
    Alloc* alloc)
{
    if (!(flags & JSON_FLAG_STATIC_VALUE))
    {
        if (alloc)
            AllocPut(alloc, value->u.string);
        else
            Free(value->u.string);
    }
}

static void _ObjectDestructor(
    JSON_Value* value,
    unsigned int flags,
    Alloc* alloc)
{
    OL_Result r = JSON_Object_Release(value->u.object);
    (void)r;
    DEBUG_ASSERT(r == OL_Result_Ok);
}

static void _ArrayDestructor(
    JSON_Value* value,
    unsigned int flags,
    Alloc* alloc)
{
    OL_Result r = JSON_Array_Release(value->u.array);
    (void)r;
    DEBUG_ASSERT(r == OL_Result_Ok);
}

ValueDestructor __destructors[] =
{
    NULL, /* Null */
    NULL, /* Boolean */
    NULL, /* Int64 */
    NULL, /* Double */
    _StringDestructor, /* String */
    _ObjectDestructor, /* Object */
    _ArrayDestructor, /* Array */
    NULL, /* Byte */
    NULL, /* SByte */
    NULL, /* Int16 */
    NULL, /* Int32 */
    NULL, /* Single */
    NULL, /* Decimal */
    NULL, /* Binary */
    NULL, /* Date */
    NULL, /* TimeOfDay */
    NULL, /* DateTimeOffset */
    NULL, /* Duration */
    NULL, /* Guid */
    _StringDestructor, /* NavigationLink */
    _StringDestructor, /* AssociationLink */
};

