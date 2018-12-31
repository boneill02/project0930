/* CPU Operations */
#include "emulator.h"
#include "device.h"

void op_add(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] += cpu->r[y];
}

void op_adc(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] += cpu->r[y] + cpu->r[C];
}

void op_sub(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] -= cpu->r[y];
}

void op_sbc(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] -= cpu->r[y] + cpu->r[C];
}

void op_rsb(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->r[y] - cpu->r[x];
}

void op_rbc(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = (cpu->r[y] - cpu->r[x]) + cpu->r[C];
}

void op_mul(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] *= cpu->r[y];
}

void op_mls(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }

    short res = srx * sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_div(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] /= cpu->r[y];
}

void op_dvs(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }

    short res = srx / sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_mod(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] %= cpu->r[y];
}

void op_mds(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }

    short res = srx % sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_mov(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->r[y];
}

void op_inc(cpu_t *cpu, byte x, byte y) {
    cpu->r[x]++;
}

void op_dec(cpu_t *cpu, byte x, byte y) {
    cpu->r[x]--;
}

void op_clr(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = 0;
}

void op_sal(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->r[x] << cpu->r[y];
}

void op_sar(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->r[x] >> cpu->r[y];
}

void op_sls(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }

    short res = srx << sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_srs(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }

    short res = srx >> sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_and(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] &= cpu->r[y];
}

void op_ior(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] |= cpu->r[y];
}

void op_not(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = ~cpu->r[y];
}

void op_xor(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] ^= cpu->r[y];
}

void op_addi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] += cpu->m[++cpu->r[PC]];
}

void op_adci(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] += cpu->m[++cpu->r[PC]] + cpu->r[C];
}

void op_subi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] -= cpu->m[++cpu->r[PC]];
}

void op_sbci(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] -= cpu->m[++cpu->r[PC]] + cpu->r[C];
}

void op_rsbi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[++cpu->r[PC]] - cpu->r[x];
}

void op_rbci(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[++cpu->r[PC]] - cpu->r[x] - cpu->r[C];
}

void op_muli(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] *= cpu->m[++cpu->r[PC]];
}

void op_mlsi(cpu_t *cpu, byte x, byte y) {
    int srx, sim; // signed Rx, IMM
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }
    int imm = cpu->m[++cpu->r[PC]];
    if (is_positive(imm)) {
        sim = get_unsigned(imm);
    } else {
        sim = get_unsigned(imm) * -1;
    }

    short res = srx * sim;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_divi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[++cpu->r[PC]];
}

void op_dvsi(cpu_t *cpu, byte x, byte y) {
    int srx, sim; // signed Rx, IMM
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }
    int imm = cpu->m[++cpu->r[PC]];
    if (is_positive(imm)) {
        sim = get_unsigned(imm);
    } else {
        sim = get_unsigned(imm) * -1;
    }

    short res = srx / sim;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_modi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] %= cpu->m[++cpu->r[PC]];
}

void op_mdsi(cpu_t *cpu, byte x, byte y) {
    int srx, sim; // signed Rx, IMM
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }
    int imm = cpu->m[++cpu->r[PC]];
    if (is_positive(imm)) {
        sim = get_unsigned(imm);
    } else {
        sim = get_unsigned(imm) * -1;
    }

    short res = srx % sim;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_movi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[++cpu->r[PC]];
}

void op_sali(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->r[x] << cpu->m[++cpu->r[PC]];
}

void op_sari(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->r[x] >> cpu->m[++cpu->r[PC]];
}

void op_slsi(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }

    short res = srx << sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_srsi(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }

    short res = srx << sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_andi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] &= cpu->m[++cpu->r[PC]];
}

void op_iori(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] |= cpu->m[++cpu->r[PC]];
}

void op_noti(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = ~cpu->m[++cpu->r[PC]];
}

void op_xori(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] ^= cpu->m[++cpu->r[PC]];
}

