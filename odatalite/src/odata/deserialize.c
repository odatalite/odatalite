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
#include <base/array.h>
#include "json.h"
#include "jsonobject.h"
#include "json.h"
#include "jsonparser.h"
#include "return.h"
#include "getters.h"
#include "setters.h"
#include "destructors.h"

#define static

#define MIN_STACK_CAPACITY 32

typedef struct _StackElem
{
    const char* name;
    JSON_Value value;
}
StackElem;

typedef struct _Stack /* overlays Array from <base/array.h> */
{
    StackElem* data;
    size_t size;
    size_t capacity;
}
Stack;

typedef struct _CallbackData
{
    const JSON_Char* name;
    Stack stack;
    int foundFirstObject;
    unsigned long long aligment;
    char allocBuf[sizeof(StackElem) * MIN_STACK_CAPACITY];
    Alloc alloc;
}
CallbackData;

static int _Push(
    CallbackData* data,
    const char* name,
    const JSON_Value* value)
{
    if (ArrayReserve(
        (Array*)&data->stack, 
        data->stack.size + 1,
        sizeof(StackElem),
        MIN_STACK_CAPACITY,
        &data->alloc) != 0)
    {
        return -1;
    }

    data->stack.data[data->stack.size].name = name;
    data->stack.data[data->stack.size].value = *value;
    data->stack.size++;

    return 0;
}

static OL_Result _AddValueToParent(
    JSON_Value* parent,
    const char* name,
    const JSON_Value* value,
    unsigned int flags)
{
    OL_Result r;

    if (parent->type == JSON_Type_Object)
    {
        if ((r = JSON_Object_AddF(
            parent->u.object,
            name, 
            value,
            flags)) != OL_Result_Ok)
        {
            RETURN(OL_Result_Failed);
        }

        return OL_Result_Ok;
    }
    else if (parent->type == JSON_Type_Array)
    {
        if ((r = JSON_Array_Append(parent->u.array, value)) != OL_Result_Ok)
            RETURN(OL_Result_Failed);

        return OL_Result_Ok;
    }

    RETURN(OL_Result_Failed);
}

