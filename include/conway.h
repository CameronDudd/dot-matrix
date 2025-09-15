/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef CONWAY_H
#define CONWAY_H

#include <stdint.h>

#define CONWAY_ROWS 64
#define CONWAY_COLS 64

extern uint64_t *conwayGrid;

void conwayUpdate(void);

#endif  // CONWAY_H
