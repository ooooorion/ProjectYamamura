#include "block.h"

/* 0x021AB5A8 .. 0x021AB5E8, 17 instructions, 68 bytes.
   Runs one no-argument setup routine, then forwards this object through three
   teardown helpers. */

extern void func_0212F7B8(void);
extern void func_0212F7E0(s32 arg0);
extern void func_0212D5AC(s32 arg0);
extern void func_0212D5D4(s32 arg0);

void func_021AB5A8(s32 arg0) {
    func_0212F7B8();
    func_0212F7E0(arg0);
    func_0212D5AC(arg0);
    func_0212D5D4(arg0);
}
