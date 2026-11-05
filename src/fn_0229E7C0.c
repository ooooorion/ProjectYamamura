#include "block.h"

/* 0x0229E7C0 .. 0x0229E838, 31 instructions, 124 bytes.
   Checks a global +0x18 object and compares +0x46C. */

#include <stddef.h>

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern void *func_02296B28(void);

s32 func_0229E7C0(void) {
    void *temp_r11;
    void *temp_r11_2;
    void *temp_r3;

    temp_r3 = func_02296B28();
    if (temp_r3 != NULL) {
        temp_r11 = M2C_FIELD(temp_r3, void **, 0x348);
        if ((temp_r11 != NULL) && ((s32) M2C_FIELD(temp_r11, s32 *, 0xC) == 1)) {
            temp_r11_2 = M2C_FIELD(*(void **)0x10188308, void **, 0x18);
            if ((temp_r11_2 != NULL) && ((u32) M2C_FIELD(temp_r11_2, u32 *, 0x46C) != (u32) M2C_FIELD(temp_r3, u32 *, 0xF4))) {
                return 1;
            }
        }
    }
    return 0;
}
