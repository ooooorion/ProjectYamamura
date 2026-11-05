#include "block.h"

/* 0x0250801C .. 0x02508050, 14 instructions, 56 bytes.
   Releases the first subresource and forwards to the shared teardown. */

typedef struct { u8 pad0[0x9C]; s32 field_9C; } Obj;
extern void func_0246DC7C(s32 value);
extern void func_02507FE4(Obj *self);
void func_0250801C(Obj *self) {
    func_0246DC7C(self->field_9C);
    func_02507FE4(self);
}
