#include "block.h"

/* 0x02314DE8 .. 0x02314E44, 24 instructions, 96 bytes.
   Returns true when either guard is set. */

extern s32 func_02314B8C(void);
extern s32 func_02314C84(s32 arg0);
s32 func_02314DE8(s32 arg0) {
    if (func_02314B8C() != 0 || func_02314C84(arg0) != 0) return 1;
    return 0;
}
