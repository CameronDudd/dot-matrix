/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef USART_H
#define USART_H

#include <stdint.h>

#define BAUD 9600

void usartInit(uint32_t clkHz);
void usart2TxChar(const uint8_t c);
void usart2TxStr(const char *s);

#endif  // USART_H
