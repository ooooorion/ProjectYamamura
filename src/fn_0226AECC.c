#include "block.h"

/* 0226AECC wrapper: runs vtable slot 5 when +0x0C is -1, then forwards through
   0226ADCC, 0276912C and the object-only cleanup 0226AE4C. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *self);

struct Obj {
    u8 pad0[4];
    ObjMethod *vtable;
    u8 pad8[4];
    s32 field_C;
};

extern void func_0226ADCC(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_0226AE4C(Obj *self);

void func_0226AECC(Obj *self, s32 arg1) {
    if (self->field_C == -1) {
        self->vtable[5](self);
    }
    func_0226ADCC(self, arg1);
    func_0276912C(self, arg1);
    func_0226AE4C(self);
}
