#include "block.h"

/* 0x02310AD8 .. 0x02310B40, 27 instructions, 108 bytes.
   Tests two objects and dispatches the matching branch. */

extern s32 func_02310A08(void);
extern s32 func_020A2CAC(void *left, void *right);
extern s32 func_02310A60(s32 arg0, s32 arg1);
s32 func_02310AD8(s32 arg0) {
    if (func_02310A08() != 0 && func_020A2CAC((void *)(arg0 + 0x4E8), (void *)(arg0 + 0xB8)) != 0)
        return func_02310A60(arg0, 0);
    return 0;
}
