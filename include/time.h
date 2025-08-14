/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef TIME_H
#define TIME_H

#include <stdint.h>

void SysTick_Handler(void);
void systickInit(uint32_t clkHz);
void tim2Init(uint32_t clkHz);
uint32_t epochMs(void);
uint32_t epochUs(void);
void sleepMs(uint32_t ms);
void sleepUs(uint32_t us);

#endif  // TIME_H
