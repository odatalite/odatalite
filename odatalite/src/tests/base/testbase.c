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
#include <tests/test.h>
#include <assert.h>
#include <phit.h>
#include <base/str.h>
#include <base/http.h>
#include <base/chars.h>
#include <base/parse.h>
#include <base/ptrarray.h>
#include <base/base64.h>
#include <base/dump.h>
#include <base/role.h>
#include <base/getopt.h>
#include <base/format.h>
#include <base/alloc.h>
#include <base/plugininfo.h>
#include <base/path.h>
#include <base/env.h>
#include <base/cleanup.h>
#include <base/find.h>
#include <limits.h>
#include <base/conffile.h>

const char* arg0;

/*
**==============================================================================
**
** TestUIntToStrPerf()
**
**==============================================================================
*/

INLINE void TestUIntToStrPerf()
{
    size_t i;
    unsigned int x;
    char buf[11];
    size_t size;
    const char* str;

    for (i = 0; i < 1000000; i++)
    {
        for (x = 0; x < 10; x++)
        {
            str = UIntToStr(buf, x, &size);
        }
    }
}

/*
**==============================================================================
**
** TestUIntToStrPerf2()
**
**==============================================================================
*/

INLINE void TestUIntToStrPerf2()
{
    size_t i;
    unsigned int x;
    char buf[11];
    size_t size;
    const char* str;

    for (i = 0; i < 1000; i++)
    {
        for (x = 0; x < 1000; x++)
        {
            str = UIntToStr(buf, x, &size);
        }
    }
}

/*
**==============================================================================
**
** TestUIntToStr()
**
**==============================================================================
*/

BEGINTEST(TestUIntToStr)
{
    unsigned int i;

    for (i = 0; i < 1000; i++)
    {
        char buf1[11];
        char buf2[11];
        size_t size;
        const char* str;

        Snprintf(buf1, sizeof(buf1), "%u", i);
        str = UIntToStr(buf2, i, &size);
        TEST(strcmp(str, buf1) == 0);
        TEST(size == strlen(buf1));
    }
}
ENDTEST(TestUIntToStr)

/*
**==============================================================================
**
** TestSIntToStr()
**
**==============================================================================
*/

BEGINTEST(TestSIntToStr)
{
    int i;

    for (i = -1000; i < 1000; i++)
    {
        char buf1[12];
        char buf2[12];
        size_t size;
        const char* str;

        Snprintf(buf1, sizeof(buf1), "%d", i);
        str = SIntToStr(buf2, i, &size);
        TEST(strcmp(str, buf1) == 0);
        TEST(size == strlen(buf1));
    }
}
ENDTEST(TestSIntToStr)

/*
**==============================================================================
**
** TestSLongLongToStr()
**
**==============================================================================
*/

BEGINTEST(TestSLongLongToStr)
{
    long long i;

    for (i = -1000; i < 1000; i++)
    {
        char buf1[22];
        char buf2[22];
        size_t size;
        const char* str;

        Snprintf(buf1, sizeof(buf1), "%lld", i);
        str = SLongLongToStr(buf2, i, &size);
        TEST(strcmp(str, buf1) == 0);
        TEST(size == strlen(buf1));
    }
}
ENDTEST(TestSLongLongToStr)

/*
**==============================================================================
**
** TestULongToStr()
**
**==============================================================================
*/

BEGINTEST(TestULongToStr)
{
    unsigned long i;

    for (i = 0; i < 1000; i++)
    {
        char buf1[21];
        char buf2[21];
        size_t size;
        const char* str;

        Snprintf(buf1, sizeof(buf1), "%lu", i);
        str = ULongToStr(buf2, i, &size);
        TEST(strcmp(str, buf1) == 0);
        TEST(size == strlen(buf1));
    }
}
ENDTEST(TestULongToStr)

/*
**==============================================================================
**
** TestHTTPParseHeaders1()
**
**==============================================================================
*/

