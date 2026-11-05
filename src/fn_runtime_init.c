#include "block.h"

/* 0x02711500 .. 0x0271154C, 20 instructions, 80 bytes.
   Saves the loader's two arguments, runs the constructor table, publishes
   both arguments, then calls main and returns zero. */

extern void __init(void);
extern void main(void);
extern u32 runtime_arg0;
extern u32 runtime_arg1;

s32 runtime_init(s32 arg0, s32 arg1) {
    __init();
    runtime_arg0 = arg0;
    runtime_arg1 = arg1;
    main();
    return 0;
}
