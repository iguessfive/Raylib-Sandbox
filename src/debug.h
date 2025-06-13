#ifndef DEBUG_H
#define DEBUG_H



#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef DEBUG

// ANSI colour codes for log levels
#define GREEN_TEXT "\033[32m"
#define YELLOW_TEXT "\033[33m"
#define GREY_TEXT "\033[90m"
#define RED_TEXT "\033[31m"
#define BOLD_RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

static void ColoredTraceLogCallback(int logLevel, const char *text, va_list args) {
    switch (logLevel) {
        case LOG_INFO:    printf(GREEN_TEXT); break;
        case LOG_WARNING: printf(YELLOW_TEXT "⚠️  "); break;
        case LOG_ERROR:   printf(RED_TEXT "❗️  "); break;
        case LOG_DEBUG:   printf(GREY_TEXT); break;
        case LOG_FATAL:   printf(BOLD_RED_TEXT "‼️  "); break;
        case LOG_TRACE:   printf(RESET_TEXT); break;
        default: break;
    }

    vprintf(text, args);
    printf(RESET_TEXT "\n"); // Reset and newline
}

// Call early in main() to enable coloured logs
static inline void InitDebugLogging(void) {
    SetTraceLogCallback(ColoredTraceLogCallback);
}

  #define ASSERT(cond, msg) \
    if (!(cond)) { \
      TraceLog(LOG_FATAL, "ASSERT FAILED: %s", msg); \
      exit(1); \
    } // if true, continue, otherwise terminate
#else
  #define ASSERT(cond, msg) ((void)0)  // no-op in release builds
#endif

#endif