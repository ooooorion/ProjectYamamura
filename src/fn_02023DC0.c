#include "block.h"

/* 0x02023DC0 .. 0x02023DD4, 6 instructions, 24 bytes.
   fcmpu, then mfcr + rlwinm r3,r0,2,31,31. Calibration against known
   expressions on this compiler shows SH=2 is GT and SH=3 is EQ, so this is
   "greater than", not equality -- the mask decides, not intuition. Both u8
   and b8 return types reproduce the target exactly. */

typedef struct {
    u8 pad0[252];
    f32 value_252;
    f32 value_256;
    f32 value_260;
} Obj;

b8 func_02023DC0(Obj *self) {
    return self->value_252 > self->value_260;
}
