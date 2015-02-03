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
#include <base/str.h>
#include <base/path.h>
#include <odata/json.h>
#include <odata/odata.h>
#include <odata/compare.h>
#include <odata/outstream.h>
#include <odata/providerentry.h>
#include <odata/serialize.h>
#include <odata/uri.h>
#include <odata/uriparser.h>
#include <odata/format.h>
#include <odata/odatamacros.h>
#include <odata/queryoption.h>
#include <odata/csdl.h>
#include <limits.h>

const char* arg0;

/*
**==============================================================================
**
** TestJSON()
**
**==============================================================================
*/

JSON_Value MakeArray(
    JSON_Array** array, 
    const JSON_Value* data, 
    size_t size)
{
    JSON_Value v;
    size_t i;

    *array = JSON_Array_New();
    assert(array);

    for (i = 0; i < size; i++)
    {
        OL_Result r = JSON_Array_Append(*array, &data[i]);
        assert(r == OL_Result_Ok);
    }

    v.type = JSON_Type_Array;
    v.u.array = *array;

    return v;
}

BEGINTEST(TestJSON)
{
    JSON_Object* obj;
    JSON_Object* newObj;
    OL_Result r;
    JSON_Value v;
    
    obj = JSON_Object_New();
    TEST(obj != NULL);

    /* String */
    {
        v = JSON_StringValue("Fred");

        r = JSON_Object_AddF(obj, "\006String"+1, &v, 
            JSON_FLAG_STATIC_NAME|JSON_FLAG_LENGTH_NAME);
        TEST(r == OL_Result_Ok);
    }

    /* TypeMismatch */
    {
        r = JSON_Object_GetAs(obj, "String", JSON_Type_Boolean, &v);
        TEST(r == OL_Result_TypeMismatch);
    }

    /* Boolean */
    {
        v.type = JSON_Type_Boolean;
        v.u.boolean = JSON_TRUE;
        r = JSON_Object_Add(obj, "Boolean", &v);
        TEST(r == OL_Result_Ok);
    }

    /* BooleanNull */
    {
        v.type = JSON_Type_Null;
        r = JSON_Object_Add(obj, "BooleanNull", &v);
        TEST(r == OL_Result_Ok);
    }

    /* Integer */
    {
        v.type = JSON_Type_Integer;
        v.u.integer = 32;
        r = JSON_Object_Add(obj, "Integer", &v);
        TEST(r == OL_Result_Ok);
    }

    /* StringArray */
    {
        JSON_Value data[3];
        data[0] = JSON_StringValue("red");
        data[1] = JSON_StringValue("green");
        data[2] = JSON_StringValue("blue");
        JSON_Array* array;
        v = MakeArray(&array, data, 3);

        r = JSON_Object_Add(obj, "Colors", &v);
        TEST(r == OL_Result_Ok);
        JSON_Array_Release(array);
    }

    /* IntegerArray */
    {
        JSON_Value data[2];
        data[0] = JSON_IntegerValue(10);
        data[1] = JSON_IntegerValue(20);
        JSON_Array* array;
        v = MakeArray(&array, data, OL_ARRAYSIZE(data));
        r = JSON_Object_Add(obj, "Numbers", &v);
        TEST(r == OL_Result_Ok);
        JSON_Array_Release(array);
    }

    /* Expect 6 elements */
    {
        size_t count = JSON_Object_Count(obj);
        TEST(count == 6);
    }

#if 0
    JSON_Object_Print(obj, 0);
#endif

    /* Set 'String' */
    {
        v = JSON_StringValue("Bob");
        r = JSON_Object_Set(obj, "String", &v);
        TEST(r == OL_Result_Ok);
    }

    /* Get 'String' */
    {
        JSON_Value value;
        unsigned int flags = JSON_FLAG_LENGTH_NAME;
        r = JSON_Object_GetF(obj, "\006String"+1, &value, &flags);
        TEST(r == OL_Result_Ok);
        TEST(value.type == JSON_Type_String);
        TEST(strcmp(value.u.string, "Bob") == 0);
    }

    /* Get 'Colors' */
    {
        JSON_Value value;
        unsigned int flags = JSON_FLAG_LENGTH_NAME;
        r = JSON_Object_GetF(obj, "\006Colors"+1, &value, &flags);
        TEST(r == OL_Result_Ok);

        TEST(value.type == JSON_Type_Array);

        TEST(value.u.array);
        TEST(JSON_Array_Count(value.u.array) == 3);

        {
            JSON_Value v;
            r = JSON_Array_Get(value.u.array, 0, &v);
            TEST(r == OL_Result_Ok);
            TEST(v.type == JSON_Type_String);
            TEST(strcmp(v.u.string, "red") == 0);
        }
        {
            JSON_Value v;
            r = JSON_Array_Get(value.u.array, 1, &v);
            TEST(r == OL_Result_Ok);
            TEST(v.type == JSON_Type_String);
            TEST(strcmp(v.u.string, "green") == 0);
        }
        {
            JSON_Value v;
            r = JSON_Array_Get(value.u.array, 2, &v);
            TEST(r == OL_Result_Ok);
            TEST(v.type == JSON_Type_String);
            TEST(strcmp(v.u.string, "blue") == 0);
        }
    }

    {
        r = JSON_Object_Remove(obj, "BooleanNull", 0);
        TEST(r == OL_Result_Ok);
    }

    /* Set Object */
    {
        JSON_Object* obj2 = JSON_Object_New();
        TEST(obj2 != NULL);

        /* obj2.Color */
        v = JSON_StringValue("MyObject");
        r = JSON_Object_Add(obj2, "Name", &v);
        TEST(r == OL_Result_Ok);

        /* obj2.Color */
        v = JSON_IntegerValue(12345);
        r = JSON_Object_Add(obj2, "Integer", &v);
        TEST(r == OL_Result_Ok);

        /* obj.Object */
        v = JSON_ObjectValue(obj2);
        r = JSON_Object_Add(obj, "Object", &v);
        TEST(r == OL_Result_Ok);

        r = JSON_Object_Release(obj2);
        TEST(r == OL_Result_Ok);
    }

#if 0
    JSON_Object_Print(obj, 0);
#endif

    /* Expect 6 elements */
    {
        size_t count = JSON_Object_Count(obj);
        TEST(count == 6);
    }

    {
        newObj = JSON_Object_Clone(obj);
        TEST(newObj != NULL);
    }

#if 0
    JSON_Object_Print(newObj, 0);
#endif

    JSON_Object_AddRef(obj);
    JSON_Object_Release(obj);

    JSON_Object_Release(obj);
    JSON_Object_Release(newObj);
}
ENDTEST(TestJSON)

/*
**==============================================================================
**
** TestJSONHelpers()
**
**==============================================================================
*/

