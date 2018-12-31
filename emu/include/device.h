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

display1_t *display;

display1_t *init_display1();
void write_display1(byte y, word imm);

#endif // EMU_DEVICE_H
