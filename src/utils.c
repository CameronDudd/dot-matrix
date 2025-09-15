/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "utils.h"

__attribute__((weak)) void *memcpy(void *dst, const void *src, size_t n) {
  char *dstPtr       = (char *)dst;
  const char *srcPtr = (const char *)src;
  if (dstPtr && srcPtr) {
    while (n--) {
      *dstPtr++ = *srcPtr++;
    }
  }
  return dst;
}
