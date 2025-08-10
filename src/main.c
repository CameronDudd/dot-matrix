/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "color.h"
#include "display.h"
#include "gpio.h"
#include "time.h"

static void init(void) {
  systickInit(16000000);
  gpioInit();
  clearDisplay();
}

int main(void) {
  init();
  str2display(0, 0, "Hello, world!", RED);
  str2display(7, 0, "Hello, world!", GREEN);
  str2display(14, 0, "Hello, world!", BLUE);
  str2display(21, 0, "Hello, world!", WHITE);
  while (1) {
    renderDisplay();
  }
  return 0;
}
