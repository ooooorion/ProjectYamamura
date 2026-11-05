#include "block.h"

/* 0x02080D78 .. 0x02080D7C, 2 instructions, 8 bytes.
   Adjustor thunk returning its argument plus 0x14; 0x02080D80 is identical. */

s32 func_02080D78(s32 value) {
    return value + 0x14;
}
