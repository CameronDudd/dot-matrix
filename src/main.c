/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "display.h"
#include "time.h"
#include "usart.h"

#define SYSCLK 16000000UL  // 16MHz HSI
#define START  1755177805UL

static void init(void) {
  systickInit(SYSCLK);
  tim2Init(SYSCLK);
  usartInit(SYSCLK);
  displayInit();
}

int main(void) {
  init();
  while (1) {
    if (recvBuffComplete) {
      clearDisplay();
      recvBuff2display();
      recvBuffComplete = 0;
    }
    renderDisplay();
  }
}
