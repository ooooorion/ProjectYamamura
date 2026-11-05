#include "block.h"

/* 0x02333108 .. 0x02333128, 9 instructions, 36 bytes.
   Selects a float from bit 0 of +0xCF8. */

typedef struct { u8 pad0[0xCF8]; u16 field_CF8; } Obj;
f32 func_02333108(Obj *self) {
    if (self->field_CF8 & 1) return *(f32 *)0x10065E4C;
    return *(f32 *)0x10065D7C;
}
