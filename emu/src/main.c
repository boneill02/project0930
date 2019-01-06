#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <argp.h>
#include <pthread.h>
#include <signal.h>

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

void dump_mem(word *rom, char *outfile) {

    int char_index = 0;

    FILE *fp = fopen(outfile, "wb");

    for (int i = 0; i < sizeof(rom) / sizeof(word); i++) {
        if (char_index  % 2) {
            fputc(outfile, (rom[i] & 0xFF00) >> 8);
        } else {
            fputc(outfile, rom[i] & 0x00FF);
        }

        char_index++;
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, exit);

    pthread_t emu_thread;

    word *rom;
    char *outfile = "dump.o";
    if (argc == 2) {
        rom = load_rom(argv[1]);
    } else {
        exit(1);
    }


    pthread_create(&emu_thread, NULL, start_emulation, rom);

    pthread_join(emu_thread, NULL);
    
    return 0;
}
