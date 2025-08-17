/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stdint.h>

#include "stm32f401xe.h"
#include "time.h"
#include "usart.h"

#define IRQ_ZERO      16
#define IRQ_POS(irqn) ((irqn) + IRQ_ZERO)

extern uint32_t _stack;
extern uint32_t _data_loadaddr, _data, _edata;
extern uint32_t _bss, _ebss;

void reset_handler(void);
void default_handler(void);

// clang-format off
__attribute__((section(".vectors"))) void (*const vector_table[])(void) = {
  (void (*)(void))(&_stack),
  reset_handler,
  [2 ... 14] = default_handler,
  [15] = SysTick_Handler,
  [IRQ_POS(USART2_IRQn)] = Usart2GlobalInterrupt_Handler,
};
// clang-format on

void reset_handler(void) {
  uint32_t *src = &_data_loadaddr;
  uint32_t *dst = &_data;
  while (dst < &_edata) {
    *dst++ = *src++;
  }

  dst = &_bss;
  while (dst < &_ebss) {
    *dst++ = 0;
  }

  extern int main(void);
  main();

  while (1) {
  }
}

void default_handler(void) {
  while (1) {
  }
}
