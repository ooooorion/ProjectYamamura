#include "block.h"

/* 022543CC wrapper: runs vtable slot 5 when +0x0C is -1, then forwards through
   022542CC, 0276912C and the object-only cleanup 0225434C. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
};

extern void func_022542CC(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_0225434C(Obj *self);

void func_022543CC(Obj *self, s32 arg1) {
    if (self->field_C == -1) {
        self->vtable[5](self);
    }
    func_022542CC(self, arg1);
    func_0276912C(self, arg1);
    func_0225434C(self);
}
