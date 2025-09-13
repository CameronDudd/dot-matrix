/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stddef.h>

#include "color.h"
#include "display.h"
#include "entity.h"
#include "rand.h"
#include "time.h"
#include "usart.h"
#include "vec.h"

#define SQUARE_WIDTH 5

static void init(void) {
  clockInit();
  systickInit();
  tim2Init();
  usartInit();
  randInit();
  displayInit();
}

int main(void) {
  init();

  Creature friend = {
      {
          {32, 32},
          {1, -1},
          RED,
          0,
      },
      NULL,
      drawCreature,
  };

  while (1) {
    DRAW_OBJECT(friend);
    renderDisplay();
    clearDisplay();
  }
}
