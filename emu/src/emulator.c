/* The core of the emulator. */
#include "emulator.h"
#include "device.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <SDL2/SDL.h>
#include <pthread.h>

static cpu_t *cpu;

/*
    Initialize components for emulation
 */
void start_emulation(word *rom, bool debug) {
    SDL_Init(SDL_INIT_EVERYTHING);
    init_display1();
    if (sizeof(rom) != sizeof(ROM_MAX) * sizeof(word)) {
        error(1, "Invalid ROM", "Incorrect size", true);
    }

    cpu = malloc(sizeof(cpu_t));
    memset(cpu, 0, sizeof(cpu_t));
    
    for (int i = 0; i < ROM_MAX; i++) {
        cpu->m[i] = rom[i];
    }

    cpu->debug = debug;

    free(rom);
    emulate();
}

/* 
   Executes the operation at memory location PC
*/
void exec_op() {
    word opw = cpu->m[cpu->r[PC]];
    op_t *op = construct_op(opw);
    if (ops[op->c][op->o] == NULL) {
        error(1, cpu->r[PC], "Invalid opcode", true);
    }
    ops[op->c][op->o](cpu, op->x, op->y);
}

/*
   Main emulator loop
 */
void emulate() {
    cpu->running = true;
    SDL_Event event;
    while (cpu->running) {
        exec_op();

        cpu->r[PC]++;
        if (cpu->r[PC] >= ROM_MAX - 1) {
            cpu->running = false; // Halt processing if PC is out of bounds
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    cpu->running = false;
                default:
                    break;
            }
        }
    }

    if (cpu->debug) {
        dump_reg();
    }

    stop_emulation();
}

void stop_emulation() {
    free(cpu);
    free(display);
    free(r);
    free(fillr);
    SDL_Quit();
}

/*
    Dumps the CPU register information
*/
void dump_reg() {
    for (int i = 0; i < 15; i++) {
        printf("R%d: 0x%x\n", i, cpu->r[i]);
    }
}

void error(int code, int location, const char *desc, bool fatal) {
    printf("An exception occured at 0x%x.\n", location);
    printf("Code: 0x%x\n", code);
    printf("Description: %s\n", desc);
    if (fatal) {
        printf("Program cannot continue.\n");
        stop_emulation();
        exit(code);
    }
}
