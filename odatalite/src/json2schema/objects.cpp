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
#include <stdio.h>
#include <stdlib.h>
#include <base/iprintf.h>
#include <base/file.h>
#include <odata/jsonparser.h>
#include <odata/return.h>
#include <odata/json.h>
#include <odata/types.h>
#include "objects.h"

#undef RETURN
#define RETURN(COND) return COND

using namespace std;

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

static void _PrintString(const char* str)
{
    printf("\"");

    while (*str)
    {
        char c = *str++;

        switch (c)
        {
            case '"':
                printf("\\\"");
                break;
            case '\\':
                printf("\\\\");
                break;
            case '\b':
                printf("\\b");
                break;
            case '\f':
                printf("\\f");
                break;
            case '\n':
                printf("\\n");
                break;
            case '\r':
                printf("\\r");
                break;
            case '\t':
                printf("\\t");
                break;
            default:
            {
                if (isprint(c))
                    printf("%c", c);
                else
                    printf("\\u%04X", c);
            }
        }
    }

    printf("\"");
}

static void _PrintValue(JSON_Type type, const JSON_Union* value)
{
    switch (type)
    {
        case JSON_Type_Null:
            printf("null");
            break;
        case JSON_Type_Boolean:
            printf("%s", value->boolean ? "true" : "false");
            break;
        case JSON_Type_Integer:
            printf("%lld", value->integer);
            break;
        case JSON_Type_Real:
            printf("%E", value->real);
            break;
        case JSON_Type_String:
#if 1
            _PrintString(value->string);
#else
            printf("\"%s\"", value->string);
            (void)_PrintString;
#endif
            break;
        default:
            break;
    }
}

static void _Indent(size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("  ");
}

/*
**==============================================================================
**
** JSON
**
**==============================================================================
*/

static void PrintCommentBox(const string& comment)
{
    printf("/*\n");

    for (size_t i = 0; i < 80; i++)
        putchar('*');

    printf("**\n");
    printf("** %s\n", comment.c_str());
    printf("**\n");

    for (size_t i = 0; i < 80; i++)
        putchar('*');

    printf("*/\n");
    printf("\n");
}

static string MakeIdent(const string& str)
{
    string r;

    for (size_t i = 0; i < str.size(); i++)
    {
        char c = str[i];

        if (!isalnum(c) && c != '_')
            r += '_';
        else
            r += c;
    }

    return r;
}

void JSONProperty::Print(size_t n) const
{
    Iprintf(n, "JSONProperty\n");
    Iprintf(n, "{\n");
    n++;

    Iprintf(n, "Name{%s}\n", Name.c_str());
    Iprintf(n, "Type{%s}\n", Type.c_str());
    Iprintf(n, "TypeClass{%s}\n", TypeClass.c_str());
    Iprintf(n, "IsArray{%u}\n", IsArray);
    Iprintf(n, "Nullable{%u}\n", Nullable);

    n--;
    Iprintf(n, "}\n");
}

