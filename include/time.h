/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef TIME_H
#define TIME_H

#include <stdint.h>

extern uint32_t sysclk;

void SysTick_Handler(void);
void systickInit(void);
void tim2Init(void);
void sleepMs(uint32_t ms);
void sleepUs(uint32_t us);
uint32_t epochS(void);
uint32_t epochMs(void);
uint32_t epochUs(void);
void clockInit(void);

#endif  // TIME_H
