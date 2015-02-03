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
#include <stdlib.h>
#include <odata/jsonparser.h>
#include <base/file.h>
#include <stack>
#include "objects.h"

const char* arg0;

using namespace std;

typedef struct _CallbackData
{
    Object* object; // root object
    std::string name;

    /* Object or Array elements */
    std::stack<Aggregate*> aggregates;
}
CallbackData;

ODATA_Result _Callback(
    JSON_Parser* parser,
    JSON_Reason reason,
    JSON_Type type,
    const JSON_Union* value,
    void* callbackData)
{
    CallbackData* data = (CallbackData*)callbackData;

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
            if (data->object)
            {
                Aggregate* parent = data->aggregates.top();
                assert(parent != 0);

                Object* child = new Object;
                parent->Add(data->name, child);
                data->aggregates.push(child);
            }
            else
            {
                data->object = new Object;
                data->aggregates.push(data->object);
            }

            break;
        }
        case JSON_Reason_EndObject:
        {
            data->aggregates.pop();
            break;
        }
        case JSON_Reason_BeginArray:
        {
            Aggregate* parent = data->aggregates.top();
            assert(parent != 0);

            Array* child = new Array;
            parent->Add(data->name, child);
            data->aggregates.push(child);

            break;
        }
        case JSON_Reason_EndArray:
        {
            data->aggregates.pop();
            break;
        }
        case JSON_Reason_Value:
        {
            Aggregate* parent = data->aggregates.top();
            assert(parent != 0);

            assert(value != 0);

            Value* child = new Value(type, *value);

            parent->Add(data->name, child);
            break;
        }
    }

    return ODATA_Result_Ok;
}

Object* LoadJSONFile(
    const char* path)
{
    ODATA_Result r;
    JSON_Parser parser;
    char* data;
    size_t size;
    CallbackData callbackData;

    callbackData.object = NULL;

    if (FileLoad(path, NULL, &data, &size) != 0)
    {
        return NULL;
    }

    if ((r = JSON_Parser_Init(&parser, data, size, _Callback, 
        &callbackData)) != ODATA_Result_Ok)
    {
        free(data);
        return NULL;
    }

    if ((r = JSON_Parser_Parse(&parser)) != ODATA_Result_Ok)
    {
        free(data);
        return NULL;
    }

    if (callbackData.aggregates.size() != 0)
    {
        delete callbackData.object;
        free(data);
        return NULL;
    }

    callbackData.object->ReleaseOnDestruct(data);
    return callbackData.object;
}

int main(int argc, char** argv)
{
    int i;

    arg0 = argv[0];

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s path...\n", argv[0]);
        exit(1);
    }

    JSONSchema schema;

    for (i = 1; i < argc; i++)
    {
        fprintf(stderr, "==== Parse{%s}\n", argv[i]);

        if (!schema.ParseJSONFile(argv[i]))
        {
            fprintf(stderr, "%s: CreateSchema() failed\n", arg0);
            exit(1);
        }
    }

#if 0
    schema.Print(0);
#endif

    schema.GenerateSchema("schema");

    return 0;
}
