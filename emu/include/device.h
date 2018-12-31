#ifndef EMU_DEVICE_H
#define EMU_DEVICE_H

#include "emulator.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct display1 {
    byte x;
    byte y;
    bool p[256][256];
    SDL_Window *window;
    SDL_Renderer *renderer;
} display1_t;

#endif // EMU_DEVICE_H
