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
#ifndef _odatacxxinlines_h
#define _odatacxxinlines_h

/*
**==============================================================================
**
** URI
**
**==============================================================================
*/

inline URI::URI()
{
    _rep = __OL_URI_New();
    assert(_rep);
}

inline URI::URI(const URI& x)
{
    OL_URI_AddRef(_rep = x._rep);
}

inline URI::URI(OL_URI* array, bool addRef) : _rep(array)
{
    assert(array);

    if (addRef)
        OL_URI_AddRef(array);
}

inline URI::~URI()
{
    OL_URI_Release(_rep);
}

inline URI& URI::operator=(const URI& x)
{
    if (_rep != x._rep)
    {
        OL_URI_Release(_rep);
        OL_URI_AddRef(_rep = x._rep);
    }
    return *this;
}

inline URI URI::Clone() const
{
    return URI(OL_URI_Clone(_rep), false);
}

inline bool URI::Clear()
{
    return !OL_URI_Clear(_rep);
}

inline bool URI::SetFlags(unsigned int flags)
{
    return !OL_URI_SetFlags(_rep, flags);
}


/*
**==============================================================================
**
** Array
**
**==============================================================================
*/

inline Array::Array()
{
    _rep = __OL_Array_New();
    assert(_rep);
}

inline Array::Array(const Array& x)
{
    OL_Array_AddRef(_rep = x._rep);
}

inline Array::Array(OL_Array* array, bool addRef) : _rep(array)
{
    assert(array);

    if (addRef)
        OL_Array_AddRef(array);
}

inline Array::~Array()
{
    OL_Array_Release(_rep);
}

inline Array& Array::operator=(const Array& x)
{
    if (_rep != x._rep)
    {
        OL_Array_Release(_rep);
        OL_Array_AddRef(_rep = x._rep);
    }
    return *this;
}

inline Array Array::Clone() const
{
    return Array(OL_Array_Clone(_rep), false);
}

inline bool Array::Clear()
{
    return !OL_Array_Clear(_rep);
}

inline bool Array::SetFlags(unsigned int flags)
{
    return !OL_Array_SetFlags(_rep, flags);
}

inline size_t Array::Count() const
{
    return OL_Array_Count(_rep);
}

inline bool Array::Append(const Value& value)
{
    return !OL_Array_Append(_rep, &value);
}

inline bool Array::Set(size_t index, const Value& value) const
{
    return !OL_Array_Set(_rep, index, &value);
}

inline bool Array::Get(size_t index, Value& value) const
{
    return !OL_Array_Get(_rep, index, &value);
}

inline bool Array::Remove(size_t index)
{
    return !OL_Array_Remove(_rep, index);
}

inline bool Array::Print(size_t indent) const
{
    return !OL_Array_PrintIndent(_rep, indent);
}

