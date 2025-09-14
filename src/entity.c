/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "entity.h"

#include "time.h"

void updateEntity(Entity *entity) {
  EntityState *state = &entity->state;

  // Init state
  if (state->lastUpdatedMs == 0) {
    state->lastUpdatedMs = epochMs();
    return;
  }

  // Update timing
  uint32_t nowMs       = epochMs();
  uint32_t deltaMs     = nowMs - state->lastUpdatedMs;
  state->lastUpdatedMs = nowMs;
  float dt             = deltaMs / 1000.0f;

  // Update position
  state->pos.x += state->vel.x * dt;
  state->pos.y += state->vel.y * dt;
}
