#pragma once

#include <cstdio>
#include <cstring>

#define __FILENAME__ \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef DEBUG_LOGGING
#define LOG_DEBUG(fmt, ...)                                        \
  fprintf(stderr, "[%s:%d] %s: " fmt "\n", __FILENAME__, __LINE__, \
          __FUNCTION__, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#endif

#ifndef NDEBUG
#define LOG_INFO(fmt, ...)                                         \
  fprintf(stderr, "[%s:%d] %s: " fmt "\n", __FILENAME__, __LINE__, \
          __FUNCTION__, ##__VA_ARGS__)
#else
#define LOG_INFO(fmt, ...)
#endif

#define LOG(fmt, ...)                                             \
  fprintf(stderr, "[%s:%d] %s:" fmt "\n", __FILENAME__, __LINE__, \
          __FUNCTION__, ##__VA_ARGS__)
