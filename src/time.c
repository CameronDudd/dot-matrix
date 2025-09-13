/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "time.h"

#include "stm32f401xe.h"

uint32_t sysclk             = 16000000;  // Default sysclk from HSI 16MHz
volatile uint32_t currentMs = 0;

void SysTick_Handler(void) { ++currentMs; }

void clockInit(void) {
  // HSI     - High Speed Internal Oscillator
  // HSE     - High Speed External Oscillator
  // RCC     - Reset and Clock Control
  // CR      - Clock Control Register
  // VCO     - Voltage Controlled Oscillator
  // ACR     - Access Control Register
  // PLL     - Phase Locked Loop (generates higher freq from input)
  // PLLCFGR - PLL Configuration Register

  // Enable HSI [103]
  RCC->CR |= RCC_CR_HSION;              // HSI (16 MHz)
  while (!(RCC->CR & RCC_CR_HSIRDY)) {  // Wait ready
  }

  // Configure flash latency for 84MHz 2WS [page 46 60]
  FLASH->ACR |= FLASH_ACR_LATENCY_2WS;

  // Want SYSCLK 84MHz [page ]
  //   f_vco_out = f_pll_in * ( PLLN / PLLM )
  //   f_pll_out = f_vco / PLLP
  //   f_usb     = f_vco / PLLQ
  //
  // PLLP:
  //   192MHz <= f_vco_out <= 432MHz
  //   f_vco_out = sysclk * PLLP
  //   f_vco_out = 84 * 4 = 336
  //   PLLP      = 4
  //
  // PLLM:
  //   1MHz <= f_vco_in <= 2MHz
  //   f_vco_in = f_pll_in / PLLM;
  //   PLLM     = f_pll_in / f_vco_in = 16 / 1 = 16
  //
  // PLLN:
  //   f_vco_out = f_vco_in * PLLN
  //   PLLN = f_vco_out / f_vco_in = 336 / 1 = 336
  //
  // PLLQ:
  //   f_usb = f_vco_out / PLLQ
  //   PLLQ  = f_vco_out / f_usb = 336 / 48 = 7
  RCC->PLLCFGR = (1u << RCC_PLLCFGR_PLLP_Pos) | (16u << RCC_PLLCFGR_PLLM_Pos) | (336u << RCC_PLLCFGR_PLLN_Pos) | (7u << RCC_PLLCFGR_PLLQ_Pos) |
                 (0u << RCC_PLLCFGR_PLLSRC_Pos);

  // Enable PLL [103]
  RCC->CR |= RCC_CR_PLLON;              // Enable PLL
  while (!(RCC->CR & RCC_CR_PLLRDY)) {  // Wait ready
  }

  // Set system clock to PLL [107]
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {
  }

  // Update global
  sysclk = 84000000;
}

void systickInit() {
  SysTick->LOAD = (sysclk / 1000) - 1;
  SysTick->VAL  = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void tim2Init(void) {
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  TIM2->PSC = (sysclk / 1000000) - 1;
  TIM2->ARR = 0xFFFFFFFF;
  TIM2->CNT = 0;
  TIM2->EGR = TIM_EGR_UG;
  TIM2->CR1 |= TIM_CR1_CEN;
}

// FIXME(cameron): don't accept unless systickInit called
void sleepMs(uint32_t ms) {
  uint32_t startMs = currentMs;
  while ((currentMs - startMs) < ms) {
  }
}

// FIXME(cameron): don't accept unless tim2Init called
void sleepUs(uint32_t us) {
  uint32_t startUs = TIM2->CNT;
  while ((TIM2->CNT - startUs) < us) {
  }
}

uint32_t epochS(void) { return currentMs / 1000; }
uint32_t epochMs(void) { return currentMs; }
uint32_t epochUs(void) { return TIM2->CNT; }