BEGINTEST(TestJSONHelpers)
{
    OL_Result r;
    JSON_Integer integer;
    const JSON_Char* string;
    
    JSON_Object* obj = JSON_Object_New();
    TEST(obj != NULL);

    r = JSON_Object_AddInteger(obj, "Integer", 99);
    TEST(r == OL_Result_Ok);

    r = JSON_Object_GetInteger(obj, "Integer", &integer);
    TEST(r == OL_Result_Ok);
    TEST(integer == 99);

    r = JSON_Object_AddString(obj, "String", "Hello World");
    TEST(r == OL_Result_Ok);

    r = JSON_Object_GetString(obj, "String", &string);
    TEST(r == OL_Result_Ok);
    TEST(string != NULL);
    TEST(strcmp(string, "Hello World") == 0);

#if 0
    JSON_Object_Print(obj, 0);
#endif
    JSON_Object_Release(obj);

}
ENDTEST(TestJSONHelpers)

/*
**==============================================================================
**
** MakeServiceEntity()
**
**==============================================================================
*/

JSON_Object* MakeServiceEntity(
    const char* name,
    const char* title,
    const char* kind,
    const char* url)
{
    OL_Result r;

    JSON_Object* obj = JSON_Object_New();
    assert(obj != NULL);

    if (name)
    {
        r = JSON_Object_AddString(obj, "name", name);
        assert(r == OL_Result_Ok);
    }

    if (title)
    {
        r = JSON_Object_AddString(obj, "title", title);
        assert(r == OL_Result_Ok);
    }

    if (kind)
    {
        r = JSON_Object_AddString(obj, "kind", kind);
        assert(r == OL_Result_Ok);
    }

    if (url)
    {
        r = JSON_Object_AddString(obj, "url", url);
        assert(r == OL_Result_Ok);
    }

    return obj;
}

/*
**==============================================================================
**
** TestServiceDoc()
**
**==============================================================================
*/

BEGINTEST(TestServiceDoc)
{
    OL_Result r;
    OutStream os;

    OutStreamInit(&os);

    JSON_Object* obj = JSON_Object_New();
    TEST(obj != NULL);

    r = JSON_Object_AddString(obj, "@odata.context",  
        "http://host/service/$metadata");
    TEST(r == OL_Result_Ok);

    {
        JSON_Object* odata[4];
        JSON_Value v;
        JSON_Value data[4];
        
        odata[0] = MakeServiceEntity(
            "Orders", /* name */
            NULL, /* title */
            "EntitySet", /* kind */
            "Orders"); /* url */
        TEST(odata != NULL);

        odata[1] = MakeServiceEntity(
            "Order Items", /* name */
            "Order Details", /* title */
            NULL, /* kind */
            "OrderItems"); /* url */
        TEST(odata != NULL);

        odata[2] = MakeServiceEntity(
            "Contoso", /* name */
            "Contoso Ltd.", /* title */
            "Singleton", /* kind */
            "Contoso"); /* url */
        TEST(odata != NULL);

        odata[3] = MakeServiceEntity(
            "Human Resources", /* name */
            NULL, /* title */
            "ServiceDocument", /* kind */
            "http://host/HR/"); /* url */
        TEST(odata != NULL);

        data[0] = JSON_ObjectValue(odata[0]);
        data[1] = JSON_ObjectValue(odata[1]);
        data[2] = JSON_ObjectValue(odata[2]);
        data[3] = JSON_ObjectValue(odata[3]);

        JSON_Array* array;
        v = MakeArray(&array, data, OL_ARRAYSIZE(data));
        r = JSON_Object_Add(obj, "value", &v);
        TEST(r == OL_Result_Ok);
        JSON_Array_Release(array);

        JSON_Object_Release(odata[0]);
        JSON_Object_Release(odata[1]);
        JSON_Object_Release(odata[2]);
        JSON_Object_Release(odata[3]);
    }

    JSON_Object_Serialize(obj, &os.base, 0);

#if 0
    printf("%.*s\n", (int)os.out->size, os.out->data);
#endif

    JSON_Object_Release(obj);
    OutStreamDestroy(&os);
}
ENDTEST(TestServiceDoc)

/*
**==============================================================================
**
** MakePersonEntity()
**
**==============================================================================
*/

JSON_Object* MakePersonEntity()
{
    OL_Result r;

    JSON_Object* obj = JSON_Object_New();
    assert(obj != NULL);

    r = JSON_Object_AddString(obj, "First", "John");
    assert(r == OL_Result_Ok);

    r = JSON_Object_AddString(obj, "Last", "Smith");
    assert(r == OL_Result_Ok);

    r = JSON_Object_AddInteger(obj, "Age", 25);
    assert(r == OL_Result_Ok);

    return obj;
}

/*
**==============================================================================
**
** TestJSONSerialize()
**
**==============================================================================
*/

int _CompareObjectSerializations(JSON_Object* obj1, JSON_Object* obj2)
{
    OL_Result r;
    OutStream os1;
    OutStream os2;

    OutStreamInit(&os1);
    OutStreamInit(&os2);

    r = JSON_Object_Serialize(obj1, &os1.base, 0);

    if (r != OL_Result_Ok)
        return 0;

    r = JSON_Object_Serialize(obj2, &os2.base, 0);

    if (r != OL_Result_Ok)
        return 0;

    if (os1.out->size != os2.out->size)
        return 0;

    if (memcmp(os1.out->data, os2.out->data, os1.out->size) != 0)
        return 0;

    OutStreamDestroy(&os1);
    OutStreamDestroy(&os2);
    return 1;
}

JSON_Object* NewTestObject()
{
    OL_Result r;
    JSON_Object* person;

    JSON_Object* obj = JSON_Object_New();
    assert(obj != NULL);

    person = MakePersonEntity();
    assert(person != NULL);

    r = JSON_Object_AddBoolean(obj, "Byte", JSON_TRUE);
    assert(r == OL_Result_Ok);

    {
        const char* s;

        r = JSON_Object_AddString(obj, "String", 
            "\nLF\rCR\tTAB\rCR\001ONE");
        assert(r == OL_Result_Ok);

        r = JSON_Object_GetString(obj, "String", &s);
        assert(r == OL_Result_Ok);
        assert(strcmp(s, "\nLF\rCR\tTAB\rCR\001ONE") == 0);
    }

    {
        const char* s;

        r = JSON_Object_AddString(obj, "EscString2", 
            "ABCDEFG\nLF\rCR\tTAB\rCR\001ONE");
        assert(r == OL_Result_Ok);
        r = JSON_Object_GetString(obj, "EscString2", &s);
        assert(r == OL_Result_Ok);
        assert(strcmp(s, "ABCDEFG\nLF\rCR\tTAB\rCR\001ONE") == 0);
    }

    r = JSON_Object_AddInteger(obj, "Integer", 12345678);
    assert(r == OL_Result_Ok);

    r = JSON_Object_AddReal(obj, "Real", 123.456);
    assert(r == OL_Result_Ok);

    r = JSON_Object_AddObject(obj, "Person", person);
    assert(r == OL_Result_Ok);

    {
        JSON_Value data[3];
        JSON_Value v;
        data[0] = JSON_StringValue("red");
        data[1] = JSON_StringValue("green");
        data[2] = JSON_StringValue("blue");
        JSON_Array* array;
        v = MakeArray(&array, data, 3);

        r = JSON_Object_Add(obj, "Colors", &v);
        assert(r == OL_Result_Ok);
        JSON_Array_Release(array);
    }

    {
        JSON_Value data[3];
        JSON_Value v;
        data[0] = JSON_IntegerValue(-64);
        data[1] = JSON_IntegerValue(64);
        data[2] = JSON_IntegerValue(12345);
        JSON_Array* array;
        v = MakeArray(&array, data, OL_ARRAYSIZE(data));
        r = JSON_Object_Add(obj, "IntegerA", &v);
        assert(r == OL_Result_Ok);
        JSON_Array_Release(array);
    }

    {
        JSON_Value data[2];
        JSON_Value v;
        data[0] = JSON_ObjectValue(person);
        data[1] = JSON_ObjectValue(person);
        JSON_Array* array;
        v = MakeArray(&array, data, OL_ARRAYSIZE(data));
        r = JSON_Object_Add(obj, "Persons", &v);
        assert(r == OL_Result_Ok);
        JSON_Array_Release(array);
    }

    {
        JSON_Value data[3];
        JSON_Value v;

        data[0] = JSON_StringValue("string");
        data[1] = JSON_IntegerValue(12345);
        data[2] = JSON_ObjectValue(person);
        JSON_Array* array;
        v = MakeArray(&array, data, 3);

        r = JSON_Object_Add(obj, "Mixed", &v);
        assert(r == OL_Result_Ok);
        JSON_Array_Release(array);
    }

    JSON_Object_Release(person);

    return obj;
}

