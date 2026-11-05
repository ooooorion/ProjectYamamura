#include "block.h"

/* 0x023EED54 .. 0x023EED78, 10 instructions, 40 bytes.
   Returns the flag of the second array element when it exists. */

typedef struct { u8 pad0[0x39C]; u32 count; u8 pad3A0[4]; void **array; } Obj;
s32 func_023EED54(Obj *self) {
    void *item;
    item = 0;
    if (self->count > 1U) item = (*(void ***)((u8 *)self + 0x3A4))[1];
    return *(s32 *)((u8 *)item + 0x1B4) != 0;
}
