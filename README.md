# PROJECT 0930

An emulator of a fantasy hardware ISA (inspired by DCPU-16).

## Overview

This is a project designed to help me learn about low level computing in the coolest way
possible (in my opinion), by creating a computer emulator for custom hardware! Of course,
this could be useful to anyone, the casual programmer, the CS student, etc. so take a look
at the code! Forking is encouraged, also.

## Design

This emulator is designed to be, well, easy to emulate. It uses mainly hex in the code, with binary only used for signing. This makes it easier on the brain.

## Goals

I have these uncompleted goals set in place:

* Debugger
* Keyboard
* Monochrome Display

## How To

Use the assembler:

    ./assemble (source) (destination)

Use the disassembler:
   
    ./disassemble (rom) (destination)

To start the emulator:

    ./emulate (rom)

## License

MIT, refer to LICENSE.txt.
