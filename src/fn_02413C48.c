#include "block.h"

/* 0x02413C48 .. 0x02413C5C, 6 instructions, 24 bytes.
   Clears the byte at +0x100 in two stored objects. */

typedef struct { u8 pad0[0x27C]; void *field_27C; void *field_280; } Obj;
void func_02413C48(Obj *self) {
    *(u8 *)((u8 *)self->field_27C + 0x100) = 0;
    *(u8 *)((u8 *)self->field_280 + 0x100) = 0;
}
