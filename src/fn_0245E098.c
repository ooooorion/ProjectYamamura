#include "block.h"

/* 0x0245E098 .. 0x0245E0A0, 3 instructions, 12 bytes.
   Sets byte +0x352. */

typedef struct { u8 pad0[0x352]; s8 field_352; } Obj;
void func_0245E098(Obj *self) { self->field_352 = 1; }
