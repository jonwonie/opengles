
#ifndef __EXLOG_H__
#define __EXLOG_H__
#define LOG_ENABLED 1

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

static void putchar(char c);

static void print(int prio, const char *tag, const char *fmt, ...);

void verbose(const char *tag, const char *fmt, ...);

void debug(const char *tag, const char *fmt, ...);

void info(const char *tag, const char *fmt, ...);

void warn(const char *tag, const char *fmt, ...);

void error(const char *tag, const char *fmt, ...);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif