/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#define NUM_COLORS 7

typedef enum {
  BRT0 = (uint8_t)0b00000000,
  BRT1 = (uint8_t)0b00000001,
  BRT2 = (uint8_t)0b00000010,
  BRT3 = (uint8_t)0b00000100,
  BRT4 = (uint8_t)0b00001000,
} Brightness;

typedef struct {
  uint8_t r : 1;
  uint8_t g : 1;
  uint8_t b : 1;
  uint8_t brt : 4;
  uint8_t _pad : 1;
} RGBColor;

extern const RGBColor *BLACK;
extern const RGBColor *RED;
extern const RGBColor *GREEN;
extern const RGBColor *YELLOW;
extern const RGBColor *BLUE;
extern const RGBColor *MAGENTA;
extern const RGBColor *CYAN;
extern const RGBColor *WHITE;
extern const RGBColor ALL_COLORS[NUM_COLORS];

#endif  // COLOR_H
