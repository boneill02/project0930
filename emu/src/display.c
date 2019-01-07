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
    r->w = SDL_WINDOW_SIZE / DISPLAY1_SIZE;
    r->h = SDL_WINDOW_SIZE / DISPLAY1_SIZE;
}

void write_display1(word imm, cpu_t *cpu) {
    byte op = (imm & 0xFF00) >> 8;
    byte val = imm & 0x00FF;

    if (display->w) {
        display->p[op][val] = !display->p[op][val];
        display->w = false;
        return;
    }

    if (op == 0) {
        memset(display->p, 0, sizeof(display->p));
    } else if (op == 1) {
        memset(display->p, 1, sizeof(display->p));
    } else if (op == 2) {
        SDL_RenderClear(display->renderer);

        SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 0);

        SDL_RenderFillRect(display->renderer, fillr);

        SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 0);

        for (int i = 0; i < DISPLAY1_SIZE; i++) {
            for (int j = 0; j < DISPLAY1_SIZE; j++) {
                if (display->p[i][j]) {
                    r->x = i * (SDL_WINDOW_SIZE / DISPLAY1_SIZE);
                    r->y = j * (SDL_WINDOW_SIZE / DISPLAY1_SIZE);
                    SDL_RenderFillRect(display->renderer, r);
                }
            }
        }
        
        SDL_RenderPresent(display->renderer);
    } else if (op == 3) {
        display->w = true;
    } else if (op == 4) {
        display->x = val;
    } else if (op == 5) {
        display->y = val;
    } else if (op == 6) {
        display->p[display->x][display->y] = !display->p[display->x][display->y];
    } else if (op == 7) {
        cpu->r[val] = display->p[display->x][display->y];
    }
}
