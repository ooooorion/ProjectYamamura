#ifndef BLOCK_H
#define BLOCK_H

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     s32;
typedef float          f32;

/* Scalar names m2c emits. These match the GHS block in Cafe SDK 2.12.13
   system/include/types.h; kept here so a generated candidate can include
   block.h without repeating a typedef block. */
typedef signed char        s8;
typedef signed short       s16;
typedef signed long long   s64;
typedef unsigned long long u64;
typedef double             f64;

/* GHS spells 1-byte booleans _Bool; the target returns them zero-extended
   with clrlwi r3,rX,24. */
typedef _Bool b8;

#endif
