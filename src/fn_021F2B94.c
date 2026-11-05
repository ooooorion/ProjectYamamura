#include "block.h"

/* 0x021F2B94 .. 0x021F2C44, 45 instructions, 180 bytes.
   Maps the object's mode and the requested value to one of four state codes;
   unmatched combinations return zero. */

typedef struct {
    u8 pad0[8];
    s32 field_8;
} Obj;

extern u32 func_021260E0(s32 value);

s32 func_021F2B94(Obj *self, u32 arg1) {
    s32 result;
    u32 mode;

    result = 0;
    mode = func_021260E0(self->field_8);
    switch (mode) {
    case 2:
        switch (arg1) {
        case 1:
        case 3:
            result = 0xB8;
            break;
        case 5:
        case 7:
            result = 0xB9;
            break;
        }
        break;
    case 3:
        switch (arg1) {
        case 3:
        case 7:
            result = 0xBA;
            break;
        case 1:
        case 5:
            result = 0xBB;
            break;
        }
        break;
    }
    return result;
}
