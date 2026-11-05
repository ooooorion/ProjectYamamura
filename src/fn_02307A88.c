#include "block.h"

/* 0x02307A88 .. 0x02307B00, 31 instructions, 124 bytes.
   Lazily allocates the +0x1728 object when bit 10 is set. */

extern s32 func_0276FB54(s32 size);
extern s32 func_0209929C(void);
s32 func_02307A88(void *self) {
    s32 result;
    if (*(s32 *)((u8 *)self + 0x1728) == 0 && ((*(u32 *)((u8 *)self + 0x24) >> 10) & 1)) {
        result = func_0276FB54(0x100);
        if (result != 0) result = func_0209929C();
        *(s32 *)((u8 *)self + 0x1728) = result;
        if (result == 0) return 0;
        return 1;
    }
    return 1;
}
