/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include "usart.h"

#include <stdarg.h>

#include "format.h"
#include "gpio.h"
#include "stm32f401xe.h"
#include "time.h"

#define AF_BITS_PER_PIN 4
#define AF_USART        7u

static volatile char _c;
volatile char recvBuffComplete = 0;
volatile char recvBuff[RECV_BUFF_SIZE];
volatile char *_recvBuffPtr = recvBuff;

void Usart2GlobalInterrupt_Handler(void) {
  if (USART2->SR & USART_SR_RXNE) {
    _c = USART2->DR;
    if ((_recvBuffPtr - recvBuff) >= RECV_BUFF_SIZE) {
      recvBuffComplete = 0;
      _recvBuffPtr     = recvBuff;
    } else if (_c == '=') {
      *_recvBuffPtr++  = _c;
      _recvBuffPtr     = recvBuff;
      recvBuffComplete = 1;
    } else {
      *_recvBuffPtr++ = _c;
    }
  }
}

void usartInit(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

  // clear
  GPIO_MODER_CLR(GPIOA, 2);
  GPIO_MODER_CLR(GPIOA, 3);

  // set AF
  GPIO_MODER_SET_ALTERNATE(GPIOA, 2);
  GPIO_MODER_SET_ALTERNATE(GPIOA, 3);

  GPIOA->AFR[0] |= (AF_USART << (2 * AF_BITS_PER_PIN)) | (AF_USART << (3 * AF_BITS_PER_PIN));

  USART2->BRR = sysclk / BAUD;
  USART2->CR1 &= ~USART_CR1_M;                                                    // word Length: 1 Start bit, 8 Data bits, n Stop bit
  USART2->CR2 &= ~USART_CR2_STOP_Msk;                                             // 00: 1 Stop bit
  USART2->CR1 = (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE | USART_CR1_RXNEIE);  // enable tx, rx, usart, interrupt

  // Clear recv buffer
  for (int b = 0; b < RECV_BUFF_SIZE; ++b) {
    recvBuff[b] = '\0';
  }
  NVIC_EnableIRQ(USART2_IRQn);  // Enable interrupt
}

void usart2TxChar(const char c) {
  while (!(USART2->SR & USART_SR_TXE)) {
  }
  USART2->DR = c;
}

void usart2TxStr(const char *s) {
  while (*s) {
    usart2TxChar(*s++);
  }
}

void usart2Printf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  for (const char *p = fmt; *p; ++p) {
    if (*p == '%' && *(p + 1)) {
      ++p;
      if ((*p == 'd') || (*p == 'i')) {
        int val = va_arg(args, int);
        for (const char *c = itoa(val); *c != '\0'; ++c) {
          usart2TxChar(*c);
        }
      } else if (*p == 's') {
        char *s = va_arg(args, char *);
        while (*s != '\0') {
          usart2TxChar(*s++);
        }
      } else {
        usart2TxChar(*p);
      }
    } else {
      usart2TxChar(*p);
    }
  }
  va_end(args);
}
