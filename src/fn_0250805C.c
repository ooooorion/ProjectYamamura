#include "block.h"

/* 0x0250805C .. 0x02508068, 4 instructions, 16 bytes.
   Marks the nested object ready. */

typedef struct { u8 pad0[0x9C]; void *field_9C; } Obj;
void func_0250805C(Obj *self) {
    *(s8 *)((u8 *)self->field_9C + 0x244) = 1;
}
