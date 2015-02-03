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
#include <string.h>

int main()
{
    int c;

    for (c = 0; c < 256; c++)
    {
        unsigned char x = 0;

        if (isspace(c))
        {
            x |= 1;
        }
        if (c && !isspace(c))
        {
            x |= 2;
        }
        if (isalnum(c) || c == '_')
        {
            x |= 4;
        }
        if (c == '\r' || c == '\n')
        {
            x |= 8;
        }
        if (c == '(' || c == ')' || c == '<' || c == '>' || c == '@' || 
            c == ',' || c == ';' || c == ':' || c == '\\' || c == '"' || 
            c == '/' || c == '[' || c == ']' || c == '?' || c == '=' || 
            c == '{' || c == '}' || c == ' ' || c == '\t')
        {
            /* HTTP Separators */
            x |= 16;
        }
        if (c == ' ' || c == '\t')
        {
            /* LWS */
            x |= 32;
        }
        if (c && c != ';' && c != ' ' && c != '\t')
        {
            x |= 64;
        }
        if ((c >= 0 && c <= 31) || c == 127)
        {
            /* HTTP CTL */
            x |= 128;
        }

        printf("0x%02x, ", x);

        if ((c + 1) % 8 == 0)
            printf("\n");
    }

    return 0;
}
