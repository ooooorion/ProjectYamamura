#include "block.h"

/* 0x0229E120 .. 0x0229E190, 29 instructions, 116 bytes.
   Dispatches state 3 through the +0x348 child. */

extern void *func_02296B28(void);
extern void func_022A2CF0(void *self, s32 arg1);
s32 func_0229E120(s32 arg0) {
    void *owner = func_02296B28();
    if (owner != 0) {
        void *child = *(void **)((u8 *)owner + 0x348);
        if (child != 0 && *(s32 *)((u8 *)child + 0xC) == 3) {
            func_022A2CF0((void *)(arg0 + 0x10), 7);
            return 1;
        }
    }
    return 0;
}
