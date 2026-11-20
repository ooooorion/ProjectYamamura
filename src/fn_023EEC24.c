#include "block.h"

/* 0x023EEC24 .. 0x023EEC2C, 2 instructions, 8 bytes.
   Returns byte +0x69B. */

typedef struct { u8 pad0[0x69B]; u8 field_69B; } Obj;
u8 func_023EEC24(Obj *self) { return self->field_69B; }