BEGINTEST(TestHTTPParseHeaders1)
{
    char DATA[] =
        "M-POST /wxyz HTTP/1.1\r\n"
        "Content-Type: text/plain ; charset = utf-8 ; x=1; s =\"hello\"  \r\n"
        "Content-Length: 12345\r\n"
        "User-Agent: PHIT\r\n"
        "Host: localhost:7777\r\n"
        "Authorization: Basic XXX\r\n"
        "TE: chunked, trailers\r\n"
        "PHIT-Command: echo one two three\r\n"
        "YYY: yyy\r\n"
        "ZZZ: zzz\r\n"
        "\r\n";
    HTTPRequest req;

    int r = HTTPRequestParse(&req, DATA, PHIT_ARRAY_SIZE(DATA) - 1);
    TEST(r == 0);

    TEST(strcmp(req.uri, "/wxyz") == 0);

#if 0
    HTTPRequestDump(&req);
#endif

    TEST(req.headers.contentType.found);
    TEST(req.headers.contentType.mediaType);
    TEST(strcmp(req.headers.contentType.mediaType, "text") == 0);
    TEST(strcmp(req.headers.contentType.mediaSubType, "plain") == 0);

    TEST(req.headers.contentType.found);
    TEST(req.headers.contentType.nparameters == 3);

    TEST(req.headers.contentType.parameters[0].name);
    TEST(req.headers.contentType.parameters[0].value);
    TEST(strcmp(req.headers.contentType.parameters[0].name, "charset") == 0);
    TEST(strcmp(req.headers.contentType.parameters[0].value, "utf-8") == 0);

    TEST(req.headers.contentType.parameters[1].name);
    TEST(req.headers.contentType.parameters[1].value);
    TEST(strcmp(req.headers.contentType.parameters[1].name, "x") == 0);
    TEST(strcmp(req.headers.contentType.parameters[1].value, "1") == 0);

    TEST(req.headers.contentType.parameters[2].name);
    TEST(req.headers.contentType.parameters[2].value);
    TEST(strcmp(req.headers.contentType.parameters[2].name, "s") == 0);
    TEST(strcmp(req.headers.contentType.parameters[2].value, "hello") == 0);

    TEST(req.headers.contentLength.found);
    TEST(req.headers.contentLength.value == 12345);

    TEST(req.headers.userAgent.found);
    TEST(req.headers.userAgent.value);
    TEST(strcmp(req.headers.userAgent.value, "PHIT") == 0);

    TEST(req.headers.authorization.found);
    TEST(req.headers.authorization.type == PHIT_AUTHORIZATIONTYPE_BASIC);
    TEST(strcmp(req.headers.authorization.credentials, "XXX") == 0);

    TEST(req.headers.te.found);
    TEST(req.headers.te.chunked);
    TEST(req.headers.te.trailers);

    TEST(req.buf.headersBufSize == 3);

    TEST(strcmp(req.buf.headersBuf[0].name, "PHIT-Command") == 0);
    TEST(strcmp(req.buf.headersBuf[0].value, "echo one two three") == 0);

    TEST(strcmp(req.buf.headersBuf[1].name, "YYY") == 0);
    TEST(strcmp(req.buf.headersBuf[1].value, "yyy") == 0);

    TEST(strcmp(req.buf.headersBuf[2].name, "ZZZ") == 0);
    TEST(strcmp(req.buf.headersBuf[2].value, "zzz") == 0);

    TEST(req.buf.headersBufSize == req.headers.nheaders);

    TEST(strcmp(req.headers.headers[0].name, "PHIT-Command") == 0);
    TEST(strcmp(req.headers.headers[0].value, "echo one two three") == 0);

    TEST(strcmp(req.headers.headers[1].name, "YYY") == 0);
    TEST(strcmp(req.headers.headers[1].value, "yyy") == 0);

    TEST(strcmp(req.headers.headers[2].name, "ZZZ") == 0);
    TEST(strcmp(req.headers.headers[2].value, "zzz") == 0);
}
ENDTEST(TestHTTPParseHeaders1)

/*
**==============================================================================
**
** TestHTTPParseHeaders2()
**
**==============================================================================
*/

