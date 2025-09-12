/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "format.h"

#include <stddef.h>

#define A_MAX 11

const char* itoa(uint32_t i) {
  static size_t p;
  static char a[A_MAX];

  // Reset a
  p = 0;
  for (; p < sizeof(a); ++p) {
    a[p] = '\0';
  }

  // Populate a
  p       = 0;
  int mag = 1;
  while ((i / mag) >= 10) {
    mag *= 10;
  }
  for (; mag > 0; mag /= 10) {
    a[p++] = i / mag;
    i %= mag;
  }
  a[p++] = '\0';
  return a;
}
