#include "block.h"

/* 0x020A37EC .. 0x020A37F4, 3 instructions, 12 bytes.
   Returns bit 2 of the byte at +0x910. The byte load and the shift both
   narrow to u8 before the mask, so the intermediate type matters. */

typedef struct {
    u8 pad0[0x910];
    u8 flags_910;
} Obj;

s32 func_020A37EC(Obj *self) {
    return (self->flags_910 >> 2) & 1;
}
