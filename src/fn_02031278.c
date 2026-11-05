#include "block.h"

/* 0x02031278 .. 0x020312A0, 11 instructions, 44 bytes.
   count/capacity/items at +0x44/+0x48/+0x4C, the same bounded-append shape
   as func_02020410. The reload of count after the store is deliberate: the
   compiler cannot prove items does not alias it. */

typedef struct {
    u8 pad0[68];
    s32 count;
    s32 capacity;
    u32 *items;
} Vec;

void func_02031278(Vec *self, u32 value) {
    if (self->count >= self->capacity) return;
    self->items[self->count] = value;
    self->count = self->count + 1;
}
