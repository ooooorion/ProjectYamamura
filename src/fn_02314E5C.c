#include "block.h"

/* 0x02314E5C .. 0x02314ED4, 31 instructions, 124 bytes.
   Sets +0x4B4 on the state-2 object selected by the global helper. */

extern void *func_0230E174(void);
extern s32 func_023073E0(void *object);
s32 func_02314E5C(void *self) {
    void *object;
    if (*(s32 *)((u8 *)self + 0x368) == 2 && ((*(u32 *)((u8 *)self + 0x178C) >> 8) & 1)) {
        object = func_0230E174();
        if (object != 0 && func_023073E0(object) != 0) {
            *(s32 *)((u8 *)object + 0x4B4) = 0x14;
            return 1;
        }
    }
    return 0;
}
