/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "data.h"

#include "geometry.h"
#include "math.h"
#include "vec.h"

// FIXME: after a 'camera' has been created the data shouldn't need to be scaled down
#define POLYDATA_SF       (float)0.43f
#define POLYDATA_X_OFFSET (float)0.0f
#define POLYDATA_Y_OFFSET (float)0.0f
#define POLYDATA_ARC_N    3

PolyLine readPolyData(const uint8_t* start, const uint8_t* end) {
  PolyLine polyLine = {
      .numLines = 0,
      .numArcs  = 0,
  };
  const uint8_t* ptr = start;
  while (ptr < end) {
    uint8_t tag = *ptr;
    if (tag == 1) {
      polyLine.lineRecords[polyLine.numLines++] = *(const LineRecord*)ptr;
      ptr += sizeof(LineRecord);
    } else if (tag == 2) {
      polyLine.arcRecords[polyLine.numArcs++] = *(const ArcRecord*)ptr;
      ptr += sizeof(ArcRecord);
    } else {
      break;
    }
  }
  return polyLine;
}

Mesh2D polyData2Mesh2D(const uint8_t* start, const uint8_t* end) {
  Mesh2D mesh = {
      .numVertices = 0,
      .numEdges    = 0,
  };
  const uint8_t* ptr = start;
  while ((ptr < end) && (mesh.numVertices < MAX_VERTICES) && (mesh.numEdges < MAX_EDGES)) {
    uint8_t tag = *ptr;
    if (tag == 1) {
      const LineRecord* line            = (const LineRecord*)ptr;
      mesh.vertices[mesh.numVertices++] = (Vec2){.x = (line->x0 * POLYDATA_SF) + POLYDATA_X_OFFSET, .y = (line->y0 * POLYDATA_SF) + POLYDATA_Y_OFFSET};
      mesh.vertices[mesh.numVertices++] = (Vec2){.x = (line->x1 * POLYDATA_SF) + POLYDATA_X_OFFSET, .y = (line->y1 * POLYDATA_SF) + POLYDATA_Y_OFFSET};
      mesh.edges[mesh.numEdges++]       = (Edge){.start = mesh.numVertices - 2, .end = mesh.numVertices - 1};
      ptr += sizeof(LineRecord);
    } else if (tag == 2) {
      const ArcRecord* arc              = (const ArcRecord*)ptr;
      mesh.vertices[mesh.numVertices++] = (Vec2){.x = ((arc->cx + (arc->r * cosd(arc->startTheta))) * POLYDATA_SF) + POLYDATA_X_OFFSET,
                                                 .y = ((arc->cy + (arc->r * sind(arc->startTheta))) * POLYDATA_SF) + POLYDATA_Y_OFFSET};
      float delta                       = (arc->endTheta - arc->startTheta) / (float)POLYDATA_ARC_N;
      for (int i = 1; i <= POLYDATA_ARC_N; ++i) {
        float angle                       = arc->startTheta + i * delta;
        mesh.vertices[mesh.numVertices++] = (Vec2){.x = ((arc->cx + (arc->r * cosd(angle))) * POLYDATA_SF) + POLYDATA_X_OFFSET,
                                                   .y = ((arc->cy + (arc->r * sind(angle))) * POLYDATA_SF) + POLYDATA_Y_OFFSET};
        mesh.edges[mesh.numEdges++]       = (Edge){.start = mesh.numVertices - 2, .end = mesh.numVertices - 1};
      }
      ptr += sizeof(ArcRecord);
    } else {
      break;
    }
  }
  mesh.centroid = centroidMesh2D(&mesh);
  return mesh;
}