void JSONProperty::GenerateSchema(
    const JSONSchema& schema,
    const std::string& prefix) const
{
    string var = "_" + prefix + "_" + Name + "_property";

    // JSON_Property.flags:
    unsigned char flags = 0;
    {
        if (TypeClass == "Primitive")
            flags |= JSON_PROPERTY_FLAG_PRIMITIVETYPE;
        else if (TypeClass == "ComplexType")
            flags |= JSON_PROPERTY_FLAG_COMPLEXTYPE;
        else if (TypeClass == "EnumType")
            flags |= JSON_PROPERTY_FLAG_ENUMTYPE;
        else if (TypeClass == "EntityType")
            flags |= JSON_PROPERTY_FLAG_ENTITYTYPE;
        else
        {
            fprintf(stderr, "%s(%u): unknown TypeClass: %s\n", 
                __FILE__, __LINE__, TypeClass.c_str());
            exit(1);
        }

        if (IsArray)
            flags |= JSON_PROPERTY_FLAG_ARRAY;

        if (Nullable)
            flags |= JSON_PROPERTY_FLAG_NULLABLE;
    }

    // JSON_Property.type:
    JSON_Type type;
    unsigned short index = 0;
    {
        if (TypeClass == "Primitive")
        {
            if (Type == "string")
                type = JSON_Type_String;
            else if (Type == "integer")
                type = JSON_Type_Integer;
            else if (Type == "number")
                type = JSON_Type_Integer;
            else if (Type == "boolean")
                type = JSON_Type_Boolean;
            else
            {
                fprintf(stderr, "%s(%u): unknown Type: %s.%s: %s\n", 
                    __FILE__, __LINE__, prefix.c_str(), Name.c_str(),
                    Type.c_str());
                exit(1);
            }
        }
        else if (TypeClass == "ComplexType")
        {
            type = JSON_Type_Object;

            if (Type == "object")
            {
                /* This value represents untyped 'object' */
                index = 0xFFFF;
            }
            else
            {
                size_t n = schema.FindComplexType(Type);

                if (n == (size_t)-1)
                {
                    fprintf(stderr, "%s(%u): unknown ComplexType: %s\n", 
                        __FILE__, __LINE__, Type.c_str());
                    exit(1);
                }

                if (n > 255)
                {
                    fprintf(stderr, "%s(%u): too many ComplexType: %s\n", 
                        __FILE__, __LINE__, Type.c_str());
                    exit(1);
                }

                index = (unsigned short)n;
            }
        }
        else if (TypeClass == "EntityType")
        {
            type = JSON_Type_Object;

            if (Type == "object")
            {
                /* This value represents untyped 'object' */
                index = 0xFFFF;
            }
            else
            {
                size_t n = schema.FindEntityType(Type);

                if (n == (size_t)-1)
                {
                    fprintf(stderr, "%s(%u): unknown EntityType: %s\n", 
                        __FILE__, __LINE__, Type.c_str());
                    exit(1);
                }

                if (n > 255)
                {
                    fprintf(stderr, "%s(%u): too many EntityType: %s\n", 
                        __FILE__, __LINE__, Type.c_str());
                    exit(1);
                }

                index = (unsigned short)n;
            }
        }
        else if (TypeClass == "EnumType")
        {
            size_t n = schema.FindEnumType(Type);

            type = JSON_Type_Integer;

            if (n == (size_t)-1)
            {
                fprintf(stderr, "%s(%u): unknown EnumType: %s\n", 
                    __FILE__, __LINE__, Type.c_str());
                exit(1);
            }

            if (n > 255)
            {
                fprintf(stderr, "%s(%u): too many EnumType: %s\n", 
                    __FILE__, __LINE__, Type.c_str());
                exit(1);
            }

            index = (unsigned short)n;
        }
        else
        {
            fprintf(stderr, "%s(%u): unknown TypeClass: %s\n", 
                __FILE__, __LINE__, TypeClass.c_str());
            exit(1);
        }
    }

    printf("static const JSON_Property _%s_%s_property =\n",
        prefix.c_str(), Name.c_str());
    printf("{\n");
    printf("  %u, /* flags */\n", flags);
    printf("  JSON_Type_%s, /* type */\n", TypeNameOf(type));
    printf("  %u, /* index */\n", index);
    printf("  \"\\\%03o%s\" /* name */\n", (int)Name.size(), Name.c_str());
    printf("};\n");
    printf("\n");
}

void JSONEnumType::Print(size_t n) const
{
    Iprintf(n, "JSONEnumType\n");
    Iprintf(n, "{\n");
    n++;

    Iprintf(n, "Name{%s}\n", Name.c_str());

    for (size_t i = 0; i < Values.size(); i++)
        Iprintf(n, "Value{%s}\n", Values[i].c_str());

    n--;
    Iprintf(n, "}\n");
}

void JSONEnumType::GenerateSchema(
    const JSONSchema& schema,
    const std::string& prefix_) const
{
    string prefix = "_" + prefix_ + "_" + MakeIdent(Name);
    PrintCommentBox(prefix + "_enumType");

    // JSON_Property.members:

    for (size_t i = 0; i < Values.size(); i++)
    {
        string tag = MakeIdent(Values[i]);
        JSON_Integer val = (JSON_Integer)i;

        if (IsInteger)
        {
            char* end;
            unsigned long x = (unsigned long)strtoul(tag.c_str(), &end, 10);

            if (!end || *end != '\0')
                assert(0);

            val = (JSON_Integer)x;

            tag = "T" + tag;
        }

        /*
            struct _EDM_Member
            {
                const char* name;
                JSON_Integer value;
            };
        */

        printf("static const JSON_Member %s_%s_member =\n", 
            prefix.c_str(), tag.c_str());
        printf("{\n");
        printf("  \"\\%03o%s\", /* name */\n", (int)tag.size(), tag.c_str());
        printf("  %llu, /* value */\n", val);
        printf("};\n");
        printf("\n");
    }

    printf("static const JSON_Member* %s_members[] =\n", prefix.c_str());
    printf("{\n");

    for (size_t i = 0; i < Values.size(); i++)
    {
        string tag = MakeIdent(Values[i]);

        if (IsInteger)
            tag = "T" + tag;

        printf("  &%s_%s_member,\n", prefix.c_str(), tag.c_str());
    }

    printf("};\n");
    printf("\n");

    /*
        struct _EDM_EnumType
        {
            unsigned char flags;
            unsigned char underlyingType;
            unsigned char membersSize;
            const JSON_Member* members;
        };
    */

    printf("static const JSON_EnumType %s_enumType =\n", prefix.c_str());
    printf("{\n");
    printf("  %u, /* flags */\n", 0);
    printf("  JSON_Type_Integer, /* underlyingType */\n");
    printf("  ODATA_ARRAYSIZE(%s_members), /* membersSize */\n",prefix.c_str());
    printf("  \"\\%03o%s\", /* name */\n", (int)Name.size(), Name.c_str());
    printf("  %s_members /* members */\n", prefix.c_str());
    printf("};\n");
    printf("\n");
}

