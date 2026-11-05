#include "block.h"

/* 0x0232E59C .. 0x0232E5E8, 20 instructions, 80 bytes.
   Calls vtable slot 9 unless the id already matches. */

typedef void (*VoidMethod)(void);
typedef struct { u8 pad0[4]; VoidMethod *vtable; u8 pad8[4]; u32 field_C; } Obj;
s32 func_0232E59C(Obj *self, u32 value) {
    if (value == self->field_C) return 0;
    self->vtable[9]();
    return 1;
}
