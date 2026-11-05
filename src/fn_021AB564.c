#include "block.h"

/* 0x021AB564 .. 0x021AB5A4, 17 instructions, 68 bytes.
   Runs one no-argument setup routine, then forwards this object through three
   teardown helpers. */

extern void func_0212F7B8(void);
extern void func_0211ECD0(s32 arg0);
extern void func_0212D5AC(s32 arg0);
extern void func_0212D5D4(s32 arg0);

void func_021AB564(s32 arg0) {
    func_0212F7B8();
    func_0211ECD0(arg0);
    func_0212D5AC(arg0);
    func_0212D5D4(arg0);
}
