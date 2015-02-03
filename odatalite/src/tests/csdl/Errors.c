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
#include <odata/odata.h>

static const EDM_Term _Error_severity =
{
    1, /* Nullable */
    0, /* Extended */
    "severity", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Term _Error_resolution =
{
    1, /* Nullable */
    0, /* Extended */
    "resolution", /* Name */
    "Edm.String" /* Type */
};

static const EDM_Term* _Error_TermsArray[] =
{
    (const EDM_Term*)&_Error_severity,
    (const EDM_Term*)&_Error_resolution
};

static const EDM_Schema _Error_Schema =
{
    "Errors.0.9.2", /* Namespace */
    "Error", /* Alias */
    NULL, /* EntityTypes */
    0, /* NumEntityTypes */
    NULL, /* ComplexTypes */
    0, /* NumComplexTypes */
    NULL, /* EnumTypes */
    0, /* NumEnumTypes */
    NULL, /* Actions */
    0, /* NumActions */
    NULL, /* TypeDefinitions */
    0, /* NumTypeDefinitions */
    NULL, /* EntityContainers */
    0, /* NumEntityContainers */
    _Error_TermsArray,
    OL_ARRAYSIZE(_Error_TermsArray)
};

static const EDM_Schema* _SchemasArray[] =
{
    &_Error_Schema
};

static const EDMX_DataServices _DataServices =
{
    _SchemasArray, /* Schemas */
    OL_ARRAYSIZE(_SchemasArray) /* NumSchemas */
};

const EDMX_Edmx Errors_Edmx =
{
    NULL, /* References */
    0, /* NumReferences */
    &_DataServices
};

