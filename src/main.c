/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "color.h"
#include "display.h"
#include "time.h"

#define SYSCLK 16000000UL  // 16MHz HSI
#define START  1755177805UL

static void init(void) {
  systickInit(SYSCLK);
  tim2Init(SYSCLK);
  displayInit();
}

int main(void) {
  init();
  while (1) {
    int2display(0, 0, 1755188300 + epochS(), RED);
    str2display(19, 22, "LIVE", RED);
    str2display(26, 22, "LAUGH", RED);
    str2display(33, 22, "TBONE", RED);
    renderDisplay();
    clearDisplay();
  }
}
