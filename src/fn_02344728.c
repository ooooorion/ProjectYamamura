#include "block.h"

/* 0x02344728 .. 0x02344780, 23 instructions, 92 bytes.
   Runs the release helper on two adjacent subobjects. */

extern void func_02757D68(s32 arg0);
extern void func_02344640(void *self, void *left, void *right);
void func_02344728(void *self) {
    func_02757D68(*(s32 *)((u8 *)self + 0x44));
    func_02344640(self, (u8 *)self + 0x2C, (u8 *)self + 0x3C);
    if (*(s32 *)((u8 *)self + 0x3C) == 0) func_02344640(self, (u8 *)self + 0x18, (u8 *)self + 0x28);
}
