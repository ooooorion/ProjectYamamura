#include "block.h"

/* 0x021FCF9C .. 0x021FCFA4, 3 instructions, 12 bytes.
   Stores a byte at +0 and a word at +4. */

typedef struct { s8 field_0; u8 pad1[3]; s32 field_4; } Obj;
void func_021FCF9C(Obj *self, s8 byte, s32 word) {
    self->field_0 = byte;
    self->field_4 = word;
}