JSON_Object* Deserialize(
    char* data,
    size_t size)
{
    OL_Result r;
    size_t offset;

    JSON_Object* obj = JSON_Object_New();
    assert(obj != NULL);

#if 0
    Dump(stdout, "DATA", data, size);
    printf("%.*s\n", (int)size, data);
#endif

    r = JSON_Object_Deserialize(obj, data, size, &offset);
    assert(r == OL_Result_Ok);

    return obj;
}

BEGINTEST(TestJSONSerialize)
{
    OL_Result r;
    OutStream os;
    JSON_Object* obj;
    size_t i;

    OutStreamInit(&os);

    obj = NewTestObject();
    r = JSON_Object_Serialize(obj, &os.base, 0);
    TEST(r == OL_Result_Ok);

#if 0
    printf("%.*s\n", (int)os.out->size, os.out->data);
#endif

#if 0
    for (i = 0; i < 10000; i++)
#endif
    {
        OutStream os2;
        OutStreamInit(&os2);
        r = JSON_Object_Serialize(obj, &os2.base, 0);
        TEST(r == OL_Result_Ok);
        OutStreamDestroy(&os2);
    }

    for (i = 0; i < 1; i++)
    {
        Buf buf = BUF_INITIALIZER;
        JSON_Object* obj2;

        BufCat(&buf, os.out->data, os.out->size);
        {
            obj2 = Deserialize(buf.data, buf.size);

            if (i == 0)
            {
#if 0
                JSON_Object_Print(obj2, 0);
#endif
                TEST(_CompareObjectSerializations(obj, obj2));
            }
        }
        BufDestroy(&buf);

        JSON_Object_Release(obj2);
    }

    JSON_Object_Release(obj);
    OutStreamDestroy(&os);
}
ENDTEST(TestJSONSerialize)

/*
**==============================================================================
**
** TestSizes()
**
**==============================================================================
*/

BEGINTEST(TestSizes)
{
    TEST(sizeof(JSON_Union) == sizeof(OL_Union));
    TEST(sizeof(JSON_Value) == sizeof(OL_Value));
    TEST(sizeof(JSON_Boolean) == sizeof(OL_Boolean));
    TEST(sizeof(JSON_Integer) == sizeof(OL_Int64));
    TEST(sizeof(JSON_Real) == sizeof(OL_Double));
    TEST(sizeof(JSON_String) == sizeof(OL_String));
    TEST(sizeof(JSON_Array) == sizeof(OL_Array));
}
ENDTEST(TestSizes)

/*
**==============================================================================
**
** TestODATA()
**
**==============================================================================
*/

OL_Value ODATAMakeArray(
    OL_Array** array, 
    const OL_Value* data, 
    size_t size)
{
    OL_Value v;
    size_t i;

    *array = __OL_Array_New();
    assert(array);

    for (i = 0; i < size; i++)
    {
        OL_Result r = OL_Array_Append(*array, &data[i]);
        assert(r == OL_Result_Ok);
    }

    v.type = OL_Type_Array;
    v.u.array = *array;

    return v;
}

int AddGetCheck(
    OL_Object* obj, 
    const char* name, 
    const OL_Value value)
{
    OL_Result r;
    OL_Value v;

    r = OL_Object_Add(obj, name, (const OL_Value*)&value);

    if (r != OL_Result_Ok)
    {
        TRACE;
        return -1;
    }

    r = OL_Object_Get(obj, name, &v);

    if (r != OL_Result_Ok)
    {
        TRACE;
        return -1;
    }

    if (v.type != value.type)
    {
        TRACE;
        return -1;
    }

    if (ValueCompare(&value, &v) != 0)
    {
        TRACE;
        return -1;
    }

    return 0;
}

static int TestBinary(
    OL_Object* obj, 
    const char* name,
    void* data, 
    size_t size)
{
    OL_Binary b1;
    OL_Binary b2;
    OL_Result r;

    b1.data = data;
    b1.size = size;

    if ((r = OL_Object_AddBinary(obj, name, b1)) != OL_Result_Ok)
        return 0;

#if 0
    OL_Object_Print(obj);
#endif

    if ((r = OL_Object_GetBinary(obj, name, &b2)) != OL_Result_Ok)
        return 0;

    if (b1.size != b2.size)
        return 0;

    if (memcmp(b1.data, b2.data, b1.size) != 0)
        return 0;

    return 1;
}