BEGINTEST(TestHTTPParseHeaders2)
{
    char DATA[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Transfer-Encoding: chunked\r\n"
        "Trailer: AAA, BB,,C,,,   \r\n"
        "\r\n";
    HTTPResponse res;

    int r = HTTPResponseParse(&res, DATA, PHIT_ARRAY_SIZE(DATA) - 1);
    TEST(r == 0);

#if 0
    HTTPResponseDump(&res);
#endif

    TEST(res.statusCode == 200);
    TEST(strcmp(res.statusMsg, "OK") == 0);

    TEST(res.headers.contentType.found);
    TEST(res.headers.contentType.mediaType);
    TEST(strcmp(res.headers.contentType.mediaType, "text") == 0);
    TEST(strcmp(res.headers.contentType.mediaSubType, "plain") == 0);

    TEST(res.headers.transferEncoding.found);
    TEST(res.headers.transferEncoding.chunked);

    TEST(res.headers.trailer.data != NULL);
    TEST(res.headers.trailer.size == 3);
    TEST(strcmp(res.headers.trailer.data[0], "AAA") == 0);
    TEST(strcmp(res.headers.trailer.data[1], "BB") == 0);
    TEST(strcmp(res.headers.trailer.data[2], "C") == 0);
}
ENDTEST(TestHTTPParseHeaders2)

/*
**==============================================================================
**
** TestBuf()
**
**==============================================================================
*/

BEGINTEST(TestBuf)
{
    Buf buf = BUF_INITIALIZER;

    BufFmt(&buf, "this is a test; %s: %d\n", "this is only a test", 10);

    TEST(strcmp(buf.data, "this is a test; this is only a test: 10\n") == 0);

    BufDestroy(&buf);
}
ENDTEST(TestBuf)

/*
**==============================================================================
**
** TestHexStr()
**
**==============================================================================
*/

BEGINTEST(TestHexStr)
{
    {
        char buf[3];
        UCharToHexStr(buf, 0xAB);
        buf[2] = '\0';
        TEST(strcmp(buf, "AB") == 0);
    }
    {
        char buf[9];
        UIntToHexStr(buf, 0x1234ABCD, NULL);
        buf[8] = '\0';
        TEST(strcmp(buf, "1234ABCD") == 0);
    }
    {
        char buf[9];
        const char* str;
        str = UIntToHexStr(buf, 0xBB, NULL);
        buf[8] = '\0';
        TEST(strcmp(str, "BB") == 0);
    }
    {
        unsigned int x;
        int r = HexStr4ToUint("FACE", &x);
        TEST(r == 0);
        TEST(x == 0xFACE);
    }
    {
        unsigned int x;
        int r = HexStr4ToUint("WXYZ", &x);
        TEST(r == -1);
    }
    {
        unsigned char x;
        int r = HexStr2ToUChar("0F", &x);
        TEST(r == 0);
        TEST(x == 0x0F);
    }
    {
        unsigned char x;
        int r = HexStr2ToUChar("..", &x);
        TEST(r == -1);
    }
}
ENDTEST(TestHexStr)

/*
**==============================================================================
**
** TestStrncaseeq()
**
**==============================================================================
*/

BEGINTEST(TestStrncaseeq)
{
    TEST(Strncaseeq("abc", "a", 1) == 0);
    TEST(Strncaseeq("a", "abc", 1) == 0);
    TEST(Strncaseeq("hello", "hello", 1) == 0);
    TEST(Strncaseeq("hello", "hello", 2) == 0);
    TEST(Strncaseeq("hello", "hello", 3) == 0);
    TEST(Strncaseeq("hello", "hello", 4) == 0);
    TEST(Strncaseeq("hello", "hello", 5) == 0);
    TEST(Strncaseeq("hello world", "hello", 5) == 0);
    TEST(Strncaseeq("hello", "hello world", 5) == 0);
}
ENDTEST(TestStrncaseeq)

/*
**==============================================================================
**
** TestBase64Aux()
**
**==============================================================================
*/

int TestBase64Aux(
    const char* str,
    size_t len)
{
    char encbuf[1024];
    char decbuf[1024];

    /* Encode */
    *encbuf = '\0';
    {
        Base64EncState state = BASE64ENCSTATE_INITIALIZER;
        char data[4+1];
        const size_t size = sizeof(data) - 1;
        size_t n;

        while ((n = Base64Enc(&state, str, len, data, size)) > 0)
        {
#if 0
            printf("data[%.*s]\n", (int)n, data);
#endif
            data[n] = '\0';
            Strlcat(encbuf, data, sizeof(encbuf));
        }
    }

#if 0
    printf("encbuf{%s}\n", encbuf);
#endif

    /* Decode */
    *decbuf = '\0';
    {
        Base64DecState state = BASE64DECSTATE_INITIALIZER;
        char data[4+1];
        const size_t size = sizeof(data) - 1;
        int n;

        while ((n = Base64Dec(
            &state, encbuf, strlen(encbuf), data, size)) > 0)
        {
#if 0
            printf("data[%.*s]\n", (int)n, data);
#endif
            data[n] = '\0';
            Strlcat(decbuf, data, sizeof(decbuf));
        }
    }

#if 0
    printf("decbuf{%s}\n", decbuf);
#endif

    return strcmp(str, decbuf) == 0;
}

/*
**==============================================================================
**
** TestBase64InplaceAux()
**
**==============================================================================
*/

int TestBase64InplaceAux(
    void* data_,
    size_t size_)
{
    char encbuf[4096];
    size_t enclen = 0;
    size_t declen = 0;

    {
        Base64EncState state = BASE64ENCSTATE_INITIALIZER;
        char data[4+1];
        const size_t size = sizeof(data) - 1;
        size_t n;

        while ((n = Base64Enc(&state, data_, size_, data, size)) > 0)
        {
            memcpy(&encbuf[enclen], data, n);
            enclen += n;
        }
    }

    /* Decode */
    {
        Base64DecState state = BASE64DECSTATE_INITIALIZER;
        size_t n;

        n = Base64Dec(&state, encbuf, enclen, encbuf, sizeof(encbuf));

        if (n <= 0)
            return 0;

        declen += n;
    }


    if (declen != size_)
        return 0;

    return memcmp(data_, encbuf, size_) == 0;
}

/*
**==============================================================================
**
** TestBase64()
**
**==============================================================================
*/

BEGINTEST(TestBase64)
{
    TEST(TestBase64Aux(STRLIT("a")));
    TEST(TestBase64Aux(STRLIT("ab")));
    TEST(TestBase64Aux(STRLIT("abc")));
    TEST(TestBase64Aux(STRLIT("abcd")));
    TEST(TestBase64Aux(STRLIT("abcde")));
    TEST(TestBase64Aux(STRLIT("abcdef")));
    TEST(TestBase64Aux(STRLIT("abcdefg")));
    TEST(TestBase64Aux(STRLIT("abcdefgh")));
    TEST(TestBase64Aux(STRLIT("abcdefghi")));
    TEST(TestBase64Aux(STRLIT("abcdefghij")));
    TEST(TestBase64Aux(STRLIT("abcdefghijk")));
    TEST(TestBase64Aux(STRLIT("abcdefghijkl")));
    TEST(TestBase64Aux(STRLIT("abcdefghijkln")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklno")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoq")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqr")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqrs")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqrst")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqrstu")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqrstuv")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqrstuvw")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqrstuvwx")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqrstuvwxy")));
    TEST(TestBase64Aux(STRLIT("abcdefghijklnoqrstuvwxyz")));

    TEST(TestBase64InplaceAux(STRLIT("a")));
    TEST(TestBase64InplaceAux(STRLIT("ab")));
    TEST(TestBase64InplaceAux(STRLIT("abc")));
    TEST(TestBase64InplaceAux(STRLIT("abcd")));
    TEST(TestBase64InplaceAux(STRLIT("abcde")));
    TEST(TestBase64InplaceAux(STRLIT("abcdef")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefg")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefgh")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghi")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghij")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijk")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijkl")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijkln")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklno")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoq")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqr")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqrs")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqrst")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqrstu")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqrstuv")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqrstuvw")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqrstuvwx")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqrstuvwxy")));
    TEST(TestBase64InplaceAux(STRLIT("abcdefghijklnoqrstuvwxyz")));

    {
        char buf[2048];
        size_t n = sizeof(buf);
        size_t i;

        for (i = 0; i < n; i++)
            buf[i] = rand() % 256;

        TEST(TestBase64InplaceAux(buf, n));
    }
}
ENDTEST(TestBase64)

