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
#include <ctype.h>
#include "xml.h"
#include <base/file.h>
#include <base/str.h>
#include <base/path.h>
#include <base/ptrarray.h>
#include <base/format.h>
#include <odata/odata.h>

static FILE* _os;

static const char* s_arg0;
static const char* s_path;

PRINTF_FORMAT(1, 2)
void err(const char* format, ...)
{
    va_list ap;

    fprintf(stderr, "%s: %s: ", s_arg0, s_path);

    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);

    fprintf(stderr, "\n");

    exit(1);
}

PRINTF_FORMAT(2, 3)
void errl(size_t line, const char* format, ...)
{
    va_list ap;

    fprintf(stderr, "%s: %s(%u): ", s_arg0, s_path, (unsigned int)line);

    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);

    fprintf(stderr, "\n");

    exit(1);
}

PRINTF_FORMAT(1, 2)
void put(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(_os, format, ap);
    va_end(ap);
}

PRINTF_FORMAT(1, 2)
void putl(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(_os, format, ap);
    va_end(ap);
    fprintf(_os, "\n");
}

void nl()
{
    fprintf(_os, "\n");
}

void WritePreamble()
{
    putl("#include <odata/odata.h>");
    nl();
}

void WriteCommentLine()
{
    size_t i;

    put("**");

    for (i = 0; i < 78; i++)
        put("=");

    nl();
}

void WriteCommentBox(const char* msg)
{
    putl("/*");
    WriteCommentLine();

    putl("**");
    putl("** %s", msg);
    putl("**");

    WriteCommentLine();
    putl("*/");
    nl();
}

void WriteFlags(
    const char* flags[32],
    size_t nflags)
{
    size_t i;

    for (i = 0; i < nflags; i++)
    {
        put("    %s", flags[i]);

        if (i + 1 == nflags)
            putl(", /* Flags */");
        else
            putl(" |");
    }
}

void WriteStringInitializer(
    const char* name,
    const char* value,
    int writeComma)
{
    const char* comma = writeComma ? "," : "";

    if (value)
        putl("    \"%s\"%s /* %s */", value, comma, name);
    else
        putl("    NULL%s /* %s */", comma, name);
}

void WriteProperty(
    const char* schemaAlias,
    const char* entityTypeName,
    const EDM_ExtendedProperty* md)
{
    if (md->Extended)
        put("static const EDM_ExtendedProperty ");
    else
        put("static const EDM_Property ");

    putl("_%s_%s_%s =", schemaAlias, entityTypeName, md->Name);
    putl("{");

    /* EDM_ExtendedProperty.Nullable */
    putl("    %u, /* Nullable */", md->Nullable);

    /* EDM_ExtendedProperty.Extended */
    putl("    %u, /* Extended */", md->Extended);

    /* EDM_ExtendedProperty.Name */
    WriteStringInitializer("Name", md->Name, 1);

    /* EDM_ExtendedProperty.Type */
    WriteStringInitializer("Type", md->Type, md->Extended);

    if (md->Extended)
    {
        /* EDM_ExtendedProperty.MaxLength */
        WriteStringInitializer("MaxLength", md->MaxLength, 1);

        /* EDM_ExtendedProperty.Precision */
        WriteStringInitializer("Precision", md->Precision, 1);

        /* EDM_ExtendedProperty.Scale */
        WriteStringInitializer("Scale", md->Scale, 1);

        /* EDM_ExtendedProperty.Unicode */
        WriteStringInitializer("Unicode", md->Unicode, 1);

        /* EDM_ExtendedProperty.SRID */
        WriteStringInitializer("SRID", md->SRID, 1);

        /* EDM_ExtendedProperty.DefaultValue */
        WriteStringInitializer("DefaultValue", md->DefaultValue, 0);
    }

    putl("};");
    nl();
}

void WriteNavigationProperty(
    const char* schemaAlias,
    const char* entityTypeName,
    const EDM_NavigationProperty* md)
{
    putl("static const EDM_NavigationProperty _%s_%s_%s =", 
        schemaAlias, entityTypeName, md->Name);
    putl("{");

    /* EDM_NavigationProperty.Flags */
    {
        if (md->Flags)
        {
            const char* flags[32];
            size_t nflags = 0;

            if (md->Flags & EDM_NavigationProperty_Flags_Nullable)
            {
                flags[nflags++] = 
                    "EDM_NavigationProperty_Flags_Nullable";
            }

            if (md->Flags & EDM_NavigationProperty_Flags_ContainsTarget)
            {
                flags[nflags++] = 
                    "EDM_NavigationProperty_Flags_ContainsTarget";
            }

            WriteFlags(flags, nflags);
        }
        else
        {
            putl("    0,");
        }
    }

    /* EDM_NavigationProperty.Name */
    putl("    \"%s\", /* Name */", md->Name);

    /* EDM_NavigationProperty.Type */
    putl("    \"%s\", /* Type */", md->Type);

    /* EDM_NavigationProperty.Partner */
    if (md->Partner)
        putl("    \"%s\", /* Partner */", md->Partner);
    else
        putl("    NULL, /* Partner */");

    putl("};");
    nl();
}

void WriteArray1(
    const char* schemaAlias,
    const char* objectName,
    const char* suffix,
    char* names[],
    size_t nnames)
{
    if (nnames)
    {
        size_t i;

        putl("static const EDM_%s* _%s_%sArray[] =", 
            objectName, schemaAlias, suffix);
        putl("{");

        for (i = 0; i < nnames; i++)
        {
            put("    (const EDM_%s*)&_%s_%s", 
                objectName, schemaAlias, names[i]);

            if (i + 1 != nnames)
                put(",");

            nl();
        }

        putl("};");
        nl();
    }
}

void WriteArrayInitializer1(
    const char* schemaAlias,
    const char* suffix,
    size_t count,
    int writeComma)
{
    const char* comma = writeComma ? "," : "";

    if (count)
    {
        putl("    _%s_%sArray,", schemaAlias, suffix);
        putl("    OL_ARRAYSIZE(_%s_%sArray)%s", schemaAlias, suffix, comma);
    }
    else
    {
        putl("    NULL, /* %s */", suffix);
        putl("    0%s /* Num%s */", comma, suffix);
    }
}

void WriteArrayInitializer2(
    const char* schemaAlias,
    const char* name,
    const char* suffix,
    size_t count,
    int writeComma)
{
    const char* comma = writeComma ? "," : "";

    if (count)
    {
        putl("    _%s_%s_%sArray,", schemaAlias, name, suffix);
        putl("    OL_ARRAYSIZE(_%s_%s_%sArray)%s", schemaAlias, name, suffix,
            comma);
    }
    else
    {
        putl("    NULL, /* %s */", suffix);
        putl("    0%s /* Num%s */", comma, suffix);
    }
}

