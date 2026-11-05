#include "block.h"

/* 0x020799A4 .. 0x020799B4, 5 instructions, 20 bytes.
   Tests the five flag bits at +0x164 (mask 0x1E) and returns the 0/1
   materialised by the branchless sequence. */

typedef struct {
    u8 pad0[0x164];
    u8 flags_164;
} Obj;

s32 func_020799A4(Obj *self) {
    return (self->flags_164 & 0x1E) != 0;
}
