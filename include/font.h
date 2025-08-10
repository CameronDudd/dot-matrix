/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef FONT_H
#define FONT_H

#include <stdint.h>

#define TEST_STR " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"

typedef struct {
  char *label;
  int width;
  int height;
  uint16_t map[];
} Font;

extern Font simpleFont;

int charUnsupported(uint16_t charMap);

#endif  // FONT_H
