#include "block.h"

/* 0x024121BC .. 0x0241222C, 29 instructions, 116 bytes.
   Vtable wrapper followed by two forwards and a cleanup. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; s32 field_C; };
extern void func_0241213C(Obj *self, s32 arg1);
extern void func_0276912C(Obj *self, s32 arg1);
extern void func_02411FD0(Obj *self);
void func_024121BC(Obj *self, s32 arg1) {
    if (self->field_C == -1) self->vtable[5](self);
    func_0241213C(self, arg1);
    func_0276912C(self, arg1);
    func_02411FD0(self);
}
