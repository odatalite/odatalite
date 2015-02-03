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
#ifndef _odatacxx_h
#define _odatacxx_h

#if 0 && !defined(OL_CHECK_FOR_NULL_SELF)
# define OL_CHECK_FOR_NULL_SELF
#endif

#include "odata.h"
#include <cassert>

/*
**==============================================================================
**
** OL_NAMESPACE_BEGIN
** OL_NAMESPACE_END
**
**==============================================================================
*/

#define OL_NAMESPACE_BEGIN namespace odata {
#define OL_NAMESPACE_END }

/*
**==============================================================================
**
** OL_NAMESPACE_BEGIN
**
**==============================================================================
*/

OL_NAMESPACE_BEGIN

/*
**==============================================================================
**
** OL_Type
**
**==============================================================================
*/

typedef OL_Type Type;

/*
**==============================================================================
**
** Value
**
**==============================================================================
*/

typedef OL_Value Value;

/*
**==============================================================================
**
** OL_Result
**
**==============================================================================
*/

typedef OL_Result Result;

/*
**==============================================================================
**
** Boolean
**
**==============================================================================
*/

typedef bool Boolean;

/*
**==============================================================================
**
** Int64
**
**==============================================================================
*/

typedef OL_Int64 Int64;

/*
**==============================================================================
**
** Double
**
**==============================================================================
*/

typedef OL_Double Double;

/*
**==============================================================================
**
** String
**
**==============================================================================
*/

typedef OL_Char Char;

typedef OL_String String;

/*
**==============================================================================
**
** Byte
**
**==============================================================================
*/

typedef OL_Byte Byte;

/*
**==============================================================================
**
** SByte
**
**==============================================================================
*/

typedef OL_SByte SByte;

/*
**==============================================================================
**
** Int16
**
**==============================================================================
*/

typedef OL_Int16 Int16;

/*
**==============================================================================
**
** Int32
**
**==============================================================================
*/

typedef OL_Int32 Int32;

/*
**==============================================================================
**
** Single
**
**==============================================================================
*/

typedef OL_Single Single;

/*
**==============================================================================
**
** Decimal
**
**==============================================================================
*/

class Decimal
{
public:

    Decimal()
    {
        _rep.integral = 0;
        _rep.fractional = 0;
    }

    explicit Decimal(const OL_Decimal& x)
    {
        _rep = x;
    }

    Decimal(
        signed long long integral, 
        signed long long fractional) 
    {
        _rep.integral = integral;
        _rep.fractional = fractional;
    }

    signed long long GetIntegral() const
    {
        return _rep.integral;
    }

    signed long long GetFractional() const
    {
        return _rep.fractional;
    }

private:
    friend class Object;
    friend class Array;
    OL_Decimal _rep;
};

/*
**==============================================================================
**
** Binary
**
**==============================================================================
*/

typedef OL_Binary Binary;

/*
**==============================================================================
**
** Date
**
**==============================================================================
*/

class Date
{
public:

    Date()
    {
        memset(&_rep, 0, sizeof(_rep));
    }

    explicit Date(const OL_Date& x)
    {
        _rep = x;
    }

    Date(
        unsigned int year,
        unsigned int month,
        unsigned int day)
    {
        _rep.year = year;
        _rep.month = month;
        _rep.day = day;
    }

    unsigned int GetYear() const
    {
        return _rep.year;
    }

    unsigned int GetMonth() const
    {
        return _rep.month;
    }

    unsigned int GetDay() const
    {
        return _rep.day;
    }

private:
    friend class Object;
    friend class Array;
    OL_Date _rep;
};

/*
**==============================================================================
**
** TimeOfDay
**
**==============================================================================
*/

class TimeOfDay
{
public:

    TimeOfDay()
    {
        memset(&_rep, 0, sizeof(_rep));
    }

    explicit TimeOfDay(const OL_TimeOfDay& x)
    {
        _rep = x;
    }

    TimeOfDay(
        unsigned int hour,
        unsigned int minute,
        unsigned int second,
        unsigned long long fractionalSecond)
    {
        _rep.hour = hour;
        _rep.minute = minute;
        _rep.second = second;
        _rep.fractionalSecond = fractionalSecond;
    }

    unsigned int GetYear() const
    {
        return _rep.hour;
    }

