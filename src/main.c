/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stddef.h>

#include "display.h"
#include "entity.h"
#include "rand.h"
#include "time.h"
#include "usart.h"

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

  int minX = SQUARE_WIDTH;
  int maxX = DISPLAY_COLS - SQUARE_WIDTH;
  int minY = SQUARE_WIDTH;
  int maxY = DISPLAY_ROWS - SQUARE_WIDTH;

  Entity entities[] = {
      CREATE_ENTITY(randRange(minX, maxX), randRange(minY, maxY), SQUARE_WIDTH, SQUARE_WIDTH, randRange(1, 10), randRange(1, 10), RED, moveSquare, drawSquare),
      CREATE_ENTITY(randRange(minX, maxX), randRange(minY, maxY), SQUARE_WIDTH, SQUARE_WIDTH, randRange(1, 10), randRange(1, 10), RED, moveSquare, drawSquare),
      CREATE_ENTITY(randRange(minX, maxX), randRange(minY, maxY), SQUARE_WIDTH, SQUARE_WIDTH, randRange(1, 10), randRange(1, 10), RED, moveSquare, drawSquare),
  };

  while (1) {
    for (size_t i = 0; i < sizeof(entities) / sizeof(Entity); ++i) {
      ENTITY_DRAW(entities[i]);
      ENTITY_UPDATE(entities[i]);
    }
    renderDisplay();
    clearDisplay();
  }
}
