/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "color.h"

#define WIDTH  64
#define HEIGHT 64

extern RGBColor1 _buff[HEIGHT][WIDTH];

void displayInit(void);
void clearDisplay(void);
void str2display(const int xpos, const int ypos, const char *str, const RGBColor1 *color);
void renderDisplay(void);

#endif  // DISPLAY_H