void WriteEntityType(
    const char* schemaAlias, 
    EDM_EntityType* md,
    size_t nkeys,
    size_t nproperties,
    size_t nnavigationproperties)
{
    putl("static const EDM_EntityType _%s_%s =", schemaAlias, md->Name);
    putl("{");

    /* EntityType.Name */
    WriteStringInitializer("Name", md->Name, 1);

    /* EntityType.BaseType */
    WriteStringInitializer("BaseType", md->BaseType, 1);

    /* EntityType.Abstract */
    WriteStringInitializer("Abstract", md->Abstract, 1);

    /* EntityType.OpenType */
    WriteStringInitializer("OpenType", md->OpenType, 1);

    /* EntityType.HasStream */
    WriteStringInitializer("HasStream", md->HasStream, 1);

    /* EntityType.Key */
    if (nkeys)
        putl("    &_%s_%s_Key, /* Key */", schemaAlias, md->Name);
    else
        putl("    NULL, /* Key */");

    /* EntityType.Properties & EntityType.NumProperties */
    WriteArrayInitializer2(schemaAlias, md->Name, "Properties", nproperties, 1);

    /* EntityType.NavigationProperties & EntityType.NumNavigationProperties */
    WriteArrayInitializer2(schemaAlias, md->Name, "NavigationProperties", 
        nnavigationproperties, 0);

    putl("};");
    nl();
}

void WriteComplexType(
    const char* schemaAlias, 
    EDM_ComplexType* md,
    size_t nproperties,
    size_t nnavigationproperties)
{
    putl("static const EDM_ComplexType _%s_%s =", schemaAlias, md->Name);
    putl("{");

    /* ComplexType.Name */
    WriteStringInitializer("Name", md->Name, 1);

    /* ComplexType.BaseType */
    WriteStringInitializer("BaseType", md->BaseType, 1);

    /* ComplexType.Abstract */
    WriteStringInitializer("Abstract", md->Abstract, 1);

    /* ComplexType.OpenType */
    WriteStringInitializer("OpenType", md->OpenType, 1);

    /* ComplexType.Properties & ComplexType.NumProperties */
    WriteArrayInitializer2(schemaAlias, md->Name, "Properties", nproperties, 1);

    /* ComplexType.NavigationProperties & ComplexType.NumNavigationProperties */
    WriteArrayInitializer2(schemaAlias, md->Name, "NavigationProperties", 
        nnavigationproperties, 0);

    putl("};");
    nl();
}

void WriteEnumType(
    const char* schemaAlias, 
    EDM_EnumType* md,
    size_t nmembers,
    int hasValues)
{
    putl("static const EDM_EnumType _%s_%s =", schemaAlias, md->Name);
    putl("{");

    /* EnumType.Name */
    WriteStringInitializer("Name", md->Name, 1);

    /* EnumType.UnderlyingType */
    WriteStringInitializer("UnderlyingType", md->UnderlyingType, 1);

    /* EnumType.Flags */
    WriteStringInitializer("IsFlags", md->IsFlags, 1);

    /* EnumType.MemberType */
    if (hasValues)
        putl("    EDM_MemberType_Struct,");
    else
        putl("    EDM_MemberType_String,");

    /* EnumType.Members & EnumType.NumMembers */
    if (nmembers)
    {
        putl("    (const void** const)_%s_%s_MembersArray,", schemaAlias, 
            md->Name);
        putl("    OL_ARRAYSIZE(_%s_%s_MembersArray)", schemaAlias, md->Name);
    }
    else
    {
        putl("    NULL, /* Members */");
        putl("    0 /* NumMembers */");
    }

    putl("};");
    nl();
}

void WriteTypeDefinition(
    const char* schemaAlias, 
    EDM_TypeDefinition* md)
{
    putl("static const EDM_TypeDefinition _%s_%s =", 
        schemaAlias, md->Name);
    putl("{");

    /* EnumType.Name */
    putl("    \"%s\", /* Name */", md->Name);

    /* EnumType.UnderlyingType */
    if (md->UnderlyingType)
        putl("    \"%s\" /* UnderlyingType */", md->UnderlyingType);
    else
        putl("    NULL /* UnderlyingType */");

    putl("};");
    nl();
}

void FixupName(char *name)
{
    char* p = name;

    if (*p != '_' && !isalnum(*p))
        *p = '_';

    for (p++; *p; p++)
    {
        if (*p != '_' && !isalnum(*p))
            *p = '_';
    }
}

void WriteMember(
    const char* schemaAlias,
    const char* enumTypeName,
    const EDM_Member* md)
{
    char* name = Strdup(md->Name);

    FixupName(name);

    putl("static const EDM_Member _%s_%s_%s =", 
        schemaAlias, enumTypeName, name);
    putl("{");

    /* EDM_Member.Name */
    putl("    \"%s\", /* Name */", md->Name);

    /* EDM_Member.Value */
    if (md->Value)
        putl("    \"%s\", /* Value */", md->Value);
    else
        putl("    NULL, /* Value */");

    putl("};");
    nl();

    Free(name);
}

void WriteParameter(
    const char* schemaAlias,
    const char* enumTypeName,
    const EDM_Parameter* md)
{
    putl("static const EDM_Parameter _%s_%s_%s =", 
        schemaAlias, enumTypeName, md->Name);
    putl("{");

    /* EDM_Parameter.Name */
    WriteStringInitializer("Name", md->Name, 1);

    /* EDM_Parameter.Type */
    WriteStringInitializer("Type", md->Type, 1);

    /* EDM_Parameter.Nullable */
    WriteStringInitializer("Nullable", md->Nullable, 0);

    putl("};");
    nl();
}

void WriteArray2(
    const char* schemaAlias,
    const char* parentName,
    const char* objectName,
    const char* suffix,
    char* names[],
    size_t nnames)
{
    if (nnames)
    {
        size_t i;

        putl("static const EDM_%s* _%s_%s_%sArray[] =", 
            objectName, schemaAlias, parentName, suffix);
        putl("{");

        for (i = 0; i < nnames; i++)
        {
            put("    (const EDM_%s*)&_%s_%s_%s", 
                objectName, schemaAlias, parentName, names[i]);

            if (i + 1 != nnames)
                put(",");

            nl();
        }

        putl("};");
        nl();
    }
}