    unsigned int GetMonth() const
    {
        return _rep.minute;
    }

    unsigned int GetDay() const
    {
        return _rep.second;
    }

    unsigned long long GetMsec() const
    {
        return _rep.fractionalSecond;
    }

private:
    friend class Object;
    friend class Array;
    OL_TimeOfDay _rep;
};

/*
**==============================================================================
**
** DateTimeOffset
**
**==============================================================================
*/

class DateTimeOffset
{
public:

    DateTimeOffset()
    {
        memset(&_rep, 0, sizeof(_rep));
    }

    explicit DateTimeOffset(const OL_DateTimeOffset& x)
    {
        _rep = x;
    }

    DateTimeOffset(
        unsigned int year,
        unsigned int month,
        unsigned int day,
        unsigned int hour,
        unsigned int minute,
        unsigned int second,
        unsigned long long fractionalSecond)
    {
        _rep.year = year;
        _rep.month = month;
        _rep.day = day;
        _rep.hour = hour;
        _rep.minute = minute;
        _rep.second = second;
        _rep.fractionalSecond = fractionalSecond;
    }

    unsigned int GetYear() const
    {
        return _rep.year;
    }

    unsigned int GetMonth() const
    {
        return _rep.month;
    }

    unsigned int GetDay() const
    {
        return _rep.day;
    }

    unsigned int GetHour() const
    {
        return _rep.hour;
    }

    unsigned int GetMinute() const
    {
        return _rep.minute;
    }

    unsigned int GetSecond() const
    {
        return _rep.second;
    }

    unsigned long long GetMsec() const
    {
        return _rep.fractionalSecond;
    }

private:
    friend class Object;
    friend class Array;
    OL_DateTimeOffset _rep;
};

/*
**==============================================================================
**
** Duration
**
**==============================================================================
*/

class Duration
{
public:

    Duration()
    {
        memset(&_rep, 0, sizeof(_rep));
    }

    explicit Duration(const OL_Duration& x)
    {
        _rep = x;
    }

    Duration(
        bool negative,
        unsigned int days,
        unsigned int hour,
        unsigned int minute,
        unsigned int second,
        unsigned long long fractionalSecond)
    {
        _rep.negative = negative;
        _rep.days = days;
        _rep.hour = hour;
        _rep.minute = minute;
        _rep.second = second;
        _rep.fractionalSecond = fractionalSecond;
    }

    bool GetNegative() const
    {
        return _rep.negative;
    }

    unsigned int GetDays() const
    {
        return _rep.days;
    }

    unsigned int GetHour() const
    {
        return _rep.hour;
    }

    unsigned int GetMinute() const
    {
        return _rep.minute;
    }

    unsigned long long GetMsec() const
    {
        return _rep.fractionalSecond;
    }

private:
    friend class Object;
    friend class Array;
    OL_Duration _rep;
};

/*
**==============================================================================
**
** Guid
**
**==============================================================================
*/

class Guid
{
public:

    Guid()
    {
        memset(&_rep, 0, sizeof(_rep));
    }

    explicit Guid(const OL_Guid& x)
    {
        _rep = x;
    }

    /* AAAAAAAA-BBBB-CCCC-DDDD-EEEEEEEEEEEE */
    Guid(
        unsigned int data1, /* AAAAAAAA */
        unsigned short data2, /* BBBB */
        unsigned short data3, /* CCCC */
        unsigned short data4, /* DDDD */
        unsigned short data5, /* EEEE */
        unsigned int data6) /* EEEEEEEE */
    {
        _rep.data1 = data1;
        _rep.data2 = data2;
        _rep.data3 = data3;
        _rep.data4 = data4;
        _rep.data5 = data5;
        _rep.data6 = data6;
    }

    unsigned int GetData1()
    {
        return _rep.data1;
    }

    unsigned short GetData2()
    {
        return _rep.data2;
    }

    unsigned short GetData3()
    {
        return _rep.data3;
    }

    unsigned short GetData4()
    {
        return _rep.data4;
    }

    unsigned short GetData5()
    {
        return _rep.data5;
    }

    unsigned int GetData6()
    {
        return _rep.data6;
    }

private:
    friend class Object;
    friend class Array;
    OL_Guid _rep;
};

