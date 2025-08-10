/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef struct {
  uint8_t r : 1;
  uint8_t g : 1;
  uint8_t b : 1;
  uint8_t _ : 5;
} RGBColor1;

extern const RGBColor1 *WHITE;
extern const RGBColor1 *RED;
extern const RGBColor1 *GREEN;
extern const RGBColor1 *BLUE;

#endif  // COLOR_H
