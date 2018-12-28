/* All the emulator stuff */
#ifndef EMU_EMULATOR_H
#define EMU_EMULATOR_H

#include <stdbool.h>
#include <stdint.h>

/* Definitions for special-purpose registers */
#define PC 12 // Program Counter
#define SP 13 // Stack Pointer
#define IA 14 // Interrupt Address
#define C  15 // Carry

/* Number of program words in ROM */
#define PROGRAM_MAX 65536

/* Number of words in ROM */
#define MEMORY_MAX 131072

/* Standard CPU type definitions */
typedef uint16_t word;
typedef uint8_t  byte;
typedef bool     bit;

typedef struct cpu {
    word r[16]; // Registers
    word m[MEMORY_MAX]; // Memory
    bool running;
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

cpu_t *init_emu(word *rom);

byte get_byte(word src, byte offset);
byte get_nibble_from_word(word src, byte offset);
byte get_nibble_from_byte(byte src, byte offset);
op_t *construct_op(word code);

void exec_op(cpu_t *cpu);
void emulate(cpu_t *cpu);

/* Basic Arithmetic */
void op_add(cpu_t *cpu, byte x, byte y);
void op_adc(cpu_t *cpu, byte x, byte y);
void op_sub(cpu_t *cpu, byte x, byte y);
void op_sbc(cpu_t *cpu, byte x, byte y);
void op_rsb(cpu_t *cpu, byte x, byte y);
void op_rbc(cpu_t *cpu, byte x, byte y);
void op_mul(cpu_t *cpu, byte x, byte y);
void op_mls(cpu_t *cpu, byte x, byte y);
void op_div(cpu_t *cpu, byte x, byte y);
void op_dvs(cpu_t *cpu, byte x, byte y);
void op_mod(cpu_t *cpu, byte x, byte y);
void op_mds(cpu_t *cpu, byte x, byte y);
void op_mov(cpu_t *cpu, byte x, byte y);
void op_inc(cpu_t *cpu, byte x, byte y);
void op_dec(cpu_t *cpu, byte x, byte y);
void op_clr(cpu_t *cpu, byte x, byte y);

/* Bitwise/Shifts */
void op_sal(cpu_t *cpu, byte x, byte y);
void op_sar(cpu_t *cpu, byte x, byte y);
void op_sls(cpu_t *cpu, byte x, byte y);
void op_srs(cpu_t *cpu, byte x, byte y);
void op_and(cpu_t *cpu, byte x, byte y);
void op_ior(cpu_t *cpu, byte x, byte y);
void op_not(cpu_t *cpu, byte x, byte y);
void op_xor(cpu_t *cpu, byte x, byte y);

/* Basic with immediate */
void op_addi(cpu_t *cpu, byte x, byte y);
void op_adci(cpu_t *cpu, byte x, byte y);
void op_subi(cpu_t *cpu, byte x, byte y);
void op_sbci(cpu_t *cpu, byte x, byte y);
void op_rsbi(cpu_t *cpu, byte x, byte y);
void op_rbci(cpu_t *cpu, byte x, byte y);
void op_muli(cpu_t *cpu, byte x, byte y);
void op_mlsi(cpu_t *cpu, byte x, byte y);
void op_divi(cpu_t *cpu, byte x, byte y);
void op_dvsi(cpu_t *cpu, byte x, byte y);
void op_modi(cpu_t *cpu, byte x, byte y);
void op_mdsi(cpu_t *cpu, byte x, byte y);
void op_movi(cpu_t *cpu, byte x, byte y);

/* Bitwise/Shifts with immediate */
void op_sali(cpu_t *cpu, byte x, byte y);
void op_sari(cpu_t *cpu, byte x, byte y);
void op_slsi(cpu_t *cpu, byte x, byte y);
void op_srsi(cpu_t *cpu, byte x, byte y);
void op_andi(cpu_t *cpu, byte x, byte y);
void op_iori(cpu_t *cpu, byte x, byte y);
void op_noti(cpu_t *cpu, byte x, byte y);
void op_xori(cpu_t *cpu, byte x, byte y);

/* Conditional */
void op_ife(cpu_t *cpu, byte x, byte y);
void op_ifn(cpu_t *cpu, byte x, byte y);
void op_ifl(cpu_t *cpu, byte x, byte y);
void op_ifs(cpu_t *cpu, byte x, byte y);
void op_ifg(cpu_t *cpu, byte x, byte y);
void op_ifh(cpu_t *cpu, byte x, byte y);
void op_ils(cpu_t *cpu, byte x, byte y);
void op_iss(cpu_t *cpu, byte x, byte y);
void op_igs(cpu_t *cpu, byte x, byte y);
void op_ihs(cpu_t *cpu, byte x, byte y);

/* Memory */
void op_lpw(cpu_t *cpu, byte x, byte y);
void op_ldw(cpu_t *cpu, byte x, byte y);
void op_lpb(cpu_t *cpu, byte x, byte y);
void op_ldb(cpu_t *cpu, byte x, byte y);
void op_cpb(cpu_t *cpu, byte x, byte y);
void op_cdb(cpu_t *cpu, byte x, byte y);
void op_cpw(cpu_t *cpu, byte x, byte y);
void op_cdw(cpu_t *cpu, byte x, byte y);

/* Memory with immediate */
void op_lpwi(cpu_t *cpu, byte x, byte y);
void op_ldwi(cpu_t *cpu, byte x, byte y);
void op_lpbi(cpu_t *cpu, byte x, byte y);
void op_ldbi(cpu_t *cpu, byte x, byte y);
void op_spwi(cpu_t *cpu, byte x, byte y);
void op_sdwi(cpu_t *cpu, byte x, byte y);
void op_spbi(cpu_t *cpu, byte x, byte y);
void op_sdbi(cpu_t *cpu, byte x, byte y);

/* Branching */
void op_jmp(cpu_t *cpu, byte x, byte y);
void op_jmpi(cpu_t *cpu, byte x, byte y);
void op_jsr(cpu_t *cpu, byte x, byte y);
void op_jsri(cpu_t *cpu, byte x, byte y);
void op_ret(cpu_t *cpu, byte x, byte y);

/* I/O */
void op_hwi(cpu_t *cpu, byte x, byte y);
void op_hwii(cpu_t *cpu, byte x, byte y);
void op_hwn(cpu_t *cpu, byte x, byte y);

/* Other */
void op_hlt(cpu_t *cpu, byte x, byte y);

static void (*ops[16][16])(cpu_t *cpu, byte x, byte y) = {
    {
        op_add,
        op_adc,
        op_sub,
        op_sbc,
        op_rsb,
        op_rbc,
        op_mul,
        op_mls,
        op_div,
        op_dvs,
        op_mod,
        op_mds,
        op_mov,
        op_inc,
        op_dec,
        op_clr
    },
    {
        op_sal,
        op_sar,
        op_sls,
        op_srs,
        op_and,
        op_ior,
        op_not,
        op_xor
    },
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {
        op_hlt
    }
};

#endif
