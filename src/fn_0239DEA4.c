#include "block.h"

/* 0x0239DEA4 .. 0x0239DEE0, 16 instructions, 64 bytes.
   Rejects the inactive global states. */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

s32 func_0239DEA4(void) {
    s32 temp_r0;
    void *temp_r12;

    temp_r12 = M2C_FIELD(*(void **)0x10187184, void **, 0x12068);
    temp_r0 = M2C_FIELD(temp_r12, s32 *, 0);
    if ((temp_r0 == 3) || (temp_r0 == 0) || ((s32) M2C_FIELD(temp_r12, s32 *, 0x10C) == 2)) {
        return 0;
    }
    return 1;
}
