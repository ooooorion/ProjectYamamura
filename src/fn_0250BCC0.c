#include "block.h"

/* 0x0250BCC0 .. 0x0250BCEC, 12 instructions, 48 bytes.
   True when the shared predicate returns one. */

typedef struct { u8 pad0[0xA4]; s32 field_A4; } Obj;
extern s32 func_02469714(s32 value);
s32 func_0250BCC0(Obj *self) {
    return (func_02469714(self->field_A4) ^ 1) == 0;
}
