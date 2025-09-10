/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "color.h"

static const RGBColor _BLACK = {
    .r = 0,
    .g = 0,
    .b = 0,
};

static const RGBColor _RED = {
    .r = 255,
    .g = 0,
    .b = 0,
};

static const RGBColor _GREEN = {
    .r = 0,
    .g = 255,
    .b = 0,
};

static const RGBColor _YELLOW = {
    .r = 255,
    .g = 255,
    .b = 0,
};

static const RGBColor _BLUE = {
    .r = 0,
    .g = 0,
    .b = 255,
};

static const RGBColor _MAGENTA = {
    .r = 255,
    .g = 0,
    .b = 255,
};

static const RGBColor _CYAN = {
    .r = 0,
    .g = 255,
    .b = 255,
};

static const RGBColor _WHITE = {
    .r = 255,
    .g = 255,
    .b = 255,
};

const RGBColor *BLACK   = &_BLACK;
const RGBColor *RED     = &_RED;
const RGBColor *GREEN   = &_GREEN;
const RGBColor *YELLOW  = &_YELLOW;
const RGBColor *BLUE    = &_BLUE;
const RGBColor *MAGENTA = &_MAGENTA;
const RGBColor *CYAN    = &_CYAN;
const RGBColor *WHITE   = &_WHITE;

const RGBColor ALL_COLORS[NUM_COLORS] = {
    _RED, _GREEN, _YELLOW, _BLUE, _MAGENTA, _CYAN, _WHITE,
};