void JSONNavigationProperty::Print(size_t n) const
{
    Iprintf(n, "JSONNavigationProperty\n");
    Iprintf(n, "{\n");
    n++;

    Iprintf(n, "Name{%s}\n", Name.c_str());
    Iprintf(n, "Type{%s}\n", Type.c_str());

    n--;
    Iprintf(n, "}\n");
}

void JSONComplexType::Print(size_t n) const
{
    Iprintf(n, "JSONComplexType\n");
    Iprintf(n, "{\n");
    n++;

    Iprintf(n, "Name{%s}\n", Name.c_str());
    Iprintf(n, "OpenType{%u}\n", OpenType);

    /* Properties */
    {
        Iprintf(n, "Properties\n");
        Iprintf(n, "{\n");
        n++;

        for (size_t i = 0; i < Properties.size(); i++)
        {
            Properties[i]->Print(n);
        }

        n--;
        Iprintf(n, "}\n");
    }

    n--;
    Iprintf(n, "}\n");
}

void JSONComplexType::GenerateSchema(
    const JSONSchema& schema,
    const std::string& prefix_) const
{
    string prefix = prefix_ + "_" + MakeIdent(Name);
    PrintCommentBox(prefix + "_complexType");

    if (Properties.size())
    {
        // Properties
        for (size_t i = 0; i < Properties.size(); i++)
        {
            Properties[i]->GenerateSchema(schema, prefix);
        }

        printf("static const JSON_Property* _%s_properties[] =\n", 
            prefix.c_str());
        printf("{\n");

        // Properties array:
        for (size_t i = 0; i < Properties.size(); i++)
        {
            const JSONProperty* prop = Properties[i];
            string tmp = 
                "_" + prefix + "_" + prop->Name + "_property";
            printf("  (const JSON_Property*)&%s,\n", tmp.c_str());
        }

        printf("};\n");

        printf("\n");
    }

    /*
        struct _EDM_ComplexType
        {
            unsigned char flags;
            const char* name;
            const JSON_Property** properties;
            size_t propertiesSize;
        };
    */
    {
        printf("static const JSON_ComplexType _%s_complexType =\n", 
            prefix.c_str());
        printf("{\n");

        // JSON_ComplexType.flags:
        if (OpenType)
            printf("  0, /* flags */\n");
        else
            printf("  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */\n");

        // JSON_ComplexType.name:
        printf("  \"%s\", /* name */\n", Name.c_str());

        // JSON_ComplexType.properties:
        // JSON_ComplexType.propertiesSize:
        if (Properties.size())
        {
            printf("  _%s_properties, /* properties */\n", prefix.c_str());
            printf("  ODATA_ARRAYSIZE(_%s_properties), /* propertiesSize */\n", 
                prefix.c_str());
        }
        else
        {
            printf("  NULL, /* properties */\n");
            printf("  0, /* propertiesSize */\n");
        }

        printf("};\n");
        printf("\n");
    }
}

void StringTable::Put(const std::string& str)
{
    for (size_t i = 0; i < _rep.size(); i++)
    {
        if (_rep[i].first == str)
        {
            _rep[i].second++;
            return;
        }
    }

    _rep.push_back(Pair(str, 1));
}

void JSONEntityType::Print(size_t n) const
{
    Iprintf(n, "JSONEntityType\n");
    Iprintf(n, "{\n");
    n++;

    Iprintf(n, "Name{%s}\n", Name.c_str());
    Iprintf(n, "BaseType{%s}\n", BaseType.c_str());
    Iprintf(n, "OpenType{%u}\n", OpenType);

    /* Properties */
    {
        Iprintf(n, "Properties\n");
        Iprintf(n, "{\n");
        n++;

        for (size_t i = 0; i < Properties.size(); i++)
        {
            Properties[i]->Print(n);
        }

        n--;
        Iprintf(n, "}\n");
    }

    n--;
    Iprintf(n, "}\n");
}