void WriteAction(
    const char* schemaAlias,
    const EDM_Action* md,
    size_t nparameters)
{
    put("static const EDM_Action _%s_%s =\n", schemaAlias, md->Name);

    putl("{");

    /* EDM_Action.Name */
    WriteStringInitializer("Name", md->Name, 1);

    /* EDM_Action.IsBound */
    WriteStringInitializer("IsBound", md->IsBound, 1);

    /* EDM_Action.EntitySetPath */
    WriteStringInitializer("EntitySetPath", md->EntitySetPath, 1);

    /* EnumType.Parameters & EnumType.NumParameters */
    WriteArrayInitializer2(schemaAlias, md->Name, "Parameters", nparameters, 1);

    putl("};");
    nl();
}

void WriteKey(
    EDM_Key* md,
    const char* schemaAlias,
    const char* entityTypeName)
{
    putl("static const EDM_Key _%s_%s_Key =", schemaAlias, 
        entityTypeName);
    putl("{");
    putl("    {");

    /* Key.PropertyRef.Name */
    putl("        \"%s\", /* PropertyRef.Name */", md->PropertyRef.Name);

    /* Key.PropertyRef.Alias */
    if (md->PropertyRef.Alias)
        putl("        \"%s\", /* PropertyRef.Alias */", md->PropertyRef.Alias);
    else
        putl("        NULL, /* PropertyRef.Alias */");

    putl("    }");

    putl("};");
    nl();
}

void WriteInclude(
    const EDMX_Include* md,
    size_t referenceIndex,
    size_t includeIndex)
{
    putl("static const EDMX_Include _%u_%u_Include =", 
        (int)referenceIndex,
        (int)includeIndex);
    putl("{");

    /* Include.Namespace */
    putl("    \"%s\", /* Include.Namespace */", md->Namespace);

    /* Include.Alias */
    if (md->Alias)
        putl("    \"%s\" /* Include.Alias */", md->Alias);
    else
        putl("    NULL /* Include.Alias */");

    putl("};");
    nl();
}

void WriteIncludeAnnotations(
    const EDMX_IncludeAnnotations* md,
    size_t referenceIndex,
    size_t includeAnnotationIndex)
{
    putl("static const EDMX_IncludeAnnotations "
        "_%u_%u_IncludeAnnotations =", (int)referenceIndex, 
        (int)includeAnnotationIndex);
    putl("{");

    /* IncludeAnnotations.Namespace */
    putl("    \"%s\", /* IncludeAnnotations.TermNamespace */", 
        md->TermNamespace);

    /* IncludeAnnotations.Qualifier */
    if (md->Qualifier)
        putl("    \"%s\", /* IncludeAnnotations.Qualifier */", md->Qualifier);
    else
        putl("    NULL, /* IncludeAnnotations.Qualifier */");

    /* IncludeAnnotations.TargetNamespace */
    if (md->TargetNamespace)
    {
        putl("    \"%s\", /* IncludeAnnotations.TargetNamespace */", 
            md->TargetNamespace);
    }
    else
        putl("    NULL, /* IncludeAnnotations.TargetNamespace */");

    putl("};");
    nl();
}

void WriteReference(
    const EDMX_Reference* md,
    size_t referenceIndex,
    size_t nincludes,
    size_t nincludeassocations)
{
    char* s = Strdup(md->Uri);
    assert(s);

    FixupName(s);

    putl("static const EDMX_Reference _%u_Reference =", 
        (int)referenceIndex);
    putl("{");

    /* Reference.Uri */
    putl("    \"%s\", /* Uri */", md->Uri);

    /* Reference.Includes[] */
    if (nincludes)
    {
        putl("    _%u_IncludesArray, /* Includes */", (int)referenceIndex);
        putl("    OL_ARRAYSIZE(_%u_IncludesArray), /* NumIncludes */", 
            (int)referenceIndex);
    }
    else
    {
        putl("    NULL, /* Includes */");
        putl("    0, /* NumIncludes */");
    }

    /* Reference.IncludeAnnotations[] */
    if (nincludeassocations)
    {
        putl("    _%u_IncludeAnnotationsArray, /* IncludeAnnotations */", 
            (int)referenceIndex);
        putl("    OL_ARRAYSIZE(_%u_IncludeAnnotationsArray) "
            "/* NumIncludeAnnotations */", (int)referenceIndex);
    }
    else
    {
        putl("    NULL, /* NumIncludeAnnotations */");
        putl("    0 /* NumIncludeAnnotations */");
    }

    putl("};");
    nl();
    Free(s);
}

void WriteSingleton(
    const char* parentName, 
    EDM_Singleton* md)
{
    putl("static const EDM_Singleton _%s_%s =", parentName, 
        md->Name);
    putl("{");

    /* Singleton.Name */
    putl("    \"%s\", /* Name */", md->Name);

    /* Singleton.Type */
    putl("    \"%s\" /* Type */", md->Type);

    putl("};");
    nl();
}

void WriteEntityContainer(
    EDM_EntityContainer* md,
    const char* schemaAlias,
    size_t nsingletons)
{
    putl("static const EDM_EntityContainer _%s_%s =", schemaAlias, md->Name);
    putl("{");

    /* EntityContainer.Name */
    putl("    \"%s\", /* Name */", md->Name);

    /* EntityContainer.Extends */
    if (md->Extends)
        putl("    \"%s\", /* Extends */", md->Extends);
    else
        putl("    NULL, /* Extends */");

    WriteArrayInitializer1(md->Name, "Singletons", nsingletons, 0);

    putl("};");
    nl();
}

void WriteSchema(
    const char* schemaAlias, 
    EDM_Schema* md,
    size_t nentitytypes,
    size_t ncomplextypes,
    size_t nenumtypes,
    size_t nactions,
    size_t ntypedefinitions,
    size_t nentitycontainers,
    size_t nterms)
{
    putl("static const EDM_Schema _%s_Schema =", schemaAlias);
    putl("{");

    /* Schema.Namespace */
    if (md->Namespace)
        putl("    \"%s\", /* Namespace */", md->Namespace);
    else
        putl("    NULL, /* Namespace */");

    /* Schema.BaseType */
    if (md->Alias)
        putl("    \"%s\", /* Alias */", md->Alias);
    else
        putl("    NULL, /* Alias */");

    /* Schema.EntityTypes & Schema.NumEntityTypes */
    WriteArrayInitializer1(schemaAlias, "EntityTypes", nentitytypes, 1);

    /* Schema.ComplexTypes & Schema.NumComplexTypes */
    WriteArrayInitializer1(schemaAlias, "ComplexTypes", ncomplextypes, 1);

    /* Schema.EnumTypes & Schema.NumEnumTypes */
    WriteArrayInitializer1(schemaAlias, "EnumTypes", nenumtypes, 1);

    /* Schema.Actions & Schema.NumActions */
    WriteArrayInitializer1(schemaAlias, "Actions", nactions, 1);

    /* Schema.TypeDefinitions & Schema.NumTypeDefinitions */
    WriteArrayInitializer1(schemaAlias, "TypeDefinitions", ntypedefinitions, 1);

    /* Schema.EntityContainers & Schema.NumEntityContainers */
    WriteArrayInitializer1(schemaAlias, "EntityContainers", nentitycontainers, 
        1);

    /* Schema.Terms & Schema.NumTerms */
    WriteArrayInitializer1(schemaAlias, "Terms", nterms, 0);

    putl("};");
    nl();
}

