/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef GPIO_H
#define GPIO_H

// From reference
// MODERy[1:0]: Port x configuration bits (y = 0..15)
// These bits are written by software to configure the I/O direction mode.
// 00: Input (reset state)
// 01: General purpose output mode
// 10: Alternate function mode
// 11: Analog mode
#define GPIO_MODER_CLR(port, pin)           ((port)->MODER &= ~(0x3 << ((pin) * 2)))
#define GPIO_MODER_SET_OUTPUT(port, pin)    ((port)->MODER |= (0x1 << ((pin) * 2)))
#define GPIO_MODER_SET_INPUT(port, pin)     ((port)->MODER &= ~(0x3 << ((pin) * 2)))
#define GPIO_MODER_SET_ALTERNATE(port, pin) ((port->MODER) |= (0x2 << ((pin) * 2)))
#define GPIO_MODER_SET_ANALOG(port, pin)    ((port)->MODER |= (0x3 << ((pin) * 2)))

#endif  // GPIO_H
