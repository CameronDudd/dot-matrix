/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef DATA_H
#define DATA_H

#include <stdint.h>

#include "geometry.h"

#define MAX_DATA_LINES 50

#define poly1Start _binary_data_poly1_dat_start
#define poly1End   _binary_data_poly1_dat_end
#define poly1Size  _binary_data_poly1_dat_size
extern const uint8_t poly1Start[];
extern const uint8_t poly1End[];
extern const uint8_t poly1Size;

#define poly2Start _binary_data_poly2_dat_start
#define poly2End   _binary_data_poly2_dat_end
#define poly2Size  _binary_data_poly2_dat_size
extern const uint8_t poly2Start[];
extern const uint8_t poly2End[];
extern const uint8_t poly2Size;

#define poly3Start _binary_data_poly3_dat_start
#define poly3End   _binary_data_poly3_dat_end
#define poly3Size  _binary_data_poly3_dat_size
extern const uint8_t poly3Start[];
extern const uint8_t poly3End[];
extern const uint8_t poly3Size;

#define poly4Start _binary_data_poly4_dat_start
#define poly4End   _binary_data_poly4_dat_end
#define poly4Size  _binary_data_poly4_dat_size
extern const uint8_t poly4Start[];
extern const uint8_t poly4End[];
extern const uint8_t poly4Size;

#define poly5Start _binary_data_poly5_dat_start
#define poly5End   _binary_data_poly5_dat_end
#define poly5Size  _binary_data_poly5_dat_size
extern const uint8_t poly5Start[];
extern const uint8_t poly5End[];
extern const uint8_t poly5Size;

#define poly6Start _binary_data_poly6_dat_start
#define poly6End   _binary_data_poly6_dat_end
#define poly6Size  _binary_data_poly6_dat_size
extern const uint8_t poly6Start[];
extern const uint8_t poly6End[];
extern const uint8_t poly6Size;

#define poly7Start _binary_data_poly7_dat_start
#define poly7End   _binary_data_poly7_dat_end
#define poly7Size  _binary_data_poly7_dat_size
extern const uint8_t poly7Start[];
extern const uint8_t poly7End[];
extern const uint8_t poly7Size;

#define poly8Start _binary_data_poly8_dat_start
#define poly8End   _binary_data_poly8_dat_end
#define poly8Size  _binary_data_poly8_dat_size
extern const uint8_t poly8Start[];
extern const uint8_t poly8End[];
extern const uint8_t poly8Size;

typedef struct __attribute__((packed)) {
  uint8_t tag;  // 1
  float x0;
  float y0;
  float x1;
  float y1;
} LineRecord;

typedef struct __attribute__((packed)) {
  uint8_t tag;  // 2
  float cx;
  float cy;
  float r;
  float startTheta;
  float endTheta;
} ArcRecord;

typedef struct {
  LineRecord lineRecords[MAX_DATA_LINES];
  unsigned int numLines;
  ArcRecord arcRecords[MAX_DATA_LINES];
  unsigned int numArcs;
} PolyLine;

PolyLine readPolyData(const uint8_t* start, const uint8_t* end);
Mesh2D polyData2Mesh2D(const uint8_t* start, const uint8_t* end);

#endif  // DATA_H
