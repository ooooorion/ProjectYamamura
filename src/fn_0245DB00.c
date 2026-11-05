#include "block.h"

/* 0x0245DB00 .. 0x0245DB30, 13 instructions, 52 bytes.
   Runs the shared update and selects state 1. */

typedef struct { u8 pad0[0x31C]; s32 field_31C; } Obj;
extern void func_0245ABA8(void);
void func_0245DB00(Obj *self) {
    func_0245ABA8();
    self->field_31C = 1;
}
