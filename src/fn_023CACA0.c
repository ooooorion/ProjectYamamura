#include "block.h"

/* 0x023CACA0 .. 0x023CACE8, 19 instructions, 76 bytes.
   Runs the shared setup then four per-object routines. */

extern void func_023CA508(void);
extern void func_023CA900(s32 arg0);
extern void func_023CA9A0(s32 arg0);
extern void func_023CAAD0(s32 arg0);
extern void func_023CAC00(s32 arg0);
void func_023CACA0(s32 arg0) {
    func_023CA508();
    func_023CA900(arg0);
    func_023CA9A0(arg0);
    func_023CAAD0(arg0);
    func_023CAC00(arg0);
}