void WriteDataServices(
    size_t nschemas)
{
    putl("static const EDMX_DataServices _DataServices =");
    putl("{");

    if (nschemas)
    {
        putl("    _SchemasArray, /* Schemas */");
        putl("    OL_ARRAYSIZE(_SchemasArray) /* NumSchemas */");
    }
    else
    {
        putl("    NULL, /* Schemas */");
        putl("    0 /* NumSchemas */");
    }

    putl("};");
    nl();
}

void WriteEdmx(
    const char* prefix,
    size_t nreferences)
{
    putl("const EDMX_Edmx %s_Edmx =", prefix);
    putl("{");

    if (nreferences)
    {
        putl("    _ReferencesArray, /* References */");
        putl("    OL_ARRAYSIZE(_ReferencesArray), /* NumReferences */");
    }
    else
    {
        putl("    NULL, /* References */");
        putl("    0, /* NumReferences */");
    }

    putl("    &_DataServices");

    putl("};");
    nl();
}

void WriteTerm(
    const EDM_ExtendedTerm* md,
    const char* schemaAlias)
{
    if (md->Extended)
        putl("static const EDM_ExtendedTerm _%s_%s =", schemaAlias, md->Name);
    else
        putl("static const EDM_Term _%s_%s =", schemaAlias, md->Name);

    putl("{");

    putl("    %u, /* Nullable */", md->Nullable);
    putl("    %u, /* Extended */", md->Extended);

    WriteStringInitializer("Name", md->Name, 1);
    WriteStringInitializer("Type", md->Type, md->Extended);

    if (md->Extended)
    {
        WriteStringInitializer("BaseTerm", md->BaseTerm, 1);
        WriteStringInitializer("AppliesTo", md->AppliesTo, 1);
        WriteStringInitializer("DefaultValue", md->DefaultValue, 1);
        WriteStringInitializer("MaxLength", md->MaxLength, 1);
        WriteStringInitializer("Precision", md->Precision, 1);
        WriteStringInitializer("Scale", md->Scale, 1);
        WriteStringInitializer("SRID", md->SRID, 0);
    }

    putl("};");
    nl();
}

/* <Annotation> */
/* ATTN: ignoring annotation elements for now */
void ParseAnnotation(XML* xml, XMLElem* elem)
{
    const char* term;

    if (!(term = XMLElemAttr(elem, "Term")))
        err("Missing Annotation.Term attribute");

    XMLSkip(xml);
}

/* <edmx:Term> */
void ParseTerm(
    XML* xml, 
    const char* schemaAlias,
    XMLElem* elem,
    const char** termName)
{
    XMLElem e;
    EDM_ExtendedTerm md;
    const char* s;

    memset(&md, 0, sizeof(md));

    /* Term.Name */
    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing Term.Name attribute");

    *termName = md.Name;

    /* Term.Type */
    if (!(md.Type = XMLElemAttr(elem, "Type")))
        err("Missing Term.Type attribute");

    /* Term.BaseTerm */
    if ((md.BaseTerm = XMLElemAttr(elem, "BaseTerm")))
        md.Extended = 1;

    /* Term.AppliesTo */
    if ((md.AppliesTo = XMLElemAttr(elem, "ApliesTo")))
        md.Extended = 1;

    /* Term.Nullable */
    if ((s = XMLElemAttr(elem, "Nullable")))
    {
        if (Strcasecmp(s, "true") == 0)
            md.Nullable = 1;
        else if (Strcasecmp(s, "false") == 0)
            md.Nullable = 0;
        else
            err("Bad value for Property.Nullable");
    }
    else
        md.Nullable = 1;

    /* Term.DefaultValue */
    if ((md.DefaultValue = XMLElemAttr(elem, "DefaultValue")))
        md.Extended = 1;

    /* Term.MaxLength */
    if ((md.MaxLength = XMLElemAttr(elem, "MaxLength")))
        md.Extended = 1;

    /* Term.Precision */
    if ((md.Precision = XMLElemAttr(elem, "Precision")))
        md.Extended = 1;

    /* Term.Scale */
    if ((md.Scale = XMLElemAttr(elem, "Scale")))
        md.Extended = 1;

    /* Term.SRID */
    if ((md.SRID = XMLElemAttr(elem, "SRID")))
        md.Extended = 1;

    /* Parse child elements */
    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "Term") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteTerm(&md, schemaAlias);
}

/* <edmx:Include> */
void ParseInclude(
    XML* xml, 
    XMLElem* elem,
    size_t referenceIndex,
    size_t includeIndex)
{
    EDMX_Include md;
    XMLElem e;

    memset(&md, 0, sizeof(md));

    /* Property.Namespace */
    if (!(md.Namespace = XMLElemAttr(elem, "Namespace")))
        err("Missing Property.Namespace attribute");

    /* Property.Alias */
    md.Alias = XMLElemAttr(elem, "Alias");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_END && strcmp(e.tag, "edmx:Include") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteInclude(&md, referenceIndex, includeIndex);
}

/* <edmx:IncludeAnnotations> */
void ParseIncludeAnnotations(
    XML* xml, 
    XMLElem* elem,
    size_t referenceIndex,
    size_t includeAnnotationsIndex)
{
    EDMX_IncludeAnnotations md;
    XMLElem e;

    memset(&md, 0, sizeof(md));

    /* Property.Namespace */
    if (!(md.TermNamespace = XMLElemAttr(elem, "TermNamespace")))
        err("Missing Property.TermNamespace attribute");

    /* Property.Qualifier */
    md.Qualifier = XMLElemAttr(elem, "Qualifier");

    /* Property.TargetNamespace */
    md.TargetNamespace = XMLElemAttr(elem, "TargetNamespace");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_END && strcmp(e.tag, "edmx:IncludeAnnotations") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteIncludeAnnotations(&md, referenceIndex, includeAnnotationsIndex);
}

