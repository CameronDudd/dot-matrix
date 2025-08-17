/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "display.h"

#include <stdint.h>

#include "b64.h"
#include "color.h"
#include "font.h"
#include "gpio.h"
#include "stm32f401xe.h"
#include "time.h"
#include "usart.h"

#define CLK 5
#define E   6
#define D   7
#define B2  8
#define A   9
#define R1  10

#define G1  3
#define R2  4
#define B1  5
#define C   6
#define OE  8
#define LAT 9
#define G2  10

#define B 7

const Font *font = &simpleFont;

unsigned char _dotBuff[512];
RGBColor1 _colorDispBuff[HEIGHT][WIDTH];

void displayInit(void) {
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);

  // Clear mode bits
  // PORT A
  GPIO_MODER_CLR(GPIOA, CLK);
  GPIO_MODER_CLR(GPIOA, E);
  GPIO_MODER_CLR(GPIOA, D);
  GPIO_MODER_CLR(GPIOA, B2);
  GPIO_MODER_CLR(GPIOA, A);
  GPIO_MODER_CLR(GPIOA, R1);
  // PORT B
  GPIO_MODER_CLR(GPIOB, G1);
  GPIO_MODER_CLR(GPIOB, R2);
  GPIO_MODER_CLR(GPIOB, B1);
  GPIO_MODER_CLR(GPIOB, C);
  GPIO_MODER_CLR(GPIOB, OE);
  GPIO_MODER_CLR(GPIOB, LAT);
  GPIO_MODER_CLR(GPIOB, G2);
  // PORT C
  GPIO_MODER_CLR(GPIOC, B);

  // Set mode bits
  // PORT A
  GPIO_MODER_SET_OUTPUT(GPIOA, CLK);
  GPIO_MODER_SET_OUTPUT(GPIOA, E);
  GPIO_MODER_SET_OUTPUT(GPIOA, D);
  GPIO_MODER_SET_OUTPUT(GPIOA, B2);
  GPIO_MODER_SET_OUTPUT(GPIOA, A);
  GPIO_MODER_SET_OUTPUT(GPIOA, R1);
  // PORT B
  GPIO_MODER_SET_OUTPUT(GPIOB, G1);
  GPIO_MODER_SET_OUTPUT(GPIOB, R2);
  GPIO_MODER_SET_OUTPUT(GPIOB, B1);
  GPIO_MODER_SET_OUTPUT(GPIOB, C);
  GPIO_MODER_SET_OUTPUT(GPIOB, OE);
  GPIO_MODER_SET_OUTPUT(GPIOB, LAT);
  GPIO_MODER_SET_OUTPUT(GPIOB, G2);
  // PORT C
  GPIO_MODER_SET_OUTPUT(GPIOC, B);

  // clear RGB lines
  GPIOA->ODR &= ~((1u << B2) | (1u << R1));
  GPIOB->ODR &= ~((1u << G1) | (1u << R2) | (1u << B1) | (1u << G2));

  // clear row select lines
  GPIOA->ODR &= ~((1u << E) | (1u << D) | (1u << A));
  GPIOB->ODR &= ~(1u << C);
  GPIOC->ODR &= ~(1u << B);

  // clear clock line
  GPIOA->ODR &= ~(1u << CLK);

  // clear latch line
  GPIOB->ODR &= ~(1u << LAT);

  // set output disabled
  GPIOB->ODR |= (1u << OE);  // OE HIGH - DISPLAY OFF

  clearDisplay();
}

void clearDisplay(void) {
  for (uint8_t row = 0; row < WIDTH; ++row) {
    for (uint8_t col = 0; col < HEIGHT; ++col) {
      _colorDispBuff[row][col].r = 0;
      _colorDispBuff[row][col].g = 0;
      _colorDispBuff[row][col].b = 0;
    }
  }
}

