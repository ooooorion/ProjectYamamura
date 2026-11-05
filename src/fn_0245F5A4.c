#include "block.h"

/* 0x0245F5A4 .. 0x0245F5FC, 23 instructions, 92 bytes.
   Runs the inner cleanup and clears the active marker. */

typedef struct { u8 pad0[0x280]; void **field_280; u8 pad284[0xCD]; u8 field_351; } Obj;
typedef void (*InnerMethod)(void **);
extern void func_0281A640(void *self, s32 value);
void func_0245F5A4(Obj *self) {
    void **object;
    if (self->field_351 != 0) {
        object = self->field_280;
        (*(InnerMethod *)((u8 *)*object + 0x9C))(object);
        func_0281A640((u8 *)self + 0x200, -1);
        self->field_351 = 0;
    }
}
