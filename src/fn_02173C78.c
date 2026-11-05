#include "block.h"

/* 0x02173C78 .. 0x02173C80, 3 instructions, 12 bytes.
   Sets the signed byte at +0x1F to 1; the target uses stb, not stw. */

typedef struct {
    u8 pad0[0x1F];
    s8 field_1F;
} Obj;

void func_02173C78(Obj *self) {
    self->field_1F = 1;
}
