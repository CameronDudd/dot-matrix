/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stddef.h>

#include "animation.h"
#include "display.h"
#include "geometry.h"
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
  Mesh3D cube       = cuboidMesh(45, -13, 0, 30, 30, 30);
  int lastUpdatedTs = 0;
  while (1) {
    if ((lastUpdatedTs == 0) || ((epochMs() - lastUpdatedTs) >= 30)) {
      lastUpdatedTs = epochMs();
      rollMesh3D(&cube, 1);
      pitchMesh3D(&cube, 1);
      yawMesh3D(&cube, 1);
      clearFrameBuffer();
      drawMesh3DIsometric(&cube);
    }
    renderDisplay();
  }
}
