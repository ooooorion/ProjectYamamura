#include "block.h"

/* 0x024F1F00 .. 0x024F1F08, 2 instructions, 8 bytes.
   Returns byte +0x326. */

typedef struct { u8 pad0[0x326]; u8 field_326; } Obj;
u8 func_024F1F00(Obj *self) { return self->field_326; }
