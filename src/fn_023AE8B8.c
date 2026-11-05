#include "block.h"

/* 0x023AE8B8 .. 0x023AE8F8, 17 instructions, 68 bytes.
   Releases the +0x254/+0x258 objects and the +0x1DC helper. */

extern void func_023A5734(s32 value);
extern void func_023B9770(s32 value);
extern void func_023AFA50(void *self, s32 arg1);
void func_023AE8B8(void *self) {
    func_023A5734(*(s32 *)((u8 *)self + 0x254));
    func_023B9770(*(s32 *)((u8 *)self + 0x258));
    func_023AFA50((u8 *)self + 0x1DC, 0);
}
