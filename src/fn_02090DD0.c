#include "block.h"

/* 0x02090DD0 .. 0x02090DD8, 3 instructions, 12 bytes.
   Extracts bit 0 of the word at +0xBF0 with a mask, so the return is s32. */

typedef struct {
    u8 pad0[0xBF0];
    s32 flags_BF0;
} Obj;

s32 func_02090DD0(Obj *self) {
    return self->flags_BF0 & 1;
}
