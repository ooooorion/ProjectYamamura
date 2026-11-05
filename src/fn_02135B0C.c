#include "block.h"

/* 0x02135B0C .. 0x02135B14, 3 instructions, 12 bytes.
   Extracts bits 5..6 of the word at +0x14. */

typedef struct {
    u8 pad0[0x14];
    u32 flags_14;
} Obj;

s32 func_02135B0C(Obj *self) {
    return (self->flags_14 >> 5) & 3;
}
