#include "block.h"

/* 0x023D2510 .. 0x023D2520, 5 instructions, 20 bytes.
   Copies the float pair at +0x24C. */

typedef struct { u8 pad0[0x24C]; f32 x; f32 y; } Obj;
typedef struct { f32 x; f32 y; } Vec2;
void func_023D2510(Obj *self, Vec2 *out) { out->x = self->x; out->y = self->y; }
