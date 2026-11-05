#include "block.h"

/* 0x0234B4F0 .. 0x0234B560, 29 instructions, 116 bytes.
   Vtable wrapper followed by two forwards and a cleanup. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; s32 field_C; };
extern void func_0234B470(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_0234B3F0(Obj *self);
void func_0234B4F0(Obj *self, s32 arg1) {
    if (self->field_C == -1) self->vtable[5](self);
    func_0234B470(self, arg1);
    func_0276912C(self, arg1);
    func_0234B3F0(self);
}
