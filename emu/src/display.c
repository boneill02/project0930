#include "device.h"

#include <memory.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

void init_display1() {
    display = malloc(sizeof(display1_t));
    memset(display, 0, sizeof(display1_t));
    display->window = SDL_CreateWindow("EMU0930", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SIZE, SDL_WINDOW_SIZE, SDL_WINDOW_SHOWN);
    display->renderer = SDL_CreateRenderer(display->window, 0, -1);
    r = malloc(sizeof(SDL_Rect));
    fillr = malloc(sizeof(SDL_Rect));

    fillr->x = 0;
    fillr->y = 0;
    fillr->w = 512;
    fillr->h = 512;

    r->x = 0;
    r->y = 0;
    r->w = 8;
    r->h = 8;
}

void write_display1(byte y, word imm) {

    if (display->w) {
        display->p[y] = !display->p[y];
        display->w = false;
        return;
    }

    if (y == 0) {
        memset(display->p, 0, sizeof(display->p));
    } else if (y == 1) {
        memset(display->p, 1, sizeof(display->p));
    } else if (y == 2) {
        SDL_RenderClear(display->renderer);

        SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 0);

        for (int i = 0; i < DISPLAY1_SIZE * DISPLAY1_SIZE; i++) {
            if (display->p[i]) {
                r->x = (i % DISPLAY1_SIZE) * (SDL_WINDOW_SIZE / DISPLAY1_SIZE);
                r->y = (i / DISPLAY1_SIZE) * (SDL_WINDOW_SIZE / DISPLAY1_SIZE);
                SDL_RenderFillRect(display->renderer, r);
            }
        }
        
        SDL_RenderPresent(display->renderer);
    } else if (y == 3) {
        display->p[imm] = !display->p[imm];
    } else if (y == 4) {
        display->w = true;
    }
}
