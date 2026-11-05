#include "block.h"

/* 0x023EFCEC .. 0x023EFCF4, 3 instructions, 12 bytes.
   Sets byte +0x6E8. */

typedef struct { u8 pad0[0x6E8]; s8 field_6E8; } Obj;
void func_023EFCEC(Obj *self) { self->field_6E8 = 1; }
