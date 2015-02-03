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
#ifndef _common_h
#define _common_h

#if defined(_MSC_VER)
# include "winconfig.h"
#else
# include "config.h"
/* ATTN: move into config.h */
# define HAVE_POSIX
#endif

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "phitfeatures.h"

/*
**==============================================================================
**
** ENABLE_DEBUG
**
**==============================================================================
*/

#if (CONFIG_DEBUG == 1)
# define ENABLE_DEBUG
#endif

/*
**==============================================================================
**
** EXPORT
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
# define EXPORT __attribute__((visibility("default")))
# define IMPORT /* empty */
#elif defined(sun)
# define EXPORT __global
# define IMPORT /* empty */
#else
# define EXPORT
# define IMPORT
#endif

/*
**==============================================================================
**
** INLINE
**
**==============================================================================
*/

#if defined(_MSC_VER)
# define INLINE static __inline
# define ALWAYS_INLINE static __inline
#elif defined(__GNUC__)
# define INLINE static __inline
# define ALWAYS_INLINE __attribute__((always_inline)) static __inline
#elif defined(sun)
# define INLINE static inline
# define ALWAYS_INLINE static inline
#elif defined(__PPC)
# define INLINE __inline__
# define ALWAYS_INLINE __inline__
#else
# define INLINE static __inline
# define ALWAYS_INLINE static __inline
#endif

/* FORCE_INLINE must be defined before inclusion of <common.h> */
#if defined(FORCE_INLINE)
# undef INLINE
# define INLINE ALWAYS_INLINE
#endif

#if !defined(ENABLE_ALWAYS_INLINE)
# undef ALWAYS_INLINE
# define ALWAYS_INLINE INLINE
#endif

/*
**==============================================================================
**
** SIZEMAX
**
**==============================================================================
*/

#define SIZEMAX ((size_t)-1)

/*
**==============================================================================
**
** PRINTF_FORMAT
**
**==============================================================================
*/

#if defined(__GNUC__) && (__GNUC__ >= 4) && !defined(CONFIG_ENABLE_WCHAR)
# define PRINTF_FORMAT(N,M) __attribute__((format(printf, N, M)))
#else
# define PRINTF_FORMAT(N,M) /* empty */
#endif

/*
**==============================================================================
**
** DEBUG_ASSERT
**
**==============================================================================
*/

#if defined(ENABLE_DEBUG)
# define DEBUG_ASSERT(COND) assert(COND)
#else
# define DEBUG_ASSERT(COND)
#endif

/*
**==============================================================================
**
** MAX_PATH_SIZE
**
**==============================================================================
*/

#define MAX_PATH_SIZE 1024

/*
**==============================================================================
**
** USERNAME_SIZE
**
**==============================================================================
*/

#define USERNAME_SIZE 128

/*
**==============================================================================
**
** PASSWORD_SIZE
**
**==============================================================================
*/

#define PASSWORD_SIZE 128

/*
**==============================================================================
**
** GROUPNAME_SIZE
**
**==============================================================================
*/

#define GROUPNAME_SIZE 128

/*
**==============================================================================
**
** PHIT_BIG_ENDIAN
** PHIT_LITTLE_ENDIAN
** PHIT_PDP_ENDIAN
** PHIT_UNKNOWN_ENDIAN
**
**==============================================================================
*/

#if defined(__GNUC__)
# if (__BYTE_ORDER == __BIG_ENDIAN)
#  define PHIT_BIG_ENDIAN
# elif (__BYTE_ORDER == __LITTLE_ENDIAN)
#  define PHIT_LITTLE_ENDIAN
# elif (__BYTE_ORDER == __PDP_ENDIAN)
#  define PHIT_PDP_ENDIAN
# endif
#endif

#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_AMD64))
# define PHIT_LITTLE_ENDIAN
#endif

#if !defined(PHIT_BIG_ENDIAN) && \
    !defined(PHIT_PDP_ENDIAN) && \
    !defined(PHIT_LITTLE_ENDIAN)
# define PHIT_UNKNOWN_ENDIAN
#endif

/*
**==============================================================================
**
** PHIT_X86
** PHIT_X64
** PHIT_ARM
** PHIT_ALPHA
** PHIT_SPARC
** PHIT_PARISC
** PHIT_PPC
** PHIT_PPC64
** PHIT_IA64
**
**==============================================================================
*/

#if defined(__i386__) || defined(_M_IX86)
# define PHIT_X86
#elif defined(__x86_64__) || defined(_M_IX64) || defined(_M_AMD64)
# define PHIT_X64
#elif defined(__arm__) || defined(_M_ARM)
# define PHIT_ARM
#elif defined(__alpha__) || defined(_M_ALPHA)
# define PHIT_ALPHA
#elif defined(__sparc__) || defined(__sparc)
# define PHIT_SPARC
#elif defined(__hppa__) || defined(__HPPA__)
# define PHIT_PARISC
#elif defined(__ppc64__)
# define PHIT_PPC64
#elif defined(__ppc__) || defined(_M_PPC)
# define PHIT_PPC
#elif defined(__ia64__) || defined(_M_IA64)
# define PHIT_PPC
#else
# error "unidentified architecture"
#endif

/*
**==============================================================================
**
** PHIT_ONE_BYTE_ALIGNMENT
**
**     Defined if integers may be aligned on one-byte boundaries.
**
**==============================================================================
*/

#if defined(PHIT_X86) || defined(PHIT_X64)
# define PHIT_ONE_BYTE_ALIGNMENT
#endif

/*
**==============================================================================
**
** TRACE
**
**==============================================================================
*/

#define TRACE printf("%s(%u): TRACE\n", __FILE__, __LINE__)

/*
**==============================================================================
**
** FAULT -- conditionally include fault injection code
**
**==============================================================================
*/

#if defined(ENABLE_FAULTS)
# define FAULT(FIELD) (faults && faults->FIELD)
#else
# define FAULT(FIELD) 0
#endif

/*
**==============================================================================
**
** ARRSIZE
**
**==============================================================================
*/

#define ARRSIZE(ARR) (sizeof(ARR) / sizeof(ARR[0]))

/*
**==============================================================================
**
** SHLIBEXT
**
**==============================================================================
*/

#if defined(HAVE_POSIX)
# define SHLIBEXT ".so"
#elif defined(_MSC_VER)
# define SHLIBEXT ".dll"
#endif

/*
**==============================================================================
**
** EXTERNC_BEGIN
** EXTERNC_END
**
**==============================================================================
*/

#if defined(__cplusplus)
# define EXTERNC_BEGIN extern "C" {
# define EXTERNC_END }
#else
# define EXTERNC_BEGIN
# define EXTERNC_END
#endif

/*
**==============================================================================
**
** SHLIB_PREFIX
** SHLIB_SUFFIX
**
**==============================================================================
*/

#if defined(__APPLE__)
# define SHLIB_PREFIX "lib"
# define SHLIB_SUFFIX ".dylib"
#else
# define SHLIB_PREFIX "lib"
# define SHLIB_SUFFIX ".so"
#endif

#endif /* _common_h */
