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

bool is_positive(word src);
byte get_byte(word src, byte offset);
byte get_nibble_from_word(word src, byte offset);
byte get_nibble_from_byte(byte src, byte offset);
op_t *construct_op(word code);
bool has_immediate(op_t *op);

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

/* Load/Store bytes */
void op_lph(cpu_t *cpu, byte x, byte y);
void op_lpl(cpu_t *cpu, byte x, byte y);
void op_ldh(cpu_t *cpu, byte x, byte y);
void op_ldl(cpu_t *cpu, byte x, byte y);
void op_sph(cpu_t *cpu, byte x, byte y);
void op_spl(cpu_t *cpu, byte x, byte y);
void op_sdh(cpu_t *cpu, byte x, byte y);
void op_sdl(cpu_t *cpu, byte x, byte y);
void op_cph(cpu_t *cpu, byte x, byte y);
void op_cpl(cpu_t *cpu, byte x, byte y);
void op_cdh(cpu_t *cpu, byte x, byte y);
void op_cdl(cpu_t *cpu, byte x, byte y);

/* Load/Store words */
void op_lpw(cpu_t *cpu, byte x, byte y);
void op_ldw(cpu_t *cpu, byte x, byte y);
void op_spw(cpu_t *cpu, byte x, byte y);
void op_sdw(cpu_t *cpu, byte x, byte y);
void op_cpw(cpu_t *cpu, byte x, byte y);
void op_cdw(cpu_t *cpu, byte x, byte y);

/* Load/Store bytes with immediate */
void op_lphi(cpu_t *cpu, byte x, byte y);
void op_lpli(cpu_t *cpu, byte x, byte y);
void op_ldhi(cpu_t *cpu, byte x, byte y);
void op_ldli(cpu_t *cpu, byte x, byte y);
void op_sphi(cpu_t *cpu, byte x, byte y);
void op_spli(cpu_t *cpu, byte x, byte y);
void op_sdhi(cpu_t *cpu, byte x, byte y);
void op_sdli(cpu_t *cpu, byte x, byte y);
void op_cphi(cpu_t *cpu, byte x, byte y);
void op_cpli(cpu_t *cpu, byte x, byte y);
void op_cdhi(cpu_t *cpu, byte x, byte y);
void op_cdli(cpu_t *cpu, byte x, byte y);

/* Load/Store words with immediate */
void op_lpwi(cpu_t *cpu, byte x, byte y);
void op_ldwi(cpu_t *cpu, byte x, byte y);
void op_spwi(cpu_t *cpu, byte x, byte y);
void op_sdwi(cpu_t *cpu, byte x, byte y);
void op_cpwi(cpu_t *cpu, byte x, byte y);
void op_cdwi(cpu_t *cpu, byte x, byte y);

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
void op_nop(cpu_t *cpu, byte x, byte y);

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
    {
        op_addi,
        op_adci,
        op_subi,
        op_sbci,
        op_rsbi,
        op_rbci,
        op_muli,
        op_mlsi,
        op_divi,
        op_dvsi,
        op_modi,
        op_mdsi,
        op_movi,
    },
    {
        op_sali,
        op_sari,
        op_slsi,
        op_srsi,
        op_andi,
        op_iori,
        op_noti,
        op_xori
    },
    {
        op_ife,
        op_ifn,
        op_ifl,
        op_ifs,
        op_ifg,
        op_ifh,
        op_ils,
        op_iss,
        op_igs,
        op_ihs
    },
    {
        op_lph,
        op_lpl,
        op_ldh,
        op_ldl,
        op_sph,
        op_spl,
        op_sdh,
        op_sdl,
        op_cph,
        op_cpl,
        op_cdh,
        op_cdl
    },
    {
        op_lpw,
        op_ldw,
        op_spw,
        op_sdw,
        op_cpw,
        op_cdw
    },
    {
        op_lphi,
        op_lpli,
        op_ldhi,
        op_ldli,
        op_sphi,
        op_spli,
        op_sdhi,
        op_sdli
    },
    {
        op_lpwi,
        op_ldwi,
        op_spwi,
        op_sdwi
    },
    {
        op_jmp,
        op_jmpi,
        op_jsr,
        op_jsri,
        op_ret
    },
    {
        op_hwi,
        op_hwii
    },
    {
        op_hlt,
        op_nop
    },
    {},
    {}
};

#endif
