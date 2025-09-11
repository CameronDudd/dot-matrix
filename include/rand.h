/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef RAND_H
#define RAND_H

#include <stdint.h>

void randInit(void);
uint32_t rand(void);
uint32_t randRange(uint32_t min, uint32_t max);

#endif  // RAND_H