/* <edmx:Reference> */
void ParseReference(
    XML* xml, 
    XMLElem* elem, 
    size_t referenceIndex)
{
    EDMX_Reference md;
    XMLElem e;
    size_t includeIndex = 0;
    size_t includeAnnotationsIndex = 0;

    memset(&md, 0, sizeof(md));

    /* Reference.Uri */
    if (!(md.Uri = XMLElemAttr(elem, "Uri")))
        err("Missing Property.Uri attribute");

    /* Reference elements */
    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "edmx:Include") == 0)
        {
            ParseInclude(xml, &e, referenceIndex, includeIndex);
            includeIndex++;
        }
        else if (e.type == XML_START && 
            strcmp(e.tag, "edmx:IncludeAnnotations") == 0)
        {
            ParseIncludeAnnotations(xml, &e, referenceIndex, 
                includeAnnotationsIndex);
            includeAnnotationsIndex++;
        }
        else if (e.type == XML_END && strcmp(e.tag, "edmx:Reference") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    /* Reference.Includes */
    if (includeIndex)
    {
        size_t i;

        putl("static const EDMX_Include* _%u_IncludesArray[] =",
            (int)referenceIndex);

        putl("{");

        for (i = 0; i < includeIndex; i++)
        {
            put("    &_%u_%u_Include", (int)referenceIndex, (int)i);

            if (i + 1 != includeIndex)
                put(",");

            nl();
        }

        putl("};");
        nl();
    }

    /* Reference.IncludeAnnotations */
    if (includeAnnotationsIndex)
    {
        size_t i;

        putl("static const EDMX_IncludeAnnotations* "
            "_%u_IncludeAnnotationsArray[] =", (int)referenceIndex);

        putl("{");

        for (i = 0; i < includeAnnotationsIndex; i++)
        {
            put("    &_%u_%u_IncludeAnnotations", (int)referenceIndex, (int)i);

            if (i + 1 != includeAnnotationsIndex)
                put(",");

            nl();
        }

        putl("};");
        nl();
    }

    WriteReference(&md, referenceIndex, includeIndex, includeAnnotationsIndex);
}

/* <Singleton> */
void ParseSingleton(
    XML* xml, 
    XMLElem* elem,
    const char* parentName,
    const char** name)
{
    XMLElem e;
    EDM_Singleton md;

    memset(&md, 0, sizeof(md));

    /* Singleton.Name */
    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing Singleton.Name attribute");

    *name = md.Name;

    /* Singleton.Type */
    if (!(md.Type = XMLElemAttr(elem, "Type")))
        err("Missing Singleton.Type attribute");

    /* Process elements */
    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "Singleton") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteSingleton(parentName, &md);
}

/* <edmx:EntityContainer> */
void ParseEntityContainer(
    XML* xml, 
    XMLElem* elem,
    const char* schemaAlias,
    const char** entityContainerName)
{
    XMLElem e;
    EDM_EntityContainer md;
    PtrArray singletons;

    PtrArray_Construct(&singletons, 8, Free);

    memset(&md, 0, sizeof(md));

    /* EntityContainer.Name */
    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing EntityContainer.Name attribute");

    *entityContainerName = md.Name;

    /* EntityContainer.Extends */
    md.Extends = XMLElemAttr(elem, "Extends");

    /* Process elements */
    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "Singleton") == 0)
        {
            const char* singletonName;
            ParseSingleton(xml, &e, md.Name, &singletonName);
            PtrArray_Append(&singletons, Strdup(singletonName));
        }
        else if (e.type == XML_END && strcmp(e.tag, "EntityContainer") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteArray1(md.Name, "Singleton", "Singletons", (char**)singletons.data, 
        singletons.size);

    WriteEntityContainer(&md, schemaAlias, singletons.size);

    PtrArray_Destruct(&singletons);
}

/* <Property> */
void ParseProperty(
    XML* xml,
    const char* schemaAlias,
    const char* entityTypeName,
    XMLElem* elem)
{
    XMLElem e;
    EDM_ExtendedProperty md;
    const char* s;

    memset(&md, 0, sizeof(md));

    /* Property.Name */
    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing Property.Name attribute");

    /* Property.Type */
    if (!(md.Type = XMLElemAttr(elem, "Type")))
        err("Missing Property.Type attribute");

    /* Property.Nullable */
    if ((s = XMLElemAttr(elem, "Nullable")))
    {
        if (Strcasecmp(s, "true") == 0)
            md.Nullable = 1;
        else if (Strcasecmp(s, "false") == 0)
            md.Nullable = 0;
        else
            err("Bad value for Property.Nullable");
    }
    else
        md.Nullable = 1;

    /* Property.MaxLength */
    if ((md.MaxLength = XMLElemAttr(elem, "MaxLength")))
        md.Extended = 1;

    /* Property.Precision */
    if ((md.MaxLength = XMLElemAttr(elem, "Precision")))
        md.Extended = 1;

    /* Property.Scale */
    if ((md.Scale = XMLElemAttr(elem, "Scale")))
        md.Extended = 1;

    /* Property.Unicode */
    if ((md.Unicode = XMLElemAttr(elem, "Unicode")))
        md.Extended = 1;

    /* Property.SRID */
    if ((md.SRID = XMLElemAttr(elem, "SRID")))
        md.Extended = 1;

    /* Property.DefaultValue */
    if ((md.DefaultValue = XMLElemAttr(elem, "DefaultValue")))
        md.Extended = 1;

    WriteProperty(schemaAlias, entityTypeName, &md);

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "Property") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }
}

/* <NavigationProperty> */
void ParseNavigationProperty(
    XML* xml,
    const char* schemaAlias,
    const char* entityTypeName,
    XMLElem* elem)
{
    XMLElem e;
    EDM_NavigationProperty md;
    const char* s;

    memset(&md, 0, sizeof(md));

    /* NavigationProperty.Name */
    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing NavigationProperty.Name attribute");

    /* NavigationProperty.Type */
    if (!(md.Type = XMLElemAttr(elem, "Type")))
        err("Missing NavigationProperty.Type attribute");

    /* NavigationProperty.Partner */
    md.Partner = XMLElemAttr(elem, "Partner");

    /* NavigationProperty.Nullable */
    if ((s = XMLElemAttr(elem, "Nullable")))
    {
        if (Strcasecmp(s, "true") == 0)
            md.Flags |= EDM_NavigationProperty_Flags_Nullable;
        else if (Strcasecmp(s, "false") != 0)
            err("Bad value for NavigationProperty.Nullable attribute");
    }
    else
    {
        md.Flags |= EDM_NavigationProperty_Flags_Nullable;
    }

    /* NavigationProperty.ContainsTarget */
    if ((s = XMLElemAttr(elem, "ContainsTarget")))
    {
        if (Strcasecmp(s, "true") == 0)
            md.Flags |= EDM_NavigationProperty_Flags_ContainsTarget;
        else if (Strcasecmp(s, "false") != 0)
            err("Bad value for NavigationProperty.ContainsTarget attribute");
    }

    WriteNavigationProperty(schemaAlias, entityTypeName, &md);

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "NavigationProperty") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }
}

