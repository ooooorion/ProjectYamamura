#include "block.h"

/* 0x023330E4 .. 0x02333104, 9 instructions, 36 bytes.
   Selects a float from bit 1 of +0xCF8. */

typedef struct { u8 pad0[0xCF8]; u16 field_CF8; } Obj;
f32 func_023330E4(Obj *self) {
    if ((self->field_CF8 >> 1) & 1) return *(f32 *)0x10065E48;
    return *(f32 *)0x10065D7C;
}
