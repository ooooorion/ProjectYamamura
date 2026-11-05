#include "block.h"

/* 0x023B9770 .. 0x023B97A8, 15 instructions, 60 bytes.
   Releases the +0x27C value and the +0x1DC helper. */

extern void func_023B220C(s32 value);
extern void func_023AFD9C(void *self, s32 arg1);
void func_023B9770(void *self) {
    func_023B220C(*(s32 *)((u8 *)self + 0x27C));
    func_023AFD9C((u8 *)self + 0x1DC, 0);
}
