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
#ifndef _phit_base_str_h
#define _phit_base_str_h

#include "common.h"
#include "alloc.h"

#define STRLIT(STR) STR, sizeof(STR)-1
#define STRN(STR) (sizeof(STR)-1)

typedef struct _StrLit
{
    const char* str;
    unsigned char len;
}
StrLit;

/* Returns 0 on match */
INLINE int Streq(const char* s1, const char* s2)
{
    return !(s1[0] == s2[0] && strcmp(s1+1, s2+1) == 0);
}

/* Returns 0 on match (use for short strings) */
INLINE int StreqShort(const char* s1, const char* s2)
{
    if (s1[0] - s2[0])
        return -1;

    if (s1[0] == '\0')
        return 0;

    if (s1[1] - s2[1])
        return -1;

    if (s1[1] == '\0')
        return 0;

    if (s1[2] - s2[2])
        return -1;

    if (s1[2] == '\0')
        return 0;

    if (s1[3] - s2[3])
        return -1;

    if (s1[3] == '\0')
        return 0;

    if (s1[4] - s2[4])
        return -1;

    if (s1[4] == '\0')
        return 0;

    return strcmp(&s1[4], &s2[4]);
}

/* Returns 0 on match */
INLINE int Streq3(const char* s1, const char* s2)
{
    return 
        !(s1[0] == s2[0] &&
        s1[1] == s2[1] &&
        s1[2] == s2[2] &&
        s1[3] == s2[3]);
}

/* Returns 0 on match */
INLINE int Streq4(const char* s1, const char* s2)
{
    return 
        !(s1[0] == s2[0] &&
        s1[1] == s2[1] &&
        s1[2] == s2[2] &&
        s1[3] == s2[3] &&
        s1[4] == s2[4]);
}

size_t Strlcpy(
    char* dest,
    const char* src,
    size_t size);

size_t Strlcpy2(
    char* dest,
    const char* s1,
    const char* s2,
    size_t size);

size_t Strlcpy3(
    char* dest,
    const char* s1,
    const char* s2,
    const char* s3,
    size_t size);

size_t Strlcat(
    char* dest,
    const char* src,
    size_t size);

size_t Strlcat2(
    char* dest,
    const char* s1,
    const char* s2,
    size_t size);

size_t Strlcat3(
    char* dest,
    const char* s1,
    const char* s2,
    const char* s3,
    size_t size);

#define UIntToStrBufSize 12

const char* UIntToStr(
    char buf[UIntToStrBufSize], 
    unsigned int x, 
    size_t* size);

void UIntToStrZeroPadded(
    char* buf,
    size_t paddedSize,
    unsigned int x);

void ULongLongToStrZeroPadded(
    char* buf,
    size_t paddedSize,
    unsigned long long x);

#define SIntToStrBufSize 12

const char* SIntToStr(
    char buf[SIntToStrBufSize], 
    int x, 
    size_t* size);

#define ULongToStrBufSize 21

const char* ULongToStr(
    char buf[ULongToStrBufSize], 
    unsigned long x, 
    size_t* size);

#define ULongLongToStrBufSize 21

const char* ULongLongToStr(
    char buf[ULongLongToStrBufSize], 
    unsigned long long x, 
    size_t* size);

#define SLongLongToStrBufSize 22

const char* SLongLongToStr(
    char buf[SLongLongToStrBufSize], 
    long long x, 
    size_t* size);

extern const char __hexNibbleToChar[];

INLINE unsigned char CharToHexNibble(char c)
{
    extern const unsigned char __charToHexNibble[];
#if defined(FAST_STRING_TO_HEX)
    return __charToHexNibble[(unsigned char)c];
#else
    return isxdigit(c) ? __charToHexNibble[(unsigned char)c - '0'] : 0xFF;
#endif
}

/* Format: "FF" (unterminated) */
INLINE void UCharToHexStr(
    char buf[2],
    unsigned char x)
{
    buf[0] = __hexNibbleToChar[((0xF0 & x) >> 4)];
    buf[1] = __hexNibbleToChar[((0x0F & x))];
}

