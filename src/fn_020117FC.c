#include "block.h"

/* 0x020117FC .. 0x02011808, 4 instructions, 16 bytes.
   The subtract is folded into addi and the argument is added last, so the
   source order is (field - 29) + value. */

typedef struct {
    u8 pad0[472];
    u32 field_472;
} Obj;

u32 func_020117FC(Obj *self, u32 value) {
    return (self->field_472 - 29) + value;
}