// FIXME: Usage of helper functions to de-clutter is extremely important here
Mesh3D polyData2Mesh3D(const uint8_t* start, const uint8_t* end, float depth) {
  Mesh3D mesh = {
      .numVertices = 0,
      .numEdges    = 0,
  };
  const uint8_t* ptr = start;
  while ((ptr < end) && (mesh.numVertices < MAX_VERTICES) && (mesh.numEdges < MAX_EDGES)) {
    uint8_t tag = *ptr;
    if (tag == 1) {
      const LineRecord* line            = (const LineRecord*)ptr;
      mesh.vertices[mesh.numVertices++] = (Vec3){.x = (line->x0 * POLYDATA_SF) + POLYDATA_X_OFFSET, .y = (line->y0 * POLYDATA_SF) + POLYDATA_Y_OFFSET, .z = 0};
      mesh.vertices[mesh.numVertices++] = (Vec3){.x = (line->x1 * POLYDATA_SF) + POLYDATA_X_OFFSET, .y = (line->y1 * POLYDATA_SF) + POLYDATA_Y_OFFSET, .z = 0};
      mesh.edges[mesh.numEdges++]       = (Edge){.start = mesh.numVertices - 2, .end = mesh.numVertices - 1};
      mesh.vertices[mesh.numVertices++] =
          (Vec3){.x = (line->x0 * POLYDATA_SF) + POLYDATA_X_OFFSET, .y = (line->y0 * POLYDATA_SF) + POLYDATA_Y_OFFSET, .z = depth};
      mesh.vertices[mesh.numVertices++] =
          (Vec3){.x = (line->x1 * POLYDATA_SF) + POLYDATA_X_OFFSET, .y = (line->y1 * POLYDATA_SF) + POLYDATA_Y_OFFSET, .z = depth};
      mesh.edges[mesh.numEdges++] = (Edge){.start = mesh.numVertices - 2, .end = mesh.numVertices - 1};
      mesh.edges[mesh.numEdges++] = (Edge){.start = mesh.numVertices - 3, .end = mesh.numVertices - 1};
      mesh.edges[mesh.numEdges++] = (Edge){.start = mesh.numVertices - 4, .end = mesh.numVertices - 2};
      ptr += sizeof(LineRecord);
    } else if (tag == 2) {
      const ArcRecord* arc              = (const ArcRecord*)ptr;
      mesh.vertices[mesh.numVertices++] = (Vec3){.x = ((arc->cx + (arc->r * cosd(arc->startTheta))) * POLYDATA_SF) + POLYDATA_X_OFFSET,
                                                 .y = ((arc->cy + (arc->r * sind(arc->startTheta))) * POLYDATA_SF) + POLYDATA_Y_OFFSET,
                                                 .z = 0};
      mesh.vertices[mesh.numVertices++] = (Vec3){.x = ((arc->cx + (arc->r * cosd(arc->startTheta))) * POLYDATA_SF) + POLYDATA_X_OFFSET,
                                                 .y = ((arc->cy + (arc->r * sind(arc->startTheta))) * POLYDATA_SF) + POLYDATA_Y_OFFSET,
                                                 .z = depth};
      float delta                       = (arc->endTheta - arc->startTheta) / (float)POLYDATA_ARC_N;
      for (int i = 1; i <= POLYDATA_ARC_N; ++i) {
        float angle                       = arc->startTheta + i * delta;
        mesh.vertices[mesh.numVertices++] = (Vec3){.x = ((arc->cx + (arc->r * cosd(angle))) * POLYDATA_SF) + POLYDATA_X_OFFSET,
                                                   .y = ((arc->cy + (arc->r * sind(angle))) * POLYDATA_SF) + POLYDATA_Y_OFFSET,
                                                   .z = 0};
        mesh.vertices[mesh.numVertices++] = (Vec3){.x = ((arc->cx + (arc->r * cosd(angle))) * POLYDATA_SF) + POLYDATA_X_OFFSET,
                                                   .y = ((arc->cy + (arc->r * sind(angle))) * POLYDATA_SF) + POLYDATA_Y_OFFSET,
                                                   .z = depth};
        mesh.edges[mesh.numEdges++]       = (Edge){.start = mesh.numVertices - 4, .end = mesh.numVertices - 2};
        mesh.edges[mesh.numEdges++]       = (Edge){.start = mesh.numVertices - 3, .end = mesh.numVertices - 1};
        mesh.edges[mesh.numEdges++]       = (Edge){.start = mesh.numVertices - 2, .end = mesh.numVertices - 1};
      }
      ptr += sizeof(ArcRecord);
    } else {
      break;
    }
  }
  mesh.centroid = centroidMesh3D(&mesh);
  centerMesh3D(&mesh);
  return mesh;
}
