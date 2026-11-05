#include "block.h"

/* 0x021313AC .. 0x021313B8, 4 instructions, 16 bytes.
   Clears bit 0 of the word at +0x4B4. */

typedef struct {
    u8 pad0[0x4B4];
    u32 bits_4B4;
} Obj;

void func_021313AC(Obj *self) {
    self->bits_4B4 &= 0xFFFFFFFE;
}
