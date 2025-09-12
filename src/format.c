/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "format.h"

#include <stddef.h>

#define A_MAX 30

const char* itoa(int i) {
  static size_t p;
  static char a[A_MAX];

  // Reset a
  p = 0;
  for (; p < sizeof(a); ++p) {
    a[p] = '\0';
  }

  // Populate a
  p = 0;

  // Handle negative
  if (i < 0) {
    i *= -1;
    a[p++] = '-';
  }

  // Write number
  int mag = 1;
  while ((i / mag) >= 10) {
    mag *= 10;
  }
  for (; mag > 0 && p < A_MAX; mag /= 10) {
    a[p++] = '0' + (i / mag);
    i %= mag;
  }
  a[p++] = '\0';
  return a;
}
