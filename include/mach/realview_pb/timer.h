#ifndef __RVPB_TIMER_H__
#define __RVPB_TIMER_H__

#include <stdint.h>

union timerx_control {
    u32 all;
    struct {
        u32 oneshot:1;      // [0]
        u32 size:1;         // [1]
        u32 prescale:2;     // [3:2]
        u32 __reserved1:1;  // [4]
        u32 int_en:1;       // [5]
        u32 mode:1;         // [6]
        u32 en:1;           // [7]
        u32 __reserved2:24; // [31:8]
    } bits;
};

union timerx_ris {
    u32 all;
    struct {
        u32 ris:1;          // [0]
        u32 __reserved:31;  // [31:1]
    } bits;
};

union timerx_mis {
    u32 all;
    struct {
        u32 mis:1;          // [0]
        u32 __reserved:31;  // [31:1]
    } bits;
};

struct sp804_timer {
    u32 load;                       // 0x00
    u32 value;                      // 0x04
    union timerx_control control;   // 0x08
    u32 intclr;                     // 0x0c
    union timerx_ris ris;           // 0x10
    union timerx_mis mis;           // 0x14
    u32 bgload;                     // 0x18
};

#define TIMER_CPU_BASE 0x10011000
#define TIMER_INTERRUPT 36

#define TIMER_FREERUNNING 0
#define TIMER_PERIODIC 1

#define TIMER_16BITS_COUNTER 0
#define TIMER_32BITS_COUNTER 1

#define div_val_from_prescale(x) (16<<(x))
#define TIMCLK 1000000
#define REFCLK 32768
#define TIMCLKEN_CYCLE 1 // guess.. (trial & error)

#define get_timer() ((volatile struct sp804_timer*)__timer)
extern struct sp804_timer* __timer;

#endif /* __RVPB_TIMER_H__ */
