#include "block.h"

/* 0x020250EC .. 0x02025118, 12 instructions, 48 bytes.
   The object is the second argument; r3 is unused. It resolves a pointer
   through +0xE8 and +0x1C, bails silently when that is null, sets bit 1 in
   the +0x44 flags, and writes 255 or the caller's value to +0x45. */

typedef struct {
    u8 pad0[68];
    u8 flags_68;
    u8 field_69;
} Inner;

typedef struct {
    u8 pad0[28];
    Inner *inner_28;
} Mid;

typedef struct {
    u8 pad0[232];
    Mid *mid_232;
} Obj;

void func_020250EC(void *unused, Obj *obj, u32 value) {
    Inner *inner = obj->mid_232->inner_28;
    if (inner == 0) return;
    inner->flags_68 |= 2;
    if (value != 0) value = 255;
    inner->field_69 = value;
}
