#include "block.h"

/* 0x021C8F60 .. 0x021C8FD0, 29 instructions, 116 bytes.
   Runs vtable slot 5 when +0x0C is -1, forwards both arguments through two
   helpers, then runs the object-only cleanup. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
};

extern void func_021C8EE0(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_021C8E60(Obj *self);

void func_021C8F60(Obj *self, s32 arg1) {
    if (self->field_C == -1) {
        self->vtable[5](self);
    }
    func_021C8EE0(self, arg1);
    func_0276912C(self, arg1);
    func_021C8E60(self);
}
