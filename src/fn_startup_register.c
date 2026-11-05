#include "block.h"

typedef struct {
    u32 field_0;
    u32 field_4;
    void *field_8;
} StartupSlot;

extern StartupSlot startup_table[36];
extern void *startup_link;
extern void (*startup_callback)(void);
extern void func_02BCF5CC(void);
extern void func_02BCF688(StartupSlot *slot);
extern void __ghsLock(void);
extern void __ghsUnlock(void);

s32 startup_register(void *arg) {
    s32 i;
    __ghsLock();
    startup_callback = func_02BCF5CC;
    for (i = 0; i < 36; i++) {
        if (startup_table[i].field_8 == 0) {
            startup_table[i].field_8 = arg;
            func_02BCF688(&startup_table[i]);
            __ghsUnlock();
            return 0;
        }
    }
    __ghsUnlock();
    return -1;
}
