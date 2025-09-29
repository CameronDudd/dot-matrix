/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "vec.h"

Vec2 add2(Vec2 a, Vec2 b) {  // a + b
  return (Vec2){
      .x = a.x + b.x,
      .y = a.y + b.y,
  };
}

Vec2 sub2(Vec2 a, Vec2 b) {  // a - b
  return (Vec2){
      .x = a.x - b.x,
      .y = a.y - b.y,
  };
}

float dot2(Vec2 a, Vec2 b) {
  return (a.x * b.x) + (a.y * b.y);
}

float cross2(Vec2 a, Vec2 b) {
  return (a.x * b.y) - (a.y * b.x);
}

Vec2 perpendicular2(Vec2 vec) {  // Counter-Clockwise
  return (Vec2){
      .x = -vec.y,
      .y = vec.x,
  };
}

int pointOnLeftOfLine(Vec2 a, Vec2 b, Vec2 p) {
  Vec2 ap     = sub2(p, a);
  Vec2 ab     = sub2(b, a);
  Vec2 abPerp = perpendicular2(ab);
  return dot2(ap, abPerp) >= 0;
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
