/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "color.h"

static const RGBColor1 _WHITE1 = {
    .r = 1,
    .g = 1,
    .b = 1,
};

static const RGBColor1 _RED1 = {
    .r = 1,
    .g = 0,
    .b = 0,
};

static const RGBColor1 _GREEN1 = {
    .r = 0,
    .g = 1,
    .b = 0,
};

static const RGBColor1 _BLUE1 = {
    .r = 0,
    .g = 0,
    .b = 1,
};

const RGBColor1 *WHITE1 = &_WHITE1;
const RGBColor1 *RED1   = &_RED1;
const RGBColor1 *GREEN1 = &_GREEN1;
const RGBColor1 *BLUE1  = &_BLUE1;

static const RGBColor _WHITE = {
    .r = 255,
    .g = 255,
    .b = 255,
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
static const RGBColor _BLUE = {
    .r = 0,
    .g = 0,
    .b = 255,
};

const RGBColor *WHITE = &_WHITE;
const RGBColor *RED   = &_RED;
const RGBColor *GREEN = &_GREEN;
const RGBColor *BLUE  = &_BLUE;
