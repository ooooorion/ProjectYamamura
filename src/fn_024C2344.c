#include "block.h"

/* 0x024C2344 .. 0x024C234C, 3 instructions, 12 bytes.
   Sets byte +0xB8. */

typedef struct { u8 pad0[0xB8]; s8 field_B8; } Obj;
void func_024C2344(Obj *self) { self->field_B8 = 1; }
