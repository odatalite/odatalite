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
#include <stdarg.h>
#include <base/str.h>
#include "csdl.h"

INLINE void _Indent(
    Buf* out,
    size_t depth)
{
    BufSet(out, ' ', depth * 2);
}

static int _PutStartTag(
    Buf* out, 
    int emptyElementTag,
    const char* tag,
    size_t tagLen,
    ...)
{
    va_list ap;
    const char* name;
    size_t nameLen;
    const char* value;

    va_start(ap, tagLen);
    {
        BufCatCh(out, '<');
        BufCat(out, tag, tagLen);

        while ((name = va_arg(ap, const char*)))
        {
            nameLen = va_arg(ap, size_t);
            value = va_arg(ap, const char*);

            if (value)
            {
                BufCatCh(out, ' ');
                BufCat(out, name, nameLen);
                BufCatCh2(out, '=', '"');
                BufCatStr(out, value);
                BufCatCh(out, '"');
            }
        }

        if (emptyElementTag)
            BufCatCh(out, '/');

        BufCatCh2(out, '>', '\n');
    }
    va_end(ap);

    return out->err;
}

static int _PutEndTag(
    Buf* out, 
    const char* tag,
    size_t tagLen)
{
    BufCatCh2(out, '<', '/');
    BufCat(out, tag, tagLen);
    BufCatCh2(out, '>', '\n');

    return out->err;
}

static void _PutInclude(
    Buf* out,
    const EDMX_Include* object,
    size_t depth)
{
    _Indent(out, depth);
    _PutStartTag(
        out,
        1,
        STRLIT("edmx:Include"),
        STRLIT("Namespace"), object->Namespace,
        STRLIT("Alias"), object->Alias,
        NULL);
}

static void _PutIncludeAnnotations(
    Buf* out,
    const EDMX_IncludeAnnotations* object,
    size_t depth)
{
    _Indent(out, depth);
    _PutStartTag(
        out,
        1,
        STRLIT("edmx:IncludeAnnotations"),
        STRLIT("TermNamespace"), object->TermNamespace,
        STRLIT("Qualifier"), object->Qualifier,
        STRLIT("TargetNamespace"), object->TargetNamespace,
        NULL);
}

static void _PutReference(
    Buf* out,
    const EDMX_Reference* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("edmx:Reference"),
        STRLIT("Uri"), object->Uri,
        NULL);

    for (i = 0; i < object->NumIncludes; i++)
        _PutInclude(out, object->Includes[i], depth+1);

    for (i = 0; i < object->NumIncludeAnnotations; i++)
        _PutIncludeAnnotations(out, object->IncludeAnnotations[i], depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("edmx:Reference"));
}

static void _PutPropertyRef(
    Buf* out,
    const EDM_PropertyRef* object,
    size_t depth)
{
    _Indent(out, depth);
    _PutStartTag(
        out,
        1,
        STRLIT("PropertyRef"),
        STRLIT("Name"), object->Name,
        STRLIT("Alias"), object->Alias,
        NULL);
}

static void _PutKey(
    Buf* out,
    const EDM_Key* object,
    size_t depth)
{
    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("Key"),
        NULL);

    _PutPropertyRef(out, &object->PropertyRef, depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("Key"));
}

static void _PutProperty(
    Buf* out,
    const EDM_Property* object,
    size_t depth)
{
    const char* Nullable = NULL;

    if (!object->Nullable)
        Nullable = "false";

    if (object->Extended)
    {
        const EDM_ExtendedProperty* extended = (EDM_ExtendedProperty*)object;

        _PutStartTag(
            out,
            1,
            STRLIT("Property"),
            STRLIT("Name"), object->Name,
            STRLIT("Type"), object->Type,
            STRLIT("MaxLength"), extended->MaxLength,
            STRLIT("Precision"), extended->Precision,
            STRLIT("Scale"), extended->Scale,
            STRLIT("Unicode"), extended->Unicode,
            STRLIT("SRID"), extended->SRID,
            STRLIT("DefaultValue"), extended->DefaultValue,
            STRLIT("Nullable"), Nullable,
            NULL);
    }
    else
    {
        _Indent(out, depth);
        _PutStartTag(
            out,
            1,
            STRLIT("Property"),
            STRLIT("Name"), object->Name,
            STRLIT("Type"), object->Type,
            STRLIT("Nullable"), Nullable,
            NULL);
    }
}

