#include "block.h"

/* 0x020359B4 .. 0x020359EC, 15 instructions, 60 bytes.
   Mirror the current count into the array at +0xD0, then perform the usual
   bounded append at +0x44/+0x48/+0x4C. The local array pointer is what
   reproduces the target's r12 count / r11 base allocation. */

typedef struct {
    u8 pad0[68];
    s32 count;
    s32 capacity;
    u32 *items;
    u8 pad_50[0x80];
    u32 *array_D0;
} Obj;

void func_020359B4(Obj *self, u32 value) {
    s32 count;
    u32 *array;

    count = self->count;
    array = self->array_D0;
    array[count] = count;

    if (self->count < self->capacity) {
        self->items[self->count] = value;
        self->count = self->count + 1;
    }
}
