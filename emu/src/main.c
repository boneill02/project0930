#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "emulator.h"

int main(int argc, char *argv[]) {
    word *rom = malloc(sizeof(word) * MEMORY_MAX);
    memset(rom, 0, sizeof(rom));

    rom[0] = 0x2000;
    rom[1] = 0x0048; // H
    rom[2] = 0x2010;
    rom[3] = 0x0045; // E
    rom[4] = 0x2020;
    rom[5] = 0x004C; // L
    rom[6] = 0x2030;
    rom[7] = 0x004F; // O
    rom[8] = 0x2040;
    rom[9] = 0x0020; // Space
    rom[10] = 0x2050;
    rom[11] = 0x0057; // W
    rom[12] = 0x2060;
    rom[13] = 0x0052; // R
    rom[14] = 0x2070;
    rom[15] = 0x0044; // D
    rom[16] = 0x2080;
    rom[17] = 0x0021; // !
    rom[18] = 0x2090;
    rom[19] = 0x000A; // \n
    // Print
    rom[20] = 0x8000;
    rom[21] = 0x8001;
    rom[22] = 0x8002;
    rom[23] = 0x8002;
    rom[24] = 0x8003;
    rom[25] = 0x8004;
    rom[26] = 0x8005;
    rom[27] = 0x8003;
    rom[28] = 0x8006;
    rom[29] = 0x8002;
    rom[30] = 0x8007;
    rom[31] = 0x8008;
    rom[32] = 0x8009;

    rom[33] = 0xA000;

    cpu_t *cpu = init_emu(rom);
    emulate(cpu);
    return 0;
}
