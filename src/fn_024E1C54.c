#include "block.h"

/* 0x024E1C54 .. 0x024E1C60, 3 instructions, 12 bytes.
   Returns word +0x24C from the pointer at +0x38. */

typedef struct { u8 pad0[0x38]; void *field_38; } Obj;
s32 func_024E1C54(Obj *self) {
    return *(s32 *)((u8 *)self->field_38 + 0x24C);
}
