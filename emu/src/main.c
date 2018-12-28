#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "emulator.h"

int main(int argc, char *argv[]) {
    word *rom = malloc(sizeof(word) * MEMORY_MAX);
    memset(rom, 0, sizeof(rom));

    rom[0] = 0x0D00;
    rom[1] = 0x0D10;
    rom[2] = 0x0001;
    rom[3] = 0x1620;
    rom[4] = 0xA000;
    cpu_t *cpu = init_emu(rom);
    emulate(cpu);
    return 0;
}