void JSONEntityType::GenerateSchema(
    const JSONSchema& schema,
    const std::string& prefix_) const
{
    string prefix = prefix_ + "_" + MakeIdent(Name);
    PrintCommentBox(prefix + "_entityType");

    if (Properties.size())
    {
        // Properties
        for (size_t i = 0; i < Properties.size(); i++)
        {
            Properties[i]->GenerateSchema(schema, prefix);
        }

        printf("static const JSON_Property* _%s_properties[] =\n", 
            prefix.c_str());
        printf("{\n");

        // Properties array:
        for (size_t i = 0; i < Properties.size(); i++)
        {
            const JSONProperty* prop = Properties[i];
            string tmp = 
                "_" + prefix + "_" + prop->Name + "_property";
            printf("  (const JSON_Property*)&%s,\n", tmp.c_str());
        }

        printf("};\n");

        printf("\n");
    }

    /*
        struct _EDM_EntityType
        {
            unsigned char flags;
            const char* name;
            const char* baseType;

            JSON_Property* properties;
            size_t propertiesSize;

            JSON_EnumType* enumTypes;
            size_t enumTypesSize;

            JSON_ComplexType* complexTypes;
            size_t complexTypesSize;
        };
    */
    {
        printf("static const JSON_EntityType _%s_entityType =\n", 
            prefix.c_str());
        printf("{\n");

        // JSON_EntityType.flags:
        if (OpenType)
            printf("  0, /* flags */\n");
        else
            printf("  JSON_ENTITYTYPE_FLAG_OPENTYPE, /* flags */\n");

        // JSON_EntityType.name:
        printf("  \"%s\", /* name */\n", Name.c_str());

        // JSON_EntityType.baseType:
        if (BaseType.size())
            printf("  \"%s\", /* baseType */\n", BaseType.c_str());
        else
            printf("  NULL, /* baseType */\n");

        // JSON_EntityType.properties:
        // JSON_EntityType.propertiesSize:
        if (Properties.size())
        {
            printf("  _%s_properties, /* properties */\n", prefix.c_str());
            printf("  ODATA_ARRAYSIZE(_%s_properties), /* propertiesSize */\n", 
                prefix.c_str());
        }
        else
        {
            printf("  NULL, /* properties */\n");
            printf("  0, /* propertiesSize */\n");
        }

        printf("};\n");
        printf("\n");
    }
}

JSONSchema::~JSONSchema()
{
    for (size_t i = 0; i < EntityTypes.size(); i++)
    {
        delete EntityTypes[i];
    }

    for (size_t i = 0; i < EnumTypes.size(); i++)
    {
        delete EnumTypes[i];
    }

    for (size_t i = 0; i < ComplexTypes.size(); i++)
    {
        delete ComplexTypes[i];
    }
}

size_t JSONSchema::FindEnumType(const std::string& name) const
{
    for (size_t i = 0; i < EnumTypes.size(); i++)
    {
        if (EnumTypes[i]->Name == name)
            return i;
    }

    // Not found!
    return (size_t)-1;
}

size_t JSONSchema::FindComplexType(const std::string& name) const
{
    for (size_t i = 0; i < ComplexTypes.size(); i++)
    {
        if (ComplexTypes[i]->Name == name)
            return i;
    }

    // Not found!
    return (size_t)-1;
}

size_t JSONSchema::FindEntityType(const std::string& name) const
{
    for (size_t i = 0; i < EntityTypes.size(); i++)
    {
        if (EntityTypes[i]->Name == name)
            return i;
    }

    // Not found!
    return (size_t)-1;
}

void JSONSchema::Print(size_t n) const
{
    Iprintf(n, "JSONSchema\n");
    Iprintf(n, "{\n");
    n++;

    /* EntityTypes */
    {
        Iprintf(n, "EntityTypes\n");
        Iprintf(n, "{\n");
        n++;

        for (size_t i = 0; i < EntityTypes.size(); i++)
        {
            EntityTypes[i]->Print(n);
        }

        n--;
        Iprintf(n, "}\n");
    }

    /* EnumTypes */
    {
        Iprintf(n, "EnumTypes\n");
        Iprintf(n, "{\n");
        n++;

        for (size_t i = 0; i < EnumTypes.size(); i++)
        {
            EnumTypes[i]->Print(n);
        }

        n--;
        Iprintf(n, "}\n");
    }

    /* ComplexTypes */
    {
        Iprintf(n, "ComplexTypes\n");
        Iprintf(n, "{\n");
        n++;

        for (size_t i = 0; i < ComplexTypes.size(); i++)
        {
            ComplexTypes[i]->Print(n);
        }

        n--;
        Iprintf(n, "}\n");
    }

    n--;
    Iprintf(n, "}\n");
}

