/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "renderer.h"

#include "animation.h"
#include "b64.h"
#include "font.h"
#include "usart.h"

const Font *font = &simpleFont;
const RGBColor *frameBuffer[BUFF_ROWS][BUFF_COLS];

// Buffer management
void clearFrameBuffer(void) {
  for (int row = 0; row < BUFF_ROWS; ++row) {
    for (int col = 0; col < BUFF_COLS; ++col) {
      frameBuffer[row][col] = BLACK;
    }
  }
}

void rendererInit(void) {
  clearFrameBuffer();
}

// Drawing funcs
void drawRect(int x, int y, int w, int h, const RGBColor *color) {
  for (int row = y; row < y + h; ++row) {
    for (int col = x; col < x + w; ++col) {
      frameBuffer[row % BUFF_ROWS][col % BUFF_COLS] = color;
    }
  }
}

void drawChar(const int col, const int row, const char c, const RGBColor *color) {
  uint16_t charMap = simpleFont.map[(int)c];
  if (charUnsupported(charMap)) {
    charMap = simpleFont.map[0];
  }
  // If remainder of display cannot fit fast fail
  if (((row + font->height) >= BUFF_ROWS) || ((col + font->width) >= BUFF_COLS)) {
    return;
  }
  // Write character to buffer
  for (int c = font->width - 1; c >= 0; --c) {
    for (int r = font->height - 1; r >= 0; --r) {
      int offset = ((font->width * font->height) - 1) - ((r * font->width) + c);
      if ((charMap >> offset) & 1) {
        frameBuffer[row + r][col + c] = color;
      }
    }
  }
}

void drawStr(const int x, const int y, const char *str, const RGBColor *color) {
  int curRow = y;
  int curCol = x;
  for (const char *c = str; *c != '\0'; ++c) {
    drawChar(curCol, curRow, *c, color);
    if (*c != ' ') {
      curCol += font->width;
    }
    curCol++;
  }
}

void drawAnimationBuffer(void) {
  for (int row = 0; row < ANIMATION_ROWS; ++row) {
    for (int col = 0; col < ANIMATION_COLS; ++col) {
      frameBuffer[row][col] = (animationGrid[row] & ((int64_t)1 << (63 - col))) ? WHITE : BLACK;
    }
  }
}

void drawUsartB64Buff(void) {
  unsigned char decodeBuff[512] = {'\0'};
  b64Decode(decodeBuff, (unsigned char *)recvBuff);
  for (int row = 0; row < BUFF_ROWS; ++row) {
    for (int col = 0; col < BUFF_COLS; ++col) {
      int cell = (row * BUFF_COLS) + col;
      int idx  = cell / 8;
      int bit  = cell % 8;
      if (decodeBuff[idx] & (1u << bit)) {
        frameBuffer[row][col] = WHITE;
      }
    }
  }
}
