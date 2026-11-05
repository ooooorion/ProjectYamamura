#include "block.h"

/* 0x0208E3B8 .. 0x0208E3DC, 10 instructions, 40 bytes.
   Returns 3 when bit 28 of +0x24 and bit 0 of +0x20 are both set, else 2.
   GHS materialises both constants on separate paths, so this stays a plain
   if/return pair rather than a conditional expression. */

typedef struct {
    u8 pad0[0x20];
    s32 flags_20;
    u32 bits_24;
} Obj;

s32 func_0208E3B8(Obj *self) {
    if (((self->bits_24 >> 28) & 1) && (self->flags_20 & 1)) {
        return 3;
    }
    return 2;
}
