#include "block.h"

/* 0x02508738 .. 0x0250879C, 26 instructions, 104 bytes.
   Selects a table entry and forwards it with the extra argument. */

typedef struct {
    u8 pad0[0x90];
    u32 count;
    u8 pad94[4];
    s32 *items;
} Obj;
extern void func_025080DC(void *self, s32 *out, s32 arg);
extern void func_0249540C(s32 value, s32 arg1);
void func_02508738(Obj *self, s32 arg1, s32 arg2) {
    s32 index;
    s32 value;

    func_025080DC(self, &index, arg1);
    value = 0;
    if ((u32)index < self->count) value = self->items[index];
    func_0249540C(value, arg2);
}
