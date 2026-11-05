#include "block.h"

/* 0x0245F600 .. 0x0245F670, 29 instructions, 116 bytes.
   Checks the inner resource and dispatches vtable slot at +0x8C. */

typedef struct { void *vtable; u8 pad4[0xE4]; void *field_E8; } Inner;
typedef struct { u8 pad0[0x1C]; s32 field_1C; } Resource;
typedef struct { u8 pad0[0x284]; Inner *field_284; } Obj;
typedef s32 (*InnerMethod)(void *);
extern s32 func_0276003C(s32 value);
s32 func_0245F600(Obj *self) {
    Inner *inner;
    inner = self->field_284;
    if (inner != 0 && func_0276003C(((Resource *)inner->field_E8)->field_1C) != 0) {
        inner = self->field_284;
        return (*(InnerMethod *)((u8 *)inner->vtable + 0x8C))(inner);
    }
    return 0;
}
