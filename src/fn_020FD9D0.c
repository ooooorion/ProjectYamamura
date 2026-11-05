#include "block.h"

/* 0x020FD9D0 .. 0x020FD9F0, 9 instructions, 36 bytes.
   Copies four floats at +0x00..+0x0C in the target's load/store order. */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

void func_020FD9D0(Vec4 *dst, Vec4 *src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->w = src->w;
}
