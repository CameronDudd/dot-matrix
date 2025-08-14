/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "time.h"

#include "stm32f401xe.h"

volatile uint32_t currentMs = 0;

void SysTick_Handler(void) { ++currentMs; }

void systickInit(uint32_t clkHz) {
  while (!(RCC->CR & RCC_CR_HSIRDY)) {
  }
  SysTick->LOAD = (clkHz / 1000) - 1;
  SysTick->VAL  = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void tim2Init(uint32_t clkHz) {
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  TIM2->PSC = (clkHz / 1000000) - 1;
  TIM2->ARR = 0xFFFFFFFF;
  TIM2->CNT = 0;
  TIM2->EGR = TIM_EGR_UG;
  TIM2->CR1 |= TIM_CR1_CEN;
}

uint32_t epochMs(void) { return currentMs; }

// FIXME(cameron): don't accept unless systickInit called
void sleepMs(uint32_t ms) {
  uint32_t startMs = currentMs;
  while ((currentMs - startMs) < ms) {
  }
}

uint32_t epochUs(void) { return TIM2->CNT; }

// FIXME(cameron): don't accept unless tim2Init called
void sleepUs(uint32_t us) {
  uint32_t startUs = TIM2->CNT;
  while ((TIM2->CNT - startUs) < us) {
  }
}