void op_ife(cpu_t *cpu, byte x, byte y) {
    if (cpu->r[x] != cpu->r[y])  {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ifn(cpu_t *cpu, byte x, byte y) {
    if (cpu->r[x] == cpu->r[y])  {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ifl(cpu_t *cpu, byte x, byte y) {
    if (cpu->r[x] >= cpu->r[y])  {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ifs(cpu_t *cpu, byte x, byte y) {
    if (cpu->r[x] > cpu->r[y])  {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ifg(cpu_t *cpu, byte x, byte y) {
    if (cpu->r[x] <= cpu->r[y])  {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ifh(cpu_t *cpu, byte x, byte y) {
    if (cpu->r[x] < cpu->r[y])  {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ils(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }
    
    if (srx >= sry) {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_iss(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }
    
    if (srx > sry) {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_igs(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }
    if (srx <= sry) {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ihs(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
    } else {
        sry = get_unsigned(cpu->r[y]) * -1;
    }
    if (srx < sry) {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_lpw(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[cpu->r[y]];
}

void op_ldw(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[cpu->r[y] + PROGRAM_MAX];
}

void op_lpb(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[cpu->r[y]] & 0x00FF;
}

void op_ldb(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[cpu->r[y] + PROGRAM_MAX] & 0x00FF;
}

void op_spw(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->r[x]] = cpu->r[y];
}

void op_sdw(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->r[x] + PROGRAM_MAX] = cpu->r[y];
}

void op_spb(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->r[x]] = cpu->r[y] & 0x00FF;
}

void op_sdb(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->r[x] + PROGRAM_MAX] = cpu->r[y] & 0x00FF;
}

void op_cpw(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->r[x]] = 0;
}

void op_cdw(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->r[x] + PROGRAM_MAX] = 0;
}

void op_lpwi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[cpu->m[++cpu->r[PC]]];
}

void op_ldwi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[cpu->m[++cpu->r[PC]] + PROGRAM_MAX];
}

void op_lpbi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[cpu->m[++cpu->r[PC]]];
}

void op_ldbi(cpu_t *cpu, byte x, byte y) {
    cpu->r[x] = cpu->m[cpu->m[++cpu->r[PC]] + PROGRAM_MAX] & 0x00FF;
}

void op_spwi(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->m[++cpu->r[PC]]] = cpu->r[x];
}

void op_sdwi(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->m[++cpu->r[PC]] + PROGRAM_MAX] = cpu->r[x];
}

void op_spbi(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->m[++cpu->r[PC]]] = cpu->r[x] & 0x00FF;
}

void op_sdbi(cpu_t *cpu, byte x, byte y) {
    cpu->m[cpu->m[++cpu->r[PC]] + PROGRAM_MAX] = cpu->r[x] & 0x00FF;
}

void op_jmp(cpu_t *cpu, byte x, byte y) {
    cpu->r[PC] = cpu->r[x];
}

void op_jmpi(cpu_t *cpu, byte x, byte y) {
    cpu->r[PC] = cpu->m[++cpu->r[PC]];
}

void op_jsr(cpu_t *cpu, byte x, byte y) {
    cpu->r[PC] = cpu->m[++cpu->r[SP]];
}

void op_jsri(cpu_t *cpu, byte x, byte y) {
    cpu->m[++cpu->r[SP]] = cpu->m[++cpu->r[PC]];
    cpu->r[PC] = cpu->m[cpu->r[SP]];
}

void op_ret(cpu_t *cpu, byte x, byte y) {
    cpu->r[PC] = cpu->m[--cpu->r[SP]];
}

void op_hwi(cpu_t *cpu, byte x, byte y) {
    // TODO hardware
    // Temporary code
    if (cpu->r[x] == 0) {
        // Output
        putchar((char) cpu->r[y]);
    } else if (cpu->r[x] == 1) {
        // Input
        cpu->r[y] = getchar();
    }
}

void op_hwii(cpu_t *cpu, byte x, byte y) {
    // TODO hardware
    if (cpu->r[x] == 1) {
        write_display1(y, cpu->m[++cpu->r[PC]]);
    }
}

void op_hwn(cpu_t *cpu, byte x, byte y) {
    // TODO hardware
}

void op_hlt(cpu_t *cpu, byte x, byte y) { 
    cpu->running = false;
}
