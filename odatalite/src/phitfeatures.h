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
#ifndef _phit_phitfeatures_h
#define _phit_phitfeatures_h

/*
**==============================================================================
**
** Choose FAST or LEAN or neither
**
**==============================================================================
*/

#if 0
# define FAST
#endif

#if 0
# define LEAN
#endif

#if 0
# define PRODUCTION
#endif

/*
**==============================================================================
**
** All Features:
**
**==============================================================================
*/

#define ENABLE_STATIC_BUFFERS
#define ENABLE_ALLOCATOR
#define ENABLE_LOGGING
#define ENABLE_SPEED_OPTIMIZATIONS
#define ENABLE_PAM_AUTH
#define ENABLE_PAM_FORKING
#define ENABLE_PIDFILE
#define ENABLE_ROLES
#define ENABLE_DATETIME_LOGGING
#define ENABLE_LOGLEVEL_LOGGING
#define ENABLE_SOCKTRACE
/*#define ENABLE_DEBUG*/
#define ENABLE_FAULTS
#define ENABLE_INDENT
#define ENABLE_WEBPAGES
#define ENABLE_ALWAYS_INLINE

#undef ENABLE_ALWAYS_INLINE

/*
**==============================================================================
**
** FAST -- achieve the fastest possible build
**
**==============================================================================
*/

#if defined(FAST)
# undef ENABLE_ALLOCATOR
# undef ENABLE_SOCKTRACE
/*# undef ENABLE_DEBUG*/
# undef ENABLE_PAM_FORKING
# undef ENABLE_DATETIME_LOGGING
# undef ENABLE_LOGLEVEL_LOGGING
#endif

/*
**==============================================================================
**
** LEAN -- achieve the smallest possible build
**
**==============================================================================
*/

#if defined(LEAN)
/*# undef ENABLE_STATIC_BUFFERS*/
# undef ENABLE_ALLOCATOR
# undef ENABLE_LOGGING
# undef ENABLE_SPEED_OPTIMIZATIONS
# undef ENABLE_PAM_AUTH
# undef ENABLE_PAM_FORKING
/*# undef ENABLE_PIDFILE*/
# undef ENABLE_ROLES
# undef ENABLE_DATETIME_LOGGING
# undef ENABLE_LOGLEVEL_LOGGING
# undef ENABLE_SOCKTRACE
/*# undef ENABLE_DEBUG*/
# undef ENABLE_FAULTS
# undef ENABLE_WEBPAGES
#endif

/*
**==============================================================================
**
** PRODUCTION
**
**==============================================================================
*/

#if defined(PRODUCTION)
/*# undef ENABLE_STATIC_BUFFERS*/
/*# undef ENABLE_ALLOCATOR*/
/*# undef ENABLE_LOGGING*/
# undef ENABLE_SPEED_OPTIMIZATIONS
/*# undef ENABLE_PAM_AUTH*/
# undef ENABLE_PAM_FORKING
/*# undef ENABLE_PIDFILE*/
/*# undef ENABLE_ROLES*/
# undef ENABLE_DATETIME_LOGGING
# undef ENABLE_LOGLEVEL_LOGGING
# undef ENABLE_SOCKTRACE
# undef ENABLE_DEBUG
# undef ENABLE_FAULTS
# undef ENABLE_INDENT
# undef ENABLE_WEBPAGES
# undef ENABLE_ALWAYS_INLINE
#endif

/*
**==============================================================================
**
** Disable features not available on Windows
**
**==============================================================================
*/

#if defined(_MSC_VER)
# undef ENABLE_PIDFILE
# undef ENABLE_PAM_AUTH
# undef ENABLE_PAM_FORKING
# undef ENABLE_ROLES
# undef ENABLE_FAULTS
#endif

#endif /* _phit_phitfeatures_h */
