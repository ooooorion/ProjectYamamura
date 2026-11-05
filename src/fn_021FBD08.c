#include "block.h"

/* 0x021FBD08 .. 0x021FBD1C, 6 instructions, 24 bytes.
   Copies a nullable source pointer and stores a float. */

typedef struct { void *field_0; f32 field_4; } Obj;
void func_021FBD08(Obj *self, void *source, f32 value) {
    void *object = source;
    if (object != 0) object = *(void **)((u8 *)object + 0x14);
    self->field_0 = object;
    self->field_4 = value;
}
