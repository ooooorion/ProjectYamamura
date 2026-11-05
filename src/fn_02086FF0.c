#include "block.h"

/* 0x02086FF0 .. 0x02086FF4, 2 instructions, 8 bytes.
   Constant accessor returning 1 MiB. */

s32 func_02086FF0(void) {
    return 0x100000;
}
