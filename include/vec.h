/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef VEC_H
#define VEC_H

typedef struct {
  float x;
  float y;
} Vec2;

typedef struct {
  float x;
  float y;
  float z;
} Vec3;

Vec2 add2(Vec2 *a, Vec2 *b);
Vec2 sub2(Vec2 *a, Vec2 *b);
float dot2(Vec2 *a, Vec2 *b);
float cross2(Vec2 *a, Vec2 *b);
Vec2 perpendicular2(Vec2 *vec);

float dot3(Vec3 *a, Vec3 *b);
Vec3 cross3(Vec3 *a, Vec3 *b);

#endif  // VEC_H
