#include "block.h"

/* 0x023F6874 .. 0x023F68C0, 20 instructions, 80 bytes.
   Runs the conditional lookup and follow-up update. */

extern s32 func_023EED54(void);
extern void func_023F49F8(s32 arg0, s32 *value, s32 arg2);
extern void func_023F1624(s32 arg0);
void func_023F6874(s32 arg0) {
    s32 value;
    if (func_023EED54() != 0) {
        value = 0;
        func_023F49F8(arg0, &value, 0);
        func_023F1624(arg0);
    }
}
