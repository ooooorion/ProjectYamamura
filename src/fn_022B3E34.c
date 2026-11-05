#include "block.h"

/* 0x022B3E34 .. 0x022B3E80, 20 instructions, 80 bytes.
   Calls vtable slot 9 unless the id already matches. */

typedef void (*VoidMethod)(void);
typedef struct { u8 pad0[4]; VoidMethod *vtable; u8 pad8[4]; u32 field_C; } Obj;
s32 func_022B3E34(Obj *self, u32 value) {
    if (value == self->field_C) return 0;
    self->vtable[9]();
    return 1;
}
