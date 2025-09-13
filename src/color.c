/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "color.h"

static const RGBColor _BLACK = {
    .r   = 0,
    .g   = 0,
    .b   = 0,
    .brt = BRT0,
};

static const RGBColor _RED = {
    .r   = 1,
    .g   = 0,
    .b   = 0,
    .brt = BRT4,
};

static const RGBColor _GREEN = {
    .r   = 0,
    .g   = 1,
    .b   = 0,
    .brt = BRT4,
};

static const RGBColor _YELLOW = {
    .r   = 1,
    .g   = 1,
    .b   = 0,
    .brt = BRT4,
};

static const RGBColor _BLUE = {
    .r   = 0,
    .g   = 0,
    .b   = 1,
    .brt = BRT4,
};

static const RGBColor _MAGENTA = {
    .r   = 1,
    .g   = 0,
    .b   = 1,
    .brt = BRT4,
};

static const RGBColor _CYAN = {
    .r   = 0,
    .g   = 1,
    .b   = 1,
    .brt = BRT4,
};

static const RGBColor _WHITE = {
    .r   = 1,
    .g   = 1,
    .b   = 1,
    .brt = BRT4,
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