/*
**==============================================================================
**
** TestStrcpyStrcat()
**
**==============================================================================
*/

BEGINTEST(TestStrcpyStrcat)
{
    {
        char buf[7];
        TEST(Strlcpy(buf, "abc", sizeof(buf)) == 3);
        TEST(Strlcat(buf, "xyz", sizeof(buf)) == 6);
        TEST(Strlcat(buf, "123", sizeof(buf)) == 9);
        TEST(strcmp(buf, "abcxyz") == 0);
    }

    {
        char buf[7];
        *buf = '\0';
        TEST(Strlcat(buf, "abc", sizeof(buf)) == 3);
        TEST(Strlcat(buf, "xyz", sizeof(buf)) == 6);
        TEST(Strlcat(buf, "123", sizeof(buf)) == 9);
        TEST(strcmp(buf, "abcxyz") == 0);
    }

    {
        char buf[4];
        *buf = '\0';
        TEST(Strlcat(buf, "a", sizeof(buf)) == 1);
        TEST(Strlcat(buf, "b", sizeof(buf)) == 2);
        TEST(Strlcat(buf, "c", sizeof(buf)) == 3);
        TEST(Strlcat(buf, "d", sizeof(buf)) == 4);
        TEST(Strlcat(buf, "e", sizeof(buf)) == 4);
        TEST(strcmp(buf, "abc") == 0);
    }

    {
        char buf[20];
        *buf = '\0';
        TEST(Strlcat(buf, "abcdefg", sizeof(buf)) == 7);
        TEST(Strlcat(buf, "hijklmnop", sizeof(buf)) == 16);
        TEST(Strlcat(buf, "qrstuvwxyz", sizeof(buf)) == 26);
        TEST(strcmp(buf, "abcdefghijklmnopqrs") == 0);

    }

    {
        char buf[5];

        TEST(Strlcpy(buf, "abcd", sizeof(buf)) == 4);
        TEST(strcmp(buf, "abcd") == 0);

        TEST(Strlcpy(buf, "abcde", sizeof(buf)) == 5);
        TEST(strcmp(buf, "abcd") == 0);

        TEST(Strlcpy(buf, "abcdefg", sizeof(buf)) == 7);
        TEST(strcmp(buf, "abcd") == 0);

    }
}
ENDTEST(TestStrcpyStrcat)

/*
**==============================================================================
**
** TestStrcatPerf()
**
**==============================================================================
*/

BEGINTEST(TestStrcatPerf)
{
    size_t i;

    for (i = 0; i < 100000; i++)
    {
        char buf[20];
        *buf = '\0';
        Strlcat(buf, "abcdefg", sizeof(buf));
        Strlcat(buf, "hijklmnop", sizeof(buf));
        Strlcat(buf, "qrstuvwxyz", sizeof(buf));
    }
}
ENDTEST(TestStrcatPerf)

/*
**==============================================================================
**
** TestStrlcpy2()
**
**==============================================================================
*/

BEGINTEST(TestStrlcpy2)
{
    char buf[128];
    size_t n;

    n = Strlcpy2(buf, "abcdefg", "hijklmnop", sizeof(buf));
    TEST(n == STRN("abcdefghijklmnop"));
    TEST(strcmp(buf, "abcdefghijklmnop") == 0);
}
ENDTEST(TestStrlcpy2)

/*
**==============================================================================
**
** TestStrlcpy3()
**
**==============================================================================
*/

BEGINTEST(TestStrlcpy3)
{
    char buf[128];
    size_t n;

    n = Strlcpy3(buf, "abcdefg", "hijklmnop", "qrstuv", sizeof(buf));
    TEST(n == STRN("abcdefghijklmnopqrstuv"));
    TEST(strcmp(buf, "abcdefghijklmnopqrstuv") == 0);
}
ENDTEST(TestStrlcpy3)

/*
**==============================================================================
**
** TestHTTPFormatRequest()
**
**==============================================================================
*/

