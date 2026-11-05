#include "block.h"

/* 0x02029ADC .. 0x02029B00, 10 instructions, 40 bytes.
   A branchy disjunction with an explicit 1/0 materialisation and a closing
   clrlwi: the return type is u8, not _Bool (no addic/subfe here). The first
   branch keeps the default 1 when field_376 is zero, so the predicate is
   field == 0 || flag != 0, not a conjunction. */

typedef struct {
    u8 pad0[376];
    u32 field_376;
    u8 pad_380[66];
    u8 flag_446;
} Obj;

u8 func_02029ADC(Obj *self) {
    return self->field_376 == 0 || self->flag_446 != 0;
}
