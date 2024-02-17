#ifndef __PRVB_INTERRUPT_H__
#define __PRVB_INTERRUPT_H__

#include <stdint.h>

union cpu_control { u32 all;
    struct {
        u32 enable:1;        // [0]
        u32 __reserved:31;   // [31:1]
    } bits;
};

union priority_mask {
    u32 all;
    struct {
        u32 reserved1:4;     // [3:0]
        u32 priority_mask:4; // [7:4]
        u32 __reserved2:24;  // [31:8]
    } bits;
};

union binary_point {
    u32 all;
    struct {
        u32 binarypoint:3;   // [2:0]
        u32 __reserved:29;   // [31:3]
    } bits;
};

union interrupt_ack {
    u32 all;
    struct {
        u32 interrupt_id:10;  // [9:0]
        u32 cpu_source_id:3;  // [12:10]
        u32 __reserved:19;    // [31:13]
    } bits;
};

union end_of_interrupt {
    u32 all;
    struct {
        u32 interrupt_id:10;   // [9:0]
        u32 cpu_source_id:3;   // [12:10]
        u32 __reserved:19;     // [31:13]
    } bits;
};

union running_interrupt {
    u32 all;
    struct {
        u32 __reserved1:4;     // [3:0]
        u32 priority:4;        // [7:4]
        u32 __reserved2:24;    // [31:8]
    } bits;
};

union highest_pend_inter {
    u32 all;
    struct {
        u32 interrupt_id:10;   // [9:0]
        u32 cpu_source_id:3;   // [12:10]
        u32 __reserved:19;     // [31:13]
    } bits;
};

union distributor_ctrl {
    u32 all;
    struct {
        u32 enable:1;          // [0]
        u32 __reserved:31;     // [31:1]
    } bits;
};

union controller_type {
    u32 all;
    struct {
        u32 id_lines_number:5; // [4:0]
        u32 cpu_number:3;      // [7:5]
        u32 __reserved:24;     // [31:8]
    } bits;
};

struct gic_cpu {
    union cpu_control cpu_control;               // 0x000
    union priority_mask priority_mask;           // 0x004
    union binary_point binarypoint;              // 0x008
    union interrupt_ack interrupt_ack;           // 0x00c
    union end_of_interrupt end_of_interrupt;     // 0x010
    union running_interrupt running_interrupt;   // 0x014
    union highest_pend_inter highest_pend_inter; // 0x018
};

struct gic_dist {
    union distributor_ctrl distributor_ctrl;     // 0x000
    union controller_type controller_type;       // 0x004
    u32 __reserved1[62];                         // 0x008-0x0fc
    u32 __reserved2;                             // 0x100
    u32 set_enable1;                             // 0x104
    u32 set_enable2;                             // 0x108
    u32 __reserved3[29];                         // 0x10c-017c
    u32 __reserved4;                             // 0x180
    u32 clear_enable1;                           // 0x184
    u32 clear_enable2;                           // 0x188
};

#define GIC_CPU_BASE    0x1e000000 // CPU Interface
#define GIC_DIST_BASE   0x1e001000 // Distributor

#define GIC_PRIORITY_MASK_NONE 0xf

#define GIC_IRQ_START   32
#define GIC_IRQ_END     95

#define INTERRUPT_HANDLER_NUM	255

#define get_gic_cpu() ((volatile struct gic_cpu*)__gic_cpu)
#define get_gic_dist() ((volatile struct gic_dist*)__gic_dist)

extern struct gic_cpu* __gic_cpu;
extern struct gic_dist* __gic_dist;

#endif /* __PRVB_INTERRUPT_H__ */
