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
#include "xml.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <expat.h>
#include <base/str.h>

struct _XML
{
    XML_Parser parser;
    int err;
    char errMessage[1024];

    XMLElem* head;
    XMLElem* tail;
    XMLElem* current;
};

void XMLElemDump(const XMLElem* self)
{
    printf("=== XMLElem: line=%u\n", (unsigned int)self->line);

    switch (self->type)
    {
        case XML_START:
        {
            size_t i;

            printf("=== START{%s}\n", self->tag);

            for (i = 0; i < self->nattrs; i++)
            {
                printf("    ATTR{%s}{%s}\n", self->attrs[i].name,
                    self->attrs[i].value);
            }

            break;
        }
        case XML_CHARS:
        {
            printf("=== CHARS{%s}\n", self->data);
            break;
        }
        case XML_END:
        {
            printf("=== END{%s}\n", self->tag);
            break;
        }
        default:
            break;
    }
}

const char* XMLElemAttr(
    const XMLElem* self,
    const char* name)
{
    size_t i;

    for (i = 0; i < self->nattrs; i++)
    {
        if (strcmp(self->attrs[i].name, name) == 0)
            return self->attrs[i].value;
    }

    return NULL;
}

static void _AppendElem(
    XML* self,
    XMLElem* elem)
{
    elem->next = NULL;

    if (self->tail)
    {
        /* Add to end of list */
        self->tail->next = elem;
        self->tail = elem;
    }
    else
    {
        self->head = elem;
        self->tail = elem;
    }

    elem->line = XML_GetCurrentLineNumber(self->parser);
}

void _StartHandler(
    void* data, 
    const char* element, 
    const char** attrs) 
{
    XML* self = (XML*)data;
    XMLElem* elem;
    size_t i = 0;
    size_t n = 0;

    if (self->err)
        return;

    /* XMLElem */
    if (!(elem = (XMLElem*)calloc(1, sizeof(XMLElem))))
    {
        self->err = -1;
        return;
    }

    /* XMLElem.type */
    elem->type = XML_START;
    
    /* XMLElem.tag */
    if (!(elem->tag = strdup(element)))
    {
        self->err = -1;
        return;
    }

    /* XMLElem.attrs */
    while (attrs[i])
    {
        if (!(elem->attrs[n].name = strdup(attrs[i++])))
        {
            self->err = -1;
            return;
        }

        if (!(elem->attrs[n].value = strdup(attrs[i++])))
        {
            self->err = -1;
            return;
        }
        n++;
    }

    elem->nattrs = n;
    _AppendElem(self, elem);
}

void _CharacterDataHandler(
    void* data, 
    const char* str,
    int len)
{
    XML* self = (XML*)data;
    XMLElem* elem;

    if (self->err)
        return;

    /* Ignore spaces */
    {
        int i;
        int found = 0;

        for (i = 0; i < len; i++)
        {
            if (!isspace(str[i]))
                found = 1;
        }

        if (!found)
            return;
    }

    /* XMLElem */
    if (!(elem = (XMLElem*)calloc(1, sizeof(XMLElem))))
    {
        self->err = -1;
        return;
    }

    /* XMLElem.type */
    elem->type = XML_CHARS;
    
    /* XMLElem.data */
    {
        if (!(elem->data = malloc(len+1)))
        {
            self->err = -1;
            return;
        }

        memcpy(elem->data, str, len);
        elem->data[len] = '\0';
    }

    _AppendElem(self, elem);
}

void _EndHandler(
    void* data, 
    const char* element) 
{
    XML* self = (XML*)data;
    XMLElem* elem;

    if (self->err)
        return;

    /* XMLElem */
    if (!(elem = (XMLElem*)calloc(1, sizeof(XMLElem))))
    {
        self->err = -1;
        return;
    }

    /* XMLElem.type */
    elem->type = XML_END;
    
    /* XMLElem.tag */
    if (!(elem->tag = strdup(element)))
    {
        self->err = -1;
        return;
    }

    _AppendElem(self, elem);
}

XML* XMLNew()
{
    XML* self = (XML*)calloc(1, sizeof(XML));

    if (!self)
        return NULL;

    if (!(self->parser = XML_ParserCreate("UTF-8")))
        return NULL;

    XML_SetUserData(self->parser, self);

    XML_SetElementHandler(self->parser, _StartHandler, _EndHandler);

    XML_SetCharacterDataHandler(self->parser, _CharacterDataHandler);

    return self;
}

void XMLDelete(XML* self)
{
    XMLElem* p;

    for (p = self->head; p; )
    {
        size_t i;
        XMLElem* next = p->next;

        if (p->tag)
            free(p->tag);

        if (p->data)
            free(p->data);

        for (i = 0; i < p->nattrs; i++)
        {
            free(p->attrs[i].name);
            free(p->attrs[i].value);
        }

        free(p);

        p = next;
    }

    XML_ParserFree(self->parser);
    free(self); 
}

int XMLParse(
    XML* self, 
    const char* data, 
    size_t size)
{
    if (!XML_Parse(self->parser, data, size, 1))
    {
        const char* str = XML_ErrorString(XML_GetErrorCode(self->parser));

        if (str)
            Strlcpy(self->errMessage, str, sizeof(self->errMessage));
        else
            Strlcpy(self->errMessage, "unknown", sizeof(self->errMessage));
        return -1;
    }

    if (self->err)
    {
        Strlcpy(self->errMessage, "out of memory", sizeof(self->errMessage));
        return -1;
    }

    self->current = self->head;

    return 0;
}

void XMLDump(
    const XML* self)
{
    XMLElem* p;

    printf("=== XMLDump()\n");

    for (p = self->head; p; p = p->next)
    {
        XMLElemDump(p);
    }
}

const char* XMLErr(
    const XML* self)
{
    return self->errMessage;
}

int XMLNext(
    XML* self,
    XMLElem* elem)
{
    if (!self->current)
        return -1;

    memcpy(elem, self->current, sizeof(XMLElem));
    self->current = self->current->next;
    return 0;
}

int XMLExpectStart(
    XML* self,
    const char* tag,
    XMLElem* elem)
{
    if (XMLNext(self, elem) != 0)
        return -1;

    if (elem->type != XML_START)
        return -1;

    if (strcmp(tag, tag) != 0)
        return -1;

    return 0;
}

int XMLExpectEnd(
    XML* self,
    const char* tag)
{
    XMLElem elem;

    if (XMLNext(self, &elem) != 0)
        return -1;

    if (elem.type != XML_END)
        return -1;

    if (strcmp(tag, tag) != 0)
        return -1;

    return 0;
}

int XMLSkip(
    XML* self)
{
    int n = 1;
    XMLElem e;

    while (n > 0 && XMLNext(self, &e) == 0)
    {
        if (e.type == XML_START)
            n++;

        if (e.type == XML_END)
            n--;
    }

    return 0;
}

size_t XMLGetLine(
    XML* self)
{
    return XML_GetCurrentLineNumber(self->parser);
}
