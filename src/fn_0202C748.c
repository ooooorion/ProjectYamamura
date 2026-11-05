#include "block.h"

/* 0x0202C748 .. 0x0202C754, 4 instructions, 16 bytes.
   Null test on the word at +0x178. */

typedef struct {
    u8 pad0[376];
    u32 field_376;
} Obj;

u32 func_0202C748(Obj *self) {
    return self->field_376 == 0;
}
