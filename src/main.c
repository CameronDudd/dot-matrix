/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stddef.h>

#include "animation.h"
#include "display.h"
#include "rand.h"
#include "renderer.h"
#include "time.h"
#include "usart.h"

static void init(void) {
  clockInit();
  systickInit();
  tim2Init();
  usartInit();
  randInit();
  displayInit();
  rendererInit();
  animationInit();
}

int main(void) {
  init();
  int lastUpdatedTs = 0;
  while (1) {
    if ((lastUpdatedTs == 0) || ((epochMs() - lastUpdatedTs) >= 10)) {
      lastUpdatedTs = epochMs();
      drawAnimationBuffer();
      updateAnimation();
    }
    renderDisplay();
  }
}
