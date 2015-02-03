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
#include <cstdlib>
#include <cstdio>
#include <odata/odatacxx.h>

using namespace odata;

/*
**==============================================================================
**
** TestArray()
**
**==============================================================================
*/

BEGINTEST(TestArray)
{
    Scope scope;
    {
        Array a1 = scope.NewArray();
        Array colors(a1);
        Array a3 = colors;
        Array a4 = scope.NewArray();
        a4 = a1;
    }

    {
        Array a = scope.NewArray();

        // Disable homogeneous arrays:
        a.SetFlags(0);

        TEST(a.AppendString("Hello"));
        TEST(a.AppendInt32(123));
        TEST(a.AppendBoolean(false));
        {
            Array colors = scope.NewArray();
            TEST(colors.AppendString("Red"));
            TEST(colors.AppendString("Green"));
            TEST(colors.AppendString("Blue"));
            TEST(a.AppendArray(colors));
        }
        TEST(a.AppendDate(Date(2014, 12, 21)));
        TEST(a.AppendNull(OL_Type_Int32));

#if 0
        a.Print();
#endif

        {
            const Char* s;
            TEST(a.GetString(0, s));
            TEST(strcmp(s, "Hello") == 0);
        }
        {
            Int32 x;
            TEST(a.GetInt32(1, x) && x == 123);
        }
        {
            Boolean x;
            TEST(a.GetBoolean(2, x));
            TEST(x == false);
        }
        {
            Array x = scope.NewArray();
            const Char* color;
            TEST(a.GetArray(3, x));
            TEST(x.Count() == 3);
            TEST(x.GetString(0, color) && strcmp(color, "Red") == 0);
            TEST(x.GetString(1, color) && strcmp(color, "Green") == 0);
            TEST(x.GetString(2, color) && strcmp(color, "Blue") == 0);
        }
        {
            Date x;
            TEST(a.GetDate(4, x));
            TEST(x.GetYear() == 2014);
            TEST(x.GetMonth() == 12);
            TEST(x.GetDay() == 21);
        }
    }
}
ENDTEST(TestArray)

/*
**==============================================================================
**
** TestObject()
**
**==============================================================================
*/

BEGINTEST(TestObject)
{
    Scope scope;
    {
        Object o1 = scope.NewObject();
        Object o2(o1);
        Object o3 = o2;
        Object o4 = scope.NewObject();
        o4 = o1;
    }

    Object o = scope.NewObject();
    TEST(o.AddString("Color", "Red"));
    TEST(o.AddInt32("Number", 123456));
    TEST(o.AddBoolean("Flag", true));

    Object o2 = scope.NewObject();
    TEST(o2.AddString("Name", "Fred"));
    TEST(o2.AddInt32("Age", 600));

    o.AddObject("Person", o2);

#if 0
    o.Print();
#endif

    {
        const Char* s;
        TEST(o.GetString("Color", s) && strcmp(s, "Red") == 0);
    }
    {
        Int32 x;
        TEST(o.GetInt32("Number", x) && x == 123456);
    }
    {
        Boolean x;
        TEST(o.GetBoolean("Flag", x) && x == true);
    }
    {
        Object person = scope.NewObject();
        TEST(o.GetObject("Person", person));

#if 0
        person.Print();
#endif
    }
}
ENDTEST(TestObject)

/*
**==============================================================================
**
** TestURI()
**
**==============================================================================
*/