BEGINTEST(TestHTTPFormatRequest)
{
    Buf buf = BUF_INITIALIZER;
    int r;

    r = HTTPFormatRequest(
        &buf, "phitCommand", "username", "password", STRLIT("CONTENT"));
    TEST(r == 0);

    /* Zero terminate */
    BufCatCh(&buf, '\0');
    buf.size--;

#if 0
    Dump(stdout, "BUF", buf.data, buf.size + 1);
    Dump(stdout, "EXPECT", EXPECT, strlen(EXPECT) + 1);
#endif

    {
        const char EXPECT[] =
            "M-POST / HTTP/1.1\r\n"
            "Content-Type: text/plain\r\n"
            "TE: chunked\r\n"
            "Content-Length: 7\r\n"
            "Authorization: Basic dXNlcm5hbWU6cGFzc3dvcmQ=\r\n"
            "PHIT-Command: phitCommand\r\n\r\n"
            "CONTENT";

        TEST(strncmp(EXPECT, buf.data, strlen(EXPECT)) == 0);
    }

    BufDestroy(&buf);
}
ENDTEST(TestHTTPFormatRequest)

/*
**==============================================================================
**
** TestRole()
**
**==============================================================================
*/

BEGINTEST(TestRole)
{
    TEST(strcmp(RoleName(PHIT_ROLE_NONE), "none") == 0);
    TEST(strcmp(RoleName(PHIT_ROLE_GUEST), "guest") == 0);
    TEST(strcmp(RoleName(PHIT_ROLE_OPERATOR), "operator") == 0);
    TEST(strcmp(RoleName(PHIT_ROLE_ADMIN), "admin") == 0);
}
ENDTEST(TestRole)

/*
**==============================================================================
**
** TestRoleLoad()
**
**==============================================================================
*/

BEGINTEST(TestRoleLoad)
{
    char err[64];
    int r;
    
    if ((r = RolesLoad(TESTDIR "/roles.conf", err, sizeof(err))) != 0)
    {
        fprintf(stderr, "err{%s}\n", err);
        exit(1);
    }

    TEST(r == 0);

#if 0
    RoleDump();
#endif

    {
        const Role* role = &__roles[PHIT_ROLE_GUEST-1];
        TEST(role->nusers == 1);
        TEST(strcmp(role->users[0], "*") == 0);
    }
    {
        const Role* role = &__roles[PHIT_ROLE_OPERATOR-1];
        TEST(role->nusers == 2);
        TEST(strcmp(role->users[0], "root") == 0);
        TEST(strcmp(role->users[1], "kermit") == 0);
    }
    {
        const Role* role = &__roles[PHIT_ROLE_ADMIN-1];
        TEST(role->nusers == 1);
        TEST(strcmp(role->users[0], "root") == 0);
    }

    TEST(RoleResolve("root") == PHIT_ROLE_ADMIN);
    TEST(RoleResolve("kermit") == PHIT_ROLE_OPERATOR);
    TEST(RoleResolve("fred") == PHIT_ROLE_GUEST);
}
ENDTEST(TestRoleLoad)

/*
**==============================================================================
**
** TestRoleLoadFailed()
**
**==============================================================================
*/

BEGINTEST(TestRoleLoadFailed)
{
    char err[256];
    const char* p;
    
    TEST(RolesLoad(TESTDIR "/rolesbad.conf", err, sizeof(err)) == -1);

    TEST((p = strchr(err, '(')) != NULL);
    TEST(strcmp(p, "(3): unknown role") == 0);
}
ENDTEST(TestRoleLoadFailed)

/*
**==============================================================================
**
** TestGetOpt()
**
**==============================================================================
*/

BEGINTEST(TestGetOpt)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    int opt;
    int got_t = 0;
    int got_p = 0;
    int got_q = 0;
    int got_d = 0;

    char* argv[] =
    {
        "arg0",
        "-t",
        "arg1",
        "-p",
        "ppp",
        "arg2",
        "-q",
        "qqq",
        "-d",
        "arg3",
        NULL
    };
    int argc = PHIT_ARRAY_SIZE(argv) - 1;

    while ((opt = GetOpt(&state, argc, argv, "tp:q:d")) != -1)
    {
        switch (opt)
        {
            case 't':
            {
                got_t = 1;
                TEST(state.optarg == NULL);
                break;
            }
            case 'p':
            {
                got_p = 1;
                TEST(strcmp(state.optarg, "ppp") == 0);
                break;
            }
            case 'q':
            {
                got_q = 1;
                TEST(strcmp(state.optarg, "qqq") == 0);
                break;
            }
            case 'd':
            {
                got_d = 1;
                TEST(state.optarg == NULL);
                break;
            }
            case '?':
            {
                TEST(0);
            }

        }
    }

    TEST(got_t);
    TEST(got_p);
    TEST(got_q);
    TEST(got_d);

    argc = state.optind;

    TEST(argc == 4);
    TEST(strcmp(argv[0], "arg0") == 0);
    TEST(strcmp(argv[1], "arg1") == 0);
    TEST(strcmp(argv[2], "arg2") == 0);
    TEST(strcmp(argv[3], "arg3") == 0);
}
ENDTEST(TestGetOpt)

