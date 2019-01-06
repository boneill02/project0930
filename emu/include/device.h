#ifndef EMU_DEVICE_H
#define EMU_DEVICE_H

#include "emulator.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

#define DISPLAY1_SIZE 64

typedef struct display1 {
    bool p[DISPLAY1_SIZE * DISPLAY1_SIZE];
    int o[DISPLAY1_SIZE * DISPLAY1_SIZE];
    bool w;
    int x;
    int y;
    int q;
    bool z;
    SDL_Window *window;
    SDL_Renderer *renderer;
} display1_t;

static display1_t *display;

void init_display1();
static SDL_Rect *r;
static SDL_Rect *fillr;
void write_display1(byte y, word imm);

#endif // EMU_DEVICE_H
