#include "block.h"

/* 0x025281C0 .. 0x02528230, 29 instructions, 116 bytes. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; s32 field_C; };
extern s32 func_025280C0(Obj *self);
extern s32 func_02528140(Obj *self, s32 arg1);
extern s32 func_0276912C(Obj *self, s32 arg1);
void func_025281C0(Obj *self, s32 arg1) {
    if (self->field_C == -1) self->vtable[5](self);
    func_02528140(self, arg1);
    func_0276912C(self, arg1);
    func_025280C0(self);
}
