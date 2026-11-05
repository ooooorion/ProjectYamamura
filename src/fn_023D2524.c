#include "block.h"

/* 0x023D2524 .. 0x023D2534, 5 instructions, 20 bytes.
   Copies the integer pair at +0x254. */

typedef struct { u8 pad0[0x254]; s32 x; s32 y; } Obj;
typedef struct { s32 x; s32 y; } Pair;
void func_023D2524(Obj *self, Pair *out) { out->x = self->x; out->y = self->y; }
