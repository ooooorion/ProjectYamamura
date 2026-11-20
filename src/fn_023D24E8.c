#include "block.h"

/* 0x023D24E8 .. 0x023D24F0, 2 instructions, 8 bytes.
   Stores +0x25C. */

typedef struct { u8 pad0[0x25C]; s32 field_25C; } Obj;
void func_023D24E8(Obj *self, s32 value) { self->field_25C = value; }
