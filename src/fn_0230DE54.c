#include "block.h"

/* 0x0230DE54 .. 0x0230DE64, 5 instructions, 20 bytes.
   Clears three words in the object. */

typedef struct { u8 pad0[0x180]; s32 field_180; u8 pad184[0x1470]; s32 field_15F4; s32 field_15F8; } Obj;
void func_0230DE54(Obj *self) {
    self->field_15F8 = 0;
    self->field_15F4 = 0;
    self->field_180 = 0;
}
