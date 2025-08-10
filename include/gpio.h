/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include "color.h"

void gpioInit(void);
void outputEnable(void);
void outputDisable(void);
void clock(void);
void latch(void);
void selectRow(uint8_t row);
void setColorLines(const RGBColor1 color, const uint8_t bottom);

#endif  // GPIO_H
