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
#include "getopt.h"

int GetOpt(
    GetOptState* state,
    int argc,
    char* const argv[],
    const char* optstring)
{
    char* p;

    /* If first time called */
    if (state->__argc == 0)
        state->__argc = argc;

    /* Clear state variables */
    state->optarg = NULL;
    state->optopt = 0;

    /* For each argument in argv[] */
    while (state->optind < state->__argc)
    {
        const char* opt = argv[state->optind];
        size_t n;

        /* Skip non-option arguments (as well as the -- option) */
        if (opt[0] != '-' || opt[1] == '-' || strlen(opt) != 2)
        {
            state->optind++;
            continue;
        }

        /* Find option in the option string */
        if (!(p = strchr(optstring, opt[1])))
        {
            state->optopt = opt[1];
            return '?';
        }

        /* If it has an option argument */
        if (p[1] == ':')
        {
            /* If missing option argument */
            if (state->optind + 1 == state->__argc)
            {
                state->optopt = opt[1];
                return ':';
            }

            /* Save option argument */
            state->optarg = argv[state->optind + 1];

            /* Remove two arguments */
            n = 2;
        }
        else
        {
            /* Remove one argument */
            n = 1;
        }

        /* Remove option and any argument */
        memmove(
            (void*)&argv[state->optind], 
            (void*)&argv[state->optind+n], 
            sizeof(char*) * (state->__argc - state->optind - (n - 1)));
        state->__argc -= n;

        /* Return the current option letter */
        return opt[1];
    }

    /* No more options */
    return -1;
}