static OL_Result _Callback(
    JSON_Parser* parser,
    JSON_Reason reason,
    JSON_Type type,
    const JSON_Union* value,
    void* callbackData)
{
    CallbackData* data = (CallbackData*)callbackData;
    OL_Result r;

    (void)data;

    switch (reason)
    {
        case JSON_Reason_None:
        {
            /* Unreachable */
            break;
        }
        case JSON_Reason_Name:
        {
            data->name = value->string;
            break;
        }
        case JSON_Reason_BeginObject:
        {
            JSON_Object* obj;
            StackElem* parent;
            JSON_Value v;

            if (data->stack.size == 0)
                RETURN(OL_Result_Failed);

            /* Nothing to do for root object */
            if (!data->foundFirstObject)
            {
                data->foundFirstObject = 1;
                return OL_Result_Ok;
            }

            /* Get pointer to parent (object or array) */
            parent = &data->stack.data[data->stack.size-1];

            /* Create new object */
            if (!(obj = JSON_Object_New(&obj)))
                RETURN(OL_Result_Failed);

            /* Initialize the value object */
            v.type = JSON_Type_Object;
            v.u.object = obj;

            /* Add object to parent (object or array) */
            if ((r = _AddValueToParent(
                &parent->value, 
                data->name,
                &v,
                JSON_FLAG_STATIC_NAME)) != OL_Result_Ok)
            {
                JSON_Object_Release(obj);
                RETURN(OL_Result_Failed);
            }

            /* Push object onto stack */
            if (_Push(data, data->name, &v) != 0)
            {
                JSON_Object_Release(obj);
                RETURN(OL_Result_Failed);
            }
            break;
        }
        case JSON_Reason_EndObject:
        {
            StackElem top;

            if (data->stack.size == 0)
                RETURN(OL_Result_Failed);

            /* Pop the stack */
            top = data->stack.data[--data->stack.size];

            /* Release the object on top of the stack */
            DEBUG_ASSERT(top.value.type == JSON_Type_Object);
            JSON_Object_Release(top.value.u.object);
            break;
        }
        case JSON_Reason_BeginArray:
        {
            JSON_Array* array;
            JSON_Value v;

            /* Create new object */
            if (!(array = JSON_Array_New()))
                RETURN(OL_Result_Failed);

            /* Initialize array value */
            v.type = JSON_Type_Array;
            v.u.array = array;

            /* Put array value onto stack */
            if (_Push(data, data->name, &v) != 0)
            {
#if 0
                JSON_Array_Release(array);
#endif
                RETURN(OL_Result_Failed);
            }

            break;
        }
        case JSON_Reason_EndArray:
        {
            StackElem parent;
            StackElem array;
            ValueDestructor dtor;

            if (data->stack.size == 0)
                RETURN(OL_Result_Failed);

            array = data->stack.data[--data->stack.size];

            if (array.value.type != JSON_Type_Array)
                RETURN(OL_Result_Failed);

            if (data->stack.size == 0)
                RETURN(OL_Result_Failed);

            /* Get pointer to parent (object or array) */
            parent = data->stack.data[data->stack.size-1];

            /* Add object to parent (object or array) */
            if ((r = _AddValueToParent(
                &parent.value, 
                array.name,
                &array.value,
                JSON_FLAG_STATIC_NAME)) != OL_Result_Ok)
            {
                RETURN(OL_Result_Failed);
            }

            dtor = GetDestructor(JSON_Type_Array);
            DEBUG_ASSERT(dtor);

            (*dtor)(&array.value, JSON_FLAG_STATIC_VALUE, NULL);
            break;
        }
        case JSON_Reason_Value:
        {
            JSON_Value v;
            StackElem* parent;

            if (data->stack.size == 0)
                RETURN(OL_Result_Failed);

            /* Get pointer to parent (object or array) */
            parent = &data->stack.data[data->stack.size-1];

            memset(&v, 0, sizeof(v));

            switch (type)
            {
                case JSON_Type_Null:
                {
                    v.type = JSON_Type_Null;
                    break;
                }
                case JSON_Type_Boolean:
                {
                    v.type = JSON_Type_Boolean;
                    v.u.boolean = value->boolean;
                    break;
                }
                case JSON_Type_Integer:
                {
                    v.type = JSON_Type_Integer;
                    v.u.integer = value->integer;
                    break;
                }
                case JSON_Type_Real:
                {
                    v.type = JSON_Type_Real;
                    v.u.real = value->real;
                    break;
                }
                case JSON_Type_String:
                {
                    v.type = JSON_Type_String;
                    v.u.string = (JSON_Char*)value->string;
                    break;
                }
                case JSON_Type_Object:
                case JSON_Type_Array:
                {
                    /* Nothing to do! */
                    break;
                }
            }

            /* Add object to obejct or array parent */
            if ((r = _AddValueToParent(
                &parent->value, 
                data->name, 
                &v,
                JSON_FLAG_STATIC_NAME|JSON_FLAG_STATIC_VALUE)) != OL_Result_Ok)
            {
                RETURN(OL_Result_Failed);
            }

            break;
        }
    }

    return OL_Result_Ok;
}

extern OL_Result Object_Deserialize(
    JSON_Object* self_,
    char* data,
    size_t size,
    size_t* offsetOut)
{
    JSONObject* self = (JSONObject*)self_;
    JSON_Parser parser;
    CallbackData callbackData;
    OL_Result r;
    size_t i;

    /* Check parameters */
    if (!self || self->magic != OBJECT_MAGIC || !data || !size)
        RETURN(OL_Result_BadParameter);

    /* Initialize the call data */
    {
        JSON_Value value;

        /* Clear callback data */
        memset(&callbackData, 0, sizeof(callbackData));

        /* CallbackData.alloc */
        AllocInit(
            &callbackData.alloc, 
            callbackData.allocBuf, 
            sizeof(callbackData.allocBuf));

        /* Push object onto stack */
        value.type = JSON_Type_Object;
        value.u.object = self_;
        _Push(&callbackData, NULL, &value);

        /* Add extra reference for storing on stack */
        JSON_Object_AddRef(&self->base);
    }

    /* Initialize parser */
    if ((r = JSON_Parser_Init(&parser, data, size, _Callback, 
        &callbackData)) != OL_Result_Ok)
    {
        goto done;
    }

    /* Parse input */
    if ((r = JSON_Parser_Parse(&parser)) != OL_Result_Ok)
    {
        goto done;
    }

    if (offsetOut)
        *offsetOut = parser.ptr - parser.data;

    r = OL_Result_Ok;

done:

    if (callbackData.stack.size!= 0)
        r = OL_Result_Failed;

    /* Release any leftover object on the stack */
    for (i = 0; i < callbackData.stack.size; i++)
    {
        ValueDestructor dtor;
        JSON_Value v = callbackData.stack.data[i].value;

        dtor = GetDestructor(v.type);

        if (dtor)
            (*dtor)(&v, JSON_FLAG_STATIC_VALUE, NULL);
    }

    /* Release the stack */
    AllocPut(&callbackData.alloc, callbackData.stack.data);

    return r;
}
