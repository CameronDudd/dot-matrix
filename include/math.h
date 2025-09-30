/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef MATH_H
#define MATH_H

#include <stdint.h>

#define PI               (float)3.14159265359f
#define TWOPI            (float)6.28318530717f
#define HALFPI           (float)1.57079632679f
#define SQRT2            (float)1.41421356237f
#define SQRT3            (float)1.73205080757f
#define RECIPROCAL_SQRT6 (float)0.40824829046f
#define DEG2PI           (float)0.01745329251

#define TRIG_LOOKUP_SIZE 3600

#define MIN(a, b) ((a < b) ? (a) : (b))
#define MAX(a, b) ((a > b) ? (a) : (b))

#define INF     (*(const float *)&INF_addr)
#define NEG_INF (*(const float *)&NEG_INF_addr)
extern const uint32_t INF_addr, NEG_INF_addr;

float sin(float theta);
float cos(float theta);
float sind(float theta);
float cosd(float theta);

#endif  // MATH_H
