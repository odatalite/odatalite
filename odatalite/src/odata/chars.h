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
#ifndef _odata_chars_h
#define _odata_chars_h

#include "common.h"

extern unsigned const __odataChars[256];

INLINE int IsEsc(char c)
{
    return __odataChars[(unsigned char)c] & 0x01;
}

/* isdigit(c) || c=='-' || c=='+' || c=='e' || c=='E' || c=='.' */
INLINE int IsNumberChar(char c)
{
    return __odataChars[(unsigned char)c] & 0x02;
}

/* c=='.' || c=='e' || c=='E' */
INLINE int IsDecimalOrExponent(char c)
{
    return __odataChars[(unsigned char)c] & 0x04;
}

/* c != '%' && c != '\0' */
INLINE int IsNotPercentOrZero(char c)
{
    return __odataChars[(unsigned char)c] & 0x08;
}

/* c != '/' && c != '\0' */
INLINE int IsNotSlashOrZero(char c)
{
    return __odataChars[(unsigned char)c] & 0x10;
}

/* c != '/' && c != '?' && c != '(' && c != '\0' */
INLINE int IsNotSlashQuesLeftParenOrZero(char c)
{
    return __odataChars[(unsigned char)c] & 0x20;
}

#endif /* _odata_chars_h */
