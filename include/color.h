/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGBColor;

extern const RGBColor *BLACK;
extern const RGBColor *RED;
extern const RGBColor *GREEN;
extern const RGBColor *YELLOW;
extern const RGBColor *BLUE;
extern const RGBColor *MAGENTA;
extern const RGBColor *CYAN;
extern const RGBColor *WHITE;

#endif  // COLOR_H
