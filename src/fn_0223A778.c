#include "block.h"

/* 0223A778: clears one flag, conditionally dispatches vtable slot 5, then runs
   the object through 0223A6F8 and the shared cleanup. */

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

extern void func_0223A6F8(Obj *self);
extern void func_0276914C(Obj *self);

void func_0223A778(Obj *self) {
    self->field_1D = 0;
    if (self->field_1C != 0 && self->field_C == -1) {
        self->vtable[5](self);
    }
    func_0223A6F8(self);
    func_0276914C(self);
}
