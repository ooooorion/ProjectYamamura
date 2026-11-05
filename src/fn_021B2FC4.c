#include "block.h"

/* 0x021B2FC4 .. 0x021B2FE8, 10 instructions, 40 bytes.
   True only for state 1 with +0x526 set. */

typedef struct { u8 pad0[0x308]; s32 field_308; u8 pad30C[0x21A]; u8 field_526; } Obj;
s32 func_021B2FC4(Obj *self) {
    if (self->field_308 == 1 && self->field_526 != 0) return 1;
    return 0;
}
