/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "utils.h"

// FIXME(cameron)
void itoa(uint32_t i, char *a) {
  char c;
  int mag = 1;
  while ((i / (mag *= 10))) {
  }
  mag /= 10;
  for (; mag > 0; mag /= 10) {
    c = i / mag;
    i -= (c * mag);
    *a++ = '0' + c;
  }
  *a++ = '\r';
  *a++ = '\n';
  *a++ = '\0';
}
