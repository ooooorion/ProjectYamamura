#include "block.h"

/* 0x0232AEB0 .. 0x0232AED0, 9 instructions, 36 bytes.
   Selects one of two floats for state 1. */

typedef struct { u8 pad0[0x944]; s32 field_944; } Obj;
f32 func_0232AEB0(Obj *self) {
    if (self->field_944 == 1) return *(f32 *)0x10064E78;
    return *(f32 *)0x10064E7C;
}
