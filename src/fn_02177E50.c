#include "block.h"

/* 0x02177E50 .. 0x02177E60, 5 instructions, 20 bytes.
   Swaps the two words through a register temporary; the target loads the
   second argument first, then the first. */

void func_02177E50(s32 *first, s32 *second) {
    s32 temporary;

    temporary = *first;
    *first = *second;
    *second = temporary;
}
