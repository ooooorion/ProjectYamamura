#include "block.h"

/* 0x02017320 .. 0x0201734C, 12 instructions, 48 bytes.
   flag_24A contributes bit 0; flag_249 selects 2 when set and 4 when clear.
   The early-return form below is what reproduces the target's single
   or/blr exit; the equivalent ternary form compiles to 40 bytes instead, so
   here the source shape matters more than the meaning. */

typedef struct {
    u8 pad0[0x249];
    u8 flag_249;
    u8 flag_24A;
} Obj;

u32 func_02017320(Obj *self) {
    u32 result = 0;
    if (self->flag_24A) result |= 1;
    if (self->flag_249) return result | 2;
    return result | 4;
}
