#include "block.h"

/* 0225917C wrapper: runs vtable slot 5 when +0x0C is -1, then forwards through
   0225907C, 0276912C and the object-only cleanup 022590FC. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
};

extern void func_0225907C(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_022590FC(Obj *self);

void func_0225917C(Obj *self, s32 arg1) {
    if (self->field_C == -1) {
        self->vtable[5](self);
    }
    func_0225907C(self, arg1);
    func_0276912C(self, arg1);
    func_022590FC(self);
}
