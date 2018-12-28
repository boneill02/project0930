/* Utility functions for the emulator */
#include "emulator.h"

bool is_positive(word src) {
    return (src & 0b1000000000000000) >> 15;
}

word get_negative(word src) {
    return src & 0b0111111111111111;
}

word get_unsigned(word src) {
    return src & 0b0111111111111111;
}

byte get_byte(word src, byte offset) {
    if (offset) return src & 0x00FF;
    return (src & 0xFF00) >> 8;
}

byte get_nibble_from_word(word src, byte offset) {
    if (offset == 0) return (src & 0xF000) >> 12;
    if (offset == 1) return (src & 0x0F00) >> 8;
    if (offset == 2) return (src & 0x00F0) >> 4;
    if (offset == 3) return src & 0x000F;
}

byte get_nibble_from_byte(byte src, byte offset) {
    if (offset) return src & 0x0F;
    return (src & 0xF0) >> 4;
}

op_t *construct_op(word code) {
    op_t *op = malloc(sizeof(op_t));
    
    memset(op, 0, sizeof(op));

    op->c = get_nibble_from_word(code, 0);
    op->o = get_nibble_from_word(code, 1);
    op->x = get_nibble_from_word(code, 2);
    op->y = get_nibble_from_word(code, 3);

    op->co = get_byte(code, 0);
    op->xy = get_byte(code, 1);

    return op;
}
