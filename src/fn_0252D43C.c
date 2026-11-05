#include "block.h"

/* 0x0252D43C .. 0x0252D440, 2 instructions, 8 bytes. */

typedef struct { u8 pad0[0x94]; s32 field_94; } Obj;
void func_0252D43C(Obj *self, s32 value) { self->field_94 = value; }
