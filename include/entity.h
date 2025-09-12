/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "vec.h"

#define ENTITY_DRAW(obj)   (obj).draw(&(obj))
#define ENTITY_UPDATE(obj) (obj).update(&(obj))

typedef struct {
  Vec2 pos;
  Vec2 vel;
  int colorIdx;
  uint32_t lastUpdatedMs;
} EntityState;

typedef struct Entity {
  EntityState state;
  int w;
  int h;
  void (*update)(struct Entity *entity);
  void (*draw)(struct Entity *entity);
} Entity;

#define CREATE_ENTITY(x, y, w, h, vx, vy, update, draw) \
  (Entity) { .state = {.pos = {(x), (y)}, .vel = {(vx), (vy)}, .colorIdx = 0, .lastUpdatedMs = 0}, (w), (h), (update), (draw) }

void moveSquare(Entity *square);

#endif  // ENTITY_H
