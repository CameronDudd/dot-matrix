/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "display.h"

#include <stdint.h>

#include "color.h"
#include "gpio.h"
#include "renderer.h"
#include "stm32f401xe.h"
#include "time.h"

#define HALF_DISPLAY_ROWS   (DISPLAY_ROWS / 2)
#define RENDER_SLEEP_BASE   3
#define RENDER_SLEEP_OFFSET 3

#define PIN2_Msk  0x6u
#define PIN3_Msk  0x8u
#define PIN4_Msk  0x10u
#define PIN5_Msk  0x20u
#define PIN6_Msk  0x40u
#define PIN7_Msk  0x80u
#define PIN8_Msk  0x100u
#define PIN9_Msk  0x200u
#define PIN10_Msk 0x400u

// GPIOA
#define CLK 5
#define E   6
#define D   7
#define B2  8
#define A   9
#define R1  10

// GPIOB
#define G2  2
#define C   6
#define OE  8
#define LAT 9

// GPIOC
#define R2 5
#define B1 6
#define B  7
#define G1 8

// GPIOA
#define CLK_Msk PIN5_Msk
#define E_Msk   PIN6_Msk
#define D_Msk   PIN7_Msk
#define B2_Msk  PIN8_Msk
#define A_Msk   PIN9_Msk
#define R1_Msk  PIN10_Msk

// GPIOB
#define G2_Msk  PIN2_Msk
#define R2_Msk  PIN5_Msk
#define C_Msk   PIN6_Msk
#define OE_Msk  PIN8_Msk
#define LAT_Msk PIN9_Msk

// GPIOC
#define B1_Msk PIN6_Msk
#define B_Msk  PIN7_Msk
#define G1_Msk PIN8_Msk

#define DISPLAY_OFF GPIOB->ODR |= OE_Msk;
#define DISPLAY_ON  GPIOB->ODR &= ~OE_Msk

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
  GPIO_MODER_CLR(GPIOB, G2);
  GPIO_MODER_CLR(GPIOB, C);
  GPIO_MODER_CLR(GPIOB, OE);
  GPIO_MODER_CLR(GPIOB, LAT);
  // PORT C
  GPIO_MODER_CLR(GPIOC, R2);
  GPIO_MODER_CLR(GPIOC, B1);
  GPIO_MODER_CLR(GPIOC, B);
  GPIO_MODER_CLR(GPIOC, G1);

  // Set mode bits
  // PORT A
  GPIO_MODER_SET_OUTPUT(GPIOA, CLK);
  GPIO_MODER_SET_OUTPUT(GPIOA, E);
  GPIO_MODER_SET_OUTPUT(GPIOA, D);
  GPIO_MODER_SET_OUTPUT(GPIOA, B2);
  GPIO_MODER_SET_OUTPUT(GPIOA, A);
  GPIO_MODER_SET_OUTPUT(GPIOA, R1);
  // PORT B
  GPIO_MODER_SET_OUTPUT(GPIOB, G2);
  GPIO_MODER_SET_OUTPUT(GPIOB, C);
  GPIO_MODER_SET_OUTPUT(GPIOB, OE);
  GPIO_MODER_SET_OUTPUT(GPIOB, LAT);
  // PORT C
  GPIO_MODER_SET_OUTPUT(GPIOC, R2);
  GPIO_MODER_SET_OUTPUT(GPIOC, B1);
  GPIO_MODER_SET_OUTPUT(GPIOC, B);
  GPIO_MODER_SET_OUTPUT(GPIOC, G1);

  // clear RGB lines
  GPIOA->ODR &= ~(B2_Msk | R1_Msk);
  GPIOB->ODR &= ~G2_Msk;
  GPIOC->ODR &= ~(R2_Msk | B1_Msk | G1_Msk);

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
}

static void _clearRGBTopLines(void) {
  GPIOA->ODR &= ~R1_Msk;
  GPIOC->ODR &= ~(B1_Msk | G1_Msk);
}

static void _clearRGBBottomLines(void) {
  GPIOA->ODR &= ~B2_Msk;
  GPIOB->ODR &= ~G2_Msk;
  GPIOC->ODR &= ~R2_Msk;
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
    if (color->g > bit) GPIOC->ODR |= G1_Msk;
    if (color->b > bit) GPIOC->ODR |= B1_Msk;
  } else {
    _clearRGBBottomLines();
    if (color->r > bit) GPIOC->ODR |= R2_Msk;
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