BEGINTEST(TestURI)
{
    Scope scope;
    URI u = scope.NewURI();

    char uri[1024];
    char err[256];

    strcpy(uri, "svc/Orders(4711,'XYZ')/Items");
    TEST(u.Parse(uri, err, sizeof(err)));
    TEST(u.Count() == 2);
    TEST(u.KeyCount(0) == 2);
    TEST(u.KeyCount(1) == 0);

    const char* s;
    Int64 x;

    TEST(u.GetName(0) != 0);
    TEST(strcmp(u.GetName(0), "Orders") == 0);

    TEST(u.GetKeyInt64(0, "$0", x));
    TEST(x == 4711);

    TEST(u.GetKeyString(0, "$1", s));
    TEST(strcmp(s, "XYZ") == 0);

    TEST(u.GetName(1) != 0);
    TEST(strcmp(u.GetName(1), "Items") == 0);

#if 0
    TEST(u.Add("Widgets"));
    TEST(u.AddKeyString(2, "Color", "Red"));
    TEST(u.AddKeyInt64(2, "Number", 123));
    TEST(u.AddKeyBoolean(2, "Flag", true));
    TEST(u.KeyCount(2) == 4);

    TEST(u.GetKeyString(2, "Color", s));
    TEST(strcmp(s, "Red") == 0);

    TEST(u.GetKeyInt64(2, "Number", x));
    TEST(x == 123);

    Boolean f;
    TEST(u.GetKeyBoolean(2, "Flag", f));
    TEST(f == true);

    TEST(u.Format(buf1, sizeof(buf1)));
    TEST(strcmp(buf1,
        "odata/Orders(4711,'XYZ')/Items/Widgets('Red',123,true)") == 0);
#endif

    char buf1[1024];
    strcpy(buf1, "odata/Orders(4711,'XYZ')/Items/Widgets('Red',123,true)");

    {
        strcpy(uri, "odata/Orders(4711,'XYZ')/Items/Widgets('Red',123,true)"); 
        URI u2 = scope.NewURI();
        TEST(u2.Parse(uri, err, sizeof(err)));

        char buf2[1024];
        TEST(u2.Format(buf2, sizeof(buf2)));

        TEST(strcmp(buf1, buf2) == 0);
    }

    {
        URI u = scope.NewURI();
        strcpy(uri, "/Frog(1)/Friends");
        bool f = u.Parse(uri, err, sizeof(err));
        if (!f)
            printf("err{%s}\n", err);
        TEST(f);
    }

    {
        URI u = scope.NewURI();
        strcpy(uri, "/odata/Products/?$top=4&$skip=2");
        bool f = u.Parse(uri, err, sizeof(err));
        if (!f)
            printf("err{%s}\n", err);
        TEST(f);

        unsigned int flags = u.GetQueryOptionFlags();
        TEST(flags & OL_QUERY_OPTION_TOP);
        TEST(flags & OL_QUERY_OPTION_SKIP);

        unsigned long top;
        TEST(u.GetQueryOption(OL_QUERY_OPTION_TOP, &top, sizeof(top)));
        TEST(top == 4);

        unsigned long skip;
        TEST(u.GetQueryOption(OL_QUERY_OPTION_SKIP, &skip, sizeof(skip)));
        TEST(skip == 2);
    }

#if 0
    u.Print();
#endif
}
ENDTEST(TestURI)

/*
**==============================================================================
**
** TestFrog()
**
**==============================================================================
*/

BEGINTEST(TestFrog)
{
    Scope scope;
    Object frog = scope.NewObject();
    frog.AddString("UserName", "kermit");
    frog.AddString("First", "Kermit");
    frog.AddString("Last", "Frog");
    frog.AddString("Color", "Green");
    frog.AddDate("Birthdate", Date(1955, 12, 3));

    bool b = frog.AddNavigationLink("Friend", "Frog(1)");
    TEST(b == false);

#if 0
    // This should fail since there is no 'svc' part:
    b = frog.AddNavigationLink("Friend@odata.navigationLink", 
        "http://xxx.com/Frog(1)");
    TEST(b == false);
#endif

    b = frog.AddNavigationLink("Friend@odata.navigationLink", "Frog(1)");
    TEST(b == true);

#if 0
    frog.Print();
#endif
}
ENDTEST(TestFrog)

/*
**==============================================================================
**
** main()
**
**==============================================================================
*/

int main()
{
    TestArray();
    TestObject();
    TestURI();
    TestFrog();

    PrintTestSummary();

    return 0;
}
