#include "block.h"

/* 0x023F033C .. 0x023F0384, 19 instructions, 76 bytes.
   Runs the shared setup and four per-object updates. */

extern void func_023EFE0C(void);
extern void func_023F00A8(s32 arg0);
extern void func_023F0168(s32 arg0);
extern void func_023F01FC(s32 arg0);
extern void func_023F02BC(s32 arg0);
void func_023F033C(s32 arg0) {
    func_023EFE0C();
    func_023F00A8(arg0);
    func_023F0168(arg0);
    func_023F01FC(arg0);
    func_023F02BC(arg0);
}
