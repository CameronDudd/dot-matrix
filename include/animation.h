/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdint.h>

#define ANIMATION_ROWS 64
#define ANIMATION_COLS 64

extern uint64_t *animationGrid;

void animationInit(void);
void updateAnimation(void);

#endif  // ANIMATION_H
