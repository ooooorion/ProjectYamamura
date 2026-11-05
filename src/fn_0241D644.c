#include "block.h"

/* 0x0241D644 .. 0x0241D69C, 23 instructions, 92 bytes.
   Stores a probe result and dispatches the transition when it is valid. */

typedef struct { u8 pad0[0x2C68]; u8 field_2C68; u8 pad2C69[0xB]; s32 field_2C74; } Obj;
extern s32 func_0241D3BC(Obj *self);
extern void func_0241D43C(Obj *self);
extern void func_0241EFD8(void *self, s32 arg1);
void func_0241D644(Obj *self) {
    s32 result;
    if (self->field_2C68 == 0) {
        result = func_0241D3BC(self);
        self->field_2C74 = result;
        if (result != -1) {
            func_0241D43C(self);
            func_0241EFD8((u8 *)self + 0x1DC, 2);
        }
    }
}
