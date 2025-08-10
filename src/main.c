#include <stdint.h>

#include "color.h"
#include "gpio.h"
#include "time.h"

int main(void) {
  RGBColor1 _buff[64][64];
  for (uint8_t row = 0; row < 64; ++row) {
    for (uint8_t col = 0; col < 64; ++col) {
      _buff[row][col].r = (col % 2) ? 1 : 0;
      _buff[row][col].g = ((col % 2) && (row % 2)) ? 1 : 0;
      _buff[row][col].b = 0;
    }
  }

  systickInit(16000000);
  gpioInit();
  sleepMs(1000);

  while (1) {
    for (uint8_t row = 0; row < 32; ++row) {
      outputDisable();

      selectRow(row);

      for (uint8_t col = 0; col < 64; ++col) {
        setColorLines(_buff[row][col], 0);
        setColorLines(_buff[row + 32][col], 1);
        clock();
      }

      latch();
      outputEnable();
      sleepMs(1);
    }
  }
  return 0;
}
