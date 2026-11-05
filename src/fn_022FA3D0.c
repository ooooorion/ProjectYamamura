#include "block.h"

/* 0x022FA3D0 .. 0x022FA3D4, 2 instructions, 8 bytes.
   Returns the byte at +0x64. */

typedef struct { u8 pad0[0x64]; u8 field_64; } Obj;
u8 func_022FA3D0(Obj *self) { return self->field_64; }
