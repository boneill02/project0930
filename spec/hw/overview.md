# Project 0930 Specifications

## General

Registers: 15

ROM Size: 128KiB (65536 words)

Base Clockspeed: 10MhZ

Endianness: Little

Word length: 16

## Instruction Format

* Arithmetic: 0x0oxy - 0x2oxy
  * Basic: 0x0oxy
  * Bitwise/Shifts: 0x1oxy
  * Conditional: 0x2oxy
* Memory: 0x3oxy
  * Load/Store words: 0x3oxy
* I/O: 0x4oxy
* Other: 0x5oxy - 0xFoxy

## Registers

* R0-R12: General purpose registers
* R13: Program counter
* R14: Carry register

## Memory Layout

* 0x00000 - 0x0FFFF: Program space