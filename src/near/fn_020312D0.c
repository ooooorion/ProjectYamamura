/* Near miss: 020312D0 is not byte-identical; kept for reference. */
#include "block.h"

typedef struct {
    u8 pad0[68];
    u32 count;
    u8 pad_48[4];
    s32 *items;
    u8 pad_50[0x24];
    s32 index_74;
} Obj;

s32 func_020312D0(Obj *self) {
    s32 index;
    u32 count;
    s32 result;
    index = self->index_74;
    count = self->count;
    result = 0;
    if (index < 0) return 0;
    if ((u32)index < count) result = self->items[index];
    return result;
}
