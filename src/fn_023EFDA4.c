#include "block.h"

/* 0x023EFDA4 .. 0x023EFE08, 26 instructions, 104 bytes.
   Checks the virtual readiness test and its companion flag. */

typedef struct Obj Obj;
typedef s32 (*ObjMethod)(void *);
struct Obj { u8 pad0[0x5E0]; void **object; };
extern s32 func_02022860(void *object);
s32 func_023EFDA4(Obj *self) {
    s32 result;
    result = 1;
    if ((*(ObjMethod *)((u8 *)*self->object + 0x7C))(self->object) == 0 && func_02022860(self->object) == 0) result = 0;
    return result;
}
