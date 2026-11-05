#include "block.h"

/* 022416D4 wrapper: runs vtable slot 5 when +0x0C is -1, then forwards through
   022415D4, 0276912C and the object-only cleanup 02241654. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
};

extern void func_022415D4(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_02241654(Obj *self);

void func_022416D4(Obj *self, s32 arg1) {
    if (self->field_C == -1) {
        self->vtable[5](self);
    }
    func_022415D4(self, arg1);
    func_0276912C(self, arg1);
    func_02241654(self);
}
