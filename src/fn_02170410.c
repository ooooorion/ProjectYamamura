#include "block.h"

/* 0x02170410 .. 0x02170430, 9 instructions, 36 bytes.
   The reverse of 0x021703EC: writes src[0..2] to dst[index],
   dst[index + 4] and dst[index + 8]. The first store is indexed; the
   other two reuse the base pointer formed from dst + index. */

void func_02170410(f32 *dst, f32 *src, s32 index) {
    f32 *base;

    dst[index] = src[0];
    base = dst + index;
    base[4] = src[1];
    base[8] = src[2];
}
