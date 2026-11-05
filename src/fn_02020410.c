#include "block.h"

/* 0x02020410 .. 0x02020438, 11 instructions, 44 bytes.
   count/capacity/items at +0x00/+0x04/+0x08. The reload of count after the
   store is the compiler being unable to prove that items does not alias it,
   so the increment is a separate statement rather than count++. The bounds
   compare is cmpw (signed), so count and capacity are s32. */

typedef struct {
    s32 count;
    s32 capacity;
    u32 *items;
} Vec;

void func_02020410(Vec *self, u32 value) {
    if (self->count >= self->capacity) return;
    self->items[self->count] = value;
    self->count = self->count + 1;
}
