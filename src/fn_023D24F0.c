#include "block.h"

/* 0x023D24F0 .. 0x023D24F4, 2 instructions, 8 bytes.
   Returns byte +0x269. */

typedef struct { u8 pad0[0x269]; u8 field_269; } Obj;
u8 func_023D24F0(Obj *self) { return self->field_269; }
