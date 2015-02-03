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
#ifndef _strings_h
#define _strings_h

static const char _Frog_Id[] = "\002Id";
#define Frog_Id (&_Frog_Id[1])
#define Frog_Id_Code 0x00496402
#define Frog_Id_Len 2

static const char _Frog_UserName[] = "\010UserName";
#define Frog_UserName (&_Frog_UserName[1])
#define Frog_UserName_Code 0x00556508
#define Frog_UserName_Len 8

static const char _Frog_First[] = "\005First";
#define Frog_First (&_Frog_First[1])
#define Frog_First_Code 0x00467405
#define Frog_First_Len 5

static const char _Frog_Last[] = "\004Last";
#define Frog_Last (&_Frog_Last[1])
#define Frog_Last_Code 0x004C7404
#define Frog_Last_Len 4

static const char _Frog_Color[] = "\005Color";
#define Frog_Color (&_Frog_Color[1])
#define Frog_Color_Code 0x00437205
#define Frog_Color_Len 5

static const char _Frog_Birthdate[] = "\011Birthdate";
#define Frog_Birthdate (&_Frog_Birthdate[1])
#define Frog_Birthdate_Code 0x00426509
#define Frog_Birthdate_Len 9

static const char _Frog_Friend[] = "\033Friend@odata.navigationLink";
#define Frog_Friend (&_Frog_Friend[1])
#define Frog_Friend_Code 0x00466B1B
#define Frog_Friend_Len 27

static const char _Frog_Binary[] = "\006Binary";
#define Frog_Binary (&_Frog_Binary[1])
#define Frog_Binary_Code 0x00427906
#define Frog_Binary_Len 6

static const char _Frog_Holidays[] = "\010Holidays";
#define Frog_Holidays (&_Frog_Holidays[1])
#define Frog_Holidays_Code 0x00487308
#define Frog_Holidays_Len 8

#endif /* _strings_h */
