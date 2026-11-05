#include "block.h"

/* 0x02519564 .. 0x0251959C, 15 instructions, 60 bytes. */

typedef struct { u8 pad0[0x15650]; s32 field_15650; s32 field_15654; } Obj;
extern s32 func_025151F0(void);
void func_02519564(Obj *self) {
    s32 value;

    value = func_025151F0();
    self->field_15654 = value;
    self->field_15650 = value + 0xE8;
}
