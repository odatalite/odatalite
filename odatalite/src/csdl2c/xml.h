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
#ifndef _xml_h
#define _xml_h

#include <stddef.h>

typedef enum _XMLType
{
    XML_NONE,
    XML_START,
    XML_END,
    XML_INSTRUCTION,
    XML_CHARS,
    XML_COMMENT
}
XMLType;

typedef struct  _XMLAttr
{
    char* name;
    char* value;
}
XMLAttr;

#define XMLMAXATTRS 64

typedef struct _XMLElem
{
    XMLType type;
    char* tag;
    char* data;
    XMLAttr attrs[XMLMAXATTRS];
    size_t nattrs;
    size_t line;
    struct _XMLElem* next;
}
XMLElem;

void XMLElemDump(
    const XMLElem* self);

const char* XMLElemAttr(
    const XMLElem* self,
    const char* name);

typedef struct _XML XML;

XML* XMLNew();

void XMLDelete(XML* self);

int XMLParse(
    XML* self, 
    const char* data, 
    size_t size);

void XMLDump(
    const XML* self);

const char* XMLErr(
    const XML* self);

int XMLNext(
    XML* self,
    XMLElem* elem);

int XMLExpectStart(
    XML* self,
    const char* tag,
    XMLElem* elem);

int XMLExpectEnd(
    XML* self,
    const char* tag);

int XMLSkip(
    XML* self);

size_t XMLGetLine(
    XML* self);

#endif /* _xml_h */
