#include "block.h"

/* 0x022D2FAC .. 0x022D2FB8, 4 instructions, 16 bytes.
   Copies +0xF0 into +0xEC on the pointed-to object. */

typedef struct { u8 pad0[0xEC]; s32 field_EC; s32 field_F0; } Obj;
void func_022D2FAC(Obj **self) {
    Obj *object = *self;
    object->field_EC = object->field_F0;
}
