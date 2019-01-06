/* All the emulator stuff */
#ifndef EMU_EMULATOR_H
#define EMU_EMULATOR_H

#include <stdbool.h>
#include <stdint.h>

/* Definitions for special-purpose registers */
#define PC 13 // Program Counter
#define SP 14 // Stack Pointer
#define C  15 // Carry

/* Number of words in ROM */
#define ROM_MAX 65536

/* Standard CPU type definitions */
typedef uint16_t word;
typedef uint8_t  byte;
typedef bool     bit;

typedef struct cpu {
    word r[15]; // Registers
    word m[ROM_MAX]; // Memory
    bool running;
    bool debug;
} cpu_t;

typedef struct op {
    byte c;
    byte o;
    byte x;
    byte y;

    byte co;
    byte xy;

    word coxy;
} op_t;

bool is_positive(word src);
byte get_byte(word src, byte offset);
byte get_nibble_from_word(word src, byte offset);
byte get_nibble_from_byte(byte src, byte offset);
op_t *construct_op(word code);
bool has_immediate(op_t *op);

void start_emulation(word *rom, bool debug);
void exec_op();
void emulate();

/* Arithmetic */
void op_add(cpu_t *cpu, byte x, byte y);
void op_addc(cpu_t *cpu, byte x, byte y);
void op_sub(cpu_t *cpu, byte x, byte y);
void op_subc(cpu_t *cpu, byte x, byte y);
void op_rsb(cpu_t *cpu, byte x, byte y);
void op_rsbc(cpu_t *cpu, byte x, byte y);
void op_mul(cpu_t *cpu, byte x, byte y);
void op_muls(cpu_t *cpu, byte x, byte y);
void op_div(cpu_t *cpu, byte x, byte y);
void op_divs(cpu_t *cpu, byte x, byte y);
void op_mod(cpu_t *cpu, byte x, byte y);
void op_mods(cpu_t *cpu, byte x, byte y);
void op_mov(cpu_t *cpu, byte x, byte y);

/* Bitwise/Shifts */
void op_sal(cpu_t *cpu, byte x, byte y);
void op_sar(cpu_t *cpu, byte x, byte y);
void op_sls(cpu_t *cpu, byte x, byte y);
void op_srs(cpu_t *cpu, byte x, byte y);
void op_and(cpu_t *cpu, byte x, byte y);
void op_or(cpu_t *cpu, byte x, byte y);
void op_not(cpu_t *cpu, byte x, byte y);
void op_xor(cpu_t *cpu, byte x, byte y);

/* Conditional */
void op_ife(cpu_t *cpu, byte x, byte y);
void op_ifne(cpu_t *cpu, byte x, byte y);
void op_iflt(cpu_t *cpu, byte x, byte y);
void op_ifle(cpu_t *cpu, byte x, byte y);
void op_ifgt(cpu_t *cpu, byte x, byte y);
void op_ifge(cpu_t *cpu, byte x, byte y);
void op_iflts(cpu_t *cpu, byte x, byte y);
void op_ifles(cpu_t *cpu, byte x, byte y);
void op_ifgts(cpu_t *cpu, byte x, byte y);
void op_ifges(cpu_t *cpu, byte x, byte y);

/* Load/Store */
void op_lw(cpu_t *cpu, byte x, byte y);
void op_sw(cpu_t *cpu, byte x, byte y);

/* I/O */
void op_hwi(cpu_t *cpu, byte x, byte y);

/* Other */
void op_hlt(cpu_t *cpu, byte x, byte y);

static void (*ops[16][16])(cpu_t *cpu, byte x, byte y) = {
    {
        op_add,
        op_addc,
        op_sub,
        op_subc,
        op_rsb,
        op_rsbc,
        op_mul,
        op_muls,
        op_div,
        op_divs,
        op_mod,
        op_mods,
        op_mov
    },
    {
        op_sal,
        op_sar,
        op_sls,
        op_srs,
        op_and,
        op_or,
        op_xor
    },
    {
        op_ife,
        op_ifne,
        op_iflt,
        op_ifle,
        op_ifgt,
        op_ifge,
        op_iflts,
        op_ifles,
        op_ifgts,
        op_ifges
    },
    {
        op_lw,
        op_sw
    },
    {
        op_hwi
    },
    {
        op_hlt
    },
    {},
    {}
};

#endif