/* <PropertyRef> */
void ParsePropertyRef(
    XML* xml,
    XMLElem* elem,
    EDM_PropertyRef* md)
{
    XMLElem e;

    memset(md, 0, sizeof(EDM_PropertyRef));

    if (!(md->Name = XMLElemAttr(elem, "Name")))
        errl(elem->line, "Missing PropertyRef.Name attribute");

    md->Alias = XMLElemAttr(elem, "Alias");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_END && strcmp(e.tag, "PropertyRef") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }
}

/* <Key> */
void ParseKey(
    XML* xml,
    const char* schemaAlias,
    const char* entityTypeName,
    XMLElem* elem)
{
    XMLElem e;
    EDM_Key md;

    memset(&md, 0, sizeof(md));

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "PropertyRef") == 0)
        {
            ParsePropertyRef(xml, &e, &md.PropertyRef);
        }
        else if (e.type == XML_END && strcmp(e.tag, "Key") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteKey(&md, schemaAlias, entityTypeName);
}

/* <EntityType> */
void ParseEntityType(
    XML* xml, 
    const char* schemaAlias,
    XMLElem* elem)
{
    XMLElem e;
    PtrArray properties;
    PtrArray navigationproperties;
    size_t nkeys = 0;
    EDM_EntityType md;

    PtrArray_Construct(&properties, 8, Free);
    PtrArray_Construct(&navigationproperties, 8, Free);

    memset(&md, 0, sizeof(md));

    /* EntityType.Name */
    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing EntityType.Name attribute");

    /* EntityType.BaseType */
    md.BaseType = XMLElemAttr(elem, "BaseType");

    /* EntityType.Abstract */
    md.Abstract = XMLElemAttr(elem, "Abstract");

    /* EntityType.OpenType */
    md.OpenType = XMLElemAttr(elem, "OpenType");

    /* EntityType.HasStream */
    md.HasStream = XMLElemAttr(elem, "HasStream");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "Key") == 0)
        {
            if (nkeys > 0)
                errl(e.line, "too many 'Key' elements");

            ParseKey(xml, schemaAlias, md.Name, &e);
            nkeys++;
        }
        else if (e.type == XML_START && strcmp(e.tag, "Property") == 0)
        {
            const char* s;

            if (!(s = XMLElemAttr(&e, "Name")))
                err("Missing Property.Name attribute");

            PtrArray_Append(&properties, Strdup(s));

            ParseProperty(xml, schemaAlias, md.Name, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "NavigationProperty")== 0)
        {
            const char* s;

            if (!(s = XMLElemAttr(&e, "Name")))
                err("Missing Property.Name attribute");

            PtrArray_Append(&navigationproperties, Strdup(s));

            ParseNavigationProperty(xml, schemaAlias, md.Name, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "EntityType") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteArray2(schemaAlias, md.Name, "Property", "Properties", 
        (char**)properties.data, properties.size);

    WriteArray2(schemaAlias, md.Name, "NavigationProperty", 
        "NavigationProperties", (char**)navigationproperties.data, 
            navigationproperties.size);

    WriteEntityType(schemaAlias, &md, nkeys, properties.size, 
        navigationproperties.size);

    PtrArray_Destruct(&properties);
    PtrArray_Destruct(&navigationproperties);
}

/* <ComplexType> */
void ParseComplexType(
    XML* xml, 
    const char* schemaAlias,
    XMLElem* elem)
{
    XMLElem e;
    PtrArray properties;
    PtrArray navigationproperties;
    EDM_ComplexType md;

    memset(&md, 0, sizeof(md));

    PtrArray_Construct(&properties, 8, Free);
    PtrArray_Construct(&navigationproperties, 8, Free);

    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing ComplexType.Name attribute");

    /* EntityType.BaseType */
    md.BaseType = XMLElemAttr(elem, "BaseType");

    /* EntityType.Abstract */
    md.Abstract = XMLElemAttr(elem, "Abstract");

    /* EntityType.OpenType */
    md.OpenType = XMLElemAttr(elem, "OpenType");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "Property") == 0)
        {
            const char* s;

            if (!(s = XMLElemAttr(&e, "Name")))
                err("Missing Property.Name attribute");

            PtrArray_Append(&properties, Strdup(s));

            ParseProperty(xml, schemaAlias, md.Name, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "NavigationProperty")== 0)
        {
            const char* s;

            if (!(s = XMLElemAttr(&e, "Name")))
                err("Missing Property.Name attribute");

            PtrArray_Append(&navigationproperties, Strdup(s));

            ParseNavigationProperty(xml, schemaAlias, md.Name, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "ComplexType") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteArray2(schemaAlias, md.Name, "Property", "Properties", 
        (char**)properties.data, properties.size);

    WriteArray2(schemaAlias, md.Name, "NavigationProperty", 
        "NavigationProperties", (char**)navigationproperties.data, 
        navigationproperties.size);

    WriteComplexType(schemaAlias, &md, properties.size,
        navigationproperties.size);

    PtrArray_Destruct(&properties);
    PtrArray_Destruct(&navigationproperties);
}

/* <Member> */
void ParseMember(
    XML* xml, 
    const char* schemaAlias,
    const char* enumTypeName,
    XMLElem* elem,
    PtrArray* memberStructs,
    int* hasValues)
{
    XMLElem e;
    EDM_Member md;

    *hasValues = 0;

    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing Member.Name attribute");

    md.Value = XMLElemAttr(elem, "Value");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "Member") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    /* Append member to the array */
    {
        EDM_Member* member = (EDM_Member*)Calloc(1, sizeof(EDM_Member));

        if (md.Name)
            member->Name = Strdup(md.Name);

        if (md.Value)
            member->Value = Strdup(md.Value);

        PtrArray_Append(memberStructs, member);
    }
}

void DeleteMember(void* data)
{
    EDM_Member* member = (EDM_Member*)data;
    Free((char*)member->Name);
    Free((char*)member->Value);
    Free(member);
}

