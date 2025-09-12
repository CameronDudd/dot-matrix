/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef USART_H
#define USART_H

#include <stdint.h>

#define BAUD           9600
#define RECV_BUFF_SIZE 685

extern volatile char recvBuffComplete;
extern volatile char recvBuff[RECV_BUFF_SIZE];

void Usart2GlobalInterrupt_Handler(void);
void usartInit(uint32_t clkHz);
void usart2TxChar(const char c);
void usart2TxStr(const char *s);

#endif  // USART_H