BEGINTEST(TestODATA)
{
    OL_Result r;
    
    OL_Object* obj = __OL_Object_New();
    TEST(obj != NULL);

    TEST(AddGetCheck(obj, "Guid", OL_GuidValue(
        0xAAAAAAAA,0xBBBB,0xCCCC,0xDDDD,0xEEEE,0xEEEEEEEE)) == 0);
    TEST(AddGetCheck(obj, "ByteMin", OL_ByteValue(0)) == 0);
    TEST(AddGetCheck(obj, "ByteMax", OL_ByteValue(255)) == 0);
    TEST(AddGetCheck(obj, "SByteMin", OL_SByteValue(-128)) == 0);
    TEST(AddGetCheck(obj, "SByteMax", OL_SByteValue(127)) == 0);
    TEST(AddGetCheck(obj, "Int16Min", OL_Int16Value(-32768)) == 0);
    TEST(AddGetCheck(obj, "Int32Min", OL_Int32Value(INT_MIN)) == 0);
    TEST(AddGetCheck(obj, "Int32Max", OL_Int32Value(INT_MAX)) == 0);
    TEST(AddGetCheck(obj, "Int64Max", OL_Int64Value(99999999)) == 0);
    TEST(AddGetCheck(obj, "Single1", OL_SingleValue(1)) == 0);
    TEST(AddGetCheck(obj, "Single0", OL_SingleValue(0)) == 0);
    TEST(AddGetCheck(obj, "Double0", OL_DoubleValue(0)) == 0);
    TEST(AddGetCheck(obj, "StringEmpty", OL_StringValue("")) == 0);
    TEST(AddGetCheck(obj, "StringFull", OL_StringValue("Full")) == 0);
    TEST(AddGetCheck(obj, "Date", OL_DateValue(2014,7,4)) == 0);
    TEST(AddGetCheck(obj, "DateTimeOffset", 
        OL_DateTimeOffsetValue(2014,7,4,12,15,3,666)) == 0);
    TEST(AddGetCheck(obj, "DateTimeOffset5", 
        OL_DateTimeOffsetValue(2014,7,4,12,15,0,0)) == 0);
    TEST(AddGetCheck(obj, "TimeOfDay", OL_TimeOfDayValue(12,15,3,555)) == 0);
    TEST(AddGetCheck(obj, "Duration", OL_DurationValue(OL_TRUE, 10,3,4,3,555)) == 0);
    TEST(AddGetCheck(obj, "Duration2", OL_DurationValue(OL_TRUE, 10,0,0,0,0)) == 0);

    /* StringArray */
    {
        OL_Value data[3];
        data[0] = OL_StringValue("red");
        data[1] = OL_StringValue("green");
        data[2] = OL_StringValue("blue");
        OL_Array* array;
        OL_Value v = ODATAMakeArray(&array, data, 3);

        r = OL_Object_Add(obj, "Colors", &v);
        TEST(r == OL_Result_Ok);
        OL_Array_Release(array);
    }

    /* Heterogeneous arrays (should fail) */
    {
        OL_Array* array = __OL_Array_New();
        OL_Value v;

        TEST(array != NULL);

        v = OL_StringValue("Red");
        r = OL_Array_Append(array, &v);
        TEST(r == OL_Result_Ok);

        v = OL_Int64Value(1);
        r = OL_Array_Append(array, &v);
        TEST(r == OL_Result_TypeMismatch);

        TEST(OL_Array_Count(array) == 1);
        OL_Array_Release(array);
    }


    /* DateArray */
    {
        OL_Value data[3];
        data[0] = OL_DateValue(2014,1,1);
        data[1] = OL_DateValue(2014,1,2);
        data[2] = OL_DateValue(2014,1,3);
        OL_Array* array;
        OL_Value v = ODATAMakeArray(&array, data, 3);

        r = OL_Object_Add(obj, "DateArray", &v);
        TEST(r == OL_Result_Ok);

        OL_Value tmp;
        r = OL_Object_Get(obj, "DateArray", &tmp);
        TEST(r == OL_Result_Ok);

        ValueCompare(&v, &tmp);
        OL_Array_Release(array);
    }

    /* Add string and then get as a date */
    {
        OL_Value v = OL_StringValue("2014-01-02");
        r = OL_Object_Add(obj, "StringDate", &v);
        TEST(r == OL_Result_Ok);

        r = OL_Object_GetAs(
            obj, "StringDate", OL_Type_Date, &v);
        TEST(r == OL_Result_Ok);

        TEST(v.type == OL_Type_Date);
        TEST(v.u.date.year = 2014);
        TEST(v.u.date.month = 1);
        TEST(v.u.date.day = 2);
    }

    TEST(TestBinary(obj, "OData", STRLIT("OData")));
    TEST(TestBinary(obj, "Binary1", STRLIT("A")));
    TEST(TestBinary(obj, "Binary2", STRLIT("AB")));
    TEST(TestBinary(obj, "Binary3", STRLIT("ABC")));
    TEST(TestBinary(obj, "Binary4", STRLIT("ABCD")));
    TEST(TestBinary(obj, "Binary5", STRLIT("ABCDE")));
    TEST(TestBinary(obj, "Binary6", STRLIT("ABCDEF")));
    TEST(TestBinary(obj, "Binary7", STRLIT("ABCDEFG")));
    TEST(TestBinary(obj, "Binary8", STRLIT("ABCDEFGH")));
    TEST(TestBinary(obj, "Binary9", STRLIT("ABCDEFGHI")));
    TEST(TestBinary(obj, "Binary10", STRLIT("ABCDEFGHIJ")));
    TEST(TestBinary(obj, "Binary11", STRLIT("ABCDEFGHIJK")));

#if 0
    {
        size_t count = OL_Object_Count(obj);
        TEST(count == 5);
    }
#endif

#if 0
    OL_Object_Print(obj);
#endif

    OL_Object_Release(obj);
}
ENDTEST(TestODATA)

/*
**==============================================================================
**
** TestPerson()
**
**==============================================================================
*/

BEGINTEST(TestPerson)
{
    OL_Scope* scope;
    OL_Object* object;
    OL_Result r;
    OL_Value v;
    
    /* Allocate scope */
    scope = __OL_Scope_New();
    TEST(scope);

    /* Allocate object */
    object = OL_Scope_NewObject(scope);
    TEST(object);

    /* Person.UserName */
    r = OL_Object_AddString(object, "UserName", "jsmith");
    TEST(r == OL_Result_Ok);

    /* Person.UserName */
    r = OL_Object_AddString(object, "FirstName", "John");
    TEST(r == OL_Result_Ok);

    /* Person.LastName */
    r = OL_Object_AddString(object, "LastName", "Smith");
    TEST(r == OL_Result_Ok);

    /* Person.Gender */
    r = OL_Object_AddString(object, "Gender", "Male");
    TEST(r == OL_Result_Ok);

    /* Person.Birthdate */
    v = OL_DateValue(1891, 8, 2);
    r = OL_Object_Add(object, "Birthdate", &v);
    TEST(r == OL_Result_Ok);

    /* Person.Emails */
    {
        OL_Array* array = OL_Scope_NewArray(scope);
        TEST(array);
        OL_Value v;

        v = OL_StringValue("jsmith@abc.com");
        OL_Array_Append(array, &v);

        v = OL_StringValue("john.smith@abc.com");
        OL_Array_Append(array, &v);

        r = OL_Object_AddArray(object, "Emails", array);
        TEST(r == OL_Result_Ok);

        OL_Array_Release(array);
    }

    /* Person.Address */
    {
        OL_Object* address = OL_Scope_NewObject(scope);
        TEST(address);
        TEST(address);

        r = OL_Object_AddString(address, "StreetAddress", "603 Dead Oak");
        TEST(r == OL_Result_Ok);

        r = OL_Object_AddString(address, "Country", "United States");
        TEST(r == OL_Result_Ok);

        r = OL_Object_AddString(address, "City", "Arlington");
        TEST(r == OL_Result_Ok);

        r = OL_Object_AddString(address, "State", "TX");
        TEST(r == OL_Result_Ok);

        r = OL_Object_AddObject(object, "Address", address);
        TEST(r == OL_Result_Ok);

        OL_Object_Release(address);
    }

#if 0
    OL_Object_Print(object);
#endif

    OL_Object_Release(object);

    OL_Scope_Clear(scope);

    {
        OL_Object* tmp = OL_Scope_NewObject(scope);
        TEST(tmp);
        OL_Object_Release(tmp);
    }

    {
        OL_Object* tmp = OL_Scope_NewObject(scope);
        TEST(tmp);
        OL_Object_Release(tmp);
    }


    OL_Scope_Release(scope);
}
ENDTEST(TestPerson)

