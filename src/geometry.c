/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "geometry.h"

#include "math.h"

// 2D
void rotateMesh2D(Mesh2D *mesh, float theta) {
  // Rotating a point round the origin
  // [ x']   [ cos(t) -sin(t) ] [ x ]
  //       =
  // [ y']   [ sin(t)  cos(t) ] [ y ]
  // To rotate arbitrary point, translate to the origin, rotate and then translate back
  float cx       = mesh->vertices[0].x;
  float cy       = mesh->vertices[0].y;
  float sintheta = sin(theta);
  float costheta = cos(theta);
  for (unsigned int i = 0; i < mesh->numVertices; ++i) {
    Vec2 vertex         = mesh->vertices[i];
    float x             = vertex.x - cx;
    float y             = vertex.y - cy;
    mesh->vertices[i].x = ((x * costheta) - (y * sintheta)) + cx;
    mesh->vertices[i].y = ((x * sintheta) + (y * costheta)) + cy;
  }
}

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

Mesh2D triangleMesh(int x0, int y0, int x1, int y1, int x2, int y2) {
  return (Mesh2D){
      .vertices =
          {
              {x0, y0},
              {x1, y1},
              {x2, y2},
          },
      .numVertices = 3,
      .edges =
          {
              {0, 1},
              {1, 2},
              {2, 0},
          },
      .numEdges = 3,
  };
}

Mesh2D regularNGonMesh(int cx, int cy, int r, int n) {
  Mesh2D mesh;
  float angleStep;
  int maxN         = MIN(MAX_VERTICES, n);
  mesh.numVertices = maxN;
  mesh.numEdges    = maxN;
  for (int i = 0; i < maxN; ++i) {
    angleStep           = 360.0f / maxN;
    mesh.vertices[i].x  = cx + r * cos(angleStep * i);
    mesh.vertices[i].y  = cy + r * sin(angleStep * i);
    mesh.edges[i].start = i;
    mesh.edges[i].end   = (i + 1) % maxN;
  }
  return mesh;
}

// 3D
void pitchMesh3D(Mesh3D *mesh, float theta) {
  // https://en.wikipedia.org/wiki/Rotation_matrix
  // [ x']   [      1       0       0  ] [ x ]
  // [ y'] = [      0   cos(t) -sin(t) ] [ y ]
  // [ z']   [      0   sin(t)  cos(t) ] [ z ]
  // x is horizontally across up so pitch keeps x-axis constant
  float cy       = mesh->vertices[0].y;
  float cz       = mesh->vertices[0].z;
  float sintheta = sin(theta);
  float costheta = cos(theta);
  for (unsigned int i = 0; i < mesh->numVertices; ++i) {
    Vec3 vertex         = mesh->vertices[i];
    float y             = vertex.y - cy;
    float z             = vertex.z - cz;
    mesh->vertices[i].y = ((costheta * y) - (sintheta * z)) + cy;
    mesh->vertices[i].z = ((sintheta * y) + (costheta * z)) + cz;
  }
}

void rollMesh3D(Mesh3D *mesh, float theta) {
  // https://en.wikipedia.org/wiki/Rotation_matrix
  // [ x']   [  cos(t) -sin(t)      0  ] [ x ]
  // [ y'] = [  sin(t)  cos(t)      0  ] [ y ]
  // [ z']   [      0       0       1  ] [ z ]
  // z is out of the screen roll keeps z-axis constant
  float cx       = mesh->vertices[0].x;
  float cy       = mesh->vertices[0].y;
  float sintheta = sin(theta);
  float costheta = cos(theta);
  for (unsigned int i = 0; i < mesh->numVertices; ++i) {
    Vec3 vertex         = mesh->vertices[i];
    float x             = vertex.x - cx;
    float y             = vertex.y - cy;
    mesh->vertices[i].x = ((costheta * x) + (-sintheta * y)) + cx;
    mesh->vertices[i].y = ((sintheta * x) + (costheta * y)) + cy;
  }
}

void yawMesh3D(Mesh3D *mesh, float theta) {
  // https://en.wikipedia.org/wiki/Rotation_matrix
  // [ x']   [  cos(t)      0   sin(t) ] [ x ]
  // [ y'] = [      0       1       0  ] [ y ]
  // [ z']   [ -sin(t)      0   cos(t) ] [ z ]
  // y is vertically up so yaw keeps y-axis constant
  float cx       = mesh->vertices[0].x;
  float cz       = mesh->vertices[0].z;
  float sintheta = sin(theta);
  float costheta = cos(theta);
  for (unsigned int i = 0; i < mesh->numVertices; ++i) {
    Vec3 vertex         = mesh->vertices[i];
    float x             = vertex.x - cx;
    float z             = vertex.z - cz;
    mesh->vertices[i].x = ((costheta * x) + (sintheta * z)) + cx;
    mesh->vertices[i].z = ((-sintheta * x) + (costheta * z)) + cz;
  }
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

Mesh3D pyramidMesh(int x, int y, int z, int w, int d, int h) {
  return (Mesh3D){
      .vertices =
          {
              {x, y, z},
              {x + w, y, z},
              {x + w, y, z + d},
              {x, y, z + d},
              {x + (float)w / 2, y + h, z + (float)d / 2},
          },
      .numVertices = 5,
      .edges =
          {
              // Floor-face
              {0, 1},
              {1, 2},
              {2, 3},
              {3, 0},
              // Peak-faces
              {0, 4},
              {1, 4},
              {2, 4},
              {3, 4},
          },
      .numEdges = 8,
  };
}

Mesh3D sphereMesh(int cx, int cy, int cz, int r, int n) {
  Mesh3D mesh;
  mesh.vertices[0].x = cx;
  mesh.vertices[0].y = cy + r;
  mesh.vertices[0].z = cz;
  mesh.numVertices   = 1;
  mesh.numEdges      = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      float lat                         = 180.0f * ((float)i / n);
      float lon                         = 360.0f * ((float)j / n);
      mesh.vertices[mesh.numVertices].x = cx + (r * sin(lat) * cos(lon));
      mesh.vertices[mesh.numVertices].y = cy + (r * cos(lat));
      mesh.vertices[mesh.numVertices].z = cz + (r * sin(lat) * sin(lon));
      ++mesh.numVertices;

      // Longitude edges
      mesh.edges[mesh.numEdges].start = ((i - 1) * n) + j + 1;
      mesh.edges[mesh.numEdges].end   = ((i - 1) * n) + ((j + 1) % n) + 1;
      ++mesh.numEdges;

      // Latitude edges
      if (i == 1) {  // Connect to north pole
        mesh.edges[mesh.numEdges].start = 0;
        mesh.edges[mesh.numEdges].end   = j + 1;
      } else {
        mesh.edges[mesh.numEdges].start = ((i - 2) * n + j + 1);
        mesh.edges[mesh.numEdges].end   = ((i - 1) * n + j + 1);
      }
      ++mesh.numEdges;
    }
  }
  mesh.vertices[mesh.numVertices].x = cx;
  mesh.vertices[mesh.numVertices].y = cy - r;
  mesh.vertices[mesh.numVertices].z = cz;
  for (int j = 0; j < n; ++j) {
    mesh.edges[mesh.numEdges].start = ((n - 2) * n + j + 1);
    mesh.edges[mesh.numEdges].end   = mesh.numVertices;
    mesh.numEdges++;
  }
  ++mesh.numVertices;
  return mesh;
}
