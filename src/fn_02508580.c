#include "block.h"

/* 0x02508580 .. 0x025085D4, 22 instructions, 88 bytes.
   Selects a table entry and forwards it to the indexed handler. */

typedef struct {
    u8 pad0[0x90];
    u32 count;
    u8 pad94[4];
    s32 *items;
} Obj;
extern void func_025080DC(void *self, s32 *out, s32 arg);
extern void func_024950F0(s32 value);
void func_02508580(Obj *self, s32 arg1) {
    s32 index;
    s32 value;

    func_025080DC(self, &index, arg1);
    value = 0;
    if ((u32)index < self->count) value = self->items[index];
    func_024950F0(value);
}
