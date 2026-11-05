#include "block.h"

/* 0x021799CC .. 0x02179A3C, 29 instructions, 116 bytes.
   Runs vtable slot 5 when +0x0C is -1, then forwards both arguments through
   two helpers and finishes with an object-only helper. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
};

extern void func_0217994C(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_021798CC(Obj *self);

void func_021799CC(Obj *self, s32 arg1) {
    if (self->field_C == -1) {
        self->vtable[5](self);
    }
    func_0217994C(self, arg1);
    func_0276912C(self, arg1);
    func_021798CC(self);
}
