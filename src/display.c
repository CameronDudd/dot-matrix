/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "display.h"

#include "color.h"
#include "font.h"
#include "gpio.h"
#include "stm32f401xe.h"
#include "time.h"

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

RGBColor1 _buff[HEIGHT][WIDTH] = {0};

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
  //
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
      _setColorLines(_buff[row][col], 0);
      _setColorLines(_buff[row + 32][col], 1);
      GPIOA->ODR |= (1u << CLK);
      GPIOA->ODR &= ~(1u << CLK);
    }
    GPIOB->ODR |= (1u << LAT);
    GPIOB->ODR &= ~(1u << LAT);
    GPIOB->ODR &= ~(1u << OE);
    sleepUs(313);  // 313 us per row; 10016 us per frame; 99.84 frames per second
  }
}
