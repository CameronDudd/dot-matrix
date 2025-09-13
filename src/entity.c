/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "entity.h"

#include "display.h"
#include "time.h"

void moveSquare(Entity *square) {
  EntityState *state = &square->state;
  if (state->lastUpdatedMs == 0) {
    state->lastUpdatedMs = epochMs();
    return;
  }

  // Update timing
  uint32_t nowMs       = epochMs();
  uint32_t deltaMs     = nowMs - state->lastUpdatedMs;
  state->lastUpdatedMs = nowMs;
  float dt             = deltaMs / 1000.0f;

  // Detect collision
  if ((state->pos.x <= 0) || (DISPLAY_ROWS <= state->pos.x + square->w)) {
    state->vel.x = -state->vel.x;
  }
  if ((state->pos.y <= 0) || (DISPLAY_COLS <= state->pos.y + square->h)) {
    state->vel.y = -state->vel.y;
  }

  // Update position
  state->pos.x += state->vel.x * dt;
  state->pos.y += state->vel.y * dt;
}