static void _PutNavigationProperty(
    Buf* out,
    const EDM_NavigationProperty* object,
    size_t depth)
{
    const char* Nullable = NULL;
    const char* ContainsTarget = NULL;

    if (!(object->Flags & EDM_NavigationProperty_Flags_Nullable))
        Nullable = "false";

    if ((object->Flags & EDM_NavigationProperty_Flags_ContainsTarget))
        ContainsTarget = "true";

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("NavigationProperty"),
        STRLIT("Name"), object->Name,
        STRLIT("Type"), object->Type,
        STRLIT("Partner"), object->Partner,
        STRLIT("Nullable"), Nullable,
        STRLIT("ContainsTarget"), ContainsTarget,
        NULL);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("NavigationProperty"));
}

static void _PutEntityType(
    Buf* out,
    const EDM_EntityType* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("EntityType"),
        STRLIT("Name"), object->Name,
        STRLIT("BaseType"), object->BaseType,
        STRLIT("Abstract"), object->Abstract,
        STRLIT("OpenType"), object->OpenType,
        STRLIT("HasStream"), object->HasStream,
        NULL);

    if (object->Key)
        _PutKey(out, object->Key, depth+1);

    for (i = 0; i < object->NumProperties; i++)
        _PutProperty(out, object->Properties[i], depth+1);

    for (i = 0; i < object->NumNavigationProperties; i++)
        _PutNavigationProperty(out, object->NavigationProperties[i], depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("EntityType"));
}

static void _PutComplexType(
    Buf* out,
    const EDM_ComplexType* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("ComplexType"),
        STRLIT("Name"), object->Name,
        STRLIT("BaseType"), object->BaseType,
        STRLIT("Abstract"), object->Abstract,
        STRLIT("OpenType"), object->OpenType,
        NULL);

    for (i = 0; i < object->NumProperties; i++)
        _PutProperty(out, object->Properties[i], depth+1);

    for (i = 0; i < object->NumNavigationProperties; i++)
        _PutNavigationProperty(out, object->NavigationProperties[i], depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("ComplexType"));
}

static void _PutMember(
    Buf* out,
    const EDM_Member* object,
    size_t depth)
{
    _Indent(out, depth);
    _PutStartTag(
        out,
        1,
        STRLIT("Member"),
        STRLIT("Name"), object->Name,
        STRLIT("Value"), object->Value,
        NULL);
}

static void _PutEnumType(
    Buf* out,
    const EDM_EnumType* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("EnumType"),
        STRLIT("Name"), object->Name,
        STRLIT("UnderlyingType"), object->UnderlyingType,
        STRLIT("IsFlags"), object->IsFlags,
        NULL);

    for (i = 0; i < object->NumMembers; i++)
    {
        if (object->MemberType == EDM_MemberType_Struct)
        {
            _PutMember(out, (const EDM_Member*)object->Members[i], depth+1);
        }
        else
        {
            EDM_Member member;
            member.Name = (const char*)object->Members[i];
            member.Value = NULL;
            _PutMember(out, &member, depth+1);
        }
    }

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("EnumType"));
}

static void _PutParameter(
    Buf* out,
    const EDM_Parameter* object,
    size_t depth)
{
    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("Parameter"),
        STRLIT("Name"), object->Name,
        STRLIT("Type"), object->Type,
        STRLIT("Nullable"), object->Nullable,
        NULL);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("Parameter"));
}

static void _PutAction(
    Buf* out,
    const EDM_Action* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("Action"),
        STRLIT("Name"), object->Name,
        STRLIT("IsBound"), object->IsBound,
        STRLIT("EntitySetPath"), object->EntitySetPath,
        NULL);

    for (i = 0; i < object->NumParameters; i++)
        _PutParameter(out, object->Parameters[i], depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("Action"));
}

static void _PutTypeDefinition(
    Buf* out,
    const EDM_TypeDefinition* object,
    size_t depth)
{
    _Indent(out, depth);
    _PutStartTag(
        out,
        1,
        STRLIT("TypeDefinition"),
        STRLIT("Name"), object->Name,
        STRLIT("UnderlyingType"), object->UnderlyingType,
        NULL);
}

static void _PutSingleton(
    Buf* out,
    const EDM_Singleton* object,
    size_t depth)
{
    _Indent(out, depth);
    _PutStartTag(
        out,
        1,
        STRLIT("Singleton"),
        STRLIT("Name"), object->Name,
        STRLIT("Type"), object->Type,
        NULL);
}

