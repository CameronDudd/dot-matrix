/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "color.h"

static const RGBColor1 _WHITE = {
    .r = 1,
    .g = 1,
    .b = 1,
};

static const RGBColor1 _RED = {
    .r = 1,
    .g = 0,
    .b = 0,
};

static const RGBColor1 _GREEN = {
    .r = 0,
    .g = 1,
    .b = 0,
};

static const RGBColor1 _BLUE = {
    .r = 0,
    .g = 0,
    .b = 1,
};

const RGBColor1 *WHITE = &_WHITE;
const RGBColor1 *RED   = &_RED;
const RGBColor1 *GREEN = &_GREEN;
const RGBColor1 *BLUE  = &_BLUE;
