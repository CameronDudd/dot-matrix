/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "gpio.h"
#include "time.h"

static void init(void) {
  systickInit(16000000);
  gpioInit();
}

int main(void) {
  init();
  while (1) {
    gpioToggleLED();
    sleepMs(1000);
  }
  return 0;
}
