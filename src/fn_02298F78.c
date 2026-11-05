#include "block.h"

/* 0x02298F78 .. 0x02298FD0, 23 instructions, 92 bytes.
   Runs two callbacks when the source has a +0x348 object. */

extern void func_02298E70(s32 arg0);
extern void func_02298578(s32 arg0, void *arg1, s32 arg2);
void func_02298F78(s32 arg0, void *arg1) {
    if (arg1 != 0 && *(s32 *)((u8 *)arg1 + 0x348) != 0) {
        func_02298E70(arg0);
        func_02298578(arg0, arg1, 0);
    }
}
