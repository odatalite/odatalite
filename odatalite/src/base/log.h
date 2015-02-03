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
#ifndef _phit_base_log_h
#define _phit_base_log_h

#include "common.h"
#include <stdarg.h>

typedef enum _LogLevel
{
   LOG_FATAL = 0,
   LOG_ERROR = 1,
   LOG_WARNING = 2,
   LOG_INFO = 3,
   LOG_DEBUG = 4,
   LOG_VERBOSE = 5 
}
LogLevel;

#if defined(ENABLE_LOGGING)

int LogLevelFromString(
    const char* str,
    LogLevel* level);

PRINTF_FORMAT(2, 3)
void Log(
    LogLevel level, 
    const char* format, 
    ...);

void VLog(
    LogLevel level, 
    const char* format,
    va_list ap);

extern LogLevel __logLevel;

INLINE void LogSetLevel(LogLevel level)
{
    __logLevel = level;
}

INLINE LogLevel LogGetLevel()
{
    return __logLevel;
}

void LogSetStream(FILE* os);

FILE* LogGetStream();

void LogClose();

PRINTF_FORMAT(1, 2)
void __LogF(const char* format, ...);

PRINTF_FORMAT(1, 2)
void __LogE(const char* format, ...);

PRINTF_FORMAT(1, 2)
void __LogW(const char* format, ...);

PRINTF_FORMAT(1, 2)
void __LogI(const char* format, ...);

#if defined(ENABLE_DEBUG)

PRINTF_FORMAT(1, 2)
void __LogD(const char* format, ...);

PRINTF_FORMAT(1, 2)
void __LogV(const char* format, ...);

#endif /* defined(ENABLE_DEBUG) */

# define LOGF(ARGS) __LogF ARGS
# define LOGE(ARGS) __LogE ARGS
# define LOGW(ARGS) __LogW ARGS
# define LOGI(ARGS) __LogI ARGS

# if defined(ENABLE_DEBUG)
#  define LOGD(ARGS) __LogD ARGS
#  define LOGV(ARGS) __LogV ARGS
# else
#  define LOGD(ARGS)
#  define LOGV(ARGS)
# endif

#else /* defined(ENABLE_LOGGING) */

# define LOGF(ARGS)
# define LOGE(ARGS)
# define LOGW(ARGS)
# define LOGI(ARGS)
# define LOGD(ARGS)
# define LOGV(ARGS)

INLINE void LogSetLevel(LogLevel level) { }
INLINE void LogSetStream(FILE* os) { }
INLINE void LogClose() { }
INLINE LogLevel LogGetLevel() { return LOG_FATAL; }
INLINE FILE* LogGetStream() { return stdout; }

#endif /* defined(ENABLE_LOGGING) */

#endif /* _phit_base_log_h */