/*
**==============================================================================
**
** TestGetOptUnknownOption()
**
**==============================================================================
*/

BEGINTEST(TestGetOptUnknownOption)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    int opt;

    char* argv[] =
    {
        "arg0",
        "arg1",
        "-z",
        "arg3",
        "arg4",
        NULL
    };
    int argc = PHIT_ARRAY_SIZE(argv) - 1;

    int unknownOption = 0;

    while ((opt = GetOpt(&state, argc, argv, "tp:q:d")) != -1)
    {
        if (opt == '?')
        {
            unknownOption = state.optopt;
            break;
        }

        TEST(0);
    }

    TEST(unknownOption == 'z');
}
ENDTEST(TestGetOptUnknownOption)

/*
**==============================================================================
**
** TestGetOptMissingOptArg()
**
**==============================================================================
*/

BEGINTEST(TestGetOptMissingOptArg)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    int opt;

    char* argv[] =
    {
        "arg0",
        "arg1",
        "-m",
        NULL
    };
    int argc = PHIT_ARRAY_SIZE(argv) - 1;
    int missingOptArg = 0;

    while ((opt = GetOpt(&state, argc, argv, "m:")) != -1)
    {
        if (opt == 'm')
        {
            TEST(0);
        }

        if (opt == ':')
        {
            missingOptArg = state.optopt;
            break;
        }

        TEST(0);
    }

    TEST(missingOptArg == 'm');
}
ENDTEST(TestGetOptMissingOptArg)

/*
**==============================================================================
**
** TestPluginInfo()
**
**==============================================================================
*/

BEGINTEST(TestPluginInfo)
{
    PluginInfo* array[16];
    size_t arraySize;
    char error[128];

    arraySize = PluginInfoLoad(
        TESTDIR "/phitplugins.conf",
        array,
        PHIT_ARRAY_SIZE(array),
        0,
        error,
        PHIT_ARRAY_SIZE(error));

    if (arraySize == (size_t)-1)
    {
        fprintf(stderr, "ERROR: %s\n", error);
        TEST(0);
    }

    TEST(arraySize == 2);

    TEST(array[0]->method == PHIT_METHOD_GET);
    TEST(strcmp(array[0]->uri, "/XYZ") == 0);
    TEST(strcmp(array[0]->libname, "/usr/local/lib/libxyz.so") == 0);
    TEST(strcmp(array[0]->link, "/myurl") == 0);
    TEST(array[0]->linkLen = STRN("http://myhost/myurl"));

    TEST(array[1]->method == PHIT_METHOD_MPOST);
    TEST(strcmp(array[1]->uri, "/CMD") == 0);
    TEST(strcmp(array[1]->libname, "/usr/local/lib/libcmd.so") == 0);
    TEST(strcmp(array[1]->link, "") == 0);
    TEST(array[1]->linkLen == 0);

    PluginInfoRelease(
        array,
        arraySize);
}
ENDTEST(TestPluginInfo)

/*
**==============================================================================
**
** TestStatusCodeStrings()
**
**==============================================================================
*/

#if 0

BEGINTEST(TestStatusCodeStrings)
{
    
    /* Test 417 */
    {
        int r;
        StrLit lit;

        r = GetStatusCodeString(PHIT_STATUSCODE_417_EXPECTATION_FAILED, &lit);
        TEST(r == 0);
        TEST(strcmp(lit.str, "417 Expectation Failed") == 0);
    }

    /* Test everything between 100 and 505 */
    {
        size_t i;
        int r;
        StrLit lit;
        size_t n = 0;

        for (i = 100; i <= 505; i++)
        {
            r = GetStatusCodeString((PHIT_StatusCode)i, &lit);

            if (r == 0)
            {
                char buf[11];
                int m;

                m = sprintf(buf, "%u ", (unsigned int)i);
                TEST(m == 4);

                TEST(strncmp(buf, lit.str, 4) == 0);
                n++;
            }
        }

        TEST(n == 41);
    }
}
ENDTEST(TestStatusCodeStrings)

#endif

/*
**==============================================================================
**
** TestUIntToStrZeroPadded()
**
**==============================================================================
*/

BEGINTEST(TestUIntToStrZeroPadded)
{
    char buf[11];

    UIntToStrZeroPadded(buf, 6, 123);
#if 0
    printf("BUF{%s}\n", buf);
#endif
    TEST(strcmp(buf, "000123") == 0);

    UIntToStrZeroPadded(buf, 6, 1);
#if 0
    printf("BUF{%s}\n", buf);
#endif
    TEST(strcmp(buf, "000001") == 0);

    UIntToStrZeroPadded(buf, 4, 1234);
    TEST(strcmp(buf, "1234") == 0);

    UIntToStrZeroPadded(buf, 4, 12345);
    TEST(strcmp(buf, "2345") == 0);

    UIntToStrZeroPadded(buf, 4, 1);
    TEST(strcmp(buf, "0001") == 0);
}
ENDTEST(TestUIntToStrZeroPadded)

/*
**==============================================================================
**
** TestMakePath()
**
**==============================================================================
*/

