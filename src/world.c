/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "world.h"

#include <stddef.h>

#include "entity.h"
#include "time.h"
#include "usart.h"

World world;

void worldInit(void) {
  for (uint8_t row = 0; row < WORLD_ROWS; ++row) {
    for (uint8_t col = 0; col < WORLD_COLS; ++col) {
      world.grid[row][col] = (void *)0;
    }
  }
}

void worldUpdate(void) {
  static uint32_t lastUpdatedMs = 0;
  if (lastUpdatedMs == 0) {
    lastUpdatedMs = epochMs();
    return;
  }

  uint32_t nowMs = epochMs();
  uint32_t dt    = (nowMs - lastUpdatedMs) / 1000;
  if (dt < WORLD_SECONDS_PER_TICK) {
    return;
  }
  lastUpdatedMs = nowMs;
}

void worldAddFood(float x, float y) {
  Entity food = {
      {
          {x, y},
          {0, 0},
          0,
          FOOD,
          0,
      },
      NULL,
  };
  usart2Printf("adding food to world @ (%d, %d)\r\n", (int)x, (int)y);
  world.entities[world.numEntities] = food;
  world.grid[(int)y][(int)x]        = &world.entities[world.numEntities];
  ++world.numEntities;
}

void worldAddFriend(float x, float y) {
  Entity friend = {
      {
          {x, y},
          {0, 0},
          0,
          FRIEND,
          0,
      },
      updateEntity,
  };
  int xi = (int)x;
  int yi = (int)y;
  usart2Printf("adding creature to world @ (%d, %d)\r\n", xi, yi);
  world.entities[world.numEntities]  = friend;
  world.grid[(int)y][(int)x]         = &world.entities[world.numEntities];
  world.grid[(int)y + 1][(int)x]     = &world.entities[world.numEntities];
  world.grid[(int)y][(int)x + 1]     = &world.entities[world.numEntities];
  world.grid[(int)y + 1][(int)x + 1] = &world.entities[world.numEntities];
  ++world.numEntities;
}
