/* CPU Operations */
#include "emulator.h"

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
        sry = cpu->r[y] * -1;
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
        sry = cpu->r[y] * -1;
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
        sry = cpu->r[y] * -1;
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
        sry = cpu->r[y] * -1;
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
        sry = cpu->r[y] * -1;
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

void op_hlt(cpu_t *cpu, byte x, byte y) {
    cpu->running = false;
}