/*
**==============================================================================
**
** NavigationLink
**
**==============================================================================
*/

typedef OL_NavigationLink NavigationLink;

/*
**==============================================================================
**
** AssociationLink
**
**==============================================================================
*/

typedef OL_AssociationLink AssociationLink;

/*
**==============================================================================
**
** Array
**
**==============================================================================
*/

class Object;

class Array
{
public:

    Array(const Array& x);

    ~Array();

    Array& operator=(const Array& x);

    Array Clone() const;

    bool Clear();

    bool SetFlags(unsigned int flags);

    size_t Count() const;

    bool Append(const Value& value);

    bool Set(
        size_t index,
        const Value& value) const;

    bool Get(
        size_t index,
        Value& value) const;

    bool Remove(
        size_t index);

    bool Print(
        size_t indent = 0) const;

    bool SetBoolean(
        size_t index,
        const Boolean& x);

    bool SetInt64(
        size_t index,
        const Int64& x);

    bool SetDouble(
        size_t index,
        const Double& x);

    bool SetString(
        size_t index,
        const Char* x);

    bool SetObject(
        size_t index,
        const Object& x);

    bool SetArray(
        size_t index,
        const Array& x);

    bool SetByte(
        size_t index,
        const Byte& x);

    bool SetSByte(
        size_t index,
        const SByte& x);

    bool SetInt16(
        size_t index,
        const Int16& x);

    bool SetInt32(
        size_t index,
        const Int32& x);

    bool SetSingle(
        size_t index,
        const Single& x);

    bool SetDecimal(
        size_t index,
        const Decimal& x);

    bool SetBinary(
        size_t index,
        const Binary& x);

    bool SetDate(
        size_t index,
        const Date& x);

    bool SetTimeOfDay(
        size_t index,
        const TimeOfDay& x);

    bool SetDateTimeOffset(
        size_t index,
        const DateTimeOffset& x);

    bool SetDuration(
        size_t index,
        const Duration& x);

    bool SetGuid(
        size_t index,
        const Guid& x);

    bool SetNavigationLink(
        size_t index,
        const Char* x);

    bool SetAssociationLink(
        size_t index,
        const Char* x);

    bool AppendNull(
        Type type);

    bool AppendBoolean(
        const Boolean& x);

    bool AppendInt64(
        const Int64& x);

    bool AppendDouble(
        const Double& x);

    bool AppendString(
        const Char* x);

    bool AppendObject(
        const Object& x);

    bool AppendArray(
        const Array& x);

    bool AppendByte(
        const Byte& x);

    bool AppendSByte(
        const SByte& x);

    bool AppendInt16(
        const Int16& x);

    bool AppendInt32(
        const Int32& x);

    bool AppendSingle(
        const Single& x);

    bool AppendDecimal(
        const Decimal& x);

    bool AppendBinary(
        const Binary& x);

    bool AppendDate(
        const Date& x);

    bool AppendTimeOfDay(
        const TimeOfDay& x);

    bool AppendDateTimeOffset(
        const DateTimeOffset& x);

    bool AppendDuration(
        const Duration& x);

    bool AppendGuid(
        const Guid& x);

    bool AppendNavigationLink(
        const Char* x);

    bool AppendAssociationLink(
        const Char* x);

    bool IsNull(
        size_t index) const;

    bool GetBoolean(
        size_t index,
        Boolean& x) const;

    bool GetInt64(
        size_t index,
        Int64& x) const;

    bool GetDouble(
        size_t index,
        Double& x) const;

    bool GetString(
        size_t index,
        const Char*& x) const;

    bool GetObject(
        size_t index,
        Object& x) const;

    bool GetArray(
        size_t index,
        Array& x) const;

    bool GetByte(
        size_t index,
        Byte& x) const;

    bool GetSByte(
        size_t index,
        SByte& x) const;

    bool GetInt16(
        size_t index,
        Int16& x) const;

    bool GetInt32(
        size_t index,
        Int32& x) const;

    bool GetSingle(
        size_t index,
        Single& x) const;

    bool GetDecimal(
        size_t index,
        Decimal& x) const;

    bool GetBinary(
        size_t index,
        Binary& x) const;

    bool GetDate(
        size_t index,
        Date& x) const;

