#include "block.h"

/* 0226B480 wrapper: runs vtable slot 5 when +0x0C is -1, then forwards through
   0226B380, 0276912C and the object-only cleanup 0226B400. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
};

extern void func_0226B380(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_0226B400(Obj *self);

void func_0226B480(Obj *self, s32 arg1) {
    if (self->field_C == -1) {
        self->vtable[5](self);
    }
    func_0226B380(self, arg1);
    func_0276912C(self, arg1);
    func_0226B400(self);
}
