#include "block.h"

/* 0x024C8C08 .. 0x024C8C68, 25 instructions, 100 bytes.
   True when either shared predicate accepts +0x68. */

typedef struct { u8 pad0[0x68]; s32 field_68; } Obj;
extern s32 func_02022860(s32 value);
extern s32 func_02022874(s32 value);
s32 func_024C8C08(Obj *self) {
    if (func_02022860(self->field_68) != 0 ||
        func_02022874(self->field_68) != 0) {
        return 1;
    }
    return 0;
}
