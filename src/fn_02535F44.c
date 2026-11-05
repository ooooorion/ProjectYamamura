#include "block.h"

/* 0x02535F44 .. 0x02535FB4, 29 instructions, 116 bytes. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; s32 field_C; };
extern s32 func_02535D58(Obj *self);
extern s32 func_02535EC4(Obj *self, s32 arg1);
extern s32 func_0276912C(Obj *self, s32 arg1);
void func_02535F44(Obj *self, s32 arg1) {
    if (self->field_C == -1) self->vtable[5](self);
    func_02535EC4(self, arg1);
    func_0276912C(self, arg1);
    func_02535D58(self);
}