/*
**==============================================================================
**
** TestProviderEntry()
**
**==============================================================================
*/

BEGINTEST(TestProviderEntry)
{
    char err[64];
    int r;
    ProviderEntry** entries;
    size_t entriesSize;
    size_t i;

    r = ProviderEntryLoadFile(
        TESTDIR "/providers.conf",
        &entries,
        &entriesSize,
        err, 
        sizeof(err));

    if (r != 0)
    {
        fprintf(stderr, "%s\n", err);
        TEST(0);
    }

    TEST(r != -1);

    TEST(entriesSize == 3);

    TEST(strcmp(entries[0]->libname, "/usr/lib/libmyprovider.so") == 0);
    TEST(entries[0]->paths.size == 3);
    TEST(entries[0]->paths.data[0].nsegments == 1);
    TEST(strcmp(entries[0]->paths.data[0].segments[0], "Me") == 0);
    TEST(entries[0]->paths.data[1].nsegments == 1);
    TEST(strcmp(entries[0]->paths.data[1].segments[0], "Myself") == 0);
    TEST(entries[0]->paths.data[2].nsegments == 1);
    TEST(strcmp(entries[0]->paths.data[2].segments[0], "I") == 0);
    TEST(entries[0]->queryOptions & OL_QUERY_OPTION_TOP);
    TEST(!(entries[0]->queryOptions & OL_QUERY_OPTION_SKIP));

    TEST(strcmp(entries[1]->libname, "/usr/lib/libyourprovider.so") == 0);
    TEST(entries[1]->paths.size == 2);

    TEST(entries[1]->paths.data[0].nsegments == 1);
    TEST(strcmp(entries[1]->paths.data[0].segments[0], "You") == 0);

    TEST(entries[1]->paths.data[1].nsegments == 1);
    TEST(strcmp(entries[1]->paths.data[1].segments[0], "Yours") == 0);
    TEST(entries[1]->queryOptions & OL_QUERY_OPTION_TOP);
    TEST(entries[1]->queryOptions & OL_QUERY_OPTION_SKIP);

    TEST(strcmp(entries[2]->libname, "/lib/libpersonprovider.so") == 0);
    TEST(entries[2]->paths.size == 4);

    TEST(entries[2]->paths.data[0].nsegments == 3);
    TEST(strcmp(entries[2]->paths.data[0].segments[0], "/") == 0);
    TEST(strcmp(entries[2]->paths.data[0].segments[1], "service") == 0);
    TEST(strcmp(entries[2]->paths.data[0].segments[2], "Person") == 0);

    TEST(entries[2]->paths.data[1].nsegments == 3);
    TEST(strcmp(entries[2]->paths.data[1].segments[0], "/") == 0);
    TEST(strcmp(entries[2]->paths.data[1].segments[1], "service") == 0);
    TEST(strcmp(entries[2]->paths.data[1].segments[2], "Vehicle") == 0);

    TEST(entries[2]->paths.data[2].nsegments == 3);
    TEST(strcmp(entries[2]->paths.data[2].segments[0], "/") == 0);
    TEST(strcmp(entries[2]->paths.data[2].segments[1], "service") == 0);
    TEST(strcmp(entries[2]->paths.data[2].segments[2], "Residence") == 0);

    TEST(entries[2]->paths.data[3].nsegments == 1);
    TEST(strcmp(entries[2]->paths.data[3].segments[0], "/") == 0);

    for (i = 0; i < entriesSize; i++)
    {
#if 0
        ProviderEntryPrint(entries[i]);
#endif
        ProviderEntryDelete(entries[i]);
    }

    Free(entries);
}
ENDTEST(TestProviderEntry)

/*
**==============================================================================
**
** TestURIExpandEscapes()
**
**==============================================================================
*/

int TestURIExpandEscapesAux(const char* str, const char* expect)
{
    char buf[64];

    strcpy(buf, str);

    if (URIExpandEscapes(buf) != 0)
        return -1;

    if (strcmp(buf, expect) != 0)
        return -1;

#if 0
    printf("buf[%s]\n", buf);
#endif

    return 0;
}

