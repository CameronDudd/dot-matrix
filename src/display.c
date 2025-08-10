/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "display.h"

#include "color.h"
#include "font.h"
#include "gpio.h"
#include "time.h"

const Font *font = &simpleFont;

RGBColor1 _buff[HEIGHT][WIDTH] = {0};

void clearDisplay(void) {
  for (uint8_t row = 0; row < WIDTH; ++row) {
    for (uint8_t col = 0; col < HEIGHT; ++col) {
      _buff[row][col].r = 0;
      _buff[row][col].g = 0;
      _buff[row][col].b = 0;
    }
  }
}

void str2display(const int row, const int col, const char *str, const RGBColor1 *color) {
  int curRow = row;
  int curCol = col;
  for (const char *c = str; *c != '\0'; ++c) {
    uint16_t charMap = simpleFont.map[(int)(*c)];
    if (charUnsupported(charMap)) {
      charMap = simpleFont.map[0];
    }

    // If remainder of display cannot fit fast fail
    if (((curRow + font->height) >= HEIGHT) || ((curCol + font->width) >= WIDTH)) {
      break;
    }

    // Write character to buffer
    for (int col = font->width - 1; col >= 0; --col) {
      for (int row = font->height - 1; row >= 0; --row) {
        int offset = ((font->width * font->height) - 1) - ((row * font->width) + col);
        if ((charMap >> offset) & 1) {
          _buff[curRow + row][curCol + col].r = color->r;
          _buff[curRow + row][curCol + col].g = color->g;
          _buff[curRow + row][curCol + col].b = color->b;
        }
      }
    }

    if (*c != ' ') {
      curCol += font->width;
    }
    curCol++;
  }
}

void renderDisplay(void) {
  for (uint8_t row = 0; row < 32; ++row) {
    outputDisable();
    selectRow(row);
    for (uint8_t col = 0; col < 64; ++col) {
      setColorLines(_buff[row][col], 0);
      setColorLines(_buff[row + 32][col], 1);
      clock();
    }
    latch();
    outputEnable();
    sleepMs(1);
  }
}
