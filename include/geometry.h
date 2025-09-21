/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vec.h"

#define MAX_VERTICES 10
#define MAX_EDGES    30

typedef struct {
  int start;
  int end;
} Edge;

typedef struct {
  Vec2 vertices[MAX_VERTICES];
  unsigned int numVertices;
  Edge edges[MAX_EDGES];
  unsigned int numEdges;
} Mesh2D;

typedef struct {
  Vec3 vertices[MAX_VERTICES];
  unsigned int numVertices;
  Edge edges[MAX_EDGES];
  unsigned int numEdges;
} Mesh3D;

Mesh2D rectMesh(int x, int y, int w, int h);
Mesh3D cuboidMesh(int x, int y, int z, int w, int h, int d);

#endif