BEGINTEST(TestMakePath)
{
    {
        char buf1[256];
        char buf2[256];
        const char* path;

        const char* prefix = GetPrefix();

        if (prefix)
            Strlcpy(buf1, prefix, sizeof(buf1));
        else
            Strlcpy(buf1, PREFIX, sizeof(buf1));

        Strlcat(buf1, SYSCONFDIR + STRN("${prefix}"), sizeof(buf1));
        Strlcat(buf1, "/phit/plugins.conf", sizeof(buf1));

        path = MakePath(ID_PLUGINS_CONF, buf2);
        TEST(path != NULL);

        TEST(strcmp(buf1, path) == 0);
    }

    {
        char buf1[256];
        char buf2[256];
        const char* path;

        const char* prefix = GetPrefix();

        if (prefix)
            Strlcpy(buf1, prefix, sizeof(buf1));
        else
            Strlcpy(buf1, PREFIX, sizeof(buf1));

        Strlcat(buf1, LIBDIR + STRN("${exec_prefix}"), sizeof(buf1));

        path = MakePath(ID_LIBDIR, buf2);
        TEST(path != NULL);

        TEST(strcmp(buf1, path) == 0);
    }
}
ENDTEST(TestMakePath)

/*
**==============================================================================
**
** TestFindFile()
**
**==============================================================================
*/

BEGINTEST(TestFindFile)
{
    char path[MAX_PATH_SIZE];

    TEST(FindFile(path, TESTDIR, "testbase.c") == 0);
    TEST(strcmp(path, TESTDIR "/testbase.c") == 0);

    TEST(FindFile(path, TESTDIR, "README") == 0);
    TEST(strcmp(path, TESTDIR "/FindFile/a/b/c/README") == 0);
}
ENDTEST(TestFindFile)

/*
**==============================================================================
**
** TestConf()
**
**==============================================================================
*/

typedef struct _MyFileCallbackData
{
    int n;
    char* s;
    unsigned char flag;
    char* empty;
}
MyFileCallbackData;

static int _MyFileCallback(
    const char* path,
    unsigned int line,
    char** fields,
    size_t nfields,
    void* callbackData,
    char* err,
    size_t errSize)
{
    MyFileCallbackData* data = (MyFileCallbackData*)callbackData;

    if (nfields != 2)
    {
        Snprintf(err, errSize, "%s(%u): wrong # fields", path, line);
        return -1;
    }

    if (strcmp(fields[0], "n") == 0)
    {
        return StrToInt(fields[1], &data->n);
    }
    else if (strcmp(fields[0], "s") == 0)
    {
        data->s = Strdup(fields[1]);
        return 0;
    }
    else if (strcmp(fields[0], "flag") == 0)
    {
        return StrToBool(fields[1], &data->flag);
    }
    else if (strcmp(fields[0], "empty") == 0)
    {
        data->empty = Strdup(fields[1]);
        return 0;
    }

    /* not found */
    Snprintf(err, errSize, "%s(%u): unknown: %s", path, line, fields[0]);
    return -1;
}

BEGINTEST(TestConf)
{
    char err[128];
    MyFileCallbackData data;

    if (ConfFileLoad(
        TESTDIR "/myfile.conf", 
        "=",
        _MyFileCallback,
        &data,
        err, 
        sizeof(err)) != 0)
    {
        fprintf(stderr, "err{%s}\n", err);
        TEST(0);
    }

    TEST(data.n == 12345);
    TEST(data.s != NULL && strcmp(data.s, "hello") == 0);
    TEST(data.empty != NULL && strcmp(data.empty, "") == 0);
    TEST(data.flag == 1);

    Free(data.s);
    Free(data.empty);
}
ENDTEST(TestConf)

/*
**==============================================================================
**
** TestConfFile()
**
**==============================================================================
*/

int _ConfFileCallback(
    const char* path,
    unsigned int line,
    char** fields,
    size_t nfields,
    void* callbackData,
    char* err,
    size_t errSize)
{
    static size_t n;

    if (nfields != 4)
    {
        Snprintf(err, errSize, "%s(%d): expected 4 fields", path, line);
        return -1;
    }

    if (n == 0)
    {
        if (strcmp(fields[0], "a") != 0 ||
            strcmp(fields[1], "bb") != 0 ||
            strcmp(fields[2], "ccc") != 0 ||
            strcmp(fields[3], "dddd") != 0)
        {
            return -1;
        }
    }
    else if (n == 1)
    {
        if (strcmp(fields[0], "zzzz") != 0 ||
            strcmp(fields[1], "yyy") != 0 ||
            strcmp(fields[2], "xx") != 0 ||
            strcmp(fields[3], "w") != 0)
        {
            return -1;
        }
    }
    else
        return -1;

    n++;

    return 0;
}

BEGINTEST(TestConfFile)
{
    char err[128];

    if (ConfFileLoad(
        TESTDIR "/conffile.conf", 
        ":",
        _ConfFileCallback,
        NULL,
        err, 
        sizeof(err)) != 0)
    {
        fprintf(stderr, "err{%s}\n", err);
        TEST(0);
    }
}
ENDTEST(TestConfFile)

/*
**==============================================================================
**
** TestStrtok()
**
**==============================================================================
*/

