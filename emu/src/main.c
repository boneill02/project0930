#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "emulator.h"

int main(int argc, char *argv[]) {
    word *rom = malloc(sizeof(word) * MEMORY_MAX);
    memset(rom, 0, sizeof(rom));

    rom[0] = 0x2000;
    rom[1] = 0xCCCC;
    rom[2] = 0x2010;
    rom[3] = 0xAAAA;
    rom[4] = 0xA000;

    cpu_t *cpu = init_emu(rom);
    emulate(cpu);
    return 0;
}
