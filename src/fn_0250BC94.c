#include "block.h"

/* 0x0250BC94 .. 0x0250BCBC, 11 instructions, 44 bytes.
   True when the shared predicate rejects +0xA4. */

typedef struct { u8 pad0[0xA4]; s32 field_A4; } Obj;
extern s32 func_02469714(s32 value);
s32 func_0250BC94(Obj *self) {
    return func_02469714(self->field_A4) == 0;
}
