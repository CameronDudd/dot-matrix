/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "color.h"

#define WIDTH  64
#define HEIGHT 64

void displayInit(void);
void clearDisplay(void);
void int2display(const int row, const int col, uint32_t val, const RGBColor1 *color);
void char2display(const int col, const int row, const char c, const RGBColor1 *color);
void str2display(const int xpos, const int ypos, const char *str, const RGBColor1 *color);
void recvBuff2display(void);
void renderDisplay(void);

#endif  // DISPLAY_H
