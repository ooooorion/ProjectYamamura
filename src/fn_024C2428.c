#include "block.h"

/* 0x024C2428 .. 0x024C245C, 14 instructions, 56 bytes.
   Forwards +0x48 to the shared update and marks the object ready. */

typedef struct { u8 pad0[0x48]; s32 field_48; u8 pad4C[0x71]; s8 field_BD; } Obj;
extern void func_024D3120(s32 value);
void func_024C2428(Obj *self) {
    func_024D3120(self->field_48);
    self->field_BD = 1;
}
