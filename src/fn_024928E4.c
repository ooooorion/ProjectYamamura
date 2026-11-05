#include "block.h"

/* 0x024928E4 .. 0x02492930, 20 instructions, 80 bytes.
   Dispatches vtable slot +0x24 when the state changes. */

typedef struct { u8 pad0[4]; void *vtable; u8 pad8[4]; u32 field_C; } Obj;
typedef void (*VoidMethod)(void);
s32 func_024928E4(Obj *self, u32 arg1) {
    if (arg1 == self->field_C) return 0;
    (*(VoidMethod *)((u8 *)self->vtable + 0x24))();
    return 1;
}
