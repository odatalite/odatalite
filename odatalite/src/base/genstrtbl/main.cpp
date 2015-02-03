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
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector> 
#include <fstream> 
#include <cctype> 

using namespace std;

int main(int argc, char** argv)
{
    size_t i;
    string str;
    string offStr;
    size_t off = 0;
    char buf[1024];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
        exit(1);
    }

    ifstream is(argv[1], ios::binary);

    if (!is)
    {
        fprintf(stderr, "%s: failed to open file\n", argv[0]);
        exit(1);
    }

    string line;
    vector<string> arr;

    while (getline(is, line))
    {
        while (line.size() && isspace(line[line.size()-1]))
            line.erase(line.size()-1);
        arr.push_back(line);
    }

    vector<string> strArr;

    for (i = 0; i < arr.size(); i++)
    {
        {
            const char* s = arr[i].c_str();
            sprintf(buf, "\\\%03o%s", (int)strlen(s), s);

            strcat(buf, "\\0");
            strArr.push_back(buf);

            assert(strncmp(s, buf+4, strlen(s)) == 0);

            sprintf(buf, "    0x%02X, /* '%s' */\n", (int)off, s);
            offStr += buf;
            off += strlen(s) + 2;
        }
    }

    printf("static const char* _arr =\n");

    for (size_t i = 0; i < strArr.size(); i++)
    {
        printf("    \"%s\"", strArr[i].c_str());

        if (i + 1 == strArr.size())
            printf(";");

        printf("\n");
    }

    printf("\n");

    if (off <= 0xFF)
        printf("static const unsigned char _off[] =\n");
    else if (off <= 0xFFFF)
        printf("static const unsigned short _off[] =\n");
    else
        printf("static const unsigned int _off[] =\n");

    printf("{\n");
    printf("%s", offStr.c_str());
    printf("};\n");

    return 0;
}
