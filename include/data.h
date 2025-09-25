/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef DATA_H
#define DATA_H

#include <stdint.h>

#define MAX_DATA_LINES 50

#define poly1_start _binary_data_poly1_dat_start
#define poly1_end   _binary_data_poly1_dat_end
#define poly1_size  _binary_data_poly1_dat_size
extern const uint8_t poly1_start[];
extern const uint8_t poly1_end[];
extern const uint8_t poly1_size;

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

#endif  // DATA_H
