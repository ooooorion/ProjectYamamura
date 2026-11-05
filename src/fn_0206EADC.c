#include "block.h"

/* 0x0206EADC .. 0x0206EB10, 14 instructions, 56 bytes.
   Indexed lookup from the table at +0xBD4. Index 0 is rejected with 0 and
   indices 1..10 read the table, whose last entry (+0xBFC) is also the
   multiplier used for larger indices. */

typedef struct {
    u8 pad0[0xBD4];
    s32 table_BD4[11];
} Obj;

s32 func_0206EADC(Obj *self, s32 index) {
    if (index == 0) {
        return 0;
    }
    if ((u32)index <= 10) {
        return self->table_BD4[index];
    }
    return (index - 9) * self->table_BD4[10];
}
