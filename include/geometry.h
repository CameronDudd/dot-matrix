/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vec.h"

#define MAX_VERTICES 220
#define MAX_EDGES    660

typedef struct {
  int start;
  int end;
} Edge;

typedef struct {
  Vec2 vertices[MAX_VERTICES];
  unsigned int numVertices;
  Edge edges[MAX_EDGES];
  unsigned int numEdges;
  Vec2 centroid;
} Mesh2D;

typedef struct {
  Vec3 vertices[MAX_VERTICES];
  unsigned int numVertices;
  Edge edges[MAX_EDGES];
  unsigned int numEdges;
  Vec3 centroid;
} Mesh3D;

// 2D
Vec2 centroidMesh2D(Mesh2D* mesh);
int pointInTriangleMesh2D(Mesh2D* mesh, Vec2 p);
void rotateMesh2D(Mesh2D* mesh, float theta);
Mesh2D rectMesh(int x, int y, int w, int h);
Mesh2D triangleMesh(int x0, int y0, int x1, int y1, int x2, int y2);
Mesh2D regularNGonMesh(int cx, int cy, int r, int n);

// 3D
Vec3 centroidMesh3D(Mesh3D* mesh);
void rollMesh3D(Mesh3D* mesh, float theta);
void pitchMesh3D(Mesh3D* mesh, float theta);
void yawMesh3D(Mesh3D* mesh, float theta);
Mesh3D cuboidMesh(int x, int y, int z, int w, int h, int d);
Mesh3D pyramidMesh(int x, int y, int z, int w, int d, int h);
Mesh3D sphereMesh(int cx, int cy, int cz, int r, int n);

#endif
