#include "block.h"

/* 0x02162088 .. 0x021620B8, 13 instructions, 52 bytes.
   Runs the no-argument setup routine, then forwards this object to the second
   helper. */

typedef struct Obj Obj;

extern void func_02161EFC(void);
extern void func_02132BE4(Obj *self);

void func_02162088(Obj *self) {
    func_02161EFC();
    func_02132BE4(self);
}
