#include "block.h"

/* 0x02015FCC .. 0x02015FF0, 10 instructions, 40 bytes.
   Two lbz/cmpwi tests, one hoisted li r12,1, one shared exit. The closing
   clrlwi r3,r12,24 is an 8-bit truncation, not a _Bool normalisation -- a
   _Bool return makes GHS emit addic/subfe instead and grow the function to
   44 bytes. With u8 this compiles byte-identical to the target. */

typedef struct {
    u8 pad0[584];
    u8 flag_584;
    u8 flag_585;
} Obj;

u8 func_02015FCC(Obj *self) {
    return self->flag_584 || self->flag_585;
}