static void _PutEntityContainer(
    Buf* out,
    const EDM_EntityContainer* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("EntityContainer"),
        STRLIT("Name"), object->Name,
        STRLIT("Extends"), object->Extends,
        NULL);

    for (i = 0; i < object->NumSingletons; i++)
        _PutSingleton(out, object->Singletons[i], depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("EntityContainer"));
}

static void _PutTerm(
    Buf* out,
    const EDM_Term* object,
    size_t depth)
{
    EDM_ExtendedTerm md;
    const char* Nullable = NULL;

    if (!object->Nullable)
        Nullable = "false";

    memset(&md, 0, sizeof(md));

    if (object->Extended)
    {
        md.BaseTerm = ((const EDM_ExtendedTerm*)object)->BaseTerm;
        md.AppliesTo = ((const EDM_ExtendedTerm*)object)->AppliesTo;
        md.DefaultValue = ((const EDM_ExtendedTerm*)object)->DefaultValue;
        md.MaxLength = ((const EDM_ExtendedTerm*)object)->MaxLength;
        md.Precision = ((const EDM_ExtendedTerm*)object)->Precision;
        md.Scale = ((const EDM_ExtendedTerm*)object)->Scale;
        md.SRID = ((const EDM_ExtendedTerm*)object)->SRID;
    }

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("Term"),
        STRLIT("Name"), object->Name,
        STRLIT("Type"), object->Type,
        STRLIT("Nullable"), Nullable,
        STRLIT("BaseTerm"), md.BaseTerm,
        STRLIT("AppliesTo"), md.AppliesTo,
        STRLIT("DefaultValue"), md.DefaultValue,
        STRLIT("MaxLength"), md.MaxLength,
        STRLIT("Scale"), md.Scale,
        STRLIT("SRID"), md.SRID,
        NULL);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("Term"));
}

static void _PutSchema(
    Buf* out,
    const EDM_Schema* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("Schema"),
        STRLIT("Namespace"), object->Namespace,
        STRLIT("Alias"), object->Alias,
        NULL);

    for (i = 0; i < object->NumEntityTypes; i++)
        _PutEntityType(out, object->EntityTypes[i], depth+1);

    for (i = 0; i < object->NumComplexTypes; i++)
        _PutComplexType(out, object->ComplexTypes[i], depth+1);

    for (i = 0; i < object->NumEnumTypes; i++)
        _PutEnumType(out, object->EnumTypes[i], depth+1);

    for (i = 0; i < object->NumActions; i++)
        _PutAction(out, object->Actions[i], depth+1);

    for (i = 0; i < object->NumTypeDefinitions; i++)
        _PutTypeDefinition(out, object->TypeDefinitions[i], depth+1);

    for (i = 0; i < object->NumEntityContainers; i++)
        _PutEntityContainer(out, object->EntityContainers[i], depth+1);

    for (i = 0; i < object->NumTerms; i++)
        _PutTerm(out, object->Terms[i], depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("Schema"));
}

static void _PutDataServices(
    Buf* out,
    const EDMX_DataServices* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("edmx:DataServices"),
        NULL);

    for (i = 0; i < object->NumSchemas; i++)
        _PutSchema(out, object->Schemas[i], depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("edmx:DataServices"));
}

static void _PutEdmx(
    Buf* out,
    const EDMX_Edmx* object,
    size_t depth)
{
    size_t i;

    _Indent(out, depth);
    _PutStartTag(
        out,
        0,
        STRLIT("edmx:Edmx"),
        STRLIT("xmlns:edmx"), "http://docs.oasis-open.org/odata/ns/edmx",
        STRLIT("Version"), "4.0",
        NULL);

    for (i = 0; i < object->NumReferences; i++)
        _PutReference(out, object->References[i], depth+1);

    if (object->DataServices)
        _PutDataServices(out, object->DataServices, depth+1);

    _Indent(out, depth);
    _PutEndTag(out, STRLIT("edmx:Edmx"));
}

int CSDL_Serialize(
    Buf* out, 
    const EDMX_Edmx* edmx)
{
    BufCat(out, STRLIT("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"));

    _PutEdmx(out, edmx, 0);

    BufCatCh(out, '\0');

    if (out->err == 0)
        out->size--;

    return out->err;
}