/* Format: "FFFF" (unterminated) */
INLINE void UShortToHexStr4(
    char buf[4],
    unsigned short x)
{
    buf[0] = __hexNibbleToChar[((0xF000 & x) >> 12)];
    buf[1] = __hexNibbleToChar[((0x0F00 & x) >> 8)];
    buf[2] = __hexNibbleToChar[((0x00F0 & x) >> 4)];
    buf[3] = __hexNibbleToChar[((0x000F & x))];
}

/* Format: "FFFFFFFF" (unterminated) */
const char* UIntToHexStr(
    char buf[8], 
    unsigned int x,
    size_t* size);

/* Format: "FFFFFFFF" (unterminated and always 8 bytes) */
void UIntToHexStr8(
    char buf[8], 
    unsigned int x);

/* Convert 4-byte hex string to unsigned int (e.g., "FE01") */
int HexStr4ToUint(
    const char* str4,
    unsigned int* x);

/* Convert 2-byte hex string to unsigned char (e.g., "F3") */
INLINE int HexStr2ToUChar(
    const char* s,
    unsigned char* x)
{
    unsigned char n0 = CharToHexNibble(s[0]);
    unsigned char n1 = CharToHexNibble(s[1]);

    if ((n0 | n1) & 0xF0)
        return -1;

    *x = (n0 << 4) | n1;
    return 0;
}

INLINE int HexStr2ToChar(
    const char* s,
    char* x)
{
    return HexStr2ToUChar(s, (unsigned char*)x);
}

/* Returns zero if first n characters of string match (case insensitive) */
int Strncaseeq(
    const char* s1, 
    const char* s2, 
    size_t n);

/* Use instead of Strncaseeq when there is a high probability of a case
 * sensitive match
 */
ALWAYS_INLINE int StrncaseeqProbable(
    const char* s1, 
    const char* s2, 
    size_t n)
{
    return strncmp(s1, s2, n) && Strncaseeq(s1, s2, n);
}

INLINE int Strncmp(
    const char* s1,
    const char* s2,
    size_t n)
{
    /* This is required because strncmp is a macro in some environments */
    return strncmp(s1, s2, n);
}

int Streqn(
    const char* s1,
    const char* s2,
    size_t n);

/* Converts null strings to "null" for use in "%s" format expressions. */
INLINE const char* Strnull(const char* str)
{
    return str ? str : "null";
}

INLINE int Strcasecmp(
    const char* s1,
    const char* s2)
{
#if defined(_MSC_VER)
    return _stricmp(s1, s2);
#else
    extern int strcasecmp(const char* s1, const char* s2);
    return strcasecmp(s1, s2);
#endif
}

INLINE int Strncasecmp(
    const char* s1,
    const char* s2,
    size_t n)
{
#if defined(_MSC_VER)
    return _strnicmp(s1, s2, n);
#else
    extern int strncasecmp(const char* s1, const char* s2, size_t n);
    return strncasecmp(s1, s2, n);
#endif
}

ALWAYS_INLINE unsigned int StrCode(const char* str, size_t len)
{
    return 
        (((unsigned int)str[0]) << 16) ^
        (((unsigned int)str[len-1]) << 8) ^
        ((unsigned int)len);
}

ALWAYS_INLINE size_t StrCodeLen(const char* name, unsigned int code)
{
    unsigned int n = code & 0xFF;
    return name[n] ? (n + (unsigned int)strlen(name + n)) : n;
}

/* Return 0 if str has the given suffix */
int StrcmpSuffix(
    const char* str,
    const char* suffix);

typedef union _Str8
{
    char s[8];
    unsigned long long x;
}
Str8;

/* This funciton is big so use only for hot paths; else use MakeStr8() */
INLINE unsigned long long MakeStr8Fast(const char* str)
{
    Str8 str8;
    str8.x = 0;

    (void)(
        str[0] && (str8.s[0] = str[0]) &&
        str[1] && (str8.s[1] = str[1]) &&
        str[2] && (str8.s[2] = str[2]) &&
        str[3] && (str8.s[3] = str[3]) &&
        str[4] && (str8.s[4] = str[4]) &&
        str[5] && (str8.s[5] = str[5]) &&
        str[6] && (str8.s[6] = str[6]) &&
        str[7] && (str8.s[7] = str[7]));

    return str8.x;
}

