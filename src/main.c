#include "stm32f401xe.h"

static void delay(volatile uint32_t count) {
  while (count--) {
    __asm__ volatile("nop");
  }
}

int main(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  GPIOA->MODER &= ~(3u << (5 * 2));
  GPIOA->MODER |= (1u << (5 * 2));

  while (1) {
    GPIOA->ODR ^= (1u << 5);
    delay(1000000);
  }
}
