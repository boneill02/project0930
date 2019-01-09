#ifndef EMU_DEVICE_H
#define EMU_DEVICE_H

#include "emulator.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SDL_WINDOW_SIZE 512
#define DISPLAY1_SIZE 256

typedef struct display1 {
    bool p[DISPLAY1_SIZE][DISPLAY1_SIZE];
    bool w;
    int i;
    int x, y;
    SDL_Window *window;
    SDL_Renderer *renderer;
} display1_t;

typedef struct keyboard1 {
    int k;
    bool d[256];
} keyboard1_t;

static display1_t *display;
static keyboard1_t *keyboard;

static SDL_Rect *r;
static SDL_Rect *fillr;

void init_display1();
void write_display1(word imm, cpu_t *cpu);

void init_keyboard1();
void write_keyboard1(word imm, cpu_t *cpu);
void set_keydown(int key, bool down);

#endif // EMU_DEVICE_H