BEGINTEST(TestURIExpandEscapes)
{

    TEST(TestURIExpandEscapesAux("%20", " ") == 0);
    TEST(TestURIExpandEscapesAux("A%20B", "A B") == 0);
    TEST(TestURIExpandEscapesAux("%20B", " B") == 0);
    TEST(TestURIExpandEscapesAux("A%20", "A ") == 0);
    TEST(TestURIExpandEscapesAux("%41%42%43", "ABC") == 0);

    TEST(TestURIExpandEscapesAux(".%41.%42.%43.", ".A.B.C.") == 0);

#if 0
    {
        size_t i;

        for (i = 0; i < 1000000; i++)
        {
            char buf[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa%20bbbbbbbbbbb";
            URIExpandEscapes(buf);
        }
    }
#endif
}
ENDTEST(TestURIExpandEscapes)

/*
**==============================================================================
**
** TestURIParse()
**
**==============================================================================
*/

static void PrintURI(const URI* uri)
{
#if 0
    OL_URI_Print(&uri->base, 0);
#endif
}

int CheckURLContext(
    const char* uriText,
    const char* expected)
{
    URI* uri;
    char buf[128];
    char urlContext[128];
    OL_Result r;
    char err[64];

    assert((uri = (URI*)__OL_URI_New()) != NULL);

    r = URIParse(uri, strcpy(buf, uriText), err, sizeof(err));

    if (r != OL_Result_Ok)
    {
        printf("CheckURLContext(): failed: 1\n");
        return 0;
    }

    r = URIFormatContextURL(uri, urlContext, sizeof(urlContext));

    if (r != OL_Result_Ok)
    {
        printf("CheckURLContext(): failed: 2\n");
        return 0;
    }

#if 0
    PrintURI(&uri->base, 0);
    printf("URI{%s}\n", uriText);
    printf("STR{%s}\n", urlContext);
    printf("EXP{%s}\n", expected);
#endif

    if (strcmp(urlContext, expected) != 0)
        return 0;

    OL_URI_Release(&uri->base);
    return 1;
}

BEGINTEST(TestURIParse)
{
    char err[64];
    char buf[128];
    URI* uri;

    TEST((uri = (URI*)__OL_URI_New()) != NULL);

    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "https://xyz.com/odata/Person"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(strcmp(uri->service, "odata") == 0);
        TEST(uri->segments.size == 1);
        TEST(strcmp(uri->segments.data[0].name, "Person") == 0);
        TEST(uri->segments.data[0].keysSize == 0);
    }

    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "https://xyz.com/odata/Person/Job"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->segments.size == 2);
        TEST(strcmp(uri->segments.data[0].name, "Person") == 0);
        TEST(strcmp(uri->segments.data[1].name, "Job") == 0);
    }

    {
        const URIKey* key;

        OL_Result r = URIParse(
            uri,
            strcpy(buf, 
                "https://xyz.com/odata/Person(99, msg='hello', false, true)"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->segments.size == 1);
        TEST(strcmp(uri->segments.data[0].name, "Person") == 0);
        TEST(uri->segments.data[0].keysSize == 4);

        /* 99 */
        key = &uri->segments.data[0].keys[0];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "$0") == 0);
        TEST(key->value.type == OL_Type_Int64);
        TEST(key->value.u.int64 == 99);

        /* 'hello' */
        key = &uri->segments.data[0].keys[1];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "msg") == 0);
        TEST(key->value.type == OL_Type_String);
        TEST(strcmp(key->value.u.string, "hello") == 0);

        /* false */
        key = &uri->segments.data[0].keys[2];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "$2") == 0);
        TEST(key->value.type == OL_Type_Boolean);
        TEST(key->value.u.boolean == OL_FALSE);

        /* true */
        key = &uri->segments.data[0].keys[3];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "$3") == 0);
        TEST(key->value.type == OL_Type_Boolean);
        TEST(key->value.u.boolean == OL_TRUE);

        {
            const char* name = OL_URI_GetName(&uri->base, 0);
            TEST(name != NULL);
            TEST(strcmp(name, "Person") == 0);
        }

        {
            OL_Value v;
            OL_Result r = OL_URI_GetKey(&uri->base, 0, "$0", &v);
            TEST(r == OL_Result_Ok);
            TEST(v.type == OL_Type_Int64);
            TEST(v.u.int64 == 99);
        }

        {
            OL_Value v;
            OL_Result r = OL_URI_GetKey(&uri->base, 0, "msg", &v);
            TEST(r == OL_Result_Ok);
            TEST(v.type == OL_Type_String);
            TEST(strcmp(v.u.string, "hello") == 0);
        }

        {
            OL_Value v;
            OL_Result r = OL_URI_GetKey(&uri->base, 0, "$2", &v);
            TEST(r == OL_Result_Ok);
            TEST(v.type == OL_Type_Boolean);
            TEST(v.u.boolean == OL_FALSE);
        }

        {
            OL_Value v;
            OL_Result r = OL_URI_GetKey(&uri->base, 0, "$3", &v);
            TEST(r == OL_Result_Ok);
            TEST(v.type == OL_Type_Boolean);
            TEST(v.u.boolean = OL_TRUE);
        }
    }

    {
        const URIKey* key;

        OL_Result r = URIParse(
            uri,
            strcpy(buf, "odata/Person(Name='Fred', Age=99, Single=true)"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->segments.size == 1);
        TEST(strcmp(uri->segments.data[0].name, "Person") == 0);
        TEST(uri->segments.data[0].keysSize == 3);

        /* Name='Fred' */
        key = &uri->segments.data[0].keys[0];
        TEST(strcmp(key->name, "Name") == 0);
        TEST(key->value.type == OL_Type_String);
        TEST(strcmp(key->value.u.string, "Fred") == 0);

        /* Age=99 */
        key = &uri->segments.data[0].keys[1];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "Age") == 0);
        TEST(key->value.type == OL_Type_Int64);
        TEST(key->value.u.int64 == 99);

        /* Single=true */
        key = &uri->segments.data[0].keys[2];
        TEST(strcmp(key->name, "Single") == 0);
        TEST(key->value.type == OL_Type_Boolean);
        TEST(key->value.u.boolean == OL_TRUE);
    }

    {
        const URIKey* key;

        OL_Result r = URIParse(
            uri,
            strcpy(buf, "https://xyz.com/odata/Person(1)/Job('JOB101')"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->segments.size == 2);

        /* Person */
        TEST(strcmp(uri->segments.data[0].name, "Person") == 0);
        TEST(uri->segments.data[0].keysSize == 1);
        key = &uri->segments.data[0].keys[0];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "$0") == 0);
        TEST(key->value.type == OL_Type_Int64);
        TEST(key->value.u.int64 == 1);

        /* Job */
        TEST(strcmp(uri->segments.data[1].name, "Job") == 0);
        TEST(uri->segments.data[1].keysSize == 1);
        key = &uri->segments.data[1].keys[0];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "$0") == 0);
        TEST(key->value.type == OL_Type_String);
        TEST(strcmp(key->value.u.string, "JOB101") == 0);
    }

    {
        const URIKey* key;

        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata/GetNearestAirport(lat = 33, lon = -118)"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 2);

        /* GetNearestAirport */
        TEST(strcmp(uri->segments.data[0].name, "GetNearestAirport") == 0);

        /* lat == 33 */
        key = &uri->segments.data[0].keys[0];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "lat") == 0);
        TEST(key->value.type == OL_Type_Int64);
        TEST(key->value.u.int64 == 33);

        /* lon == -118 */
        key = &uri->segments.data[0].keys[1];
        TEST(key->name != NULL);
        TEST(strcmp(key->name, "lon") == 0);
        TEST(key->value.type == OL_Type_Int64);
        TEST(key->value.u.int64 == -118);
    }

    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata/GetHeapUsage()"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 0);

        /* GetHeapUsage */
        TEST(strcmp(uri->segments.data[0].name, "GetHeapUsage") == 0);
    }

    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata-plain/stuff"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(strcmp(uri->service, "odata-plain") == 0);

        TEST(r == OL_Result_Ok);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 0);

        /* stuff */
        TEST(strcmp(uri->segments.data[0].name, "stuff") == 0);
    }

    /* PROTOCOL.10.2: Service Document */
    TEST(CheckURLContext(
        "odata",
        "odata/$metadata"));

    /* PROTOCOL.10.2: Collection of Entities */
    TEST(CheckURLContext(
        "odata/Customers",
        "odata/$metadata#Customers"));

    /* PROTOCOL.10.2: Collection of Entities */
    TEST(CheckURLContext(
        "odata/Orders(4711)/Items",
        "odata/$metadata#Orders(4711)/Items"));

    TEST(CheckURLContext(
        "odata/Orders(4711,'XYZ')/Items",
        "odata/$metadata#Orders(4711,'XYZ')/Items"));

    /* PROTOCOL.10.3: Entity */
    TEST(CheckURLContext(
        "http://host/odata/Customers(1)",
        "odata/$metadata#Customers"));

    /* PROTOCOL.10.3: Entity */
    TEST(CheckURLContext(
        "odata/Orders(4711)/Items(1)",
        "odata/$metadata#Orders(4711)/Items"));

    /* PROTOCOL.10.4: Singleton */
    TEST(CheckURLContext(
        "odata/Contoso",
        "odata/$metadata#Contoso"));

    /* TODO: PROTOCOL.10.5: Collection of Dervived Entities */

    /* TODO: PROTOCOL.10.6: Dervived Entity */

    /* TODO: PROTOCOL.10.7: Collection of Projected Entities */

    /* TODO: PROTOCOL.10.8: Projected Entity */

    /* TODO: PROTOCOL.10.9: Collection of Projected Expaneded Entities */

    /* TODO: PROTOCOL.10.10: Projected Expanded Entity */

    /* PROTOCOL.10.11: Collection of Entity References */
    /* ATTN: eventual: "odata/$metadata#Collection($ref)" */
    TEST(CheckURLContext(
        "odata/Customers('ALFKI')/Orders/$ref",
        "odata/$metadata#"));

    /* PROTOCOL.10.12: Entity Reference */
    TEST(CheckURLContext(
        "odata/Orders(10643)/Customer/$ref",
        "odata/$metadata#"));

    /* PROTOCOL.10.13 Property Value */
    TEST(CheckURLContext(
        "odata/Customers(1)/Addresses",
        "odata/$metadata#Customers(1)/Addresses"));

    /* PROTOCOL.10.14 Collection of Complex or Primitive Types */
    /* ATTN: eventual: "odata/$metadata#Collection(Edm.String)" */
    TEST(CheckURLContext(
        "odata/TopFiveHobbies",
        "odata/$metadata#TopFiveHobbies"));

    /* PROTOCOL.10.15: Complex or Primitive Type */
    /* ATTN: eventual: "odata/$metadata#Edm.String" */
    TEST(CheckURLContext(
        "odata/MostPopularName",
        "odata/$metadata#MostPopularName"));

    /* PROTOCOL.10.16: Operation Result */
    /* ATTN: eventual: "odata/$metadata#Customers" */
    TEST(CheckURLContext(
        "odata/TopFiveCustomers",
        "odata/$metadata#TopFiveCustomers"));

    /* TODO: PROTOCOL.10.17: Delta Response */

    /* TODO: PROTOCOL.10.18: Item in a Delta Response */

    /* TODO: PROTOCOL.10.19: $all Response */

    /* TODO: PROTOCOL.10.20: $crossjoin Response */

    /* ATTN.A: fix this */
