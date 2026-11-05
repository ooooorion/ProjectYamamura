#include "block.h"

/* 0x02086FD0 .. 0x02086FD4, 2 instructions, 8 bytes.
   Constant accessor returning 6 MiB. 0x02086FD8 repeats it, while
   0x02086FE0/E8/F0 return 5, 9 and 1 MiB. */

s32 func_02086FD0(void) {
    return 0x600000;
}
