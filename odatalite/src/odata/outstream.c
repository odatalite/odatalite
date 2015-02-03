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
#include "outstream.h"

static OL_Result _Put(
    JSON_OutStream* self_,
    const OL_Char* data,
    size_t size)
{
    OutStream* self = (OutStream*)self_;

    BufCat(self->out, data, size);

    return self->out->err ?  OL_Result_Failed : OL_Result_Ok;
}

JSON_OutStreamFT __OutStreamFT =
{
    _Put
};

void OutStreamInit(
    OutStream* self)
{
    /* OutStream.base.ft */
    self->base.ft = &__OutStreamFT;

    /* OutStream.alloc */
    AllocInit(&self->alloc, self->allocBuf, sizeof(self->allocBuf));

    /* OutStream.buf */
    BufInit(&self->buf, &self->alloc);
    BufReserve(&self->buf, sizeof(self->allocBuf));

    /* OutStream.out*/
    self->out = &self->buf;
}

void OutStreamInitFromBuf(
    OutStream* self,
    Buf* out)
{
    /* OutStream.base.ft */
    self->base.ft = &__OutStreamFT;

    /* OutStream.out*/
    self->out = out;
}
