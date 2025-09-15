/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "color.h"
#include "world.h"

#define DISPLAY_COLS 64
#define DISPLAY_ROWS 64

void displayInit(void);
void clearDisplay(void);
void drawRect(int x, int y, int w, int h, const RGBColor *color);
void drawWorld(const World *world);
void char2display(const int col, const int row, const char c, const RGBColor *color);
void str2display(const int x, const int y, const char *str, const RGBColor *color);
void recvBuff2display(void);
void renderDisplay(void);

#endif  // DISPLAY_H
