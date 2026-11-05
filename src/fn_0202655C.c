#include "block.h"

/* 0x0202655C .. 0x0202658C, 13 instructions.
   Six lfs/stfs pairs, source +0x00..+0x14 into destination +0x44..+0x58.
   A straight 24-byte float copy, no branches, no calls. */

typedef struct {
    u8 pad0[0x44];
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    f32 u;
    f32 v;
} Dst;

typedef struct {
    f32 a[6];
} Src;

void func_0202655C(Dst *self, Src *src) {
    self->x = src->a[0];
    self->y = src->a[1];
    self->z = src->a[2];
    self->w = src->a[3];
    self->u = src->a[4];
    self->v = src->a[5];
}
