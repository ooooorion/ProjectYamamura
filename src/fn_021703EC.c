#include "block.h"

/* 0x021703EC .. 0x0217040C, 9 instructions, 36 bytes.
   Copies three floats from src[index], src[index + 4] and src[index + 8]
   into dst[0..2]. The first load is indexed; the other two reuse the base
   pointer formed from src + index. */

void func_021703EC(f32 *dst, f32 *src, s32 index) {
    f32 *base;

    dst[0] = src[index];
    base = src + index;
    dst[1] = base[4];
    dst[2] = base[8];
}
