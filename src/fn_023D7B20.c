#include "block.h"

/* 0x023D7B20 .. 0x023D7B2C, 3 instructions, 12 bytes.
   Sets byte +0x278. */

typedef struct { u8 pad0[0x278]; s8 field_278; } Obj;
void func_023D7B20(Obj *self) { self->field_278 = 1; }
