#include "block.h"

/* 0x021FF68C .. 0x021FF6B8, 12 instructions, 48 bytes.
   Matches two source words against +3/+4. */

typedef struct { u8 pad0[3]; u8 field_3; u8 field_4; } Obj;
typedef struct { u32 field_0; u32 field_4; } Source;
s32 func_021FF68C(Obj *self, Source *source) {
    if (source->field_0 == (u8)self->field_3 && source->field_4 == (u8)self->field_4) return 1;
    return 0;
}
