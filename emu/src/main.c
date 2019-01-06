#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <getopt.h>
#include <signal.h>
#include <stdbool.h>

#include "emulator.h"

word *load_rom(char *path) {
    FILE *input = fopen(path, "rb");
    word *output = malloc(sizeof(word) * ROM_MAX);
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

    char *infile = "a.out";
    char *outfile = "dump.o";
    bool debug = false;

    int opt;
    while ((opt = getopt (argc, argv, "i:o:d")) != -1) {
        switch (opt) {
            case 'i':
                infile = optarg;
                break;
            case 'o':
                outfile = optarg;
                break;
            case 'd':
                debug = true;
                break;
        }
    }

    word *rom = load_rom(infile);

    start_emulation(rom, debug);

    return 0;
}