/* <EnumType> */
void ParseEnumType(
    XML* xml, 
    const char* schemaAlias,
    XMLElem* elem)
{
    XMLElem e;
    EDM_EnumType md;
    PtrArray members;
    PtrArray memberStructs;
    const char* s;
    int hasValues = 0;
    size_t i;

    PtrArray_Construct(&members, 8, Free);
    PtrArray_Construct(&memberStructs, 8, DeleteMember);

    memset(&md, 0, sizeof(md));

    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing Member.Name attribute");

    md.IsFlags = XMLElemAttr(elem, "IsFlags");

    md.UnderlyingType = XMLElemAttr(elem, "UnderlyingType");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "Member") == 0)
        {
            char* dup;

            if (!(s = XMLElemAttr(&e, "Name")))
                err("missing Member.Name attribute");

            dup = Strdup(s);

            PtrArray_Append(&members, dup);
            FixupName(dup);

            ParseMember(xml, schemaAlias, md.Name, &e, &memberStructs,
                &hasValues);
        }
        else if (e.type == XML_END && strcmp(e.tag, "EnumType") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    if (hasValues)
    {
        for (i = 0; i < memberStructs.size; i++)
        {
            EDM_Member* member = (EDM_Member*)memberStructs.data[i];
            WriteMember(schemaAlias, md.Name, member);
        }

        WriteArray2(schemaAlias, md.Name, "Member", "Members", 
            (char**)members.data, members.size);
    }
    else
    {
        putl("static const char* _%s_%s_MembersArray[] =", schemaAlias, 
            md.Name);
        putl("{");

        for (i = 0; i < memberStructs.size; i++)
        {
            EDM_Member* member = (EDM_Member*)memberStructs.data[i];

            put("    \"%s\"", member->Name);

            if (i + 1 != memberStructs.size)
                put(",");

            nl();
        }

        putl("};");
        nl();
    }

    WriteEnumType(schemaAlias, &md, members.size, hasValues);

    PtrArray_Destruct(&members);
    PtrArray_Destruct(&memberStructs);
}

/* <Parameter> */
void ParseParameter(
    XML* xml, 
    const char* schemaAlias,
    const char* enumTypeName,
    XMLElem* elem)
{
    XMLElem e;
    EDM_Parameter md;

    memset(&md, 0, sizeof(md));

    /* Parameter.Name */
    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing Parameter.Name attribute");

    /* Parameter.Type */
    if (!(md.Type = XMLElemAttr(elem, "Type")))
        err("Missing Parameter.Type attribute");

    /* Parameter.Nullable */
    md.Nullable = XMLElemAttr(elem, "Nullable");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "Parameter") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteParameter(schemaAlias, enumTypeName, &md);
}

/* <Action> */
void ParseAction(
    XML* xml, 
    const char* schemaAlias,
    XMLElem* elem)
{
    XMLElem e;
    EDM_Action md;
    PtrArray parameters;
    const char* s;

    PtrArray_Construct(&parameters, 8, Free);

    memset(&md, 0, sizeof(md));

    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing Member.Name attribute");

    md.EntitySetPath = XMLElemAttr(elem, "EntitySetPath");

    md.IsBound = XMLElemAttr(elem, "IsBound");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "Parameter") == 0)
        {
            if (!(s = XMLElemAttr(&e, "Name")))
                err("missing Member.Name attribute");

            PtrArray_Append(&parameters, Strdup(s));

            ParseParameter(xml, schemaAlias, md.Name, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "Action") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteArray2(schemaAlias, md.Name, "Parameter", "Parameters", 
        (char**)parameters.data, parameters.size);

    WriteAction(schemaAlias, &md, parameters.size);

    PtrArray_Destruct(&parameters);
}

