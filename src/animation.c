/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "animation.h"

#include "rand.h"

#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define RAND_ROW  randRange(0, ANIMATION_ROWS - 1);
#define RAND_COL  randRange(0, ANIMATION_COLS - 1);

static uint64_t buff1[ANIMATION_ROWS] = {0};
uint64_t *animationGrid               = buff1;

#if defined(CONWAY)
static uint64_t buff2[ANIMATION_ROWS] = {0};

static inline void _initConway(void) {
  uint64_t initBuff[ANIMATION_ROWS] = {
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
  memcpy(animationGrid, initBuff, sizeof(initBuff));
}

static inline void _updateConway(void) {
  /*
   * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
   * 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
   * 2. Any live cell with two or three live neighbours lives on to the next generation.
   * 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
   * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
   */
  uint64_t *nextGrid = (animationGrid == buff1) ? buff2 : buff1;
  for (int row = 0; row < ANIMATION_ROWS; ++row) {
    nextGrid[row] = (uint64_t)0;
  }
  for (int row = 0; row < ANIMATION_ROWS; ++row) {
    for (int col = 0; col < ANIMATION_COLS; ++col) {
      int numNeighbors = 0;
      // FIXME(cameron): use masking instead of inner loops
      for (int compRow = MAX(0, row - 1); compRow < MIN(ANIMATION_ROWS, row + 2); ++compRow) {
        for (int compCol = MAX(0, col - 1); compCol < MIN(ANIMATION_COLS, col + 2); ++compCol) {
          if ((row == compRow) && (col == compCol)) continue;
          if (animationGrid[compRow] & ((uint64_t)1 << compCol)) ++numNeighbors;
        }
      }
      if (animationGrid[row] & ((uint64_t)1 << col)) {
        if ((numNeighbors == 2) || (numNeighbors == 3)) nextGrid[row] |= ((uint64_t)1 << col);
      } else {
        if (numNeighbors == 3) nextGrid[row] |= ((uint64_t)1 << col);
      }
    }
  }
  animationGrid = nextGrid;
}
#endif

#if defined(PIPES)
#define DIRECTION_CHANGE_PERC 10
#define NUM_DIRECTIONS        4
#define RAND_DIRECTION        randRange(0, NUM_DIRECTIONS - 1)
#define RAND_CHANGE_DIRECTION randRange(1, 100) <= DIRECTION_CHANGE_PERC

typedef enum {
  UP    = 0,
  DOWN  = 1,
  LEFT  = 2,
  RIGHT = 3,
} Direction;

static int currentRow;
static int currentCol;
static Direction currentDirection;
static int triedDirections[NUM_DIRECTIONS] = {0};

static inline int _validPos(const int row, const int col) {
  if ((row < 0) || ((ANIMATION_ROWS - 1) < row) || (col < 0) || ((ANIMATION_COLS - 1) < col)) {
    return 0;
  }
  if (animationGrid[row] & ((uint64_t)1 << (ANIMATION_COLS - col - 1))) {
    return 0;
  }
  return 1;
}

static inline void _changeDirection(void) {
  switch (currentDirection) {
    case UP:
      currentDirection = (randRange(0, 1)) ? LEFT : RIGHT;
      break;
    case DOWN:
      currentDirection = (randRange(0, 1)) ? LEFT : RIGHT;
      break;
    case LEFT:
      currentDirection = (randRange(0, 1)) ? UP : DOWN;
      break;
    case RIGHT:
      currentDirection = (randRange(0, 1)) ? UP : DOWN;
      break;
  }
}

static inline void _initPipes(void) {
  currentRow       = RAND_ROW;
  currentCol       = RAND_COL;
  currentDirection = RAND_DIRECTION;
  for (int i = 0; i < NUM_DIRECTIONS; ++i) {
    triedDirections[i] = 0;
  }
}

static inline void _updatePipes(void) {
  int nextRow = currentRow;
  int nextCol = currentCol;
  switch (currentDirection) {
    case UP:
      --nextRow;
      break;
    case DOWN:
      ++nextRow;
      break;
    case LEFT:
      --nextCol;
      break;
    case RIGHT:
      ++nextCol;
      break;
  }
  if (_validPos(nextRow, nextCol)) {
    animationGrid[nextRow] |= ((uint64_t)1 << (63 - nextCol));
    currentRow = nextRow;
    currentCol = nextCol;
    if (RAND_CHANGE_DIRECTION) {
      _changeDirection();
    }
  } else {
    for (int i = 0; i < NUM_DIRECTIONS; ++i) {
      if (triedDirections[i] == 0) {
        triedDirections[i] = 1;
        currentDirection   = i;
        return;
      }
    }
    _initPipes();
  }
}
#endif

#if defined(STARS)
static unsigned int currentRow;
static unsigned int currentCol;

static inline void _initStars(void) {
  currentRow = RAND_ROW;
  currentCol = RAND_COL;
}

static inline void _updateStars(void) {
  animationGrid[currentRow] |= ((uint64_t)1 << currentCol);
  _initStars();
}
#endif

void animationInit(void) {
#if defined(CONWAY)
  _initConway();
#elif defined(PIPES)
  _initPipes();
#elif defined(STARS)
  _initStars();
#endif
}

void updateAnimation(void) {
#if defined(CONWAY)
  _updateConway();
#elif defined(PIPES)
  _updatePipes();
#elif defined(STARS)
  _updateStars();
#endif
}
