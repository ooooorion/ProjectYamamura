#include "block.h"

/* 0x023EFCF8 .. 0x023EFD04, 3 instructions, 12 bytes.
   Copies a word into +0x6EC. */

typedef struct { u8 pad0[0x6EC]; s32 value; } Obj;
void func_023EFCF8(Obj *self, s32 *src) { self->value = *src; }
