#include "block.h"

/* 0x02507FAC .. 0x02507FE0, 14 instructions, 56 bytes.
   Releases the first subresource and forwards to the shared teardown. */

typedef struct { u8 pad0[0x9C]; s32 field_9C; } Obj;
extern void func_0246DC58(s32 value);
extern void func_02507F74(Obj *self);
void func_02507FAC(Obj *self) {
    func_0246DC58(self->field_9C);
    func_02507F74(self);
}
