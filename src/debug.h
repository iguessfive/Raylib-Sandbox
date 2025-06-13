#ifndef DEBUG_H
#define DEBUG_H

#define RED_TEXT "\033[1;31m" // bold red
#define RESET_TEXT "\033[0m"

#include "raylib.h"
#include <stdlib.h>

#ifdef DEBUG
  #define ASSERT(cond, msg) \
    if (!(cond)) { \
      TraceLog(LOG_FATAL, RED_TEXT "ASSERT FAILED: %s" RESET_TEXT, msg); \
      exit(1); \
    } // if true, continue, otherwise terminate
#else
  #define ASSERT(cond, msg) ((void)0)  // no-op in release builds
#endif

#endif