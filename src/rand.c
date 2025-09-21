/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

// https://en.wikipedia.org/wiki/Linear_congruential_generator
// X_n_1 = (a * X_n + c) mod m
// m, 0 < m          [modulus]
// a, 0 < a < m      [multiplier]
// c, 0 <= c < m     [increment]
// X_0, 0 <= X_0 < m [seed]

#include "rand.h"

#include <stm32f401xe.h>

#define A 1664525
#define C 1013904223

static uint32_t seed;

void randInit(void) {
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  // Enable ADC1 clock
  ADC1->CR2 |= ADC_CR2_ADON;           // Enable ADC
  ADC1->SQR3 = 0;                      // Channel 0
  uint32_t s = 0;
  for (int i = 0; i < 8; i++) {
    ADC1->CR2 |= ADC_CR2_SWSTART;       // Start conversion
    while (!(ADC1->SR & ADC_SR_EOC)) {  // While the end of conversion bit not set
    }
    s ^= ADC1->DR << (i * 4);
  }
  seed = s ^ SysTick->VAL;
}

uint32_t rand(void) {
  seed = ((A * seed) + C);
  return seed;
}

int randRange(int min, int max) {
  return ((int64_t)((int64_t)rand() * (int64_t)(max - min + 1)) >> 32) + min;
}
