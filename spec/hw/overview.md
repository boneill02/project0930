# Project 0930 Specifications

## General

Registers: 16

ROM Size: 256KiB (131072 words)

Base Clockspeed: 10MhZ

Endianness: Little

Word length: 16

## Instruction Format

* Arithmetic: 0x0oxy - 0x4oxy
  * Basic: 0x0oxy
  * Bitwise/Shifts: 0x1oxy
  * Basic with Immediate: 0x2oxy
  * Bitwise/Shifts with Immediate: 0x3oxy
  * Conditional: 0x4oxy
* Memory: 0x5oxy - 0x8oxy
  * Load/Store bytes: 0x5oxy
  * Load/Store words: 0x6oxy
  * Load/Store bytes with Immediate: 0x7oxy
  * Load/store words with Immediate: 0x8oxy
* Branch: 0x9oxy
* I/O: 0xAoxy
* Other: 0xAoxy - 0xFoxy

## Registers

* R0-R11: General purpose registers
* R12: Program counter
* R13: Stack pointer
* R14: Interrupt Address
* R15: Carry register

## Memory Layout

* 0x00000 - 0x0FFFF: Program space
* 0x10000 - 0x1FFFF: Data space
