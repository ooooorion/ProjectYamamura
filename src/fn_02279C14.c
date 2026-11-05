#include "block.h"

/* 02279C14 wrapper: runs vtable slot 5 when +0x0C is -1, then forwards through
   02279B14, 0276912C and the object-only cleanup 02279B94. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
};

extern void func_02279B14(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_02279B94(Obj *self);

void func_02279C14(Obj *self, s32 arg1) {
    if (self->field_C == -1) {
        self->vtable[5](self);
    }
    func_02279B14(self, arg1);
    func_0276912C(self, arg1);
    func_02279B94(self);
}