void JSONSchema::GenerateSchema(const string& prefix) const
{
    printf("#include <odata/json.h>\n\n");

    // EntityTypes
    if (EntityTypes.size())
    {
        // EntityTypes
        for (size_t i = 0; i < EntityTypes.size(); i++)
        {
            EntityTypes[i]->GenerateSchema(*this, prefix);
        }

        printf("static const JSON_EntityType* _%s_entityTypes[] =\n", 
            prefix.c_str());
        printf("{\n");

        // EntityTypes array:
        for (size_t i = 0; i < EntityTypes.size(); i++)
        {
            const JSONEntityType* p = EntityTypes[i];
            string tmp = "_" + prefix + "_" + p->Name + "_entityType";
            tmp = MakeIdent(tmp);
            printf("  (const JSON_EntityType*)&%s,\n", tmp.c_str());
        }

        printf("};\n");

        printf("\n");
    }

    // EnumTypes
    if (EnumTypes.size())
    {
        // EnumTypes
        for (size_t i = 0; i < EnumTypes.size(); i++)
        {
            EnumTypes[i]->GenerateSchema(*this, prefix);
        }

        printf("static const JSON_EnumType* _%s_enumTypes[] =\n", 
            prefix.c_str());
        printf("{\n");

        // EnumTypes array:
        for (size_t i = 0; i < EnumTypes.size(); i++)
        {
            const JSONEnumType* p = EnumTypes[i];
            string tmp = "_" + prefix + "_" + p->Name + "_enumType";
            tmp = MakeIdent(tmp);
            printf("  (const JSON_EnumType*)&%s,\n", tmp.c_str());
        }

        printf("};\n");

        printf("\n");
    }

    // ComplexTypes
    if (ComplexTypes.size())
    {
        // ComplexTypes
        for (size_t i = 0; i < ComplexTypes.size(); i++)
        {
            ComplexTypes[i]->GenerateSchema(*this, prefix);
        }

        printf("static const JSON_ComplexType* _%s_complexTypes[] =\n", 
            prefix.c_str());
        printf("{\n");

        // ComplexTypes array:
        for (size_t i = 0; i < ComplexTypes.size(); i++)
        {
            const JSONComplexType* p = ComplexTypes[i];
            string tmp = "_" + prefix + "_" + p->Name + "_complexType";
            tmp = MakeIdent(tmp);
            printf("  (const JSON_ComplexType*)&%s,\n", tmp.c_str());
        }

        printf("};\n");

        printf("\n");
    }

    PrintCommentBox(prefix);
    /*
        struct _EDM_Schema
        {
            const JSON_EntityType** entityTypes;
            size_t entityTypesSize;

            JSON_EnumType* enumTypes;
            size_t enumTypesSize;

            JSON_ComplexType* complexTypes;
            size_t complexTypesSize;
        };
    */
    {
        printf("const JSON_Schema _%s =\n", prefix.c_str());
        printf("{\n");

        // JSON_Schema.entityTypes:
        // JSON_Schema.entityTypesSize:
        if (EntityTypes.size())
        {
          printf("  _%s_entityTypes, /* entityTypes */\n", prefix.c_str());
          printf("  ODATA_ARRAYSIZE(_%s_entityTypes), /* entityTypesSize */\n", 
                prefix.c_str());
        }
        else
        {
            printf("  NULL, /* entityTypes */\n");
            printf("  0, /* entityTypesSize */\n");
        }

        // JSON_Schema.enumTypes:
        // JSON_Schema.enumTypesSize:
        if (EnumTypes.size())
        {
            printf("  _%s_enumTypes, /* enumTypes */\n", prefix.c_str());
            printf("  ODATA_ARRAYSIZE(_%s_enumTypes), /* enumTypesSize */\n", 
                prefix.c_str());
        }
        else
        {
            printf("  NULL, /* enumTypes */\n");
            printf("  0, /* enumTypesSize */\n");
        }

        // JSON_Schema.complexTypes:
        // JSON_Schema.complexTypesSize:
        if (EntityTypes.size())
        {
            printf("  _%s_complexTypes, /* complexTypes */\n", prefix.c_str());
            printf("  ODATA_ARRAYSIZE(_%s_complexTypes), /* complexTypesSize */\n", 
                prefix.c_str());
        }
        else
        {
            printf("  NULL, /* complexTypes */\n");
            printf("  0, /* complexTypesSize */\n");
        }


        printf("};\n");
        printf("\n");
    }
}

/*
**==============================================================================
**
** class Element
**
**==============================================================================
*/

Element::~Element()
{
}

Value::~Value()
{
}

