/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stddef.h>

#include "display.h"
#include "entity.h"
#include "time.h"
#include "usart.h"

#define SYSCLK 16000000UL  // 16MHz HSI

Entity square1 = {
    .state =
        {
            .pos           = {.x = 30, .y = 30},
            .vel           = {.x = -7, .y = -3},
            .colorIdx      = 0,
            .lastUpdatedMs = 0,
        },
    .w      = 10,
    .h      = 10,
    .update = moveSquare,
    .draw   = drawSquare,
};

Entity square2 = {
    .state =
        {
            .pos           = {.x = 30, .y = 30},
            .vel           = {.x = 10, .y = -7},
            .colorIdx      = 1,
            .lastUpdatedMs = 0,
        },
    .w      = 10,
    .h      = 10,
    .update = moveSquare,
    .draw   = drawSquare,
};

Entity square3 = {
    .state =
        {
            .pos           = {.x = 30, .y = 30},
            .vel           = {.x = -2, .y = 8},
            .colorIdx      = 2,
            .lastUpdatedMs = 0,
        },
    .w      = 10,
    .h      = 10,
    .update = moveSquare,
    .draw   = drawSquare,
};

Entity square4 = {
    .state =
        {
            .pos           = {.x = 30, .y = 30},
            .vel           = {.x = 9, .y = 3},
            .colorIdx      = 3,
            .lastUpdatedMs = 0,
        },
    .w      = 10,
    .h      = 10,
    .update = moveSquare,
    .draw   = drawSquare,
};

static void init(void) {
  systickInit(SYSCLK);
  tim2Init(SYSCLK);
  usartInit(SYSCLK);
  displayInit();
}

int main(void) {
  Entity entities[] = {square1, square2, square3, square4};

  init();
  while (1) {
    for (size_t i = 0; i < sizeof(entities) / sizeof(Entity); ++i) {
      ENTITY_DRAW(entities[i]);
      ENTITY_UPDATE(entities[i]);
    }
    renderDisplay();
    clearDisplay();
  }
}
