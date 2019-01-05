#include "device.h"

#include <memory.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

display1_t init_display1() {
    display1_t res;
    res.x = 0;
    res.y = 0;
    res.window = SDL_CreateWindow("EMU0930", 0, 0, 512, 512, SDL_WINDOW_SHOWN);
    res.renderer = SDL_CreateRenderer(res.window, 0, -1);
    return res;
}

void write_display1(byte y, word imm) {
    if (y == 0) {
        display.p[(imm & 0xFF00) >> 8][imm & 0x00FF] = true;
    } else if (y == 1) {
        SDL_Rect *r;
        SDL_SetRenderDrawColor(display.renderer, 255, 255, 255, 0);

        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                if (display.p[i][j]) {
                    r->x = i * 2;
                    r->y = j * 2;
                    r->w = 50;
                    r->h = 50;
                    SDL_RenderFillRect(display.renderer, r);
                }
            }
        }

        SDL_RenderPresent(display.renderer);
    }
}