void Value::Print(size_t n) const
{
    _Indent(n);
    printf("Value\n");

    _Indent(n);
    printf("{\n");

    n++;
    _Indent(n);
    _PrintValue(type, &value);
    printf("\n");
    n--;

    _Indent(n);
    printf("}\n");
}

/*
**==============================================================================
**
** class Aggregate
**
**==============================================================================
*/

Aggregate::~Aggregate()
{
}

/*
**==============================================================================
**
** class Array
**
**==============================================================================
*/

Array::~Array()
{
}

void Array::Print(size_t n) const
{
    _Indent(n);
    printf("Array\n");
    _Indent(n);
    printf("{\n");
    n++;

    for (size_t i = 0; i < elements.size(); i++)
    {
        elements[i]->Print(n);
    }

    n--;
    _Indent(n);
    printf("}\n");
}

/*
**==============================================================================
**
** class Pair
**
**==============================================================================
*/

bool Pair::GetBoolean(bool& x) const
{
    const Value* value = dynamic_cast<const Value*>(element);

    if (!value || value->type != JSON_Type_Boolean)
        return false;

    x = value->value.boolean;
    return true;
}

bool Pair::GetInteger(signed long long& x) const
{
    const Value* value = dynamic_cast<const Value*>(element);

    if (!value || value->type != JSON_Type_Integer)
        return false;

    x = value->value.integer;
    return true;
}

bool Pair::GetReal(double& x) const
{
    const Value* value = dynamic_cast<const Value*>(element);

    if (!value || value->type != JSON_Type_Real)
        return false;

    x = value->value.real;
    return true;
}

bool Pair::GetString(std::string& x) const
{
    const Value* value = dynamic_cast<const Value*>(element);

    if (!value || value->type != JSON_Type_String)
        return false;

    x = value->value.string;
    return true;
}

bool Pair::GetStringArray(std::vector<std::string>& x) const
{
    const Array* array = dynamic_cast<const Array*>(element);

    if (!array)
        return false;

    for (size_t i = 0; i < array->elements.size(); i++)
    {
        const Value* value = dynamic_cast<const Value*>(array->elements[i]);

        if (!value)
            return false;

        if (value->type != JSON_Type_String)
            return false;

        if (!value->value.string)
            return false;

        x.push_back(value->value.string);
    }

    return true;
}

bool Pair::GetIntegerArray(std::vector<std::string>& x) const
{
    const Array* array = dynamic_cast<const Array*>(element);

    if (!array)
        return false;

    for (size_t i = 0; i < array->elements.size(); i++)
    {
        const Value* value = dynamic_cast<const Value*>(array->elements[i]);

        if (!value)
            return false;

        if (value->type != JSON_Type_Integer)
            return false;

        char buf[22];
        sprintf(buf, "%lld", value->value.integer);
        x.push_back(buf);
    }

    return true;
}

bool Pair::GetObject(const Object*& x) const
{
    const Object* object = dynamic_cast<const Object*>(element);

    if (!object)
        return false;

    x = object;
    return true;
}

bool Pair::GetArray(const Array*& x) const
{
    const Array* array = dynamic_cast<const Array*>(element);

    if (!array)
        return false;

    x = array;
    return true;
}

/*
**==============================================================================
**
** class Object
**
**==============================================================================
*/

Object::~Object()
{
    /* ATTN: free everything! */

    free(_releaseOnDestruct);
}

void Object::Print(size_t n) const
{
    _Indent(n);
    printf("Object\n");

    _Indent(n);
    printf("{\n");
    n++;

    for (size_t i = 0; i < pairs.size(); i++)
    {
        _Indent(n);
        printf("Pair\n");
        _Indent(n);
        printf("{\n");
        n++;

        if (pairs[i].name.size())
        {
            _Indent(n);
            printf("%s\n", pairs[i].name.c_str());
        }

        pairs[i].element->Print(n);

        n--;
        _Indent(n);
        printf("}\n");
    }

    n--;
    _Indent(n);
    printf("}\n");
}

static bool _CreateProperties(
    JSONSchema& schema,
    const std::string& ownerName,
    const Object* properties,
    std::vector<JSONProperty*>& Properties);

/* Process JSON "type" element */
static bool _ProcessTypeElement(
    const Pair& pair,
    JSONProperty* property)
{
    string type;
    vector<string> types;

    if (pair.GetString(type))
    {
        property->Type = type;

        if (property->Type == "object")
            property->TypeClass = "ComplexType";
    }
    else if (pair.GetStringArray(types))
    {
        for (size_t j = 0; j < types.size(); j++)
        {
            if (types[j] == "null")
            {
                property->Nullable = true;
            }
            else
            {

                property->Type = types[j];

                if (property->Type == "object")
                    property->TypeClass = "ComplexType";
            }
        }
    }
    else
    {
        RETURN(false);
    }

    return true;
}

