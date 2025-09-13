/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

#define NUM_COLORS 7

typedef enum {
  BRT0   = 0,
  BRT1   = 1,
  BRT2   = 2,
  BRT3   = 3,
  BRTMAX = 3,
} Brightness;

typedef struct {
  uint8_t r : 2;
  uint8_t g : 2;
  uint8_t b : 2;
  uint8_t _pad : 2;
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

const RGBColor *randColor(void);

#endif  // COLOR_H
