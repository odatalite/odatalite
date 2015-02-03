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
#ifndef _odata_serialize_h
#define _odata_serialize_h

#include "json.h"
#include "odata.h"
#include "jsonobject.h"
#include <base/buf.h>

OL_Result SerializeElement(
    Buf* out,
    const JSON_Value* v,
    size_t depth,
    OL_MetadataType metadataType);

OL_Result SerializeObject(
    const JSONObject* self,
    const char* contextURI,
    Buf* out,
    size_t depth,
    int indentOpeningBrace,
    OL_MetadataType metadataType,
    const char* propertyName);

OL_Result Object_Serialize(
    const JSON_Object* self,
    JSON_OutStream* outStream,
    size_t depth);

OL_Result SerializeRawPrimitiveValue(
    Buf* out,
    const OL_Value* value);

#endif /* _odata_serialize_h */
