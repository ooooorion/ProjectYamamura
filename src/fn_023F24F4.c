#include "block.h"

/* 0x023F24F4 .. 0x023F2584, 37 instructions, 148 bytes.
   Runs one of two failure paths through the queued event helper. */

typedef struct { u8 pad0[0x5FC]; s32 field_5FC; u8 pad600[0x90]; s32 field_690; } Obj;
extern s32 func_023F2438(void);
extern s32 func_023F2494(Obj *self);
extern void func_023FE6E4(void *self, s32 code);
extern s32 func_0241D3BC(s32 value);
s32 func_023F24F4(Obj *self) {
    s32 result;
    result = 0;
    if (func_023F2438() != 0 || func_023F2494(self) != 0) {
        func_023FE6E4((u8 *)self + 0x1DC, 0x5C);
        result = 1;
    } else if (self->field_690 == 0 && func_0241D3BC(self->field_5FC) >= 0) {
        func_023FE6E4((u8 *)self + 0x1DC, 0x5D);
        result = 1;
    }
    return result;
}
