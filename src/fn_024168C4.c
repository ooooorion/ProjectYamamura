#include "block.h"

/* 0x024168C4 .. 0x024168D4, 5 instructions, 20 bytes.
   True unless +0x1E8 is 3. */

typedef struct { u8 pad0[0x1E8]; s32 field_1E8; } Obj;
s32 func_024168C4(Obj *self) {
    return self->field_1E8 != 3;
}
