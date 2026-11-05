#include "block.h"

/* 0x0250BE2C .. 0x0250BE70, 18 instructions, 72 bytes.
   Updates the nested object and dispatches its +0x8C method. */

typedef struct { u8 pad0[0x7C]; void **field_7C; } Obj;
typedef void (*InnerMethod)(void **);
extern void func_02464770(void **self, s32 value);
void func_0250BE2C(Obj *self, s32 *arg1) {
    void **object;

    func_02464770(self->field_7C, *arg1);
    object = self->field_7C;
    (*(InnerMethod *)((u8 *)*object + 0x8C))(object);
}