inline bool Array::SetBoolean(size_t index, const Boolean& x)
{
    Value v;
    v.type = OL_Type_Boolean;
    v.u.boolean = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetInt64(size_t index, const Int64& x)
{
    Value v;
    v.type = OL_Type_Int64;
    v.u.int64 = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetDouble(size_t index, const Double& x)
{
    Value v;
    v.type = OL_Type_Double;
    v.u.double_ = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetString(size_t index, const Char* x)
{
    Value v;
    v.type = OL_Type_String;
    v.u.string = (Char*)x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetObject(size_t index, const Object& x)
{
    Value v;
    v.type = OL_Type_Object;
    v.u.object = x._rep;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetArray(size_t index, const Array& x)
{
    Value v;
    v.type = OL_Type_Array;
    v.u.array = x._rep;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetByte(size_t index, const Byte& x)
{
    Value v;
    v.type = OL_Type_Byte;
    v.u.byte = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetSByte(size_t index, const SByte& x)
{
    Value v;
    v.type = OL_Type_SByte;
    v.u.sByte = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetInt16(size_t index, const Int16& x)
{
    Value v;
    v.type = OL_Type_Int16;
    v.u.int16 = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetInt32(size_t index, const Int32& x)
{
    Value v;
    v.type = OL_Type_Int32;
    v.u.int32 = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetSingle(size_t index, const Single& x)
{
    Value v;
    v.type = OL_Type_Single;
    v.u.single = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetDecimal(size_t index, const Decimal& x)
{
    Value v;
    v.type = OL_Type_Decimal;
    v.u.decimal = x._rep;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetBinary(size_t index, const Binary& x)
{
    Value v;
    v.type = OL_Type_Binary;
    v.u.binary = x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetDate(size_t index, const Date& x)
{
    Value v;
    v.type = OL_Type_Date;
    v.u.date = x._rep;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetTimeOfDay(size_t index, const TimeOfDay& x)
{
    Value v;
    v.type = OL_Type_TimeOfDay;
    v.u.timeOfDay = x._rep;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetDateTimeOffset(size_t index, const DateTimeOffset& x)
{
    Value v;
    v.type = OL_Type_DateTimeOffset;
    v.u.dateTimeOffset = x._rep;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetDuration(size_t index, const Duration& x)
{
    Value v;
    v.type = OL_Type_Duration;
    v.u.duration = x._rep;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetGuid(size_t index, const Guid& x)
{
    Value v;
    v.type = OL_Type_Guid;
    v.u.guid = x._rep;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetNavigationLink(size_t index, const Char* x)
{
    Value v;
    v.type = OL_Type_NavigationLink;
    v.u.navigationLink = (Char*)x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::SetAssociationLink(size_t index, const Char* x)
{
    Value v;
    v.type = OL_Type_AssociationLink;
    v.u.associationLink = (Char*)x;
    return !OL_Array_Set(_rep, index, &v);
}

inline bool Array::AppendNull(Type type)
{
    Value v;
    memset(&v, 0, sizeof(v));
    v.type = OL_Type_Null;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendBoolean(const Boolean& x)
{
    Value v;
    v.type = OL_Type_Boolean;
    v.u.boolean = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendInt64(const Int64& x)
{
    Value v;
    v.type = OL_Type_Int64;
    v.u.int64 = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendDouble(const Double& x)
{
    Value v;
    v.type = OL_Type_Double;
    v.u.double_ = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendString(const Char* x)
{
    Value v;
    v.type = OL_Type_String;
    v.u.string = (Char*)x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendObject(const Object& x)
{
    Value v;
    v.type = OL_Type_Object;
    v.u.object = x._rep;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendArray(const Array& x)
{
    Value v;
    v.type = OL_Type_Array;
    v.u.array = x._rep;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendByte(const Byte& x)
{
    Value v;
    v.type = OL_Type_Byte;
    v.u.byte = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendSByte(const SByte& x)
{
    Value v;
    v.type = OL_Type_SByte;
    v.u.sByte = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendInt16(const Int16& x)
{
    Value v;
    v.type = OL_Type_Int16;
    v.u.int16 = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendInt32(const Int32& x)
{
    Value v;
    v.type = OL_Type_Int32;
    v.u.int32 = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendSingle(const Single& x)
{
    Value v;
    v.type = OL_Type_Single;
    v.u.single = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendDecimal(const Decimal& x)
{
    Value v;
    v.type = OL_Type_Decimal;
    v.u.decimal = x._rep;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendBinary(const Binary& x)
{
    Value v;
    v.type = OL_Type_Binary;
    v.u.binary = x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendDate(const Date& x)
{
    Value v;
    v.type = OL_Type_Date;
    v.u.date = x._rep;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendTimeOfDay(const TimeOfDay& x)
{
    Value v;
    v.type = OL_Type_TimeOfDay;
    v.u.timeOfDay = x._rep;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendDateTimeOffset(const DateTimeOffset& x)
{
    Value v;
    v.type = OL_Type_DateTimeOffset;
    v.u.dateTimeOffset = x._rep;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendDuration(const Duration& x)
{
    Value v;
    v.type = OL_Type_Duration;
    v.u.duration = x._rep;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendGuid(const Guid& x)
{
    Value v;
    v.type = OL_Type_Guid;
    v.u.guid = x._rep;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendNavigationLink(const Char* x)
{
    Value v;
    v.type = OL_Type_NavigationLink;
    v.u.navigationLink = (Char*)x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::AppendAssociationLink(const Char* x)
{
    Value v;
    v.type = OL_Type_AssociationLink;
    v.u.associationLink = (Char*)x;
    return !OL_Array_Append(_rep, &v);
}

inline bool Array::IsNull(size_t index) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok)
        return true;

    return false;
}

inline bool Array::GetBoolean(size_t index, Boolean& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Boolean);
    {
        x = v.u.boolean;
        return true;
    }

    return false;
}

inline bool Array::GetInt64(size_t index, Int64& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int64);
    {
        x = v.u.int64;
        return true;
    }

    return false;
}

inline bool Array::GetDouble(size_t index, Double& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Double);
    {
        x = v.u.double_;
        return true;
    }

    return false;
}

inline bool Array::GetString(size_t index, const Char*& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_String)
    {
        x = v.u.string;
        return true;
    }

    return false;
}

inline bool Array::GetObject(size_t index, Object& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Object)
    {
        OL_Object_Release(*((OL_Object**)&x));
        OL_Object_AddRef(x._rep = v.u.object);
        return true;
    }

    return false;
}

inline bool Array::GetArray(size_t index, Array& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Array)
    {
        OL_Array_Release(*((OL_Array**)&x));
        OL_Array_AddRef(x._rep = v.u.array);
        return true;
    }

    return false;
}

inline bool Array::GetByte(size_t index, Byte& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Byte)
    {
        x = v.u.byte;
        return true;
    }

    return false;
}

inline bool Array::GetSByte(size_t index, SByte& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_SByte)
    {
        x = v.u.sByte;
        return true;
    }

    return false;
}

inline bool Array::GetInt16(size_t index, Int16& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int16)
    {
        x = v.u.int16;
        return true;
    }

    return false;
}

inline bool Array::GetInt32(size_t index, Int32& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int32)
    {
        x = v.u.int32;
        return true;
    }

    return false;
}

inline bool Array::GetSingle(size_t index, Single& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Single)
    {
        x = v.u.single;
        return true;
    }

    return false;
}

inline bool Array::GetDecimal(size_t index, Decimal& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Decimal)
    {
        x._rep = v.u.decimal;
        return true;
    }

    return false;
}

inline bool Array::GetBinary(size_t index, Binary& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Binary)
    {
        x = v.u.binary;
        return true;
    }

    return false;
}

inline bool Array::GetDate(size_t index, Date& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Date)
    {
        x._rep = v.u.date;
        return true;
    }

    return false;
}

inline bool Array::GetTimeOfDay(size_t index, TimeOfDay& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_TimeOfDay)
    {
        x._rep = v.u.timeOfDay;
        return true;
    }

    return false;
}

inline bool Array::GetDateTimeOffset(size_t index, DateTimeOffset& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_DateTimeOffset)
    {
        x._rep = v.u.dateTimeOffset;
        return true;
    }

    return false;
}

inline bool Array::GetDuration(size_t index, Duration& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Duration)
    {
        x._rep = v.u.duration;
        return true;
    }

    return false;
}

inline bool Array::GetGuid(size_t index, Guid& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_Guid)
    {
        x._rep = v.u.guid;
        return true;
    }

    return false;
}

inline bool Array::GetNavigationLink(size_t index, const Char*& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_NavigationLink)
    {
        x = v.u.navigationLink;
        return true;
    }

    return false;
}

inline bool Array::GetAssociationLink(size_t index, const Char*& x) const
{
    Value v;

    if (OL_Array_Get(_rep, index, &v) == OL_Result_Ok && 
        v.type == OL_Type_AssociationLink)
    {
        x = v.u.associationLink;
        return true;
    }

    return false;
}

/*
**==============================================================================
**
** Object
**
**==============================================================================
*/

inline Object::Object()
{
    _rep = __OL_Object_New();
    assert(_rep);
}

inline Object::Object(const Object& x)
{
    OL_Object_AddRef(_rep = x._rep);
}

inline Object::Object(OL_Object* object, bool addRef) : _rep(object)
{
    assert(object);

    if (addRef)
        OL_Object_AddRef(object);
}

inline Object::~Object()
{
    OL_Object_Release(_rep);
}

inline Object& Object::operator=(const Object& x)
{
    if (_rep != x._rep)
    {
        OL_Object_Release(_rep);
        OL_Object_AddRef(_rep = x._rep);
    }
    return *this;
}

inline Object Object::Clone() const
{
    return Object(OL_Object_Clone(_rep), false);
}

inline bool Object::Clear()
{
    return !OL_Object_Clear(_rep);
}

inline bool Object::SetFlags(unsigned int flags)
{
    return !OL_Object_SetFlags(_rep, flags);
}

inline size_t Object::Count() const
{
    return OL_Object_Count(_rep);
}

inline bool Object::Add(
    const Char* name,
    const Value& value)
{
    return !OL_Object_Add(_rep, name, (const OL_Value*)&value);
}

inline bool Object::Set(
    const Char* name,
    const Value& value)
{
    return !OL_Object_Set(_rep, name, (const OL_Value*)&value);
}

inline bool Object::Get(
    const Char* name,
    Value& value)
{
    return !OL_Object_Get(_rep, name, (OL_Value*)&value);
}

inline bool Object::Remove(
    const Char* name)
{
    return !OL_Object_Remove(_rep, name, 0);
}

inline bool Object::SetAt(
    size_t index,
    const Value& value)
{
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&value);
}

inline bool Object::GetAt(
    size_t index,
    const Char*& name,
    Value& value)
{
    return !OL_Object_GetAt(_rep, index, &name, (OL_Value*)&value);
}

inline bool Object::RemoveAt(
    size_t index)
{
    return !OL_Object_RemoveAt(_rep, index, 0);
}

inline bool Object::Print(size_t indent) const
{
    return !OL_Object_PrintIndent(_rep, indent);
}

inline bool Object::AddBoolean(
    const Char* name,
    const Boolean& x)
{
    OL_Value v;
    v.type = OL_Type_Boolean;
    v.u.boolean = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddInt64(
    const Char* name,
    const Int64& x)
{
    OL_Value v;
    v.type = OL_Type_Int64;
    v.u.int64 = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddDouble(
    const Char* name,
    const Double& x)
{
    OL_Value v;
    v.type = OL_Type_Double;
    v.u.double_ = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddString(
    const Char* name,
    const Char* x)
{
    OL_Value v;
    v.type = OL_Type_String;
    v.u.string = (Char*)x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddObject(
    const Char* name,
    const Object& x)
{
    OL_Value v;
    v.type = OL_Type_Object;
    v.u.object = x._rep;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddArray(
    const Char* name,
    const Array& x)
{
    OL_Value v;
    v.type = OL_Type_Array;
    v.u.array = x._rep;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddByte(
    const Char* name,
    const Byte& x)
{
    OL_Value v;
    v.type = OL_Type_Byte;
    v.u.byte = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddSByte(
    const Char* name,
    const SByte& x)
{
    OL_Value v;
    v.type = OL_Type_SByte;
    v.u.sByte = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddInt16(
    const Char* name,
    const Int16& x)
{
    OL_Value v;
    v.type = OL_Type_Int16;
    v.u.int16 = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddInt32(
    const Char* name,
    const Int32& x)
{
    OL_Value v;
    v.type = OL_Type_Int32;
    v.u.int32 = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddSingle(
    const Char* name,
    const Single& x)
{
    OL_Value v;
    v.type = OL_Type_Single;
    v.u.single = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddDecimal(
    const Char* name,
    const Decimal& x)
{
    OL_Value v;
    v.type = OL_Type_Decimal;
    v.u.decimal = x._rep;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddBinary(
    const Char* name,
    const Binary& x)
{
    OL_Value v;
    v.type = OL_Type_Binary;
    v.u.binary = x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddDate(
    const Char* name,
    const Date& x)
{
    OL_Value v;
    v.type = OL_Type_Date;
    v.u.date = x._rep;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddTimeOfDay(
    const Char* name,
    const TimeOfDay& x)
{
    OL_Value v;
    v.type = OL_Type_TimeOfDay;
    v.u.timeOfDay = x._rep;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddDateTimeOffset(
    const Char* name,
    const DateTimeOffset& x)
{
    OL_Value v;
    v.type = OL_Type_DateTimeOffset;
    v.u.dateTimeOffset = x._rep;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddDuration(
    const Char* name,
    const Duration& x)
{
    OL_Value v;
    v.type = OL_Type_Duration;
    v.u.duration = x._rep;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddGuid(
    const Char* name,
    const Guid& x)
{
    OL_Value v;
    v.type = OL_Type_Guid;
    v.u.guid = x._rep;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddNavigationLink(
    const Char* name,
    const Char* x)
{
    OL_Value v;
    v.type = OL_Type_NavigationLink;
    v.u.navigationLink = (Char*)x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::AddAssociationLink(
    const Char* name,
    const Char* x)
{
    OL_Value v;
    v.type = OL_Type_AssociationLink;
    v.u.associationLink = (Char*)x;
    return !OL_Object_Add(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetBoolean(
    const Char* name,
    const Boolean& x)
{
    OL_Value v;
    v.type = OL_Type_Boolean;
    v.u.boolean = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetInt64(
    const Char* name,
    const Int64& x)
{
    OL_Value v;
    v.type = OL_Type_Int64;
    v.u.int64 = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetDouble(
    const Char* name,
    const Double& x)
{
    OL_Value v;
    v.type = OL_Type_Double;
    v.u.double_ = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetString(
    const Char* name,
    const Char* x)
{
    OL_Value v;
    v.type = OL_Type_String;
    v.u.string = (Char*)x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetObject(
    const Char* name,
    const Object& x)
{
    OL_Value v;
    v.type = OL_Type_Object;
    v.u.object = x._rep;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetArray(
    const Char* name,
    const Array& x)
{
    OL_Value v;
    v.type = OL_Type_Array;
    v.u.array = x._rep;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetByte(
    const Char* name,
    const Byte& x)
{
    OL_Value v;
    v.type = OL_Type_Byte;
    v.u.byte = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetSByte(
    const Char* name,
    const SByte& x)
{
    OL_Value v;
    v.type = OL_Type_SByte;
    v.u.sByte = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetInt16(
    const Char* name,
    const Int16& x)
{
    OL_Value v;
    v.type = OL_Type_Int16;
    v.u.int16 = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetInt32(
    const Char* name,
    const Int32& x)
{
    OL_Value v;
    v.type = OL_Type_Int32;
    v.u.int32 = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetSingle(
    const Char* name,
    const Single& x)
{
    OL_Value v;
    v.type = OL_Type_Single;
    v.u.single = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetDecimal(
    const Char* name,
    const Decimal& x)
{
    OL_Value v;
    v.type = OL_Type_Decimal;
    v.u.decimal = x._rep;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetBinary(
    const Char* name,
    const Binary& x)
{
    OL_Value v;
    v.type = OL_Type_Binary;
    v.u.binary = x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetDate(
    const Char* name,
    const Date& x)
{
    OL_Value v;
    v.type = OL_Type_Date;
    v.u.date = x._rep;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetTimeOfDay(
    const Char* name,
    const TimeOfDay& x)
{
    OL_Value v;
    v.type = OL_Type_TimeOfDay;
    v.u.timeOfDay = x._rep;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetDateTimeOffset(
    const Char* name,
    const DateTimeOffset& x)
{
    OL_Value v;
    v.type = OL_Type_DateTimeOffset;
    v.u.dateTimeOffset = x._rep;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetDuration(
    const Char* name,
    const Duration& x)
{
    OL_Value v;
    v.type = OL_Type_Duration;
    v.u.duration = x._rep;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetGuid(
    const Char* name,
    const Guid& x)
{
    OL_Value v;
    v.type = OL_Type_Guid;
    v.u.guid = x._rep;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetNavigationLink(
    const Char* name,
    const Char* x)
{
    OL_Value v;
    v.type = OL_Type_NavigationLink;
    v.u.navigationLink = (Char*)x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::SetAssociationLink(
    const Char* name,
    const Char* x)
{
    OL_Value v;
    v.type = OL_Type_AssociationLink;
    v.u.associationLink = (Char*)x;
    return !OL_Object_Set(_rep, name, (const OL_Value*)&v);
}

inline bool Object::GetBoolean(const Char* name, Boolean& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Boolean)
    {
        x = v.u.boolean;
        return true;
    }

    return false;
}

inline bool Object::GetInt64(const Char* name, Int64& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int64)
    {
        x = v.u.int64;
        return true;
    }

    return false;
}

inline bool Object::GetDouble(const Char* name, Double& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Double)
    {
        x = v.u.double_;
        return true;
    }

    return false;
}

inline bool Object::GetString(const Char* name, const Char*& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_String)
    {
        x = v.u.string;
        return true;
    }

    return false;
}

inline bool Object::GetObject(const Char* name, Object& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Object)
    {
        OL_Object_Release(*((OL_Object**)&x));
        OL_Object_AddRef(x._rep = v.u.object);
        return true;
    }

    return false;
}

inline bool Object::GetArray(const Char* name, Array& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Array)
    {
        OL_Array_Release(*((OL_Array**)&x));
        OL_Array_AddRef(x._rep = v.u.array);
        return true;
    }

    return false;
}

inline bool Object::GetByte(const Char* name, Byte& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Byte)
    {
        x = v.u.byte;
        return true;
    }

    return false;
}

inline bool Object::GetSByte(const Char* name, SByte& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_SByte)
    {
        x = v.u.sByte;
        return true;
    }

    return false;
}

inline bool Object::GetInt16(const Char* name, Int16& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int16)
    {
        x = v.u.int16;
        return true;
    }

    return false;
}

inline bool Object::GetInt32(const Char* name, Int32& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int32)
    {
        x = v.u.int32;
        return true;
    }

    return false;
}

inline bool Object::GetSingle(const Char* name, Single& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Single)
    {
        x = v.u.single;
        return true;
    }

    return false;
}

inline bool Object::GetDecimal(const Char* name, Decimal& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Decimal)
    {
        x._rep = v.u.decimal;
        return true;
    }

    return false;
}

inline bool Object::GetBinary(const Char* name, Binary& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Binary)
    {
        x = v.u.binary;
        return true;
    }

    return false;
}

inline bool Object::GetDate(const Char* name, Date& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Date)
    {
        x._rep = v.u.date;
        return true;
    }

    return false;
}

inline bool Object::GetTimeOfDay(const Char* name, TimeOfDay& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_TimeOfDay)
    {
        x._rep = v.u.timeOfDay;
        return true;
    }

    return false;
}

inline bool Object::GetDateTimeOffset(const Char* name, DateTimeOffset& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_DateTimeOffset)
    {
        x._rep = v.u.dateTimeOffset;
        return true;
    }

    return false;
}

inline bool Object::GetDuration(const Char* name, Duration& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Duration)
    {
        x._rep = v.u.duration;
        return true;
    }

    return false;
}

inline bool Object::GetGuid(const Char* name, Guid& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Guid)
    {
        x._rep = v.u.guid;
        return true;
    }

    return false;
}

inline bool Object::GetNavigationLink(const Char* name, NavigationLink& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_NavigationLink)
    {
        x = v.u.navigationLink;
        return true;
    }

    return false;
}

inline bool Object::GetAssociationLink(
    const Char* name, 
    const Char*& x) const
{
    Value v;

    if (OL_Object_Get(_rep, name, &v) == OL_Result_Ok && 
        v.type == OL_Type_AssociationLink)
    {
        x = v.u.associationLink;
        return true;
    }

    return false;
}

inline bool Object::SetAtBoolean(
    size_t index,
    const Boolean& x)
{
    OL_Value v;
    v.type = OL_Type_Boolean;
    v.u.boolean = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtInt64(
    size_t index,
    const Int64& x)
{
    OL_Value v;
    v.type = OL_Type_Int64;
    v.u.int64 = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtDouble(
    size_t index,
    const Double& x)
{
    OL_Value v;
    v.type = OL_Type_Double;
    v.u.double_ = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtString(
    size_t index,
    const String& x)
{
    OL_Value v;
    v.type = OL_Type_String;
    v.u.string = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtObject(
    size_t index,
    const Object& x)
{
    OL_Value v;
    v.type = OL_Type_Object;
    v.u.object = x._rep;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtArray(
    size_t index,
    const Array& x)
{
    OL_Value v;
    v.type = OL_Type_Array;
    v.u.array = x._rep;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtByte(
    size_t index,
    const Byte& x)
{
    OL_Value v;
    v.type = OL_Type_Byte;
    v.u.byte = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtSByte(
    size_t index,
    const SByte& x)
{
    OL_Value v;
    v.type = OL_Type_SByte;
    v.u.sByte = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtInt16(
    size_t index,
    const Int16& x)
{
    OL_Value v;
    v.type = OL_Type_Int16;
    v.u.int16 = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtInt32(
    size_t index,
    const Int32& x)
{
    OL_Value v;
    v.type = OL_Type_Int32;
    v.u.int32 = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtSingle(
    size_t index,
    const Single& x)
{
    OL_Value v;
    v.type = OL_Type_Single;
    v.u.single = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtDecimal(
    size_t index,
    const Decimal& x)
{
    OL_Value v;
    v.type = OL_Type_Decimal;
    v.u.decimal = x._rep;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtBinary(
    size_t index,
    const Binary& x)
{
    OL_Value v;
    v.type = OL_Type_Binary;
    v.u.binary = x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtDate(
    size_t index,
    const Date& x)
{
    OL_Value v;
    v.type = OL_Type_Date;
    v.u.date = x._rep;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtTimeOfDay(
    size_t index,
    const TimeOfDay& x)
{
    OL_Value v;
    v.type = OL_Type_TimeOfDay;
    v.u.timeOfDay = x._rep;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtDateTimeOffset(
    size_t index,
    const DateTimeOffset& x)
{
    OL_Value v;
    v.type = OL_Type_DateTimeOffset;
    v.u.dateTimeOffset = x._rep;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtDuration(
    size_t index,
    const Duration& x)
{
    OL_Value v;
    v.type = OL_Type_Duration;
    v.u.duration = x._rep;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtGuid(
    size_t index,
    const Guid& x)
{
    OL_Value v;
    v.type = OL_Type_Guid;
    v.u.guid = x._rep;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtNavigationLink(
    size_t index,
    const Char* x)
{
    OL_Value v;
    v.type = OL_Type_NavigationLink;
    v.u.navigationLink = (Char*)x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::SetAtAssociationLink(
    size_t index,
    const Char* x)
{
    OL_Value v;
    v.type = OL_Type_AssociationLink;
    v.u.associationLink = (Char*)x;
    return !OL_Object_SetAt(_rep, index, (const OL_Value*)&v);
}

inline bool Object::GetAtBoolean(
    size_t index,
    const Char*& name,
    Boolean& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Boolean)
    {
        x = v.u.boolean;
        return true;
    }

    return false;
}

inline bool Object::GetAtInt64(
    size_t index,
    const Char*& name,
    Int64& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int64)
    {
        x = v.u.int64;
        return true;
    }

    return false;
}

inline bool Object::GetAtDouble(
    size_t index,
    const Char*& name,
    Double& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Double)
    {
        x = v.u.double_;
        return true;
    }

    return false;
}

inline bool Object::GetAtString(
    size_t index,
    const Char*& name,
    const Char*& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_String)
    {
        x = v.u.string;
        return true;
    }

    return false;
}

inline bool Object::GetAtObject(
    size_t index,
    const Char*& name,
    Object& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Object)
    {
        OL_Object_AddRef(x._rep = v.u.object);
        return true;
    }

    return false;
}

inline bool Object::GetAtArray(
    size_t index,
    const Char*& name,
    Array& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Array)
    {
        OL_Array_AddRef(x._rep = v.u.array);
        return true;
    }

    return false;
}

inline bool Object::GetAtByte(
    size_t index,
    const Char*& name,
    Byte& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Byte)
    {
        x = v.u.byte;
        return true;
    }

    return false;
}

inline bool Object::GetAtSByte(
    size_t index,
    const Char*& name,
    SByte& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_SByte)
    {
        x = v.u.sByte;
        return true;
    }

    return false;
}

inline bool Object::GetAtInt16(size_t index, const Char*& name, Int16& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int16)
    {
        x = v.u.int16;
        return true;
    }

    return false;
}

inline bool Object::GetAtInt32(
    size_t index,
    const Char*& name,
    Int32& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Int32)
    {
        x = v.u.int32;
        return true;
    }

    return false;
}

inline bool Object::GetAtSingle(
    size_t index,
    const Char*& name,
    Single& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Single)
    {
        x = v.u.single;
        return true;
    }

    return false;
}

inline bool Object::GetAtDecimal(
    size_t index,
    const Char*& name,
    Decimal& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Decimal)
    {
        x._rep = v.u.decimal;
        return true;
    }

    return false;
}

inline bool Object::GetAtBinary(
    size_t index,
    const Char*& name,
    Binary& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Binary)
    {
        x = v.u.binary;
        return true;
    }

    return false;
}

inline bool Object::GetAtDate(
    size_t index,
    const Char*& name,
    Date& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Date)
    {
        x._rep = v.u.date;
        return true;
    }

    return false;
}

inline bool Object::GetAtTimeOfDay(
    size_t index,
    const Char*& name,
    TimeOfDay& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_TimeOfDay)
    {
        x._rep = v.u.timeOfDay;
        return true;
    }

    return false;
}

inline bool Object::GetAtDateTimeOffset(
    size_t index,
    const Char*& name,
    DateTimeOffset& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_DateTimeOffset)
    {
        x._rep = v.u.dateTimeOffset;
        return true;
    }

    return false;
}

inline bool Object::GetAtDuration(
    size_t index,
    const Char*& name,
    Duration& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Duration)
    {
        x._rep = v.u.duration;
        return true;
    }

    return false;
}

inline bool Object::GetAtGuid(
    size_t index,
    const Char*& name,
    Guid& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_Guid)
    {
        x._rep = v.u.guid;
        return true;
    }

    return false;
}

inline bool Object::GetAtNavigationLink(
    size_t index,
    const Char*& name,
    NavigationLink& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_NavigationLink)
    {
        x = v.u.navigationLink;
        return true;
    }

    return false;
}

inline bool Object::GetAtAssociationLink(
    size_t index,
    const Char*& name,
    const Char*& x) const
{
    Value v;

    if (OL_Object_GetAt(_rep, index, &name, &v) == OL_Result_Ok && 
        v.type == OL_Type_AssociationLink)
    {
        x = v.u.associationLink;
        return true;
    }

    return false;
}

/*
**==============================================================================
**
** Scope
**
**==============================================================================
*/

inline Scope::Scope()
{
    _rep = __OL_Scope_New();
    assert(_rep);
}

inline Scope::Scope(const Scope& x)
{
    OL_Scope_AddRef(_rep = x._rep);
}

inline Scope::Scope(OL_Scope* scope, bool addRef) : _rep(scope)
{
    assert(scope);

    if (addRef)
        OL_Scope_AddRef(_rep);
}

inline Scope::~Scope()
{
    OL_Scope_Release(_rep);
}

inline Scope& Scope::operator=(const Scope& x)
{
    if (_rep != x._rep)
    {
        OL_Scope_Release(_rep);
        OL_Scope_AddRef(_rep = x._rep);
    }
    return *this;
}

inline bool Scope::Clear()
{
    return !OL_Scope_Clear(_rep);
}

inline bool Scope::Reset()
{
    return !OL_Scope_Reset(_rep);
}

#endif /* _odatacxxinlines_h */
