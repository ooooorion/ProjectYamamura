#include "block.h"

/* 0x02314474 .. 0x02314494, 9 instructions, 36 bytes.
   Packs three fields and a tag into one word. */

typedef struct { u8 pad0[8]; s32 field_8; s32 field_C; s32 field_10; } Obj;
s32 func_02314474(Obj *self) {
    return (self->field_10 << 24) | 0x10000000 | (self->field_8 << 16) | self->field_C;
}
