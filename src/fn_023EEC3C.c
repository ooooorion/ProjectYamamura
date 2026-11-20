#include "block.h"

/* 0x023EEC3C .. 0x023EEC44, 2 instructions, 8 bytes.
   Returns byte +0x6A1. */

typedef struct { u8 pad0[0x6A1]; u8 field_6A1; } Obj;
u8 func_023EEC3C(Obj *self) { return self->field_6A1; }
