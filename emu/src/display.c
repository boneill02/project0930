#include "device.h"

#include <SDL2/SDL.h>
#include <memory.h>
#include <stdlib.h>

display1_t *init_display1() {
    display1_t res = malloc(sizeof(display1_t));
    memset(res, 0, sizeof(res));

    SDL_Init(SDL_INIT_VIDEO);
    res->window = SDL_CreateWindow("EMU0930", 0, 0, 256, 256, SDL_WINDOW_OPENGL);
    res->renderer = SDL_CreateRenderer(window, 0, -1);
    return res;
}

void write_display1(byte x, byte y, display1_t *display) {
    if (x == 0) {
        // Set display x to arg y
        display->x = y;
    } else if (x == 1) {
        display->y = y;
    } else if (x == 2) {
        display->p[x][y] = true;
    } else if (x == 3) {
        SDL_Rect *r;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                if (display->p[i][j]) {
                    r->x = i;
                    r->y = j;
                    SDL_RenderCopy(renderer, r);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }
}
