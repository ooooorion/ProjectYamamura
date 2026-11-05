#include "block.h"

/* 0x0208F98C .. 0x0208F994, 3 instructions, 12 bytes.
   Two-level getter: the child pointer at +0x18, then its word at +0x0C. */

typedef struct {
    u8 pad0[0x18];
    void *child_18;
} Obj;

typedef struct {
    u8 pad0[0xC];
    s32 value_0C;
} Child;

s32 func_0208F98C(Obj *self) {
    return ((Child *)self->child_18)->value_0C;
}
