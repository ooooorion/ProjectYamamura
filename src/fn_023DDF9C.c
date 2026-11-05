#include "block.h"

/* 0x023DDF9C .. 0x023DDFE8, 20 instructions, 80 bytes.
   Returns zero for the current value, otherwise dispatches virtual slot 9. */

typedef struct Obj Obj;
typedef s32 (*ObjMethod)(void);
struct Obj { u8 pad0[4]; ObjMethod *vtable; u8 pad8[4]; u32 field_C; };
s32 func_023DDF9C(Obj *self, u32 value) {
    if (value == self->field_C) return 0;
    (*(ObjMethod *)((u8 *)self->vtable + 0x24))();
    return 1;
}
