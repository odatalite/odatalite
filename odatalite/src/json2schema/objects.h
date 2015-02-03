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
#ifndef _objects_h
#define _objects_h

#include <vector>
#include <string>
#include <odata/jsonparser.h>

/*
**==============================================================================
**
** JSON
**
**==============================================================================
*/

struct JSONSchema;

struct JSONElement
{
    virtual void Print(size_t depth) const = 0;
};

class StringTable
{
public:

    void Put(const std::string& str);

    size_t GetSize() { return _rep.size(); }

    const std::string& GetString(size_t i) const { return _rep[i].first; }

    size_t GetCount(size_t i) const { return _rep[i].second; }

private:
    typedef std::pair<std::string, size_t> Pair;
    typedef std::vector<Pair> Rep;
    Rep _rep;
};

struct JSONProperty : public JSONElement
{
    JSONProperty() : 
        TypeClass("Primitive"),
        IsArray(false),
        Nullable(false)
    {
    }
    std::string Name;
    std::string Type;
    std::string TypeClass;
    bool IsArray;
    bool Nullable;

    virtual void Print(size_t depth) const;

    void GenerateSchema(
        const JSONSchema& schema, 
        const std::string& prefix) const;
};

struct JSONEnumType : public JSONElement
{
    JSONEnumType() : IsInteger(false) { }
    std::string Name;
    bool IsInteger;
    std::vector<std::string> Values;

    virtual void Print(size_t depth) const;

    void GenerateSchema(
        const JSONSchema& schema, 
        const std::string& prefix) const;
};

struct JSONNavigationProperty : public JSONElement
{
    std::string Name;
    std::string Type;
    bool IsArray;

    virtual void Print(size_t depth) const;
};

struct JSONComplexType : public JSONElement
{
    JSONComplexType() : OpenType(false) { }
    std::string Name;
    bool OpenType;
    std::vector<JSONProperty*> Properties;

    virtual void Print(size_t depth) const;

    void GenerateSchema(
        const JSONSchema& schema, 
        const std::string& prefix) const;
};

struct JSONEntityType : public JSONElement
{
    JSONEntityType() : OpenType(false) { }
    std::string Name;
    std::string BaseType;
    bool OpenType;
    std::vector<JSONProperty*> Properties;

    virtual void Print(size_t depth) const;

    void GenerateSchema(
        const JSONSchema& schema, 
        const std::string& prefix) const;
};

struct JSONSchema
{
    ~JSONSchema();

    size_t FindEnumType(const std::string& name) const;

    size_t FindComplexType(const std::string& name) const;

    size_t FindEntityType(const std::string& name) const;
    void Print(size_t n) const;

    bool ParseJSONFile(const std::string& path);

    void GenerateSchema(const std::string& prefix) const;

    /* (string, count) */
    StringTable stringTable;

    std::vector<JSONEntityType*> EntityTypes;
    std::vector<JSONEnumType*> EnumTypes;
    std::vector<JSONComplexType*> ComplexTypes;
};

/*
**==============================================================================
**
** class Element
**
**==============================================================================
*/

/* object, array, value */
class Element
{
public:
    virtual ~Element();

    virtual void Print(size_t depth) const = 0;
};

/*
**==============================================================================
**
** class Value
**
**==============================================================================
*/

class Value : public Element
{
public:

    Value(JSON_Type type_, const JSON_Union& value_)
    {
        type = type_;
        value = value_;
    }

    virtual ~Value();

    virtual void Print(size_t depth) const;

    JSON_Type type;
    JSON_Union value;
};

/*
**==============================================================================
**
** class Aggregate
**
**==============================================================================
*/

class Aggregate : public Element
{
public:
    virtual ~Aggregate();

    virtual void Add(const std::string& name, Element* element) = 0;

    virtual void Print(size_t depth) const = 0;
};

/*
**==============================================================================
**
** class Array
**
**==============================================================================
*/

class Array : public Aggregate
{
public:
    virtual ~Array();
    std::vector<Element*> elements;

    virtual void Add(const std::string& name, Element* element)
    {
        elements.push_back(element);
    }

    virtual void Print(size_t depth) const;
};

/*
**==============================================================================
**
** class Pair
**
**==============================================================================
*/

class Object;

class Pair
{
public:

    Pair(const std::string& name_, Element* element_)
        : name(name_), element(element_)
    {
    }

    std::string name;
    Element* element;

    bool GetBoolean(bool& x) const;

    bool GetInteger(signed long long& x) const;

    bool GetReal(double& x) const;

    bool GetString(std::string& x) const;

    bool GetStringArray(std::vector<std::string>& x) const;

    bool GetIntegerArray(std::vector<std::string>& x) const;

    bool GetObject(const Object*& x) const;

    bool GetArray(const Array*& x) const;
};

/*
**==============================================================================
**
** class Object
**
**==============================================================================
*/

class Object : public Aggregate
{
public:

    Object() : _releaseOnDestruct(0)
    {
    }

    virtual ~Object();

    std::vector<Pair> pairs;


    virtual void Add(const std::string& name, Element* element)
    {
        pairs.push_back(Pair(name, element));
    }

    virtual void Print(size_t depth) const;

    bool CreateSchema(JSONSchema& schema) const;

    void ReleaseOnDestruct(void* ptr)
    {
        _releaseOnDestruct = ptr;
    }

private:
    void* _releaseOnDestruct;
};

#endif /* _objects_h */
