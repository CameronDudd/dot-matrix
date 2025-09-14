/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "vec.h"

#define UPDATE_ENTITY(entity) (entity).update(&(entity))

typedef enum {
  FRIEND = 1,
  FOE    = 2,
  FOOD   = 3,
} EntityType;

typedef struct {
  Vec2 pos;
  Vec2 vel;
  uint8_t health;
  EntityType type;
  uint32_t lastUpdatedMs;
} EntityState;

typedef struct Entity {
  EntityState state;
  void (*update)(struct Entity *entity);
} Entity;

void updateEntity(Entity *entity);

#endif  // ENTITY_H
