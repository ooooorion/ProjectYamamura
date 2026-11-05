#include "block.h"

/* 0x024D4254 .. 0x024D4288, 14 instructions, 56 bytes.
   Runs the shared update and posts event 8 at +0x16C. */

extern void func_024D41C8(void);
extern void func_024D9FF8(void *self, s32 arg1);
void func_024D4254(void *self) {
    func_024D41C8();
    func_024D9FF8((u8 *)self + 0x16C, 8);
}
