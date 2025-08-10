/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "time.h"

#include "stm32f401xe.h"

volatile uint32_t currentMs = 0;

void SysTick_Handler(void) { ++currentMs; }

void systickInit(uint32_t clkHz) {
  SysTick->LOAD = (clkHz / 1000) - 1;
  SysTick->VAL  = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void sleepMs(uint32_t ms) {
  uint32_t endMs = currentMs + ms;
  while ((endMs - currentMs) > 0) {
    __WFI();
  }
}
