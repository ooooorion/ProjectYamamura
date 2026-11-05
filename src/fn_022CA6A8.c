#include "block.h"

/* 0x022CA6A8 .. 0x022CA6B0, 3 instructions, 12 bytes.
   Extracts bit 9 from +0x38. */

typedef struct { u8 pad0[0x38]; u32 field_38; } Obj;
s32 func_022CA6A8(Obj *self) { return (self->field_38 >> 9) & 1; }
