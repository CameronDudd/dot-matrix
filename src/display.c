/*
 *   Copyright (c) 2024 Cameron Dudd
 *   All rights reserved.
 */

#include "display.h"

#include <SDL2/SDL.h>

#include "font.h"

#define WIDTH  64
#define HEIGHT 64
#define SCALE  10

const Font *font = &simpleFont;

int _drawChar(SDL_Renderer **renderer, int x, int y, char c) {
  uint16_t charMap = font->map[(int)c];  // NOTE(cameron): assumes ASCII encoding
  if (charUnsupported(charMap)) {
    charMap = font->map[0];
  }
  SDL_SetRenderDrawColor(*renderer, 255, 225, 255, 255);
  for (int bit = 14; bit >= 0; --bit) {
    if ((1 << bit) & charMap) {
      int charx     = ((14 - bit) % font->width) * SCALE;
      int chary     = (((14 - bit) / font->width) % font->height) * SCALE;
      SDL_Rect rect = {x + charx, y + chary, SCALE, SCALE};
      SDL_RenderFillRect(*renderer, &rect);
    }
  }
  return font->width + 1;  // TODO(cameron): return wider (continuous) chars drawn
}

int _initSdl(SDL_Window **window, SDL_Renderer **renderer) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return 1;
  }
  *window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * SCALE, HEIGHT * SCALE, 0ul);
  if (!*window) {
    return 1;
  }
  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
  return (*renderer == NULL) ? 1 : 0;
}

int loop() {
  SDL_Window *window     = NULL;
  SDL_Renderer *renderer = NULL;

  if (_initSdl(&window, &renderer)) {
    SDL_Quit();
    return 1;
  }

  int running = 1;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case 'q':
              running = 0;
              break;
          }
          break;
        case SDL_QUIT:
          running = 0;
          break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int offset = 0;
    for (const char *s = TEST_STR; *s != '\0'; s++) {
      int x = offset % WIDTH;
      int y = ((offset / WIDTH) * (font->height + 1)) % HEIGHT;
      offset += _drawChar(&renderer, x * SCALE, y * SCALE, *s);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(100);
  }

  return 0;
}
