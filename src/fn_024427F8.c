#include "block.h"

/* 0x024427F8 .. 0x0244281C, 10 instructions, 40 bytes.
   Returns the flag of the first stored array element when present. */

typedef struct { u8 pad0[0x284]; s32 field_284; u8 pad288[4]; void **field_28C; } Obj;
s32 func_024427F8(Obj *self) {
    void *item;
    item = 0;
    if (self->field_284 != 0) item = *self->field_28C;
    return *(s32 *)((u8 *)item + 0x1B4) != 0;
}
