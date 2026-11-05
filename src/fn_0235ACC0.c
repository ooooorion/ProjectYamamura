#include "block.h"

/* 0x0235ACC0 .. 0x0235AD30, 29 instructions, 116 bytes.
   Vtable wrapper followed by two forwards and a cleanup. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; s32 field_C; };
extern void func_0235AC40(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_0235AAD4(Obj *self);
void func_0235ACC0(Obj *self, s32 arg1) {
    if (self->field_C == -1) self->vtable[5](self);
    func_0235AC40(self, arg1);
    func_0276912C(self, arg1);
    func_0235AAD4(self);
}
