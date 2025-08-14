/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "time.h"
#include "usart.h"
#include "utils.h"

#define SYSCLK 16000000UL  // 16MHz HSI

static void init(void) {
  systickInit(SYSCLK);
  tim2Init(SYSCLK);
  usartInit(SYSCLK);
}

int main(void) {
  init();
  char buff[200];
  while (1) {
    itoa(1234, buff);
    usart2TxStr(buff);
    sleepUs(1000000);
  }
}
