#include "block.h"

/* 0x024F1EF8 .. 0x024F1EFC, 2 instructions, 8 bytes.
   Stores byte +0x326. */

typedef struct { u8 pad0[0x326]; s8 field_326; } Obj;
void func_024F1EF8(Obj *self, s8 value) { self->field_326 = value; }
