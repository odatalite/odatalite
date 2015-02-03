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
#include "base64.h"

/* Indexed by 6-bit integer */
static const char _base64CharacterSet[] =
{
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P', 
    'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f', 
    'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v', 
    'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/',
};

INLINE char ToBase64Char(char c)
{
    return _base64CharacterSet[(unsigned char)c];
}

size_t Base64Enc(
    Base64EncState* state,
    const void* data_,
    size_t size_,
    char* dataOut,
    size_t sizeOut)
{
    switch (state->state)
    {
        case 0:
        {
            state->data = (unsigned char*)data_;
            state->size = size_;
            state->offset = 0;
            goto state0;
        }
        case 1:
        {
            goto state1;
        }
        default:
        {
            goto state2;
        }
    }

state0:

    while (state->size)
    {
        memset(state->chars, 0, sizeof(state->chars));
        state->numEncoded = 0;
        state->finished = 0;

        if (state->offset + 4 > sizeOut)
        {
            size_t offset = state->offset;
            state->state = 1;
            state->offset = 0;
            return offset;
        }

state1:

        /* Encode the next 3 bytes into 4 bytes */

        /* Handle first byte */
        {
            state->chars[0] |= (state->data[0] & 0xFC) >> 2;
            state->chars[1] |= (state->data[0] & 0x03) << 4;
            dataOut[state->offset++] = ToBase64Char(state->chars[0]);
            state->data++;
            state->size--;
            state->numEncoded++;
        }

        /* Handle second byte */
        if (state->size)
        {

            state->chars[1] |= (state->data[0] & 0xF0) >> 4;
            state->chars[2] |= (state->data[0] & 0x0F) << 2;
            dataOut[state->offset++] = ToBase64Char(state->chars[1]);
            state->data++;
            state->size--;
            state->numEncoded++;
        }
        else
        {
            dataOut[state->offset++] = ToBase64Char(state->chars[1]);
            state->finished = 1;
        }

        /* Handle third byte */
        if (state->size)
        {
            state->chars[2] |= (state->data[0] & 0xCF) >> 6;
            state->chars[3] |= state->data[0] & 0x3F;
            dataOut[state->offset++] = ToBase64Char(state->chars[2]);
            dataOut[state->offset++] = ToBase64Char(state->chars[3]);
            state->data++;
            state->size--;
            state->numEncoded++;
        }
        else if (!state->finished)
        {
            dataOut[state->offset++] = ToBase64Char(state->chars[2]);
        }

        /* If less than 3 bytes encoded, then pad up to next multiple of 3 */
        if (state->numEncoded < 3)
        {
            size_t n = 3 - state->numEncoded;
            memset(&dataOut[state->offset], '=', n);
            state->offset += n;
        }
    }

    /* If any bytes were encoded, then return number encoded */
    if (state->offset)
    {
        state->state = 2;
        return state->offset;
    }

state2:

    return 0;
}
