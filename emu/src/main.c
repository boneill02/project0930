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
        exit(1);
    }

    cpu_t *cpu = init_emu(rom);
    emulate(cpu);
    return 0;
}
