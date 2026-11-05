#include "block.h"

/* 0x0239E2D8 .. 0x0239E31C, 18 instructions, 72 bytes.
   Runs the cleanup path when +0x55 is set. */

extern void func_0276912C(void *self, s32 arg1);
extern void func_0205B1E8(void *self);
void func_0239E2D8(void *self) {
    if (*(u8 *)((u8 *)self + 0x55) != 0) {
        func_0276912C(self, *(s32 *)((u8 *)self + 0x14));
        func_0205B1E8(self);
    }
}
