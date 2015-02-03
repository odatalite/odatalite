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
#include <base/alloc.h>

const char* arg0;

static const char* _reasons[] =
{
    "None",
    "Name",
    "BeginObject",
    "EndObject",
    "BeginArray",
    "EndArray",
    "Value"
};

static const char* _types[] =
{
    "Null",
    "Boolean",
    "Integer",
    "Real",
    "String"
};

typedef struct _CallbackData
{
    int depth;
    int newline;
    int comma;
}
CallbackData;

static void _PrintString(const char* str)
{
    printf("\"");

    while (*str)
    {
        char c = *str++;

        switch (c)
        {
            case '"':
                printf("\\\"");
                break;
            case '\\':
                printf("\\\\");
                break;
            case '\b':
                printf("\\b");
                break;
            case '\f':
                printf("\\f");
                break;
            case '\n':
                printf("\\n");
                break;
            case '\r':
                printf("\\r");
                break;
            case '\t':
                printf("\\t");
                break;
            default:
            {
                if (isprint(c))
                    printf("%c", c);
                else
                    printf("\\u%04X", c);
            }
        }
    }

    printf("\"");
}

static void _PrintValue(JSON_Type type, const JSON_Value* value)
{
    switch (type)
    {
        case JSON_Type_Null:
            printf("null");
            break;
        case JSON_Type_Boolean:
            printf("%s", value->u.boolean ? "true" : "false");
            break;
        case JSON_Type_Integer:
            printf("%lld", value->u.integer);
            break;
        case JSON_Type_Real:
            printf("%E", value->u.real);
            break;
        case JSON_Type_String:
#if 1
            _PrintString(value->u.string);
#else
            printf("\"%s\"", value->u.string);
            (void)_PrintString;
#endif
            break;
        default:
            break;
    }
}

void DumpCallbackParameters(
    JSON_Parser* parser,
    JSON_Reason reason,
    JSON_Type type,
    const JSON_Value* value,
    void* callbackData)
{
    printf("reason{%s}\n", _reasons[reason]);

    if (reason == JSON_Reason_Value)
    {
        printf("type{%s}\n", _types[type]);
        printf("value{");
        _PrintValue(type, value);
        printf("}\n");
    }
}

static void _Indent(int depth)
{
    size_t i;

    for (i = 0; i < depth; i++)
        printf("  ");
}

OL_Result _Callback(
    JSON_Parser* parser,
    JSON_Reason reason,
    JSON_Type type,
    const JSON_Union* un,
    void* callbackData)
{
    CallbackData* data = (CallbackData*)callbackData;

    /* Print commas */
    if (reason != JSON_Reason_EndArray &&
        reason != JSON_Reason_EndObject &&
        data->comma)
    {
        data->comma = 0;
        printf(",");
    }

    /* Decrease depth */
    if (reason == JSON_Reason_EndObject ||
        reason == JSON_Reason_EndArray)
    {
        data->depth--;
    }

    /* Print newline */
    if (data->newline)
    {
        data->newline = 0;
        printf("\n");
        _Indent(data->depth);
    }

    switch (reason)
    {
        case JSON_Reason_None:
        {
            /* Unreachable */
            break;
        }
        case JSON_Reason_Name:
        {
            _PrintString(un->string);
            printf(": ");
            data->comma = 0;
            break;
        }
        case JSON_Reason_BeginObject:
        {
            data->depth++;
            data->newline = 1;
            data->comma = 0;
            printf("{");
            break;
        }
        case JSON_Reason_EndObject:
        {
            data->newline = 1;
            data->comma = 1;
            printf("}");
            break;
        }
        case JSON_Reason_BeginArray:
        {
            data->depth++;
            data->newline = 1;
            data->comma = 0;
            printf("[");
            break;
        }
        case JSON_Reason_EndArray:
        {
            data->newline = 1;
            data->comma = 1;
            printf("]");
            break;
        }
        case JSON_Reason_Value:
        {
            JSON_Value v;
            v.type = type;
            v.u = *un;
            data->newline = 1;
            data->comma = 1;
            _PrintValue(type, &v);
            break;
        }
    }

    /* Final newline */
    if (reason == JSON_Reason_EndObject ||
        reason == JSON_Reason_EndArray)
    {
        if (data->depth == 0)
            printf("\n");
    }

    return OL_Result_Ok;
}

void Parse(const char* path)
{
    JSON_Parser parser;
    char* data;
    size_t size;
    OL_Result r;
    CallbackData callbackData;

    callbackData.depth = 0;
    callbackData.newline = 0;
    callbackData.comma = 0;

    if (FileLoad(path, NULL, &data, &size) != 0)
    {
        fprintf(stderr, "%s: failed to access '%s'\n", arg0, path);
        exit(1);
    }

    if ((r = JSON_Parser_Init(&parser, data, size, _Callback, 
        &callbackData)) != OL_Result_Ok)
    {
        fprintf(stderr, "%s: JSON_Parser_Init() failed: %d\n", arg0, r);
        exit(1);
    }

    if ((r = JSON_Parser_Parse(&parser)) != OL_Result_Ok)
    {
        fprintf(stderr, "%s: JSON_Parser_Init() failed: %d\n", arg0, r);
        exit(1);
    }

    if (callbackData.depth != 0)
    {
        fprintf(stderr, "%s: unterminated objects\n", arg0);
        exit(1);
    }
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

    for (i = 1; i < argc; i++)
    {
        Parse(argv[i]);
    }

    return 0;
}
