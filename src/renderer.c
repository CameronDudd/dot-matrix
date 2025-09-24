/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "renderer.h"

#include "animation.h"
#include "b64.h"
#include "font.h"
#include "math.h"
#include "usart.h"

#define ABS(x) (((x) < 0) ? (-(x)) : (x))

const Font* font = &simpleFont;
const RGBColor* frameBuffer[BUFF_ROWS][BUFF_COLS];

// Buffer management
void clearFrameBuffer(void) {
  for (int row = 0; row < BUFF_ROWS; ++row) {
    for (int col = 0; col < BUFF_COLS; ++col) {
      frameBuffer[row][col] = BLACK;
    }
  }
}

void rendererInit(void) {
  clearFrameBuffer();
}

// Drawing funcs
static void _drawBresenhamLineLow(int x0, int y0, int x1, int y1) {
  // Bresenham's line algorithm
  // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }
  int D = (2 * dy) - dx;
  int y = y0;
  for (int x = x0; x <= x1; ++x) {
    if ((0 <= y) && (y < BUFF_ROWS) && (0 <= x) && (x < BUFF_COLS)) frameBuffer[BUFF_ROWS - 1 - y][x] = WHITE;
    if (D > 0) {
      y += yi;
      D += (2 * (dy - dx));
    } else {
      D += 2 * dy;
    }
  }
}

static void _drawBresenhamLineHigh(int x0, int y0, int x1, int y1) {
  // Bresenham's line algorithm
  // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }
  int D = (2 * dx) - dy;
  int x = x0;
  for (int y = y0; y <= y1; ++y) {
    if ((0 <= y) && (y < BUFF_ROWS) && (0 <= x) && (x < BUFF_COLS)) frameBuffer[BUFF_ROWS - 1 - y][x] = WHITE;

    if (D > 0) {
      x += xi;
      D += (2 * (dx - dy));
    } else {
      D += 2 * dx;
    }
  }
}

// TODO: Don't need complicated draw methods if dx = 0 and or dy = 0
void drawLine(int x0, int y0, int x1, int y1) {
  // Bresenham's line algorithm
  // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
  if (ABS(y1 - y0) < ABS(x1 - x0)) {
    if (x0 > x1) {
      _drawBresenhamLineLow(x1, y1, x0, y0);
    } else {
      _drawBresenhamLineLow(x0, y0, x1, y1);
    }
  } else {
    if (y0 > y1) {
      _drawBresenhamLineHigh(x1, y1, x0, y0);
    } else {
      _drawBresenhamLineHigh(x0, y0, x1, y1);
    }
  }
}

void drawRect(int x, int y, int w, int h, const RGBColor *color) {
  for (int row = y; row < y + h; ++row) {
    for (int col = x; col < x + w; ++col) {
      frameBuffer[row % BUFF_ROWS][col % BUFF_COLS] = color;
    }
  }
}

void drawChar(const int col, const int row, const char c, const RGBColor *color) {
  uint16_t charMap = simpleFont.map[(int)c];
  if (charUnsupported(charMap)) {
    charMap = simpleFont.map[0];
  }
  // If remainder of display cannot fit fast fail
  if (((row + font->height) >= BUFF_ROWS) || ((col + font->width) >= BUFF_COLS)) {
    return;
  }
  // Write character to buffer
  for (int c = font->width - 1; c >= 0; --c) {
    for (int r = font->height - 1; r >= 0; --r) {
      int offset = ((font->width * font->height) - 1) - ((r * font->width) + c);
      if ((charMap >> offset) & 1) {
        frameBuffer[row + r][col + c] = color;
      }
    }
  }
}

void drawStr(const int x, const int y, const char *str, const RGBColor *color) {
  int curRow = y;
  int curCol = x;
  for (const char *c = str; *c != '\0'; ++c) {
    drawChar(curCol, curRow, *c, color);
    if (*c != ' ') {
      curCol += font->width;
    }
    curCol++;
  }
}

void drawAnimationBuffer(void) {
  for (int row = 0; row < ANIMATION_ROWS; ++row) {
    for (int col = 0; col < ANIMATION_COLS; ++col) {
      frameBuffer[row][col] = (animationGrid[row] & ((int64_t)1 << (63 - col))) ? WHITE : BLACK;
    }
  }
}

void drawUsartB64Buff(void) {
  unsigned char decodeBuff[512] = {'\0'};
  b64Decode(decodeBuff, (unsigned char *)recvBuff);
  for (int row = 0; row < BUFF_ROWS; ++row) {
    for (int col = 0; col < BUFF_COLS; ++col) {
      int cell = (row * BUFF_COLS) + col;
      int idx  = cell / 8;
      int bit  = cell % 8;
      if (decodeBuff[idx] & (1u << bit)) {
        frameBuffer[row][col] = WHITE;
      }
    }
  }
}

void drawMesh2D(Mesh2D *mesh) {
  for (unsigned int i = 0; i < mesh->numEdges; ++i) {
    Edge edge  = mesh->edges[i];
    Vec2 start = mesh->vertices[edge.start];
    Vec2 end   = mesh->vertices[edge.end];
    drawLine(start.x, start.y, end.x, end.y);
  }
}

void drawMesh3DIsometric(Mesh3D *mesh) {
  // https://en.wikipedia.org/wiki/Isometric_projection
  // [ x']      1    [  sqrt(3)       0  -sqrt(3) ] [ x ]
  // [ y'] = ------- [       1        2        1  ] [ y ]
  // [ z']   sqrt(6) [  sqrt(2) -sqrt(2) -sqrt(2) ] [ z ]
  float cx = mesh->vertices[0].x;
  float cy = mesh->vertices[0].y;
  float cz = mesh->vertices[0].z;
  for (unsigned int i = 0; i < mesh->numEdges; ++i) {
    Edge edge    = mesh->edges[i];
    Vec3 start   = mesh->vertices[edge.start];
    Vec3 end     = mesh->vertices[edge.end];
    float startx = start.x - cx;
    float starty = start.y - cy;
    float startz = start.z - cz;
    float endx   = end.x - cx;
    float endy   = end.y - cy;
    float endz   = end.z - cz;
    drawLine((RECIPROCAL_SQRT6 * ((SQRT3 * startx) - (SQRT3 * startz))) + cx, (RECIPROCAL_SQRT6 * (startx + (2 * starty) + startz)) + cy,
             (RECIPROCAL_SQRT6 * ((SQRT3 * endx) - (SQRT3 * endz))) + cx, (RECIPROCAL_SQRT6 * (endx + (2 * endy) + endz)) + cy);
  }
}
