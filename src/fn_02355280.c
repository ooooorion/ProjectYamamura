#include "block.h"

/* 0x02355280 .. 0x023552E8, 27 instructions, 108 bytes.
   Clears a flag, optionally dispatches slot 5, then runs cleanup helpers. */

typedef struct Obj Obj;
typedef void (*ObjMethod)(Obj *);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; s32 field_C; u8 pad10[0xC]; u8 field_1C; u8 field_1D; };
extern void func_02355200(Obj *self);
extern void func_0276914C(Obj *self);
void func_02355280(Obj *self) {
    self->field_1D = 0;
    if (self->field_1C != 0 && self->field_C == -1) self->vtable[5](self);
    func_02355200(self);
    func_0276914C(self);
}