    bool GetTimeOfDay(
        size_t index,
        TimeOfDay& x) const;

    bool GetDateTimeOffset(
        size_t index,
        DateTimeOffset& x) const;

    bool GetDuration(
        size_t index,
        Duration& x) const;

    bool GetGuid(
        size_t index,
        Guid& x) const;

    bool GetNavigationLink(
        size_t index,
        const Char*& x) const;

    bool GetAssociationLink(
        size_t index,
        const Char*& x) const;

private:
    Array(); /* Use Scope::NewArray() */
    explicit Array(OL_Array* array, bool addRef);
    friend class Object;
    friend class Scope;
    OL_Array* _rep;
};

/*
**==============================================================================
**
** Object
**
**==============================================================================
*/

class Object
{
public:

    Object(const Object& x);

    ~Object();

    Object& operator=(const Object& x);

    Object Clone() const;;

    bool Clear();

    bool SetFlags(unsigned int flags);

    size_t Count() const;

    bool Add(
        const Char* name,
        const Value& value);

    bool Set(
        const Char* name,
        const Value& value);

    bool Get(
        const Char* name,
        Value& value);

    bool Remove(
        const Char* name);

    bool SetAt(
        size_t index,
        const Value& value);

    bool GetAt(
        size_t index,
        const Char*& name,
        Value& value);

    bool RemoveAt(
        size_t index);

    bool Print(size_t indent = 0) const;

    bool AddBoolean(
        const Char* name,
        const Boolean& x);

    bool AddInt64(
        const Char* name,
        const Int64& x);

    bool AddDouble(
        const Char* name,
        const Double& x);

    bool AddString(
        const Char* name,
        const Char* x);

    bool AddObject(
        const Char* name,
        const Object& x);

    bool AddArray(
        const Char* name,
        const Array& x);

    bool AddByte(
        const Char* name,
        const Byte& x);

    bool AddSByte(
        const Char* name,
        const SByte& x);

    bool AddInt16(
        const Char* name,
        const Int16& x);

    bool AddInt32(
        const Char* name,
        const Int32& x);

    bool AddSingle(
        const Char* name,
        const Single& x);

    bool AddDecimal(
        const Char* name,
        const Decimal& x);

    bool AddBinary(
        const Char* name,
        const Binary& x);

    bool AddDate(
        const Char* name,
        const Date& x);

    bool AddTimeOfDay(
        const Char* name,
        const TimeOfDay& x);

    bool AddDateTimeOffset(
        const Char* name,
        const DateTimeOffset& x);

    bool AddDuration(
        const Char* name,
        const Duration& x);

    bool AddGuid(
        const Char* name,
        const Guid& x);

    bool AddNavigationLink(
        const Char* name,
        const Char* x);

    bool AddAssociationLink(
        const Char* name,
        const Char* x);

    bool SetBoolean(
        const Char* name,
        const Boolean& x);

    bool SetInt64(
        const Char* name,
        const Int64& x);

    bool SetDouble(
        const Char* name,
        const Double& x);

    bool SetString(
        const Char* name,
        const Char* x);

    bool SetObject(
        const Char* name,
        const Object& x);

    bool SetArray(
        const Char* name,
        const Array& x);

    bool SetByte(
        const Char* name,
        const Byte& x);

    bool SetSByte(
        const Char* name,
        const SByte& x);

    bool SetInt16(
        const Char* name,
        const Int16& x);

    bool SetInt32(
        const Char* name,
        const Int32& x);

    bool SetSingle(
        const Char* name,
        const Single& x);

    bool SetDecimal(
        const Char* name,
        const Decimal& x);

    bool SetBinary(
        const Char* name,
        const Binary& x);

    bool SetDate(
        const Char* name,
        const Date& x);

    bool SetTimeOfDay(
        const Char* name,
        const TimeOfDay& x);

    bool SetDateTimeOffset(
        const Char* name,
        const DateTimeOffset& x);

    bool SetDuration(
        const Char* name,
        const Duration& x);

    bool SetGuid(
        const Char* name,
        const Guid& x);

    bool SetNavigationLink(
        const Char* name,
        const Char* x);

    bool SetAssociationLink(
        const Char* name,
        const Char* x);

