#include "block.h"

/* 0x0239E42C .. 0x0239E44C, 9 instructions, 36 bytes.
   Returns the helper result minus 0x7C. */

extern s32 func_0239E3C0(void);
s32 func_0239E42C(void) { return func_0239E3C0() - 0x7C; }
