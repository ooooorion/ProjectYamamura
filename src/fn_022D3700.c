#include "block.h"

/* 0x022D3700 .. 0x022D3724, 10 instructions, 40 bytes.
   Selects a float from bit 18 of +0x400. */

typedef struct { u8 pad0[0x400]; u32 field_400; } Obj;
f32 func_022D3700(Obj **self) {
    if (((*self)->field_400 >> 18) & 1) return *(f32 *)0x1005A1D8;
    return *(f32 *)0x1005A0D4;
}