#if 0
    TEST(CheckURLContext(
        "odata/People/$count",
        "odata/$metadata#People/$count"));
#endif

    TEST(CheckURLContext(
        "odata/Orders/4711/Items",
        "odata/$metadata#Orders/4711/Items"));

#if 0
    TEST(CheckURLContext(
        "/service/Person/jsmith",
        "odata/$metadata#service/Person/jsmith"));
#endif

    /* Test odata/People/$count */
    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata/People/$count"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        PrintURI(uri);

        TEST(uri->queryOptions & OL_QUERY_OPTION_COUNT);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 0);

        /* People */
        TEST(strcmp(uri->segments.data[0].name, "People") == 0);
    }

    /* Test /odata/Products/$top=4 */
    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata/Products?$top=4"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->queryOptions & OL_QUERY_OPTION_TOP);
        TEST(uri->queryOptionTop == 4);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 0);

        /* Products */
        TEST(strcmp(uri->segments.data[0].name, "Products") == 0);
    }

    /* Test /odata/Products/$skip=1234 */
    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata/Products?$skip=1234"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->queryOptions & OL_QUERY_OPTION_SKIP);
        TEST(uri->queryOptionSkip == 1234);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 0);

        /* Products */
        TEST(strcmp(uri->segments.data[0].name, "Products") == 0);
    }

    /* Test /odata/Products/$skiptoken=1234 */
    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata/Products?$skiptoken=1234"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->queryOptions & OL_QUERY_OPTION_SKIPTOKEN);
        TEST(uri->queryOptionSkiptoken != NULL);
        TEST(strcmp(uri->queryOptionSkiptoken, "1234") == 0);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 0);

        /* Products */
        TEST(strcmp(uri->segments.data[0].name, "Products") == 0);
    }

    /* Test /odata/Products/$top=4&$skip=2 */
    {
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata/Products?$top=4&$skip=2"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        TEST(uri->queryOptions & OL_QUERY_OPTION_TOP);
        TEST(uri->queryOptions & OL_QUERY_OPTION_SKIP);
        TEST(uri->queryOptionTop == 4);
        TEST(uri->queryOptionSkip == 2);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 0);

        /* Products */
        TEST(strcmp(uri->segments.data[0].name, "Products") == 0);
    }

    /* Test odata/People(1)/Name/$value */
    {
        const URIKey* key;
        OL_Result r = URIParse(
            uri,
            strcpy(buf, "/odata/People(123456)/$value"),
            err, 
            sizeof(err));
        PrintURI(uri);

        TEST(r == OL_Result_Ok);
        PrintURI(uri);

        TEST(uri->queryOptions & OL_QUERY_OPTION_VALUE);
        TEST(uri->segments.size == 1);
        TEST(uri->segments.data[0].keysSize == 1);
        key = &uri->segments.data[0].keys[0];
        TEST(key->value.type == OL_Type_Int64);
        TEST(key->value.u.int64 == 123456);

        /* People */
        TEST(strcmp(uri->segments.data[0].name, "People") == 0);
    }

    OL_URI_Release(&uri->base);
}
ENDTEST(TestURIParse)

/*
**==============================================================================
**
** TestArray()
**
**==============================================================================
*/

static int _TestAppendBinaryElement(
    OL_Array* arr,
    void* data,
    size_t size)
{
    OL_Value v1 = OL_BinaryValue(data, size);
    OL_Value v2;
    size_t index = OL_Array_Count(arr);

    if (OL_Array_Append(arr, &v1) != OL_Result_Ok)
        return 0;

    if (OL_Array_Get(arr, index, &v2) != OL_Result_Ok)
        return 0;

    if (v1.type != OL_Type_Binary || v1.type != v2.type)
        return 0;

    if (v1.u.binary.size != size || v2.u.binary.size != size)
        return 0;

    if (memcmp(v1.u.binary.data, v2.u.binary.data, v1.u.binary.size) != 0)
        return 0;

#if 0
    printf("{%s}{%s}\n", (char*)v1.u.binary.data, (char*)v2.u.binary.data);
#endif

    return 1;
}

BEGINTEST(TestArray)
{
    OL_Array* arr = __OL_Array_New();
    TEST(arr);

    _TestAppendBinaryElement(arr, STRLIT("a"));
    _TestAppendBinaryElement(arr, STRLIT("ab"));
    _TestAppendBinaryElement(arr, STRLIT("abc"));
    _TestAppendBinaryElement(arr, STRLIT("abcd"));
    _TestAppendBinaryElement(arr, STRLIT("abcde"));
    _TestAppendBinaryElement(arr, STRLIT("abcdef"));
    _TestAppendBinaryElement(arr, STRLIT("abcdefg"));
    _TestAppendBinaryElement(arr, STRLIT("abcdefgh"));
    _TestAppendBinaryElement(arr, STRLIT("abcdefghi"));
    _TestAppendBinaryElement(arr, STRLIT("abcdefghij"));
    _TestAppendBinaryElement(arr, STRLIT("abcdefghijk"));

#if 0
    OL_Array_Print(arr);
#endif

    OL_Array_Release(arr);

}
ENDTEST(TestArray)

/*
**==============================================================================
**
** TestDateFormat()
**
**==============================================================================
*/

BEGINTEST(TestDateFormat)
{
    {
        char buf[128];
        OL_Date date = { UINT_MAX, UINT_MAX, UINT_MAX };
        FormatDate(buf, &date);
        TEST(strcmp(buf, "7295-95-95") == 0);
        TEST(strlen(buf) + 1 == DateBufSize);
    }
}
ENDTEST(TestDateFormat)

