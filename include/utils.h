/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void *memset(void *dst, int c, size_t n) __attribute__((weak));
void *memcpy(void *dst, const void *src, size_t n) __attribute__((weak));

#endif  // UTILS_H
