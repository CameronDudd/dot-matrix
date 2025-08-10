/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef TIME_H
#define TIME_H

#include <stdint.h>

void SysTick_Handler(void);
void systickInit(uint32_t clkHz);
void sleepMs(uint32_t ms);

#endif  // TIME_H
