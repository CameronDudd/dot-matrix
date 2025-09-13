/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef FONT_H
#define FONT_H

#include <stdint.h>

#define TEST_STR " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

typedef struct {
  char *label;
  const uint8_t width;
  const uint8_t height;
  const uint16_t map[127];
} Font;

extern const Font simpleFont;

int charUnsupported(const uint16_t charMap);

#endif  // FONT_H
