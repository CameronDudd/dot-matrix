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

static const RGBColor8 _WHITE8 = {
    .r = 255,
    .g = 255,
    .b = 255,
};
static const RGBColor8 _RED8 = {
    .r = 255,
    .g = 255,
    .b = 255,
};
static const RGBColor8 _GREEN8 = {
    .r = 255,
    .g = 255,
    .b = 255,
};
static const RGBColor8 _BLUE8 = {
    .r = 255,
    .g = 255,
    .b = 255,
};

const RGBColor8 *WHITE8 = &_WHITE8;
const RGBColor8 *RED8   = &_RED8;
const RGBColor8 *GREEN8 = &_GREEN8;
const RGBColor8 *BLUE8  = &_BLUE8;
