#ifndef GPIO_H
#define GPIO_H

#define GPIO_PIN_PA5  5
#define GPIO_PIN_PA6  6
#define GPIO_PIN_PA7  7
#define GPIO_PIN_PA8  8
#define GPIO_PIN_PA9  9
#define GPIO_PIN_PA10 10

#define GPIO_PIN_PB3  3
#define GPIO_PIN_PB4  4
#define GPIO_PIN_PB5  5
#define GPIO_PIN_PB6  6
#define GPIO_PIN_PB8  8
#define GPIO_PIN_PB9  9
#define GPIO_PIN_PB10 10

#define GPIO_PIN_PC7 7

#define GPIO_MODER_BITS_PER_PIN 2
#define GPIO_MODER_MODE_MASK    0b11u
#define GPIO_MODER_MODE_OUTPUT  0b01u
#define GPIO_MODER_SHIFT(PIN)   ((PIN) * GPIO_MODER_BITS_PER_PIN)

#endif  // GPIO_H