/* <TypeDefinition> */
void ParseTypeDefinition(
    XML* xml, 
    const char* schemaAlias,
    XMLElem* elem)
{
    XMLElem e;
    EDM_TypeDefinition md;

    memset(&md, 0, sizeof(md));

    if (!(md.Name = XMLElemAttr(elem, "Name")))
        err("Missing Member.Name attribute");

    md.UnderlyingType = XMLElemAttr(elem, "UnderlyingType");

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Annotation") == 0)
        {
            ParseAnnotation(xml, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "TypeDefinition") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteTypeDefinition(schemaAlias, &md);
}

#define ALIAS_SIZE 128

/* <Schema> */
void ParseSchema(
    XML* xml, 
    XMLElem* elem,
    char alias[ALIAS_SIZE])
{
    XMLElem e;
    const char* s;
    EDM_Schema md;
    PtrArray entitytypes;
    PtrArray complextypes;
    PtrArray enumtypes;
    PtrArray actions;
    PtrArray typedefinitions;
    PtrArray entitycontainers;
    PtrArray terms;

    memset(&md, 0, sizeof(md));

    PtrArray_Construct(&entitytypes, 8, Free);
    PtrArray_Construct(&complextypes, 8, Free);
    PtrArray_Construct(&enumtypes, 8, Free);
    PtrArray_Construct(&actions, 8, Free);
    PtrArray_Construct(&typedefinitions, 8, Free);
    PtrArray_Construct(&entitycontainers, 8, Free);
    PtrArray_Construct(&terms, 8, Free);

    if (!(md.Namespace = XMLElemAttr(elem, "Namespace")))
        err("Missing Schema.Namespace attribute");

    if ((md.Alias = XMLElemAttr(elem, "Alias")))
    {
        Strlcpy(alias, md.Alias, ALIAS_SIZE);
    }
    else
    {
        char* p;
        Strlcpy(alias, md.Namespace, ALIAS_SIZE);

        if ((p = strchr(alias, '.')))
            *p = '\0';
    }

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Term") == 0)
        {
            const char* termName;
            ParseTerm(xml, alias, &e, &termName);
            PtrArray_Append(&terms, Strdup(termName));
        }
        else if (e.type == XML_START && strcmp(e.tag, "EntityContainer") == 0)
        {
            const char* enityContainerName;
            ParseEntityContainer(xml, &e, alias, &enityContainerName);
            PtrArray_Append(&entitycontainers, Strdup(enityContainerName));
        }
        else if (e.type == XML_START && strcmp(e.tag, "EntityType") == 0)
        {
            if (!(s = XMLElemAttr(&e, "Name")))
                err("missing EntityType.Name attribute");

            PtrArray_Append(&entitytypes, Strdup(s));

            ParseEntityType(xml, alias, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "ComplexType") == 0)
        {
            if (!(s = XMLElemAttr(&e, "Name")))
                err("missing ComplexType.Name attribute");

            PtrArray_Append(&complextypes, Strdup(s));

            ParseComplexType(xml, alias, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "EnumType") == 0)
        {
            if (!(s = XMLElemAttr(&e, "Name")))
                err("missing EnumType.Name attribute");

            PtrArray_Append(&enumtypes, Strdup(s));

            ParseEnumType(xml, alias, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "Action") == 0)
        {
            if (!(s = XMLElemAttr(&e, "Name")))
                err("missing Action.Name attribute");

            PtrArray_Append(&actions, Strdup(s));

            ParseAction(xml, alias, &e);
        }
        else if (e.type == XML_START && strcmp(e.tag, "TypeDefinition") == 0)
        {
            if (!(s = XMLElemAttr(&e, "Name")))
                err("missing Action.Name attribute");

            PtrArray_Append(&typedefinitions, Strdup(s));

            ParseTypeDefinition(xml, alias, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "Schema") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    WriteArray1(alias, "EntityType", "EntityTypes", (char**)entitytypes.data, 
        entitytypes.size);

    WriteArray1(alias, "ComplexType", "ComplexTypes", (char**)complextypes.data,
        complextypes.size);

    WriteArray1(alias, "EnumType", "EnumTypes", (char**)enumtypes.data, 
        enumtypes.size);

    WriteArray1(alias, "Action", "Actions", (char**)actions.data, actions.size);

    WriteArray1(alias, "TypeDefinition", "TypeDefinitions", 
        (char**)typedefinitions.data, typedefinitions.size);

    WriteArray1(alias, "EntityContainer", "EntityContainers", 
        (char**)entitycontainers.data, entitycontainers.size);

    WriteArray1(alias, "Term", "Terms", (char**)terms.data, terms.size);

    WriteSchema(alias, &md, entitytypes.size, complextypes.size, enumtypes.size,
        actions.size, typedefinitions.size, entitycontainers.size,
        terms.size);

    PtrArray_Destruct(&entitytypes);
    PtrArray_Destruct(&complextypes);
    PtrArray_Destruct(&enumtypes);
    PtrArray_Destruct(&actions);
    PtrArray_Destruct(&typedefinitions);
    PtrArray_Destruct(&entitycontainers);
    PtrArray_Destruct(&terms);
}

/* <edmx:DataServices> */
void ParseDataServices(
    XML* xml, 
    XMLElem* elem)
{
    XMLElem e;
    char alias[ALIAS_SIZE];
    PtrArray schemas;

    PtrArray_Construct(&schemas, 8, Free);

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "Schema") == 0)
        {
            ParseSchema(xml, &e, alias);

            PtrArray_Append(&schemas, Strdup(alias));
        }
        else if (e.type == XML_END && strcmp(e.tag, "edmx:DataServices") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    /* Schemas array */
    if (schemas.size)
    {
        size_t i;

        putl("static const EDM_Schema* _SchemasArray[] =");

        putl("{");

        for (i = 0; i < schemas.size; i++)
        {
            put("    &_%s_Schema", (const char*)schemas.data[i]);

            if (i + 1 != schemas.size)
                put(",");

            nl();
        }

        putl("};");
        nl();
    }

    WriteDataServices(schemas.size);
    PtrArray_Destruct(&schemas);
}

/* <edmx:Edmx> */
void ParseEdmx(
    XML* xml, 
    XMLElem* elem,
    const char* prefix)
{
    XMLElem e;
    size_t referenceIndex = 0;

    while (XMLNext(xml, &e) == 0)
    {
        if (e.type == XML_START && strcmp(e.tag, "edmx:Reference") == 0)
        {
            ParseReference(xml, &e, referenceIndex);
            referenceIndex++;
        }
        else if (e.type == XML_START && strcmp(e.tag, "edmx:DataServices") == 0)
        {
            ParseDataServices(xml, &e);
        }
        else if (e.type == XML_END && strcmp(e.tag, "edmx:Edmx") == 0)
        {
            break;
        }
        else
        {
            errl(e.line, "unexpected element: %s", e.tag);
        }
    }

    /* References array */
    if (referenceIndex)
    {
        size_t i;

        putl("static const EDMX_Reference* _ReferencesArray[] =");

        putl("{");

        for (i = 0; i < referenceIndex; i++)
        {
            put("    &_%u_Reference", (int)i);

            if (i + 1 != referenceIndex)
                put(",");

            nl();
        }

        putl("};");
        nl();
    }

    WriteEdmx(prefix, referenceIndex);
}

void Parse(XML* xml, const char* prefix)
{
    XMLElem e;

    WritePreamble();

    if (XMLExpectStart(xml, "edmx:Edmx", &e) != 0)
        err("expected 'edmx:Edmx' start tag");

    ParseEdmx(xml, &e, prefix);
}

void MakeOutputFilename(char filename[MAX_PATH_SIZE], const char* path)
{
    char* dot;

    Strlcpy(filename, Basename(path), MAX_PATH_SIZE);

    if ((dot = strchr(filename, '.')))
        *dot = '\0';

    Strlcat(filename, ".c", MAX_PATH_SIZE);
}

void MakePrefix(char prefix[MAX_PATH_SIZE], const char* filename)
{
    char* dot;

    Strlcpy(prefix, filename, MAX_PATH_SIZE);

    if ((dot = strchr(prefix, '.')))
        *dot = '\0';
}

void ParseFile(const char* path)
{
    XML* xml;
    char* data;
    size_t size;
    char filename[MAX_PATH_SIZE];
    char prefix[MAX_PATH_SIZE];

    MakeOutputFilename(filename, path);
    MakePrefix(prefix, filename);

    /* Open the output file */
    if (!(_os = fopen(filename, "w")))
        err("failed to open '%s' for write", filename);

    s_path = path;

    /* Create xml object */
    if (!(xml = XMLNew()))
    {
        err("XMLNew() failed");
        exit(1);
    }

    /* Load the input file */
    if (FileLoad(path, NULL, &data, &size) != 0)
    {
        err("failed to read: %s", path);
        exit(1);
    }

    /* Parse the data */
    if (XMLParse(xml, data, size) != 0)
    {
        err("error: %s(%u): %s", path, (int)XMLGetLine(xml), XMLErr(xml));
        XMLDelete(xml);
        Free(data);
        exit(1);
    }

    /* Parse the document */
    Parse(xml, prefix);
    
#if 0
    XMLDump(xml);
#endif

    /* Release the xml */
    XMLDelete(xml);

    /* Free memory */
    Free(data);

    /* Close the output file */
    printf("Created %s\n", filename);
    fclose(_os);
}

int main(int argc, char** argv)
{
    int i;

    s_arg0 = argv[0];

    /* Check parameters */
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s FILES...\n", argv[0]);
        exit(1);
    }

    for (i = 1; i < argc; i++)
        ParseFile(argv[i]);

    return 0;
}
