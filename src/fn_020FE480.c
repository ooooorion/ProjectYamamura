#include "block.h"

/* 0x020FE480 .. 0x020FE490, 5 instructions, 20 bytes.
   Returns 1 when any bit of mask is set in the word at +0x58. */

typedef struct {
    u8 pad0[0x58];
    s32 bits_58;
} Obj;

s32 func_020FE480(Obj *self, s32 mask) {
    return (self->bits_58 & mask) != 0;
}
