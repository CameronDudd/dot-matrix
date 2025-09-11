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
  ADC1->CR2 |= ADC_CR2_SWSTART;        // Start conversion
  while (!(ADC1->SR & ADC_SR_EOC)) {   // While the end of conversion bit not set
  }
  seed = ADC1->DR;  // Read data register
}

uint32_t rand(void) {
  seed = ((A * seed) + C);
  return seed;
}

uint32_t randRange(uint32_t min, uint32_t max) {
  uint64_t range = (uint64_t)max - (uint64_t)min + 1;  // cast range to 64 to not always bring value to zero; +1 inclusive
  return (uint32_t)(((uint64_t)rand() * range) >> 32) + min;
}
