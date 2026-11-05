#include "block.h"

/* 0x0211D950 .. 0x0211D954, 2 instructions, 8 bytes.
   Returns the word at +0x2F4; three adjacent accessors share this load. */

typedef struct {
    u8 pad0[0x2F4];
    s32 field_2F4;
} Obj;

s32 func_0211D950(Obj *self) {
    return self->field_2F4;
}
