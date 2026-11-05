#include "block.h"

/* 0x023153A8 .. 0x023153AC, 2 instructions, 8 bytes.
   Loads the word at +0xD6C. */

typedef struct { u8 pad0[0xD6C]; s32 field_D6C; } Obj;
s32 func_023153A8(Obj *self) { return self->field_D6C; }
