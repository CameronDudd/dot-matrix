/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "data.h"

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
