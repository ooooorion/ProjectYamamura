#include "block.h"

/* 0x02025E2C .. 0x02025E48, 8 instructions, 32 bytes.
   A count and a record pointer at +0xA8/+0xAC. Out-of-range indices fall back
   to entry zero instead of failing, hence the branch around the offset add. */

typedef struct {
    u8 pad0[168];
    u32 count_168;
    u32 *items_172;
} Obj;

u32 func_02025E2C(Obj *self, u32 index) {
    u32 *item = self->items_172;
    if (index < self->count_168) item = item + index * 2;
    return item[0];
}
