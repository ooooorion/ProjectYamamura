#include "block.h"

/* 0x0239E388 .. 0x0239E394, 4 instructions, 16 bytes.
   Stores the value and sets state three. */

typedef struct { u8 pad0[0x48]; s32 field_48; u8 pad4C[0xC]; s32 field_58; } Obj;
void func_0239E388(Obj *self, s32 value) {
    self->field_58 = value;
    self->field_48 = 3;
}
