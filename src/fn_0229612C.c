#include "block.h"

/* 0x0229612C .. 0x02296158, 12 instructions, 48 bytes.
   Normalizes a wrapped 0..5 result. */

extern s32 func_022960EC(s32 value);
s32 func_0229612C(s32 arg0, s32 arg1) {
    s32 result = func_022960EC(arg0 - arg1);
    if (result >= 3) result -= 6;
    return result;
}
