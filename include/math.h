/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MATH_H
#define MATH_H

#include <stdint.h>

#define PI               (float)3.14159265359
#define SQRT2            (float)1.41421356237
#define SQRT3            (float)1.73205080757
#define RECIPROCAL_SQRT6 (float)0.40824829046

#define TRIG_LOOKUP_SIZE 360

#define MIN(a, b) ((a < b) ? (a) : (b))
#define MAX(a, b) ((a > b) ? (a) : (b))

#define INF     (*(const float *)&INF_addr)
#define NEG_INF (*(const float *)&NEG_INF_addr)
extern const uint32_t INF_addr, NEG_INF_addr;

float sin(float theta);
float cos(float theta);

#endif  // MATH_H