/*
**==============================================================================
**
** TestTimeOfDayFormat()
**
**==============================================================================
*/

BEGINTEST(TestTimeOfDayFormat)
{
    {
        char buf[128];
        OL_TimeOfDay x = { 7, 59, 59, 999 };
        FormatTimeOfDay(buf, &x);
        TEST(strcmp(buf, "07:59:59.999") == 0);
    }
    {
        char buf[128];
        OL_TimeOfDay tod = {UINT_MAX, UINT_MAX, UINT_MAX, 0xFFFFFFFFFFFFFFFFLL};
        FormatTimeOfDay(buf, &tod);
        TEST(strcmp(buf, "95:95:95.073709551615") == 0);
        TEST(strlen(buf) + 1 == TimeOfDayBufSize);
    }
}
ENDTEST(TestTimeOfDayFormat)

/*
**==============================================================================
**
** TestGuidFormat()
**
**==============================================================================
*/

BEGINTEST(TestGuidFormat)
{
    {
        char buf[37];
        OL_Guid guid = { 0xAAAAAAAA,0xBBBB,0xCCCC,0xDDDD,0xEEEE,0xEEEEEEEE };
        FormatGuid(buf, &guid);
        TEST(strcmp(buf, "AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE") == 0);
    }

    {
        char buf[37];
        OL_Guid guid = { 0xF890DE68,0x56A8,0x4A01,0x8B0F,0x757B,0xE945AD53 };
        FormatGuid(buf, &guid);
        TEST(strcmp(buf, "F890DE68-56A8-4A01-8B0F-757BE945AD53") == 0);
        TEST(strlen(buf) + 1 == GuidBufSize);
    }
}
ENDTEST(TestGuidFormat)

/*
**==============================================================================
**
** TestDurationFormat()
**
**==============================================================================
*/

BEGINTEST(TestDurationFormat)
{
    {
        char buf[128];
        OL_Duration x = { 1, 365, 24, 60, 60, 999 };
        FormatDuration(buf, &x);
        TEST(strcmp(buf, "-P365DT24H60M60.999S") == 0);
    }

    {
        char buf[128];
        OL_Duration x = { 1, UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 
            0xFFFFFFFFFFFFFFFFLL };
        FormatDuration(buf, &x);
        TEST(strcmp(buf,
            "-P4294967295DT4294967295H4294967295M4294967295.073709551615S")==0);
        TEST(strlen(buf) + 1 == DurationBufSize);
    }
}
ENDTEST(TestDurationFormat)

/*
**==============================================================================
**
** TestDateTimeOffsetFormat()
**
**==============================================================================
*/

BEGINTEST(TestDateTimeOffsetFormat)
{
#if 0
    size_t i;
    for (i = 0; i < 100000; i++)
#endif
    {
        char buf[128];
        OL_DateTimeOffset x = { 1960, 12, 31, 24, 60, 60, 999 };
        FormatDateTimeOffset(buf, &x);
        TEST(strcmp(buf, "1960-12-31T24:60:60.999Z") == 0);
    }
    {
        char buf[128];
        OL_DateTimeOffset x = { 1960, 12, 31, 24, 60, 60, 999 };
        FormatDateTimeOffset(buf, &x);
        TEST(strcmp(buf, "1960-12-31T24:60:60.999Z") == 0);
    }
    {
        char buf[128];
        OL_DateTimeOffset x = { UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX, 
            UINT_MAX, UINT_MAX, 0xFFFFFFFFFFFFFFFFLL };
        FormatDateTimeOffset(buf, &x);
        TEST(strcmp(buf, "7295-95-95T95:95:95.073709551615Z") == 0);
        TEST(strlen(buf) + 1 == DateTimeOffsetBufSize);
    }
}
ENDTEST(TestDateTimeOffsetFormat)

/*
**==============================================================================
**
* TestNulls()
**
**==============================================================================
*/

BEGINTEST(TestNulls)
{
    OL_Object* obj = __OL_Object_New();
    TEST(obj);
    OL_Result r;
    OL_Value v;
    unsigned int flags;

    r = OL_Object_AddString(obj, "FirstName", "Bob");
    TEST(r == OL_Result_Ok);

    r = OL_Object_AddString(obj, "LastName", "Smith");
    TEST(r == OL_Result_Ok);

    v.type = OL_Type_String;
    r = OL_Object_AddF(obj, "NullString", &v, OL_FLAG_NULL);
    TEST(r == OL_Result_Ok);

    memset(&v, 0, sizeof(v));
    flags = 0;
    r = OL_Object_GetF(obj, "NullString", &v, &flags);
    TEST(r == OL_Result_Ok);
    TEST(v.type == OL_Type_String);
    TEST(flags & OL_FLAG_NULL);

#if 0
    OL_Object_Print(obj);
#endif

    OL_Object_Release(obj);
}
ENDTEST(TestNulls)

/*
**==============================================================================
**
** TestQueryOptionToStr()
**
**==============================================================================
*/

BEGINTEST(TestQueryOptionToStr)
{
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_FILTER), "filter") == 0);
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_EXPAND), "expand") == 0);
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_SELECT), "select") == 0);
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_ORDERBY), "orderby") == 0);
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_TOP), "top") == 0);
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_SKIP), "skip") == 0);
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_COUNT), "count") == 0);
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_SEARCH), "search") == 0);
    TEST(strcmp(QueryOptionToStr(OL_QUERY_OPTION_FORMAT), "format") == 0);
    TEST(strcmp(QueryOptionToStr(0x80000000), "unknown") == 0);
}
ENDTEST(TestQueryOptionToStr)

/*
**==============================================================================
**
** TestCSDL()
**
**==============================================================================
*/

static const char CSDLEXPECT[] =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<edmx:Edmx xmlns:edmx=\"http://docs.oasis-open.org/odata/ns/edmx\" Version=\"4.0\">\n"
    "</edmx:Edmx>\n";

BEGINTEST(TestCSDL)
{
    Buf buf = BUF_INITIALIZER;
    EDMX_Edmx edmx;
    int r;

    memset(&edmx, 0, sizeof(edmx));

    r = CSDL_Serialize(&buf, &edmx);
    TEST(r == 0);

    TEST(strcmp(buf.data, CSDLEXPECT) == 0);

    BufDestroy(&buf);
}
ENDTEST(TestCSDL)

/*
**==============================================================================
**
** main()
**
**==============================================================================
*/

int main(int argc, char* argv[])
{
    arg0 = argv[0];
    TestJSON();
    TestJSONHelpers();
    TestServiceDoc();
    TestJSONSerialize();
    TestSizes();
    TestODATA();
    TestPerson();
    TestProviderEntry();
    TestURIExpandEscapes();
    TestURIParse();
    TestArray();
    TestDateFormat();
    TestGuidFormat();
    TestDurationFormat();
    TestDateTimeOffsetFormat();
    TestTimeOfDayFormat();
    TestNulls();
    TestQueryOptionToStr();
    TestCSDL();

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
