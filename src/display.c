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

#define HALF_DISPLAY_ROWS   32
#define RENDER_SLEEP_BASE   3
#define RENDER_SLEEP_OFFSET 3

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

#define CLK_Msk 0x20u
#define E_Msk   0x40u
#define D_Msk   0x80u
#define B2_Msk  0x100u
#define A_Msk   0x200u
#define R1_Msk  0x400u

#define G1_Msk  0x8u
#define R2_Msk  0x10u
#define B1_Msk  0x20u
#define C_Msk   0x40u
#define OE_Msk  0x100u
#define LAT_Msk 0x200u
#define G2_Msk  0x400u

#define B_Msk 0x80u

#define DISPLAY_OFF GPIOB->ODR |= OE_Msk;
#define DISPLAY_ON  GPIOB->ODR &= ~OE_Msk

const Font *font = &simpleFont;

unsigned char monoBuff[512];
static const RGBColor *frameBuffer[DISPLAY_ROWS][DISPLAY_COLS];

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
  GPIOA->ODR &= ~(B2_Msk | R1_Msk);
  GPIOB->ODR &= ~(G1_Msk | R2_Msk | B1_Msk | G2_Msk);

  // clear row select lines
  GPIOA->ODR &= ~(E_Msk | D_Msk | A_Msk);
  GPIOB->ODR &= ~C_Msk;
  GPIOC->ODR &= ~B_Msk;

  // clear clock line
  GPIOA->ODR &= ~CLK_Msk;

  // clear latch line
  GPIOB->ODR &= ~LAT_Msk;

  // set output disabled
  DISPLAY_OFF;

  clearDisplay();
}

void clearDisplay(void) {
  for (uint8_t row = 0; row < DISPLAY_ROWS; ++row) {
    for (uint8_t col = 0; col < DISPLAY_COLS; ++col) {
      frameBuffer[row][col] = BLACK;
    }
  }
}

void drawRect(int x, int y, int w, int h, const RGBColor *color) {
  for (int row = y; row < y + h; ++row) {
    for (int col = x; col < x + w; ++col) {
      frameBuffer[row % DISPLAY_ROWS][col % DISPLAY_COLS] = *color;
    }
  }
}

void drawCreature(Creature *creature) {
  Vec2 pos = creature->state.pos;
  Vec2 vel = creature->state.vel;

  // Stationary
  if ((vel.x == 0) && (vel.y == 0)) {
    drawRect(pos.x, pos.y, 2, 2, creature->state.color);
    return;
  }

  // Vertical
  if (vel.y < 0) {
    drawRect(pos.x, pos.y, 2, 1, creature->state.color);
  } else if (vel.y > 0) {
    drawRect(pos.x, pos.y + 1, 2, 1, creature->state.color);
  }

  // Horizontal
  if (vel.x < 0) {
    drawRect(pos.x, pos.y, 1, 2, creature->state.color);
  } else if (vel.x > 0) {
    drawRect(pos.x + 1, pos.y, 1, 2, creature->state.color);
  }
}

void char2display(const int col, const int row, const char c, const RGBColor *color) {
  uint16_t charMap = simpleFont.map[(int)c];
  if (charUnsupported(charMap)) {
    charMap = simpleFont.map[0];
  }
  // If remainder of display cannot fit fast fail
  if (((row + font->height) >= DISPLAY_ROWS) || ((col + font->width) >= DISPLAY_COLS)) {
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

void str2display(const int row, const int col, const char *str, const RGBColor *color) {
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
  b64Decode(monoBuff, (unsigned char *)recvBuff);
  for (int row = 0; row < DISPLAY_ROWS; ++row) {
    for (int col = 0; col < DISPLAY_COLS; ++col) {
      int cell = (row * DISPLAY_COLS) + col;
      int idx  = cell / 8;
      int bit  = cell % 8;
      if (monoBuff[idx] & (1u << bit)) {
        frameBuffer[row][col] = WHITE;
      }
    }
  }
}

static void _clearRGBTopLines(void) {
  GPIOA->ODR &= ~R1_Msk;
  GPIOB->ODR &= ~(G1_Msk | B1_Msk);
}

static void _clearRGBBottomLines(void) {
  GPIOA->ODR &= ~B2_Msk;
  GPIOB->ODR &= ~(R2_Msk | G2_Msk);
}

static void _selectRow(uint8_t row) {
  GPIOA->ODR &= ~(E_Msk | D_Msk | A_Msk);
  GPIOB->ODR &= ~C_Msk;
  GPIOC->ODR &= ~B_Msk;
  if (row & 0x01u) GPIOA->ODR |= A_Msk;
  if (row & 0x02u) GPIOC->ODR |= B_Msk;
  if (row & 0x04u) GPIOB->ODR |= C_Msk;
  if (row & 0x08u) GPIOA->ODR |= D_Msk;
  if (row & 0x10u) GPIOA->ODR |= E_Msk;
}

static void _setColorLines(const RGBColor *color, const uint8_t bottom, const uint8_t bit) {
  if (!bottom) {
    _clearRGBTopLines();
    if (color->r > bit) GPIOA->ODR |= R1_Msk;
    if (color->g > bit) GPIOB->ODR |= G1_Msk;
    if (color->b > bit) GPIOB->ODR |= B1_Msk;
  } else {
    _clearRGBBottomLines();
    if (color->r > bit) GPIOB->ODR |= R2_Msk;
    if (color->g > bit) GPIOB->ODR |= G2_Msk;
    if (color->b > bit) GPIOA->ODR |= B2_Msk;
  }
}

static void _toggleClk(void) {
  GPIOA->ODR |= CLK_Msk;
  GPIOA->ODR &= ~CLK_Msk;
}

static void _toggleLat(void) {
  GPIOB->ODR |= LAT_Msk;
  GPIOB->ODR &= ~LAT_Msk;
}

void renderDisplay(void) {
  uint8_t sleep;
  for (uint8_t bit = 0; bit < BRTMAX; ++bit) {
    sleep = (RENDER_SLEEP_OFFSET << bit) * RENDER_SLEEP_BASE;
    for (uint8_t row = 0; row < HALF_DISPLAY_ROWS; ++row) {
      _selectRow(row);
      for (uint8_t col = 0; col < DISPLAY_COLS; ++col) {
        _setColorLines(frameBuffer[row][col], 0, bit);
        _setColorLines(frameBuffer[row + HALF_DISPLAY_ROWS][col], 1, bit);
        _toggleClk();
      }
      _toggleLat();
      DISPLAY_ON;
      sleepUs(sleep);
      DISPLAY_OFF;
    }
  }
}
