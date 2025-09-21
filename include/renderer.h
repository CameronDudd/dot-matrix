/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "color.h"
#include "geometry.h"

#define BUFF_ROWS 64
#define BUFF_COLS 64

const RGBColor *frameBuffer[BUFF_ROWS][BUFF_COLS];

// Buffer management
void clearFrameBuffer(void);
void rendererInit(void);

// Drawing funcs
void drawRect(int x, int y, int w, int h, const RGBColor *color);
void drawChar(const int col, const int row, const char c, const RGBColor *color);
void drawStr(const int x, const int y, const char *str, const RGBColor *color);
void drawAnimationBuffer(void);
void drawMesh2D(Mesh2D *mesh);
void drawMesh3DIsometric(Mesh3D *mesh);

#endif  // RENDERER_H
