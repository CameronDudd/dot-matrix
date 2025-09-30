/*
 *   Copyright (c) 2025 Cameron Dudd
 *   All rights reserved.
 */

#include <stddef.h>

#include "animation.h"
#include "data.h"
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
  Mesh3D poly       = polyData2Mesh3D(poly1Start, poly1End, 10);
  int lastUpdatedTs = 0;
  while (1) {
    if ((lastUpdatedTs == 0) || ((epochMs() - lastUpdatedTs) >= 30)) {
      lastUpdatedTs = epochMs();
      clearFrameBuffer();
      yawMesh3D(&poly, 2);
      drawMesh3DIsometric(&poly);
    }
    renderDisplay();
  }
}
