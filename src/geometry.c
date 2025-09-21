/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "geometry.h"

Mesh2D rectMesh(int x, int y, int w, int h) {
  return (Mesh2D){
      .vertices =
          {
              {x, y},
              {x + w, y},
              {x + w, y + h},
              {x, y + h},
          },
      .numVertices = 4,
      .edges =
          {
              {0, 1},
              {1, 2},
              {2, 3},
              {3, 0},
          },
      .numEdges = 4,
  };
}

Mesh3D cuboidMesh(int x, int y, int z, int w, int h, int d) {
  return (Mesh3D){
      .vertices =
          {
              {x, y, z},
              {x + w, y, z},
              {x + w, y + h, z},
              {x, y + h, z},
              {x, y, z + d},
              {x + w, y, z + d},
              {x + w, y + h, z + d},
              {x, y + h, z + d},
          },
      .numVertices = 8,
      .edges =
          {
              // Back-face
              {0, 1},
              {1, 2},
              {2, 3},
              {3, 0},
              // Face connection
              {0, 4},
              {1, 5},
              {2, 6},
              {3, 7},
              // Front-face
              {4, 5},
              {5, 6},
              {6, 7},
              {7, 4},
          },
      .numEdges = 12,
  };
}
