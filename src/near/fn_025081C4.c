#include "block.h"

/* 0x025081C4 .. 0x02508224, 25 instructions, 100 bytes.
   Selects a table entry and dispatches its +0x8C method. */

typedef struct {
    u8 pad0[0x90];
    u32 count;
    u8 pad94[4];
    void **items;
} Obj;
extern void func_025080DC(void *self, s32 *out, s32 arg);
void func_025081C4(Obj *self, s32 arg1) {
    s32 index;
    void *object;

    func_025080DC(self, &index, arg1);
    object = 0;
    if ((u32)index < self->count) object = self->items[index];
    (*(void (**)(void *))((u8 *)*(void **)object + 0x8C))(object);
}
