#include "block.h"

/* 0x021FCEF8 .. 0x021FCF04, 4 instructions, 16 bytes.
   Clears the two leading bytes. */

typedef struct { s8 field_0; s8 field_1; } Obj;
void func_021FCEF8(Obj *self) { self->field_0 = 0; self->field_1 = 0; }