    bool GetBoolean(
        const Char* name,
        Boolean& x) const;

    bool GetInt64(
        const Char* name,
        Int64& x) const;

    bool GetDouble(
        const Char* name,
        Double& x) const;

    bool GetString(
        const Char* name,
        const Char*& x) const;

    bool GetObject(
        const Char* name,
        Object& x) const;

    bool GetArray(
        const Char* name,
        Array& x) const;

    bool GetByte(
        const Char* name,
        Byte& x) const;

    bool GetSByte(
        const Char* name,
        SByte& x) const;

    bool GetInt16(
        const Char* name,
        Int16& x) const;

    bool GetInt32(
        const Char* name,
        Int32& x) const;

    bool GetSingle(
        const Char* name,
        Single& x) const;

    bool GetDecimal(
        const Char* name,
        Decimal& x) const;

    bool GetBinary(
        const Char* name,
        Binary& x) const;

    bool GetDate(
        const Char* name,
        Date& x) const;

    bool GetTimeOfDay(
        const Char* name,
        TimeOfDay& x) const;

    bool GetDateTimeOffset(
        const Char* name,
        DateTimeOffset& x) const;

    bool GetDuration(
        const Char* name,
        Duration& x) const;

    bool GetGuid(
        const Char* name,
        Guid& x) const;

    bool GetNavigationLink(
        const Char* name,
        Char*& x) const;

    bool GetAssociationLink(
        const Char* name,
        const Char*& x) const;

    bool SetAtBoolean(
        size_t index,
        const Boolean& x);

    bool SetAtInt64(
        size_t index,
        const Int64& x);

    bool SetAtDouble(
        size_t index,
        const Double& x);

    bool SetAtString(
        size_t index,
        const String& x);

    bool SetAtObject(
        size_t index,
        const Object& x);

    bool SetAtArray(
        size_t index,
        const Array& x);

    bool SetAtByte(
        size_t index,
        const Byte& x);

    bool SetAtSByte(
        size_t index,
        const SByte& x);

    bool SetAtInt16(
        size_t index,
        const Int16& x);

    bool SetAtInt32(
        size_t index,
        const Int32& x);

    bool SetAtSingle(
        size_t index,
        const Single& x);

    bool SetAtDecimal(
        size_t index,
        const Decimal& x);

    bool SetAtBinary(
        size_t index,
        const Binary& x);

    bool SetAtDate(
        size_t index,
        const Date& x);

    bool SetAtTimeOfDay(
        size_t index,
        const TimeOfDay& x);

    bool SetAtDateTimeOffset(
        size_t index,
        const DateTimeOffset& x);

    bool SetAtDuration(
        size_t index,
        const Duration& x);

    bool SetAtGuid(
        size_t index,
        const Guid& x);

    bool SetAtNavigationLink(
        size_t index,
        const Char* x);

    bool SetAtAssociationLink(
        size_t index,
        const Char* x);

    bool GetAtBoolean(
        size_t index,
        const Char*& name, 
        Boolean& x) const;

    bool GetAtInt64(
        size_t index,
        const Char*& name, 
        Int64& x) const;

    bool GetAtDouble(
        size_t index,
        const Char*& name, 
        Double& x) const;

    bool GetAtString(
        size_t index,
        const Char*& name, 
        const Char*& x) const;

    bool GetAtObject(
        size_t index,
        const Char*& name, 
        Object& x) const;

    bool GetAtArray(
        size_t index,
        const Char*& name, 
        Array& x) const;

    bool GetAtByte(
        size_t index,
        const Char*& name, 
        Byte& x) const;

    bool GetAtSByte(
        size_t index,
        const Char*& name, 
        SByte& x) const;

    bool GetAtInt16(
        size_t index,
        const Char*& name, 
        Int16& x) const;

    bool GetAtInt32(
        size_t index,
        const Char*& name, 
        Int32& x) const;

    bool GetAtSingle(
        size_t index,
        const Char*& name, 
        Single& x) const;

    bool GetAtDecimal(
        size_t index,
        const Char*& name, 
        Decimal& x) const;

    bool GetAtBinary(
        size_t index,
        const Char*& name, 
        Binary& x) const;

    bool GetAtDate(
        size_t index,
        const Char*& name, 
        Date& x) const;

