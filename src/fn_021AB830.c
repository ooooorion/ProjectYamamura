#include "block.h"

/* 0x021AB830 .. 0x021AB840, 5 instructions, 20 bytes.
   Marks the source and copies +0x14 into +0x4FC. */

typedef struct { u8 pad0[0x4FC]; s32 field_4FC; } Obj;
typedef struct { u8 pad0[0x14]; s32 field_14; u8 pad18[0x40D]; s8 field_425; } Source;
void func_021AB830(Obj *self, Source *source) {
    source->field_425 = 1;
    self->field_4FC = source->field_14;
}