BEGINTEST(TestStrtok)
{
    char buf[1024];
    char* p;
    StrtokState state;
    size_t i = 0;

    Strlcpy(buf, "        one :     two :    three     ", sizeof(buf));

    for (p = Strtok(&state, buf, ": "); p; p = Strtok(&state, NULL, ": "))
    {
        if (i == 0)
            TEST(strcmp(p, "one") == 0);
        else if (i == 1)
            TEST(strcmp(p, "two") == 0);
        else if (i == 2)
            TEST(strcmp(p, "three") == 0);

        i++;
    }
}
ENDTEST(TestStrtok)

/*
**==============================================================================
**
** TestStrlcat()
**
**==============================================================================
*/

BEGINTEST(TestStrlcat)
{
    char buf[5];

    Strlcpy(buf, "ABC", sizeof(buf));
    Strlcat(buf, "DEF", sizeof(buf));
    TEST(strcmp(buf, "ABCD") == 0);
}
ENDTEST(TestStrlcat)

/*
**==============================================================================
**
** TestSplitPath()
**
**==============================================================================
*/

BEGINTEST(TestSplitPath)
{
    char buf[MAX_PATH_SIZE];
    const char* segments[4];

    {
        Strlcpy(buf, "", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == 0);
    }

    {
        Strlcpy(buf, "/", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == 1);
        TEST(strcmp(segments[0], "/") == 0);
    }

    {
        Strlcpy(buf, "a", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == 1);
        TEST(strcmp(segments[0], "a") == 0);
    }

    {
        Strlcpy(buf, "/aaa", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == 2);
        TEST(strcmp(segments[0], "/") == 0);
        TEST(strcmp(segments[1], "aaa") == 0);
    }

    {
        Strlcpy(buf, "/a/bb", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == 3);
        TEST(strcmp(segments[0], "/") == 0);
        TEST(strcmp(segments[1], "a") == 0);
        TEST(strcmp(segments[2], "bb") == 0);
    }

    {
        Strlcpy(buf, "/a/b/c", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == 4);
        TEST(strcmp(segments[0], "/") == 0);
        TEST(strcmp(segments[1], "a") == 0);
        TEST(strcmp(segments[2], "b") == 0);
        TEST(strcmp(segments[3], "c") == 0);
    }

    {
        Strlcpy(buf, "///a////////b/////c////", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == 4);
        TEST(strcmp(segments[0], "/") == 0);
        TEST(strcmp(segments[1], "a") == 0);
        TEST(strcmp(segments[2], "b") == 0);
        TEST(strcmp(segments[3], "c") == 0);
    }

    {
        Strlcpy(buf, "/usr/include/stdio.h", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == 4);
        TEST(strcmp(segments[0], "/") == 0);
        TEST(strcmp(segments[1], "usr") == 0);
        TEST(strcmp(segments[2], "include") == 0);
        TEST(strcmp(segments[3], "stdio.h") == 0);
    }

    {
        /* Overflow segments buffer */
        Strlcpy(buf, "/a/b/c/d", sizeof(buf));
        TEST(SplitPath(buf, segments, ARRSIZE(segments)) == SIZEMAX);
    }
}
ENDTEST(TestSplitPath)

/*
**==============================================================================
**
** TestPtrArray()
**
**==============================================================================
*/

BEGINTEST(TestPtrArray)
{
    PtrArray arr;
    PtrArray_Construct(&arr, 8, Free);

    PtrArray_Append(&arr, Strdup("Red"));
    PtrArray_Append(&arr, Strdup("Green"));
    PtrArray_Append(&arr, Strdup("Blue"));

    TEST(arr.size == 3);
    TEST(strcmp((char*)arr.data[0], "Red") == 0);
    TEST(strcmp((char*)arr.data[1], "Green") == 0);
    TEST(strcmp((char*)arr.data[2], "Blue") == 0);

    PtrArray_Destruct(&arr);
}
ENDTEST(TestPtrArray);

/*
**==============================================================================
**
** main()
**
**==============================================================================
*/

int main(int argc, char** argv)
{
    arg0 = argv[0];

    TestUIntToStr();
    TestUIntToStrZeroPadded();
    TestSIntToStr();
    TestULongToStr();
    TestSLongLongToStr();
    TestHTTPParseHeaders1();
    TestHTTPParseHeaders2();
    TestHTTPFormatRequest();
    TestBuf();
    TestHexStr();
    TestStrncaseeq();
    TestBase64();
    TestStrcpyStrcat();
    TestStrlcpy2();
    TestStrlcpy3();
    TestRole();
    TestRoleLoad();
    TestRoleLoadFailed();
    TestGetOpt();
    TestGetOptUnknownOption();
    TestGetOptMissingOptArg();
    TestPluginInfo();
    /* TestStatusCodeStrings(); */
    TestMakePath();
    TestFindFile();
    TestConf();
    TestConfFile();
    TestStrtok();
    TestStrlcat();
    TestSplitPath();
    TestPtrArray();

    Cleanup();

#if defined(ENABLE_ALLOCATOR)
    if (GetBytesAllocated() != 0)
    {
        fprintf(stderr, "Error: bytes still allocated\n");
        exit(1);
    }
#endif

    PrintTestSummary();

    return 0;
}
