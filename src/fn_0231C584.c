#include "block.h"

/* 0x0231C584 .. 0x0231C5C8, 18 instructions, 72 bytes.
   Validates the object state and the +0x38 child. */

typedef struct { u8 pad0[0x38]; void *field_38; u8 pad3C[0x60]; s32 field_9C; u8 padA0[0xC]; s32 field_AC; } Obj;
s32 func_0231C584(Obj *self) {
    void *child;
    u8 state;
    if ((self->field_9C != 3 && !(self->field_AC & 0x2000)) ||
        (child = self->field_38) == 0 ||
        (((state = *(u8 *)((u8 *)child + 0x2CC)) != 3) && state != 1)) return 0;
    return 1;
}
