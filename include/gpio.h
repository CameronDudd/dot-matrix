/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include "color.h"

void gpioInit(void);

// On Board
void gpioToggleLED(void);

// Display
void gpioDisplayOutputEnable(void);
void gpioDisplayOutputDisable(void);
void gpioDisplayClock(void);
void gpioDisplayLatch(void);
void gpioDisplaySelectRow(uint8_t row);
void gpioDisplaySetColorLines(const RGBColor1 color, const uint8_t bottom);

// Bluetooth
void gpioHC05Enable(void);
void gpioHC05Disable(void);

#endif  // GPIO_H
