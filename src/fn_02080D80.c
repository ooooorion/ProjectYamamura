#include "block.h"

/* 0x02080D80 .. 0x02080D84, 2 instructions, 8 bytes.
   Adjustor thunk returning its argument plus 0x14; see 0x02080D78. */

s32 func_02080D80(s32 value) {
    return value + 0x14;
}