Object* LoadJSONFile(
    const char* path);

static bool _CreateEntityType(
    JSONSchema& schema,
    const Object* object, 
    const std::string& name,
    JSONEntityType*& entityType);

/* Handle '$ref' */
static bool _ProcessRef(
    JSONSchema& schema,
    JSONProperty* property,
    const Pair& pair)
{
    string str;

    if (!pair.GetString(str))
        RETURN(false);

    /* Examples:
     * href.0.91.0.json#
     * Type.0.91.0.json#
     * Description.0.91.0.json#
     * Status.0.91.0.json#
     * FwRev.0.91.0.json#/definitions/FWVersion
     */

    if (str.substr(0, 4) == "href")
    {
        property->Type = "string";
    }
    else if (str.substr(0, 4) == "Type")
    {
        property->Type = "string";
    }
    else if (str.substr(0, 11) == "Description")
    {
        property->Type = "string";
        property->Nullable = false;
    }
    else
    {
        string path = str.substr(0, str.rfind('#'));
        string name = str.substr(0, str.find('.'));

        /* If already defined */
        if (schema.FindEntityType(name) != (size_t)-1)
        {
            property->Type = name;
            property->TypeClass = "EntityType";
            return true;
        }

        if (!schema.ParseJSONFile(path))
            RETURN(false);

        property->Type = name;
        property->TypeClass = "EntityType";
    }

    return true;
}

/* Process JSON "items" element */
static bool _ProcessItemsElement(
    JSONSchema& schema,
    const string& objectName,
    JSONProperty* property,
    JSONEnumType*& enumType,
    const Object* items)
{
    /* ATTN */

    if (property->Type != "array")
        RETURN(false);

    property->IsArray = true;

    for (size_t i = 0; i < items->pairs.size(); i++)
    {
        const Pair& pair = items->pairs[i];

        (void)pair;

        if (pair.name == "type")
        {
            if (!_ProcessTypeElement(pair, property))
            {
                RETURN(false);
            }
        }
        else if (pair.name == "enum")
        {
            bool IsInteger = true;

            if (enumType)
                RETURN(false);

            vector<string> enums;

            if (pair.GetStringArray(enums)) 
                IsInteger = false;
            else if (pair.GetIntegerArray(enums))
                IsInteger = true;
            else
                RETURN(false);

            string type = objectName + '.' + property->Name;
            property->Type = type;
            property->TypeClass = "EnumType";

            enumType = new JSONEnumType;
            enumType->Name = type;
            enumType->IsInteger = IsInteger;
            enumType->Values = enums;
        }
        else if (pair.name == "$ref")
        {
            if (!_ProcessRef(schema, property, pair))
                RETURN(false);
        }
    }

    return true;
}

static bool _CreateProperty(
    JSONSchema& schema,
    const std::string& ownerName,
    const string& name,
    const Element* element,
    JSONProperty*& property,
    JSONEnumType*& enumType,
    JSONComplexType*& complexType)
{
    const Object* object = (const Object*)element;
    bool found = false;

    if (!object)
        RETURN(false);

    property = new JSONProperty;
    enumType = 0;
    complexType = 0;

    property->Name = name;

    for (size_t i = 0; i < object->pairs.size(); i++)
    {
        const Pair& pair = object->pairs[i];

        if (pair.name == "type")
        {
            // If 'Type' not already set by 'enum' case below
            if (property->Type.size() == 0)
            {
                if (!_ProcessTypeElement(pair, property))
                    RETURN(false);
            }
            found = true;
        }
        else if (pair.name == "description")
        {
            /* ATTN: ignore */
            found = true;
        }
        else if (pair.name == "readonly")
        {
            /* ATTN: ignore */
            found = true;
        }
        else if (pair.name == "specification")
        {
            /* ATTN: ignore */
            found = true;
        }
        else if (pair.name == "enum")
        {
            if (enumType)
                RETURN(false);

            vector<string> enums;
            bool IsInteger = true;

            if (pair.GetStringArray(enums)) 
                IsInteger = false;
            else if (pair.GetIntegerArray(enums))
                IsInteger = true;
            else
                RETURN(false);

            enumType = new JSONEnumType;
            enumType->Name = ownerName + '.' + property->Name;
            enumType->IsInteger = IsInteger;
            enumType->Values = enums;
            found = true;
        }
        else if (pair.name == "enumDescriptions")
        {
            /* ATTN: ignore */
            found = true;
        }
        else if (pair.name == "properties")
        {
            const Object* properties;

            if (!pair.GetObject(properties))
                RETURN(false);

            complexType = new JSONComplexType;
            complexType->Name = ownerName + '.' + name;

            if (!_CreateProperties(schema,
                complexType->Name, properties, complexType->Properties))
            {
                RETURN(false);
            }
            found = true;
        }
        else if (pair.name == "items" || pair.name == "item")
        {
            /* Note: 'type' must be 'array' */
            const Object* items;

            if (!pair.GetObject(items))
                RETURN(false);

            if (!_ProcessItemsElement(
                schema, ownerName, property, enumType, items))
            {
                RETURN(false);
            }
            found = true;
        }
        else if (pair.name == "$ref")
        {
            if (!_ProcessRef(schema, property, pair))
                RETURN(false);
            found = true;
        }
    }

    if (!found)
    {
        delete property;
        property = 0;
        RETURN(false);
    }

    /* Set the 'Type' field */
    if (complexType)
    {
        property->Type = complexType->Name;
        property->TypeClass = "ComplexType";
    }
    else if (enumType)
    {
        property->Type = enumType->Name;
        property->TypeClass = "EnumType";
    }

    return true;
}

