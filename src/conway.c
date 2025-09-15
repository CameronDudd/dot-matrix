/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

/*
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 * 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 * 2. Any live cell with two or three live neighbours lives on to the next generation.
 * 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
 * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 */

#include "conway.h"

#include <stddef.h>

#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))

static uint64_t grid1[CONWAY_ROWS] = {
    // clang-format off
    0b0000000000000000000000000000000000000000000000000000000000000000,
    0b0000000000000000000000000000000000000000000000000000000000000000,
    0b0000000000000000000000000000000000000000000000000000000000000000,
    0b0000000000000000000000000000000000000000000000000000000000000000,
    0b0000000000000000000000000000000000000000000000000000000000000000,
    0b0000000000000000000000001000000000000000000001100000011000000000,
    0b0000000000000000000000101000000000000000000010100000010100000000,
    0b0000000000001100000011000000000000110000000010000000000100000000,
    0b0000000000010001000011000000000000110000011010000000000101100000,
    0b1100000000100000100011000000000000000000011010100110010101100000,
    0b1100000000100010110000101000000000000000000010101001010100000000,
    0b0000000000100000100000001000000000000000000010101001010100000000,
    0b0000000000010001000000000000000000000000011010100110010101100000,
    0b0000000000001100000000000000000000000000011010000000000101100000,
    0b0000000000000000000000000000000000000000000010000000000100000000,
    0b0000000000000000000000000000000000000000000010100000010100000000,
    0b0000000000000000000000000000000000000000000001100000011000000000,
    // clang-format on
};
static uint64_t grid2[CONWAY_ROWS] = {0};
uint64_t *conwayGrid               = grid1;

void updateConway(void) {
  uint64_t *nextGrid = (conwayGrid == grid1) ? grid2 : grid1;
  for (int row = 0; row < CONWAY_ROWS; ++row) {
    nextGrid[row] = (uint64_t)0;
  }
  for (int row = 0; row < CONWAY_ROWS; ++row) {
    for (int col = 0; col < CONWAY_COLS; ++col) {
      int numNeighbors = 0;
      // FIXME(cameron): use masking instead of inner loops
      for (int compRow = MAX(0, row - 1); compRow < MIN(CONWAY_ROWS, row + 2); ++compRow) {
        for (int compCol = MAX(0, col - 1); compCol < MIN(CONWAY_COLS, col + 2); ++compCol) {
          if ((row == compRow) && (col == compCol)) continue;
          if (conwayGrid[compRow] & ((uint64_t)1 << compCol)) ++numNeighbors;
        }
      }
      if (conwayGrid[row] & ((uint64_t)1 << col)) {
        if ((numNeighbors == 2) || (numNeighbors == 3)) nextGrid[row] |= ((uint64_t)1 << col);
      } else {
        if (numNeighbors == 3) nextGrid[row] |= ((uint64_t)1 << col);
      }
    }
  }
  conwayGrid = nextGrid;
}
