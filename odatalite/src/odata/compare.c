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
#include "compare.h"

int ValueCompare(
    const OL_Value* x,
    const OL_Value* y)
{
    if (x->type != y->type)
        return -1;

    switch (x->type)
    {
        case OL_Type_String:
        {
            if (strcmp(x->u.string, y->u.string) != 0)
                return -1;
            break;
        }
        case OL_Type_Binary:
        {
            const OL_Binary* lhs = &x->u.binary;
            const OL_Binary* rhs = &y->u.binary;

            if (lhs->size != rhs->size)
                return -1;

            if (lhs->data && rhs->data)
            {
                if (memcmp(lhs->data, rhs->data, lhs->size) != 0)
                    return -1;
            }
            else if (lhs->data != NULL || rhs->data != NULL)
                return -1;

            return 0;
        }
        case OL_Type_Boolean:
        {
            if (x->u.boolean != y->u.boolean)
                return -1;
            break;
        }
        case OL_Type_Byte:
        {
            if (x->u.byte != y->u.byte)
                return -1;
            break;
        }
        case OL_Type_SByte:
        {
            if (x->u.sByte != y->u.sByte)
                return -1;
            break;
        }
        case OL_Type_Int16:
        {
            if (x->u.int16 != y->u.int16)
                return -1;
            break;
        }
        case OL_Type_Int32:
        {
            if (x->u.int32 != y->u.int32)
                return -1;
            break;
        }
        case OL_Type_Int64:
        {
            if (x->u.int64 != y->u.int64)
                return -1;
            break;
        }
        case OL_Type_Single:
        {
            if (x->u.single != y->u.single)
                return -1;
            break;
        }
        case OL_Type_Double:
        {
            if (x->u.double_ != y->u.double_)
                return -1;
            break;
        }
        case OL_Type_Decimal:
        {
            if (x->u.decimal.integral != y->u.decimal.integral ||
                x->u.decimal.fractional != y->u.decimal.fractional)
            {
                return -1;
            }
            break;
        }
        case OL_Type_Date:
        {
            if (x->u.date.year != y->u.date.year ||
                x->u.date.month != y->u.date.month ||
                x->u.date.day != y->u.date.day)
                return -1;
            break;
        }
        case OL_Type_TimeOfDay:
        {
            if (x->u.timeOfDay.hour != y->u.timeOfDay.hour ||
                x->u.timeOfDay.minute != y->u.timeOfDay.minute ||
                x->u.timeOfDay.second != y->u.timeOfDay.second ||
                x->u.timeOfDay.fractionalSecond != 
                    y->u.timeOfDay.fractionalSecond)
                return -1;
            break;
        }
        case OL_Type_DateTimeOffset:
        {
            if (x->u.dateTimeOffset.year != y->u.dateTimeOffset.year ||
                x->u.dateTimeOffset.month != y->u.dateTimeOffset.month ||
                x->u.dateTimeOffset.day != y->u.dateTimeOffset.day ||
                x->u.dateTimeOffset.hour != y->u.dateTimeOffset.hour ||
                x->u.dateTimeOffset.minute != y->u.dateTimeOffset.minute ||
                x->u.dateTimeOffset.second != y->u.dateTimeOffset.second ||
                x->u.dateTimeOffset.fractionalSecond 
                    != y->u.dateTimeOffset.fractionalSecond)
                return -1;
            break;
        }
        case OL_Type_Duration:
        {
            if (x->u.duration.negative != y->u.duration.negative ||
                x->u.duration.days != y->u.duration.days ||
                x->u.duration.hour != y->u.duration.hour ||
                x->u.duration.minute != y->u.duration.minute ||
                x->u.duration.second != y->u.duration.second ||
                x->u.duration.fractionalSecond != 
                    y->u.duration.fractionalSecond)
                return -1;
            break;
        }
        case OL_Type_Guid:
        {
            if (x->u.guid.data1 != y->u.guid.data1 ||
                x->u.guid.data2 != y->u.guid.data2 ||
                x->u.guid.data3 != y->u.guid.data3 ||
                x->u.guid.data4 != y->u.guid.data4 ||
                x->u.guid.data5 != y->u.guid.data5 ||
                x->u.guid.data6 != y->u.guid.data6)
                return -1;
            break;
        }
        case OL_Type_Object:
        {
            JSON_Object* o1 = (JSON_Object*)x->u.array;
            JSON_Object* o2 = (JSON_Object*)y->u.array;
            size_t n1;
            size_t n2;
            size_t i;

            n1 = JSON_Object_Count(o1);
            n2 = JSON_Object_Count(o1);

            for (i = 0; i < n1; i++)
            {
                const OL_Char* name1;
                JSON_Value v1;
                const OL_Char* name2;
                JSON_Value v2;

                if (JSON_Object_GetAt(o1, i, &name1, &v1) != OL_Result_Ok)
                    return -1;

                if (JSON_Object_GetAt(o2, i, &name2, &v2) != OL_Result_Ok)
                    return -1;

                if (strcmp(name1, name2) != 0)
                    return -1;

                if (ValueCompare((OL_Value*)&v1, (OL_Value*)&v2) != 0)
                    return -1;
            }
            break;
        }
        case OL_Type_NavigationLink:
        {
            if (strcmp(x->u.navigationLink, y->u.navigationLink) != 0)
                return -1;
            break;
        }
        case OL_Type_AssociationLink:
        {
            if (strcmp(x->u.associationLink, y->u.associationLink) != 0)
                return -1;
            break;
        }
        case OL_Type_Array:
        {
            JSON_Array* a1 = (JSON_Array*)x->u.array;
            JSON_Array* a2 = (JSON_Array*)y->u.array;
            size_t n1;
            size_t n2;
            size_t i;

            n1 = JSON_Array_Count(a1);
            n2 = JSON_Array_Count(a1);

            if (n1 != n2)
                return -1;

            for (i = 0; i < n1; i++)
            {
                JSON_Value v1;
                JSON_Value v2;

                if (JSON_Array_Get(a1, i, &v1) != OL_Result_Ok)
                    return -1;

                if (JSON_Array_Get(a2, i, &v2) != OL_Result_Ok)
                    return -1;

                if (ValueCompare((OL_Value*)&v1, (OL_Value*)&v2) != 0)
                {
                    return -1;
                }
            }

            break;
        }
    }

    return 0;
}
