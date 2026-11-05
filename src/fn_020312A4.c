#include "block.h"

/* 0x020312A4 .. 0x020312CC, 11 instructions, 44 bytes.
   The same bounded append as func_02031278, moved to
   +0x50/+0x54/+0x58. */

typedef struct {
    u8 pad0[80];
    s32 count;
    s32 capacity;
    u32 *items;
} Vec;

void func_020312A4(Vec *self, u32 value) {
    if (self->count >= self->capacity) return;
    self->items[self->count] = value;
    self->count = self->count + 1;
}
