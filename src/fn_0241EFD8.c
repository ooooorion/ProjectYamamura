#include "block.h"

/* 0x0241EFD8 .. 0x0241F048, 29 instructions, 116 bytes.
   Vtable wrapper followed by two forwards and a cleanup. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; s32 field_C; };
extern void func_0241EF58(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_0241EED8(Obj *self);
void func_0241EFD8(Obj *self, s32 arg1) {
    if (self->field_C == -1) self->vtable[5](self);
    func_0241EF58(self, arg1);
    func_0276912C(self, arg1);
    func_0241EED8(self);
}
