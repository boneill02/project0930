# BK-16 Specifications

## General

Registers: 16

ROM Size: 128KiB (131072 bytes)

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
* Memory: 0x5oxy - 0x6oxy
  * Load/Store: 0x5oxy
  * Load/Store with Immediate: 0x6oxy
* Branch: 0x7oxy
* I/O: 0x8oxy - 0x9oxy
* Other: 0xAoxy - 0xFoxy

## Registers

* R0-R11: General purpose registers
* R12: Program counter
* R13: Stack pointer
* R14: Interrupt Address
* R15: Carry register

## Memory Layout

* 0x00000 - 0x0FFFF: Program space
  * 0x00000 - 0x001FF: Stack space
  * 0x00200 - 0x006FF: I/O space
  * 0x00700 - 0x0FFFF: ROM space
* 0x10000 - 0x1FFFF: Data space
