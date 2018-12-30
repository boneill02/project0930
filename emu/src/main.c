#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "emulator.h"

word *load_rom(char *path) {
    FILE *input = fopen(path, "rb");
    word *output = malloc(sizeof(word) * MEMORY_MAX);
    memset(output, 0, sizeof(output));

    char c;
    int char_index = 0;
    int word_index = 0;
    while((c = fgetc(input)) != EOF) {
        if (char_index % 2 == 0) {
            output[word_index] = (word) c;
        } else {
            output[word_index] = output[word_index] << 8;
            output[word_index] |= ((word) c) & 0x00FF;
            word_index++;
        }
        char_index++;
    }

    fclose(input);

    return output;
}

int main(int argc, char *argv[]) {
    word *rom;
    if (argc == 2) {
        rom = load_rom(argv[1]);
    } else {
        printf("Loading Hello World...\n");
        rom = malloc(sizeof(word) * MEMORY_MAX);
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
        rom[20] = 0x80A0;
        rom[21] = 0x80A1;
        rom[22] = 0x80A2;
        rom[23] = 0x80A2;
        rom[24] = 0x80A3;
        rom[25] = 0x80A4;
        rom[26] = 0x80A5;
        rom[27] = 0x80A3;
        rom[28] = 0x80A6;
        rom[29] = 0x80A2;
        rom[30] = 0x80A7;
        rom[31] = 0x80A8;
        rom[32] = 0x80A9;

        rom[33] = 0xA000;
    }

    cpu_t *cpu = init_emu(rom);
    emulate(cpu);
    return 0;
}
