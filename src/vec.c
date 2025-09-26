/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "vec.h"

float dot2(Vec2 a, Vec2 b) {
  return (a.x * b.x) + (a.y * b.y);
}

float cross2(Vec2 a, Vec2 b) {
  return (a.x * b.y) - (a.y * b.x);
}

float dot3(Vec3 a, Vec3 b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 cross3(Vec3 a, Vec3 b) {
  return (Vec3){
      .x = (a.y * b.z) - (a.z * b.y),
      .y = (a.z * b.x) - (a.x * b.z),
      .z = (a.x * b.y) - (a.y * b.x),
  };
}