unsigned long long MakeStr8(const char* str);

INLINE void DumpStr8(unsigned long long x)
{
    Str8 str8;
    str8.x = x;
    printf("{%02X}", str8.s[0]);
    printf("{%02X}", str8.s[1]);
    printf("{%02X}", str8.s[2]);
    printf("{%02X}", str8.s[3]);
    printf("{%02X}", str8.s[4]);
    printf("{%02X}", str8.s[5]);
    printf("{%02X}", str8.s[6]);
    printf("{%02X}", str8.s[7]);
    printf("\n");
}

char* StripOuterSpaces(char* str);

#if 0
/* Returns 0 on match */
INLINE int Memcmp2(const char* s1, const char* s2)
{
    return !(s1[0] == s2[0] && s1[1] == s2[1]);
}

/* Returns 0 on match */
INLINE int Memcmp3(const char* s1, const char* s2)
{
    return !(s1[0] == s2[0] && s1[1] == s2[1] && s1[2] == s2[2]);
}

/* Returns 0 on match */
INLINE int Memcmp4(const char* s1, const char* s2)
{
    return !(s1[0] == s2[0] && s1[1] == s2[1] && s1[2] == s2[2] &&
        s1[3] == s2[3]);
}

/* Returns 0 on match */
INLINE int Memcmp5(const char* s1, const char* s2)
{
    return !(s1[0] == s2[0] && s1[1] == s2[1] && s1[2] == s2[2] &&
        s1[3] == s2[3] && s1[4] == s2[4]);
}

/* Returns 0 on match */
INLINE int Memcmp6(const char* s1, const char* s2)
{
    return !(s1[0] == s2[0] && s1[1] == s2[1] && s1[2] == s2[2] &&
        s1[3] == s2[3] && s1[4] == s2[4] && s1[5] == s2[5]);
}

/* Returns 0 on match */
INLINE int Memcmp7(const char* s1, const char* s2)
{
    return !(s1[0] == s2[0] && s1[1] == s2[1] && s1[2] == s2[2] &&
        s1[3] == s2[3] && s1[4] == s2[4] && s1[5] == s2[5] &&
        s1[6] == s2[6]);
}

/* Returns 0 on match */
INLINE int Memcmp8(const char* s1, const char* s2)
{
    return !(s1[0] == s2[0] && s1[1] == s2[1] && s1[2] == s2[2] &&
        s1[3] == s2[3] && s1[4] == s2[4] && s1[5] == s2[5] &&
        s1[6] == s2[6] && s1[7] == s2[7]);
}

INLINE int Memcmp(const char* s1, const char* s2, size_t n)
{
    switch (n)
    {
        case 2:
            return Memcmp2(s1, s2);
        case 3:
            return Memcmp3(s1, s2);
        case 4:
            return Memcmp4(s1, s2);
        case 5:
            return Memcmp5(s1, s2);
        case 6:
            return Memcmp6(s1, s2);
        case 7:
            return Memcmp7(s1, s2);
        case 8:
            return Memcmp8(s1, s2);
        default:
            return memcmp(s1, s2, n);
    }
}
#endif

INLINE char* StrdupBuf(char* buf, size_t size, const char* str)
{
    size_t len = strlen(str);

    if (len < size)
        return memcpy(buf, str, len + 1);

    return Strdup(str);
}

char* Strnstr(const char* str, const char* s, size_t n);

int StrToInt(const char* s, int* x);

int StrToUInt(const char* s, unsigned int* x);

int StrToULong(const char* s, unsigned long* x);

int StrToBool(const char* s, unsigned char* x);

int StrToUShort(const char* s, unsigned short* x);

typedef struct _StrtokState
{
    char* pointer;
}
StrtokState;

INLINE char* Strtok(
    StrtokState* state,
    char* str,
    const char* delim)
{
    return strtok_r(str, delim, &state->pointer);
}

/* Similar to Strtok() but trims leading and trailing whitespace */
char* StrtokTrim(
    StrtokState* state,
    char* str,
    const char* delim);

size_t Strtoks(
    char* str,
    const char* delim,
    char** toks,
    size_t ntoks);

#endif /* _phit_base_str_h */
