#include "device.h"

#include <memory.h>
#include <stdlib.h>

display1_t *init_display1() {
    display1_t *res = malloc(sizeof(display1_t));
    memset(res, 0, sizeof(res));

    SDL_Init(SDL_INIT_VIDEO);
    res->window = SDL_CreateWindow("EMU0930", 0, 0, 256, 256, SDL_WINDOW_OPENGL);
    res->renderer = SDL_CreateRenderer(res->window, 0, -1);
    return res;
}

void write_display1(byte y, word imm) {
    if (y == 0) {
        // Set display x to arg y
        display->x = y;
    } else if (y == 1) {
        display->y = y;
    } else if (y == 2) {
        display->p[(imm & 0xFF00) >> 8][imm & 0x00FF] = true;
    } else if (y == 3) {
        SDL_Rect *r;
        SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 0);

        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                if (display->p[i][j]) {
                    r->x = i;
                    r->y = j;
                    SDL_RenderDrawRect(display->renderer, r);
                }
            }
        }

        SDL_RenderPresent(display->renderer);
    }
}
