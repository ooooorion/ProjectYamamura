#include "block.h"

/* 0x0226C8CC .. 0x0226C924, 23 instructions, 92 bytes.
   Releases two adjacent fields, forwards the pair through one helper, runs
   the global update, then closes the nested +0x674 object. */

extern void func_0208EE54(s32 value);
extern void func_0226C788(s32 arg0, s32 arg1);
extern void func_0226C7F0(void);
extern void func_0226F49C(s32 address);

void func_0226C8CC(s32 arg0, s32 arg1) {
    func_0208EE54(arg0 + 0x6C4);
    func_0208EE54(arg0 + 0x6C8);
    func_0226C788(arg0, arg1);
    func_0226C7F0();
    func_0226F49C(arg0 + 0x674);
}
