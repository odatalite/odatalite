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
#ifndef _phit_base_chars_h
#define _phit_base_chars_h

#include "common.h"

extern const unsigned char __Chars[];

INLINE int IsSpace(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return __Chars[(unsigned char)c] & 1;
#else
    return isspace(c);
#endif
}

INLINE int IsNonSpace(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return __Chars[(unsigned char)c] & 2;
#else
    return c && !isspace(c);
#endif
}

/* [A-Za-z0-9_] */
INLINE int IsToken(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return __Chars[(unsigned char)c] & 4;
#else
    return isalnum(c) || c == '_';
#endif
}

/* [\r\n] */
INLINE int IsCRLF(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return __Chars[(unsigned char)c] & 8;
#else
    return c == '\r' || c == '\n';
#endif
}

INLINE int IsHTTPSeparator(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return __Chars[(unsigned char)c] & 16;
#else
    return 
        c == '(' || c == ')' || c == '<' || c == '>' || c == '@' || 
        c == ',' || c == ';' || c == ':' || c == '\\' || c == '"' || 
        c == '/' || c == '[' || c == ']' || c == '?' || c == '=' || 
        c == '{' || c == '}' || c == ' ' || c == '\t';
#endif
}

/* HTTP 'linear white space' characters */
INLINE int IsLWS(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return __Chars[(unsigned char)c] & 32;
#else
    return c == ' ' || c == '\t';
#endif
}


INLINE int IsNonLWSSemicolon(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return __Chars[(unsigned char)c] & 64;
#else
    return c && c != ';' && c != ' ' && c != '\t';
#endif
}

INLINE int IsHTTPCtl(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return __Chars[(unsigned char)c] & 128;
#else
    return (c >= 0 && c <= 31) || c == 127;
#endif
}

INLINE int IsHTTPToken(char c)
{
#if defined(ENABLE_SPEED_OPTIMIZATIONS)
    return !(__Chars[(unsigned char)c] & (16 | 128));
#else
    return !IsHTTPCtl(c) && !IsHTTPSeparator(c);
#endif
}

#endif /* _phit_base_chars_h */
