#include "block.h"

/* 0x021C6F24 .. 0x021C6F28, 2 instructions, 8 bytes.
   Returns the signed word at +0x4EC. */

typedef struct { u8 pad0[0x4EC]; s32 field_4EC; } Obj;
s32 func_021C6F24(Obj *self) { return self->field_4EC; }
