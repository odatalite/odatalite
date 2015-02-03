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
#ifndef _jsonparser_h
#define _jsonparser_h

#include <stddef.h>
#include "common.h"
#include "json.h"

EXTERNC_BEGIN

typedef enum _JSON_Reason
{
    JSON_Reason_None,
    JSON_Reason_Name,
    JSON_Reason_BeginObject,
    JSON_Reason_EndObject,
    JSON_Reason_BeginArray,
    JSON_Reason_EndArray,
    JSON_Reason_Value
}
JSON_Reason;

typedef struct _JSON_Parser JSON_Parser;

typedef OL_Result (*JSON_Parser_Callback)(
    JSON_Parser* parser,
    JSON_Reason reason,
    JSON_Type type,
    const JSON_Union* value,
    void* callbackData);

struct _JSON_Parser
{
    unsigned int magic;
    char* data;
    char* ptr;
    char* end;
    JSON_Parser_Callback callback;
    void* callbackData;
};

OL_Result JSON_Parser_Init(
    JSON_Parser* self,
    char* data,
    size_t size,
    JSON_Parser_Callback callback,
    void* callbackData);

OL_Result JSON_Parser_Parse(
    JSON_Parser* self);

EXTERNC_END

#endif /* _jsonparser_h */
