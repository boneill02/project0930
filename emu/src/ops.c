/* CPU Operations */
#include "emulator.h"
#include "device.h"

void op_add(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] += cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] += cpu->r[y];
    }
}

void op_addc(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] += cpu->m[++cpu->r[PC]] + cpu->r[C];
    } else {
        cpu->r[x] += cpu->r[y] + cpu->r[C];
    }
}

void op_sub(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] -= cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] -= cpu->r[y];
    }
}

void op_subc(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] -= cpu->m[++cpu->r[PC]] + cpu->r[C];
    } else {
        cpu->r[x] -= cpu->r[y] + cpu->r[C];
    }
}

void op_rsb(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] = cpu->m[++cpu->r[PC]] - cpu->r[x];
    } else {
        cpu->r[x] = cpu->r[y] - cpu->r[x];
    }
}

void op_rsbc(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] = (cpu->m[++cpu->r[PC]] - cpu->r[x]) + cpu->r[C];
    } else {
        cpu->r[x] = (cpu->m[++cpu->r[PC]] - cpu->r[x]) + cpu->r[C];
    }
}

void op_mul(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] *= cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] *= cpu->r[y];
    }
}

void op_muls(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
    }

    short res = srx * sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_div(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] /= cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] /= cpu->r[y];
    }
}

void op_divs(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
    }

    short res = srx / sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_mod(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] %= cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] %= cpu->r[y];
    }
}

void op_mods(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
    }

    short res = srx % sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_mov(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] = cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] = cpu->r[y];
    }
}

void op_sal(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] = cpu->r[x] << cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] = cpu->r[x] << cpu->r[y];
    }
}

void op_sar(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] = cpu->r[x] >> cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] = cpu->r[x] >> cpu->r[y];
    }
}

void op_sls(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
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

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
    }

    short res = srx >> sry;
    if (res < 0)  {
        cpu->r[x] = get_negative(res);
    } else {
        cpu->r[x] = (word) res;
    }
}

void op_and(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] &= cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] &= cpu->r[y];
    }
}

void op_or(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] |= cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] |= cpu->r[y];
    }
}

void op_xor(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] ^= cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] ^= cpu->r[y];
    }
}

void op_ife(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        if (cpu->r[x] != cpu->m[++cpu->r[PC]])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    } else {
        if (cpu->r[x] != cpu->r[y])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    }
}

void op_ifne(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        if (cpu->r[x] == cpu->m[++cpu->r[PC]])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    } else {
        if (cpu->r[x] == cpu->r[y])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    }
}

void op_iflt(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        if (cpu->r[x] >= cpu->m[++cpu->r[PC]])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    } else {
        if (cpu->r[x] >= cpu->r[y])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    }
}

void op_ifle(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        if (cpu->r[x] > cpu->m[++cpu->r[PC]])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    } else {
        if (cpu->r[x] > cpu->r[y])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    }
}

void op_ifgt(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        if (cpu->r[x] <= cpu->m[++cpu->r[PC]])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    } else {
        if (cpu->r[x] <= cpu->r[y])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    }
}

void op_ifge(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        if (cpu->r[x] < cpu->m[++cpu->r[PC]])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    } else {
        if (cpu->r[x] < cpu->r[y])  {
            cpu->r[PC]++;
            if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
                cpu->r[PC]++;
            }
        }
    }
}

void op_iflts(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
    }
    
    if (srx >= sry) {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ifles(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
    }
    
    if (srx > sry) {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ifgts(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
    }

    if (srx <= sry) {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_ifges(cpu_t *cpu, byte x, byte y) {
    int srx, sry; // signed Rx, Ry
    if (is_positive(cpu->r[x])) {
        srx = get_unsigned(cpu->r[x]);
    } else {
        srx = cpu->r[x] * -1;
    }

    if (y == 0xF) {
        word imm = cpu->m[++cpu->r[PC]];
        if (is_positive(imm)) {
        sry = get_unsigned(imm);
        } else {
            sry = get_unsigned(imm) * -1;
        }
    } else {
        if (is_positive(cpu->r[y])) {
        sry = get_unsigned(cpu->r[y]);
        } else {
            sry = get_unsigned(cpu->r[y]) * -1;
        }
    }
    
    if (srx < sry) {
        cpu->r[PC]++;
        if (has_immediate(construct_op(cpu->m[cpu->r[PC]]))) {
            cpu->r[PC]++;
        }
    }
}

void op_lw(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->r[x] = cpu->m[++cpu->r[PC]];
    } else {
        cpu->r[x] = cpu->m[cpu->r[y]];
    }
}

void op_sw(cpu_t *cpu, byte x, byte y) {
    if (y == 0xF) {
        cpu->m[cpu->r[x]] = cpu->m[++cpu->r[PC]];
    } else {
        cpu->m[cpu->r[x]] = cpu->r[y];
    }
}

void op_hwi(cpu_t *cpu, byte x, byte y) {
    // TODO hardware
    // Temporary code
    if (cpu->r[x] == 0) {
        // Output
        if (y == 0xF) {
            putchar((char) cpu->m[++cpu->r[PC]]);
        } else {
            putchar((char) cpu->r[y]);
        }
    } else if (cpu->r[x] == 1) {
        if (y == 0xF) {
            write_display1(cpu->m[++cpu->r[PC]], cpu);
        } else {
            write_display1(cpu->r[y], cpu);
        }
    }
}

void op_hlt(cpu_t *cpu, byte x, byte y) { 
    cpu->running = false;
}
