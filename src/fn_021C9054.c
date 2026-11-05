#include "block.h"

/* 0x021C9054 .. 0x021C90BC, 27 instructions, 108 bytes.
   Clears +0x1D, invokes vtable slot 5 when +0x1C is set and +0x0C is -1,
   then calls two teardown helpers. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
    u8 pad10[0xC];
    u8 field_1C;
    u8 field_1D;
};

extern void func_021C8FD4(Obj *self);
extern void func_0276914C(Obj *self);

void func_021C9054(Obj *self) {
    self->field_1D = 0;
    if (self->field_1C != 0 && self->field_C == -1) {
        self->vtable[5](self);
    }
    func_021C8FD4(self);
    func_0276914C(self);
}
