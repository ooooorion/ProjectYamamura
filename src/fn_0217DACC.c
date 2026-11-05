#include "block.h"

/* 0x0217DACC .. 0x0217DB08, 16 instructions, 64 bytes.
   Releases three consecutive handle fields in ascending order. */

typedef struct {
    u8 pad0[0x4F8];
    s32 field_4F8;
    s32 field_4FC;
    s32 field_500;
} Obj;

extern void func_026C8E48(s32 handle);

void func_0217DACC(Obj *self) {
    func_026C8E48(self->field_4F8);
    func_026C8E48(self->field_4FC);
    func_026C8E48(self->field_500);
}
