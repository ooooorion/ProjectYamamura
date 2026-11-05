#include "block.h"

/* 0x023D24F8 .. 0x023D2504, 4 instructions, 16 bytes.
   Stores a signed byte and sets the adjacent dirty flag. */

typedef struct { u8 pad0[0x268]; s8 field_268; u8 field_269; s8 field_26A; } Obj;
void func_023D24F8(Obj *self, s8 value) { self->field_268 = value; self->field_26A = 1; }