static bool _CreateProperties(
    JSONSchema& schema,
    const std::string& ownerName,
    const Object* properties,
    std::vector<JSONProperty*>& Properties)
{
    for (size_t i = 0; i < properties->pairs.size(); i++)
    {
        const Pair& pair = properties->pairs[i];

        if (pair.name == "Oem")
        {
            // ATTN: implement this!
        }
        else if (pair.name == "required")
        {
            // ATTN: implement this!
        }
        else if (pair.name == "Name")
        {
            JSONProperty* property = new JSONProperty;
            property->Name = "Name";
            property->Type = "string";
            Properties.push_back(property);
        }
        else if (pair.name == "Modified")
        {
            JSONProperty* property = new JSONProperty;
            property->Name = "Modified";
            property->Type = "string";
            Properties.push_back(property);
        }
        else if (pair.name == "AvailableActions")
        {
            // ATTN: implement this!
        }
        else
        {
            JSONProperty* property;
            JSONEnumType* enumType = 0;
            JSONComplexType* complexType = 0;

            if (!_CreateProperty(schema, ownerName,
                pair.name, pair.element, property, enumType, complexType))
            {
                fprintf(stderr, "Warning: cannot create property: %s.%s\n", 
                    ownerName.c_str(), pair.name.c_str());
                continue;
            }

            Properties.push_back(property);

            if (enumType)
            {
                if (schema.FindEnumType(enumType->Name) == (size_t)-1)
                    schema.EnumTypes.push_back(enumType);
            }

            if (complexType)
                schema.ComplexTypes.push_back(complexType);
        }
    }

    return true;
}

static bool _CreateEntityType(
    JSONSchema& schema,
    const Object* object, 
    const std::string& name,
    JSONEntityType*& entityType)
{
    entityType = new JSONEntityType;

    // This may be reset by "title" attribute:
    entityType->Name = name;

    for (size_t i = 0; i < object->pairs.size(); i++)
    {
        const Pair& pair = object->pairs[i];

        if (pair.name == "title")
        {
            string name;

            if (!pair.GetString(name))
                RETURN(false);

            entityType->Name = name.substr(0, name.find('.'));
        }
        else if (pair.name == "additionalProperties")
        {
            bool additionalProperties;

            if (!pair.GetBoolean(additionalProperties))
                RETURN(false);

            entityType->OpenType = additionalProperties;
        }
        else if (pair.name == "properties")
        {
            const Object* properties;

            if (!pair.GetObject(properties))
                RETURN(false);

            if (!_CreateProperties(schema, entityType->Name, 
                properties, entityType->Properties))
            {
                RETURN(false);
            }
        }
        else if (pair.name == "description")
        {
            /* ATTN: ignore */
        }
    }

    if (schema.FindEntityType(entityType->Name) == (size_t)-1)
        schema.EntityTypes.push_back(entityType);
    else
        delete entityType;

    return true;
}

bool Object::CreateSchema(JSONSchema& schema) const
{
    JSONEntityType* entityType;

    string name = "Unknown";
 
    if (!_CreateEntityType(schema, this, name, entityType))
        RETURN(false);

    return true;
}

bool JSONSchema::ParseJSONFile(
    const std::string& path)
{
    Object* object;

    if (!(object = LoadJSONFile(path.c_str())))
        return false;

    JSONEntityType* entityType;

    // Remove everything after the '.' character:
    string name = path.substr(0, path.find('.'));
 
    if (!_CreateEntityType(*this, object, name, entityType))
        RETURN(false);

    return true;
}

#if 0
#include "schema.c"
#endif
