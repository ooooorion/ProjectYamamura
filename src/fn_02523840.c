#include "block.h"

/* 0x02523840 .. 0x025238B0, 29 instructions, 116 bytes. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; s32 field_C; };
extern s32 func_02523740(Obj *self);
extern s32 func_025237C0(Obj *self, s32 arg1);
extern s32 func_0276912C(Obj *self, s32 arg1);
void func_02523840(Obj *self, s32 arg1) {
    if (self->field_C == -1) self->vtable[5](self);
    func_025237C0(self, arg1);
    func_0276912C(self, arg1);
    func_02523740(self);
}