    bool GetAtTimeOfDay(
        size_t index,
        const Char*& name, 
        TimeOfDay& x) const;

    bool GetAtDateTimeOffset(
        size_t index,
        const Char*& name, 
        DateTimeOffset& x) const;

    bool GetAtDuration(
        size_t index,
        const Char*& name, 
        Duration& x) const;

    bool GetAtGuid(
        size_t index,
        const Char*& name, 
        Guid& x) const;

    bool GetAtNavigationLink(
        size_t index,
        const Char*& name, 
        Char*& x) const;

    bool GetAtAssociationLink(
        size_t index,
        const Char*& name, 
        const Char*& x) const;

private:
    Object(); /* Use Scope::NewObject() */
    explicit Object(OL_Object* object, bool addRef);
    friend class Array;
    friend class Scope;
    friend class Provider;
    OL_Object* _rep;
};

/*
**==============================================================================
**
** URI
**
**==============================================================================
*/

class URI
{
public:

    URI(const URI& x);

    ~URI();

    URI& operator=(const URI& x);

    URI Clone() const;

    bool Clear();

    bool SetFlags(unsigned int flags);

    size_t Count() const
    {
        return OL_URI_Count(_rep);
    }

    size_t KeyCount(size_t index) const
    {
        return OL_URI_KeyCount(_rep, index);
    }

    const char* GetName(
        size_t index) const
    {
        return OL_URI_GetName(_rep, index);
    }

    bool GetKey(
        size_t index,
        const Char* name,
        OL_Value& value) const
    {
        return !OL_URI_GetKey(_rep, index, name, &value);
    }

    bool GetKeyString(
        size_t index,
        const Char* name,
        const Char*& x) const
    {
        OL_Value v;

        if (OL_URI_GetKey(_rep, index, name, &v) ||
            v.type != OL_Type_String)
        {
            return false;
        }

        x = v.u.string;
        return true;
    }

    bool GetKeyInt64(
        size_t index,
        const Char* name,
        Int64& x) const
    {
        OL_Value v;

        if (OL_URI_GetKey(_rep, index, name, &v) ||
            v.type != OL_Type_Int64)
        {
            return false;
        }

        x = v.u.int64;
        return true;
    }

    bool GetKeyBoolean(
        size_t index,
        const Char* name,
        Boolean& x) const
    {
        OL_Value v;

        if (OL_URI_GetKey(_rep, index, name, &v) ||
            v.type != OL_Type_Boolean)
        {
            return false;
        }

        x = v.u.boolean;
        return true;
    }

    bool GetKeyAt(
        size_t index,
        size_t offset,
        const Char*& name,
        OL_Value& value) const
    {
        return !OL_URI_GetKeyAt(_rep, index, offset, &name, &value);
    }

    bool Parse(
        char* uri,
        char* error,
        size_t errorSize)
    {
        return !OL_URI_Parse(_rep, uri, error, errorSize);
    }

    bool Format(char* buf, size_t size)
    {
        return !OL_URI_Format(_rep, buf, size);
    }

    unsigned int GetQueryOptionFlags() const
    {
        return OL_URI_GetQueryOptionFlags(_rep);
    }

    unsigned int GetQueryOption(
        unsigned int option,
        void* value,
        size_t valueSize) const
    {
        return !OL_URI_GetQueryOption(_rep, option, value, valueSize);
    }

    bool Print(size_t indent = 0) const
    {
        return !OL_URI_Print(_rep);
    }

private:
    URI();
    explicit URI(OL_URI* uri, bool addRef);
    friend class Provider;
    friend class Scope;
    OL_URI* _rep;
};

/*
**==============================================================================
**
** Scope
**
**==============================================================================
*/

class Scope
{
public:

    Scope();

    Scope(const Scope& x);

    explicit Scope(OL_Scope* object, bool addRef);

    ~Scope();

    Scope& operator=(const Scope& x);

    bool Clear();

    bool Reset();

    URI NewURI()
    {
        return URI(OL_Scope_NewURI(_rep), false);
    }

    Array NewArray()
    {
        return Array(OL_Scope_NewArray(_rep), false);
    }

    Object NewObject()
    {
        return Object(OL_Scope_NewObject(_rep), false);
    }

