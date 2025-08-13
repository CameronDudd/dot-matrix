/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#ifndef PIN_DEFS_H
#define PIN_DEFS_H

// PORT A
#define HC_05_TXD   (1u << 2)
#define HC_05_RXD   (1u << 3)
#define MATRIX_CLK  (1u << 5)
#define NUCLEO_LED  (1u << 5)
#define MATRIX_E    (1u << 6)
#define MATRIX_D    (1u << 7)
#define MATRIX_B2   (1u << 8)
#define MATRIX_A    (1u << 9)
#define MATRIX_R1   (1u << 10)
#define HC_05_STATE (1u << 13)
#define HC_05_EN    (1u << 14)

// PORT B
#define MATRIX_G1  (1u << 3)
#define MATRIX_R2  (1u << 4)
#define MATRIX_B1  (1u << 5)
#define MATRIX_C   (1u << 6)
#define MATRIX_OE  (1u << 8)
#define MATRIX_LAT (1u << 9)
#define MATRIX_G2  (1u << 10)

// PORT C
#define MATRIX_B (1u << 7)

#endif  // PIN_DEFS_H
