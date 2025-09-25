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

#define poly2_start _binary_data_poly2_dat_start
#define poly2_end   _binary_data_poly2_dat_end
#define poly2_size  _binary_data_poly2_dat_size
extern const uint8_t poly2_start[];
extern const uint8_t poly2_end[];
extern const uint8_t poly2_size;

#define poly3_start _binary_data_poly3_dat_start
#define poly3_end   _binary_data_poly3_dat_end
#define poly3_size  _binary_data_poly3_dat_size
extern const uint8_t poly3_start[];
extern const uint8_t poly3_end[];
extern const uint8_t poly3_size;

#define poly4_start _binary_data_poly4_dat_start
#define poly4_end   _binary_data_poly4_dat_end
#define poly4_size  _binary_data_poly4_dat_size
extern const uint8_t poly4_start[];
extern const uint8_t poly4_end[];
extern const uint8_t poly4_size;

#define poly5_start _binary_data_poly5_dat_start
#define poly5_end   _binary_data_poly5_dat_end
#define poly5_size  _binary_data_poly5_dat_size
extern const uint8_t poly5_start[];
extern const uint8_t poly5_end[];
extern const uint8_t poly5_size;

#define poly6_start _binary_data_poly6_dat_start
#define poly6_end   _binary_data_poly6_dat_end
#define poly6_size  _binary_data_poly6_dat_size
extern const uint8_t poly6_start[];
extern const uint8_t poly6_end[];
extern const uint8_t poly6_size;

#define poly7_start _binary_data_poly7_dat_start
#define poly7_end   _binary_data_poly7_dat_end
#define poly7_size  _binary_data_poly7_dat_size
extern const uint8_t poly7_start[];
extern const uint8_t poly7_end[];
extern const uint8_t poly7_size;

#define poly8_start _binary_data_poly8_dat_start
#define poly8_end   _binary_data_poly8_dat_end
#define poly8_size  _binary_data_poly8_dat_size
extern const uint8_t poly8_start[];
extern const uint8_t poly8_end[];
extern const uint8_t poly8_size;

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
