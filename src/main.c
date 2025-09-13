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
  Entity creature = {
      {
          {1, 1},
          {0, 0},
          3,
          TEAM1,
          0,
      },
      NULL,
  };

  Entity creature2 = {
      {
          {0, 0},
          {0, 0},
          3,
          TEAM2,
          0,
      },
      NULL,
  };

  init();
  str2display(0, 0, "TEST", RED);
  worldAddCreature(&creature);
  worldAddCreature(&creature2);
  while (1) {
    drawWorld(&world);
    renderDisplay();
  }
}
