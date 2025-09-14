/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stddef.h>

#include "display.h"
#include "rand.h"
#include "time.h"
#include "usart.h"
#include "world.h"

#define SQUARE_WIDTH 5

static void init(void) {
  clockInit();
  systickInit();
  tim2Init();
  usartInit();
  randInit();
  displayInit();
  worldInit();
}

int main(void) {
  init();
  int lastUpdatedTs = 0;
  while (1) {
    if ((lastUpdatedTs == 0) || ((epochMs() - lastUpdatedTs) / 1000 >= 60)) {
      lastUpdatedTs = epochMs();
      clearDisplay();
      for (int i = 0; i < 3000; ++i) {
        int w = randRange(1, 5);
        int h = randRange(1, 5);
        int x = randRange(0, DISPLAY_COLS - w);
        int y = randRange(0, DISPLAY_ROWS - h);
        drawRect(x, y, w, h, randColor());
      }
    }
    renderDisplay();
  }
}
