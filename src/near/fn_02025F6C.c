#include "block.h"

/* 0x02025F6C .. 0x02025F7C, 5 instructions, 20 bytes.
   not + addic + subfe is GHS's comparison normalisation. Writing the
   predicate as ~field != 0 reproduces the target's operand order; the
   alternative spelling field != 0xFFFFFFFF loads into r12 instead of r0. */

typedef struct {
    u8 pad0[308];
    u32 field_308;
} Obj;

u32 func_02025F6C(Obj *self) {
    return ~self->field_308 != 0;
}
