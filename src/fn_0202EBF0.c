#include "block.h"

/* 0x0202EBF0 .. 0x0202EC00, 5 instructions, 20 bytes.
   Equality against 1 at +0x178. */

typedef struct {
    u8 pad0[376];
    u32 field_376;
} Obj;

u32 func_0202EBF0(Obj *self) {
    return self->field_376 == 1;
}
