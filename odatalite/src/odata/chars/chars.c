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
#include <ctype.h>
#include <string.h>

void gen()
{
    int i;

    for (i = 0; i < 256; i++)
    {
        unsigned char x = 0;

        /* IsEscapeChar */
        switch (i)
        {
            case '"':
                x |= 1;
                break;
            case '\\':
                x |= 1;
                break;
            case '\b':
                x |= 1;
                break;
            case '\f':
                x |= 1;
                break;
            case '\n':
                x |= 1;
                break;
            case '\r':
                x |= 1;
                break;
            case '\t':
                x |= 1;
                break;
            default:
            {
                if (!isprint(i))
                    x |= 1;
                break;
            }
        }

        /* IsNumberChar */
        if (isdigit(i) || i=='-' || i=='+' || i=='e' || i=='E' || i=='.')
            x |= 2;

        /* IsDecimalOrExponent */
        if (i=='.' || i=='e' || i=='E')
            x |= 4;

        /* IsNotPercentOrZero */
        if (i != '%' && i != '\0')
            x |= 8;

        /* IsNotSlashOrZero */
        if (i != '/' && i != '\0')
            x |= 16;

        /* IsNotSlashQuesLeftParenOrZero */
        if (i != '/' && i != '?' && i != '(' && i != '\0')
            x |= 32;

        printf("0x%02X, ", x);

        if ((i + 1) % 8 == 0)
            printf("\n");
    }
}

int main()
{
    gen();
    return 0;
}
