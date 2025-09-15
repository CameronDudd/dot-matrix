/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stddef.h>

#include "conway.h"
#include "display.h"
#include "rand.h"
#include "time.h"
#include "usart.h"

static void init(void) {
  clockInit();
  systickInit();
  tim2Init();
  usartInit();
  randInit();
  displayInit();
}

int main(void) {
  init();
  int lastUpdatedTs = 0;
  while (1) {
    if ((lastUpdatedTs == 0) || ((epochMs() - lastUpdatedTs) >= 30)) {
      lastUpdatedTs = epochMs();
      drawConway();
      updateConway();
    }
    renderDisplay();
  }
}