void char2display(const int col, const int row, const char c, const RGBColor1 *color) {
  uint16_t charMap = simpleFont.map[(int)c];
  if (charUnsupported(charMap)) {
    charMap = simpleFont.map[0];
  }
  // If remainder of display cannot fit fast fail
  if (((row + font->height) >= HEIGHT) || ((col + font->width) >= WIDTH)) {
    return;
  }
  // Write character to buffer
  for (int c = font->width - 1; c >= 0; --c) {
    for (int r = font->height - 1; r >= 0; --r) {
      int offset = ((font->width * font->height) - 1) - ((r * font->width) + c);
      if ((charMap >> offset) & 1) {
        _colorDispBuff[row + r][col + c].r = color->r;
        _colorDispBuff[row + r][col + c].g = color->g;
        _colorDispBuff[row + r][col + c].b = color->b;
      }
    }
  }
}

void int2display(const int row, const int col, uint32_t val, const RGBColor1 *color) {
  char c;
  int curRow = row;
  int curCol = col;
  int mag    = 1;
  while ((val / mag) > 1) {
    mag *= 10;
  }
  for (; mag > 0; mag /= 10) {
    c = val / mag;
    val -= (c * mag);
    char2display(curCol, curRow, '0' + c, color);
    curCol += (font->width + 1);
  }
}

void str2display(const int row, const int col, const char *str, const RGBColor1 *color) {
  int curRow = row;
  int curCol = col;
  for (const char *c = str; *c != '\0'; ++c) {
    char2display(curCol, curRow, *c, color);
    if (*c != ' ') {
      curCol += font->width;
    }
    curCol++;
  }
}

void recvBuff2display(void) {
  b64Decode(_dotBuff, (unsigned char *)recvBuff);
  for (int row = 0; row < HEIGHT; ++row) {
    for (int col = 0; col < WIDTH; ++col) {
      int cell = (row * WIDTH) + col;
      int idx  = cell / 8;
      int bit  = cell % 8;
      if (_dotBuff[idx] & (1u << bit)) {
        _colorDispBuff[row][col].r = 1;
        _colorDispBuff[row][col].g = 0;
        _colorDispBuff[row][col].b = 0;
      }
    }
  }
}

static void _selectRow(uint8_t row) {
  GPIOA->ODR &= ~((1u << E) | (1u << D) | (1u << A));
  GPIOB->ODR &= ~(1u << C);
  GPIOC->ODR &= ~(1u << B);
  if ((row >> 0) & 1u) GPIOA->ODR |= (1u << A);
  if ((row >> 1) & 1u) GPIOC->ODR |= (1u << B);
  if ((row >> 2) & 1u) GPIOB->ODR |= (1u << C);
  if ((row >> 3) & 1u) GPIOA->ODR |= (1u << D);
  if ((row >> 4) & 1u) GPIOA->ODR |= (1u << E);
}

static void _setColorLines(const RGBColor1 color, const uint8_t bottom) {
  if (!bottom) {
    // clear lines
    GPIOA->ODR &= ~(1u << R1);
    GPIOB->ODR &= ~((1u << G1) | (1u << B1));
    // set lines
    if (color.r) GPIOA->ODR |= (1u << R1);
    if (color.g) GPIOB->ODR |= (1u << G1);
    if (color.b) GPIOB->ODR |= (1u << B1);
  } else {
    // clear lines
    GPIOA->ODR &= ~(1u << B2);
    GPIOB->ODR &= ~((1u << R2) | (1u << G2));
    // set lines
    if (color.r) GPIOB->ODR |= (1u << R2);
    if (color.g) GPIOB->ODR |= (1u << G2);
    if (color.b) GPIOA->ODR |= (1u << B2);
  }
}

void renderDisplay(void) {
  for (uint8_t row = 0; row < 32; ++row) {
    GPIOB->ODR |= (1u << OE);
    _selectRow(row);
    for (uint8_t col = 0; col < 64; ++col) {
      _setColorLines(_colorDispBuff[row][col], 0);
      _setColorLines(_colorDispBuff[row + 32][col], 1);
      GPIOA->ODR |= (1u << CLK);
      GPIOA->ODR &= ~(1u << CLK);
    }
    GPIOB->ODR |= (1u << LAT);
    GPIOB->ODR &= ~(1u << LAT);
    GPIOB->ODR &= ~(1u << OE);
    sleepUs(313);  // 313 us per row; 10016 us per frame; 99.84 frames per second
  }
}
