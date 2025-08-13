/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "gpio.h"

#include "pin_defs.h"
#include "stm32f401xe.h"

#define GPIO_MODER_CLR(port, pin)        ((port)->MODER &= ~(0x3 << ((pin) * 2)))
#define GPIO_MODER_SET_OUTPUT(port, pin) ((port)->MODER |= (0x1 << ((pin) * 2)))
#define GPIO_MODER_SET_INPUT(port, pin)  ((port)->MODER &= ~(0x3 << ((pin) * 2)))

static int _gpioInitialised = 0;

void gpioInit(void) {
  if (_gpioInitialised) {
    return;
  }
  _gpioInitialised = 1;
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);

  // Clear mode bits
  // PORT A
  GPIO_MODER_CLR(GPIOA, 2);   // BL TXD
  GPIO_MODER_CLR(GPIOA, 3);   // BL RXD
  GPIO_MODER_CLR(GPIOA, 5);   // DISP CLK
  GPIO_MODER_CLR(GPIOA, 6);   // DISP E
  GPIO_MODER_CLR(GPIOA, 7);   // DISP D
  GPIO_MODER_CLR(GPIOA, 8);   // DISP B2
  GPIO_MODER_CLR(GPIOA, 9);   // DISP A
  GPIO_MODER_CLR(GPIOA, 10);  // DISP R1
  GPIO_MODER_CLR(GPIOA, 13);  // BL STATE
  GPIO_MODER_CLR(GPIOA, 14);  // BL EN
  // PORT B
  GPIO_MODER_CLR(GPIOB, 3);   // DISP G1
  GPIO_MODER_CLR(GPIOB, 4);   // DISP R2
  GPIO_MODER_CLR(GPIOB, 5);   // DISP B1
  GPIO_MODER_CLR(GPIOB, 6);   // DISP C
  GPIO_MODER_CLR(GPIOB, 8);   // DISP OE
  GPIO_MODER_CLR(GPIOB, 9);   // DISP LAT
  GPIO_MODER_CLR(GPIOB, 10);  // DISP G2
  // PORT C
  GPIO_MODER_CLR(GPIOC, 7);  // DISP B

  // Set mode bits input (redundant)
  GPIO_MODER_SET_INPUT(GPIOA, 3);
  GPIO_MODER_SET_INPUT(GPIOA, 13);

  // Set mode bits output
  // PORT A
  GPIO_MODER_SET_OUTPUT(GPIOA, 2);
  GPIO_MODER_SET_OUTPUT(GPIOA, 5);
  GPIO_MODER_SET_OUTPUT(GPIOA, 6);
  GPIO_MODER_SET_OUTPUT(GPIOA, 7);
  GPIO_MODER_SET_OUTPUT(GPIOA, 8);
  GPIO_MODER_SET_OUTPUT(GPIOA, 9);
  GPIO_MODER_SET_OUTPUT(GPIOA, 10);
  GPIO_MODER_SET_OUTPUT(GPIOA, 14);
  // PORT B
  GPIO_MODER_SET_OUTPUT(GPIOB, 3);
  GPIO_MODER_SET_OUTPUT(GPIOB, 4);
  GPIO_MODER_SET_OUTPUT(GPIOB, 5);
  GPIO_MODER_SET_OUTPUT(GPIOB, 6);
  GPIO_MODER_SET_OUTPUT(GPIOB, 8);
  GPIO_MODER_SET_OUTPUT(GPIOB, 9);
  GPIO_MODER_SET_OUTPUT(GPIOB, 10);
  // PORT C
  GPIO_MODER_SET_OUTPUT(GPIOC, 7);

  // clear RGB lines
  GPIOA->ODR &= ~(MATRIX_B2 | MATRIX_R1);
  GPIOB->ODR &= ~(MATRIX_G1 | MATRIX_R2 | MATRIX_B1 | MATRIX_G2);

  // clear row select lines
  GPIOA->ODR &= ~(MATRIX_E | MATRIX_D | MATRIX_A);
  GPIOB->ODR &= ~MATRIX_C;
  GPIOC->ODR &= ~MATRIX_B;

  // clear clock line
  GPIOA->ODR &= ~MATRIX_CLK;

  // clear latch line
  GPIOB->ODR &= ~MATRIX_LAT;

  // set output disabled
  GPIOB->ODR |= MATRIX_OE;  // OE HIGH - DISPLAY OFF
}

void gpioDisplayOutputEnable(void) { GPIOB->ODR &= ~MATRIX_OE; }

void gpioDisplayOutputDisable() { GPIOB->ODR |= MATRIX_OE; }

void gpioDisplayClock(void) {
  GPIOA->ODR |= MATRIX_CLK;
  GPIOA->ODR &= ~MATRIX_CLK;
}

void gpioDisplayLatch(void) {
  GPIOB->ODR |= MATRIX_LAT;
  GPIOB->ODR &= ~MATRIX_LAT;
}

void gpioDisplaySelectRow(uint8_t row) {
  GPIOA->ODR &= ~(MATRIX_E | MATRIX_D | MATRIX_A);
  GPIOB->ODR &= ~MATRIX_C;
  GPIOC->ODR &= ~MATRIX_B;
  if ((row >> 0) & 1u) GPIOA->ODR |= MATRIX_A;
  if ((row >> 1) & 1u) GPIOC->ODR |= MATRIX_B;
  if ((row >> 2) & 1u) GPIOB->ODR |= MATRIX_C;
  if ((row >> 3) & 1u) GPIOA->ODR |= MATRIX_D;
  if ((row >> 4) & 1u) GPIOA->ODR |= MATRIX_E;
}

void gpioDisplaySetColorLines(const RGBColor1 color, const uint8_t bottom) {
  if (!bottom) {
    // clear lines
    GPIOA->ODR &= ~MATRIX_R1;
    GPIOB->ODR &= ~(MATRIX_G1 | MATRIX_B1);
    // set lines
    if (color.r) GPIOA->ODR |= MATRIX_R1;
    if (color.g) GPIOB->ODR |= MATRIX_G1;
    if (color.b) GPIOB->ODR |= MATRIX_B1;
  } else {
    // clear lines
    GPIOA->ODR &= ~MATRIX_B2;
    GPIOB->ODR &= ~(MATRIX_R2 | MATRIX_G2);
    // set lines
    if (color.r) GPIOB->ODR |= MATRIX_R2;
    if (color.g) GPIOB->ODR |= MATRIX_G2;
    if (color.b) GPIOA->ODR |= MATRIX_B2;
  }
}

void gpioHC05Enable(void) { GPIOA->ODR |= HC_05_EN; }

void gpioHC05Disable(void) { GPIOA->ODR &= ~HC_05_EN; }
