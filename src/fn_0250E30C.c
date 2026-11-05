#include "block.h"

/* 0x0250E30C .. 0x0250E364, 23 instructions, 92 bytes.
   Forwards the +0xA8 object, then dispatches its +0x8C method. */

typedef struct { u8 pad0[0xA8]; void **field_A8; } Obj;
extern s32 func_024750EC(void **object);
extern s32 func_024750F4(void **object, s32 arg);
void func_0250E30C(Obj *self, s32 arg1, s32 arg2) {
    void **object;

    func_024750EC(self->field_A8);
    func_024750F4(self->field_A8, arg2);
    object = self->field_A8;
    (*(void (**)(void **))((u8 *)*object + 0x8C))(object);
}
