#include "block.h"

/* 0x02023DD8 .. 0x02023DF8, 9 instructions, 36 bytes.
   Two two-float vectors into +0x88 and +0x90. The interleaved lfs/stfs pairs
   are what the target does; no branch or call. */

typedef struct {
    u8 pad0[136];
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Dst;

void func_02023DD8(Dst *self, f32 *a, f32 *b) {
    self->x = a[0];
    self->y = a[1];
    self->z = b[0];
    self->w = b[1];
}
