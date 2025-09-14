/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef WORLD_H
#define WORLD_H

#include <stddef.h>

#include "entity.h"

#define WORLD_SECONDS_PER_TICK 1
#define WORLD_COLS             64
#define WORLD_ROWS             64
#define WORLD_MAX_ENTITIES     256

typedef struct {
  Entity entities[WORLD_MAX_ENTITIES];
  Entity *grid[WORLD_ROWS][WORLD_COLS];
  size_t numEntities;
} World;

extern World world;

void worldInit(void);
void worldUpdate(void);
void worldAddFood(float x, float y);
void worldAddFriend(float x, float y);

#endif  // WORLD_H
