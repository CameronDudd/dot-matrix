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

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGBColor;

extern const RGBColor1 *WHITE1;
extern const RGBColor1 *RED1;
extern const RGBColor1 *GREEN1;
extern const RGBColor1 *BLUE1;

extern const RGBColor *WHITE;
extern const RGBColor *RED;
extern const RGBColor *GREEN;
extern const RGBColor *BLUE;

#endif  // COLOR_H
