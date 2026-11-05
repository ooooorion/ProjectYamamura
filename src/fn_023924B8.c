#include "block.h"

/* 0x023924B8 .. 0x023924C0, 3 instructions, 12 bytes.
   Clears the word at +0x10. */

typedef struct { u8 pad0[0x10]; s32 field_10; } Obj;
void func_023924B8(Obj *self) { self->field_10 = 0; }