    bool SendBeginEntitySet()
    {
        return !OL_Scope_SendBeginEntitySet(_rep);
    }

    bool SendEntity(const Object& object)
    {
        return !OL_Scope_SendEntity(_rep, object._rep);
    }

    bool SendEndEntitySet()
    {
        return !OL_Scope_SendEndEntitySet(_rep);
    }

    bool SendResult(
        Result result)
    {
        return !OL_Scope_SendResult(_rep, result);
    }

    OL_PRINTF_FORMAT(3, 4)
    bool SendResult(
        Result result,
        const char* format,
        ...)
    {
        va_list ap;
        va_start(ap, format);
        OL_Result r = OL_Scope_SendResultV(_rep, result, format, ap);
        va_end(ap);
        return !r;
    }

    void SetProviderData(
        void* ptr,
        void (*destructor)(void* ptr))
    {
        OL_Scope_SetProviderData(_rep, ptr, destructor);
    }

    void* GetProviderData()
    {
        return OL_Scope_GetProviderData(_rep);
    }

    bool GetOption(
        int option,
        void* value,
        size_t valueSize)
    {
        return !OL_Scope_GetOption(_rep, option, value, valueSize);
    }

private:
    OL_Scope* _rep;
};

/*
**==============================================================================
**
** Provider
**
**==============================================================================
*/

class Provider
{
private:

    virtual void _Load(
        OL_Scope* scope)
    {
        Scope c(scope, true);
        Load(c);
    }

    virtual void _Unload(
        OL_Scope* scope)
    {
        Scope c(scope, true);
        Unload(c);
    }

    virtual void _Get(
        OL_Scope* scope,
        const OL_URI* uri)
    {
        Scope c(scope, true);
        URI u((OL_URI*)uri, true);
        Get(c, u);
    }

    virtual void _Post(
        OL_Scope* scope,
        const OL_URI* uri,
        const OL_Object* object)
    {
        Scope c(scope, true);
        URI u((OL_URI*)uri, true);
        Object o((OL_Object*)object, true);
        Post(c, u, o);
    }

    virtual void _Patch(
        OL_Scope* scope,
        const OL_URI* uri,
        const OL_Object* object)
    {
        Scope c(scope, true);
        URI u((OL_URI*)uri, true);
        Object o((OL_Object*)object, true);
        Put(c, u, o);
    }

    virtual void _Put(
        OL_Scope* scope,
        const OL_URI* uri,
        const OL_Object* object)
    {
        Scope c(scope, true);
        URI u((OL_URI*)uri, true);
        Object o((OL_Object*)object, true);
        Put(c, u, o);
    }

    virtual void _Delete(
        OL_Scope* scope,
        const OL_URI* uri)
    {
        Scope c(scope, true);
        URI u((OL_URI*)uri, true);
        Delete(c, u);
    }

    virtual void _Pull(
        OL_Scope* scope)
    {
        Scope c(scope, true);
        Pull(c);
    }

public:

    virtual void Load(
        Scope& scope)
    {
        scope.SendResult(OL_Result_NotSupported);
    }

    virtual void Unload(
        Scope& scope)
    {
    }

    virtual void Get( 
        Scope& scope, 
        const URI& uri)
    {
        scope.SendResult(OL_Result_NotSupported);
    }

    virtual void Post(
        Scope& scope,
        const URI& uri,
        const Object& object)
    {
        scope.SendResult(OL_Result_NotSupported);
    }

    virtual void Put(
        Scope& scope,
        const URI& uri,
        const Object& object)
    {
        scope.SendResult(OL_Result_NotSupported);
    }

    virtual void Patch(
        Scope& scope,
        const URI& uri,
        const Object& object)
    {
        scope.SendResult(OL_Result_NotSupported);
    }

    virtual void Delete(
        Scope& scope,
        const URI& uri)
    {
        scope.SendResult(OL_Result_NotSupported);
    }

    virtual void Pull(
        Scope& scope)
    {
        /* Unreachable */
    }
};

/*
**==============================================================================
**
** Inline functions
**
**==============================================================================
*/

#include "odatacxxinlines.h"

/*
**==============================================================================
**
** OL_NAMESPACE_END
**
**==============================================================================
*/

OL_NAMESPACE_END

#endif /* _odatacxx_h */
