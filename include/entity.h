/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "color.h"
#include "vec.h"

#define DRAW_OBJECT(obj)   (obj).draw(&(obj))
#define UPDATE_OBJECT(obj) (obj).update(&(obj))

typedef struct {
  Vec2 pos;
  Vec2 vel;
  const RGBColor *color;
  uint32_t lastUpdatedMs;
} EntityState;

typedef struct Creature {
  EntityState state;
  void (*update)(struct Creature *creature);
  void (*draw)(struct Creature *creature);
} Creature;

#endif  // ENTITY_H
