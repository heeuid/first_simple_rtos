#ifndef __RVPB_UART_H__
#define __RVPB_UART_H__
#include <stdint.h>

union uart_dr {    // 0x000
    u32 all;
    struct {
        u32 data:8;    // 7:0
        u32 fe:1;      // 8
        u32 pe:1;      // 9
        u32 be:1;      // 10
        u32 oe:1;      // 11
        u32 reserved:20;
    } bits;
};

union uart_rsr {   // 0x004
    u32 all;
    struct {
        u32 fe:1;      // 0
        u32 pe:1;      // 1
        u32 be:1;      // 2
        u32 oe:1;      // 3
        u32 reserved:28;
    } bits;
};

union uart_ecr {   // 0x004
    u32 all;
    struct {
        u32 fe:1;      // 0
        u32 pe:1;      // 1
        u32 be:1;      // 2
        u32 oe:1;      // 3
        u32 reserved:28;
    } bits;
};

union uart_fr {    // 0x018
    u32 all;
    struct {
        u32 cts:1;     // 0
        u32 dsr:1;     // 1
        u32 dcd:1;     // 2
        u32 busy:1;    // 3
        u32 rxfe:1;    // 4
        u32 txff:1;    // 5
        u32 rxff:1;    // 6
        u32 txfe:1;    // 7
        u32 ri:1;      // 8
        u32 reserved:23;
    } bits;
};

union uart_ilpr {  // 0x020
    u32 all;
    struct {
        u32 ilpdvsr:8; // 7:0
        u32 reserved:24;
    } bits;
};

union uart_ibrd {  // 0x024
    u32 all;
    struct {
        u32 baud_divint:16;    // 15:0
        u32 reserved:16;
    } bits;
};

union uart_fbrd {  // 0x028
    u32 all;
    struct {
        u32 baud_divfrac:6;    // 5:0
        u32 reserved:26;
    } bits;
};

union uart_lcr_h { // 0x02C
    u32 all;
    struct {
        u32 brk:1;     // 0
        u32 pen:1;     // 1
        u32 eps:1;     // 2
        u32 stp2:1;    // 3
        u32 fen:1;     // 4
        u32 wlen:2;    // 6:5
        u32 sps:1;     // 7
        u32 reserved:24;
    } bits;
};

union uart_cr {    // 0x030
    u32 all;
    struct {
        u32 en:1;      // 0
        u32 siren:1;       // 1
        u32 sirlp:1;       // 2
        u32 reserved1:4;   // 6:3
        u32 lbe:1;         // 7
        u32 txe:1;         // 8
        u32 rxe:1;         // 9
        u32 dtr:1;         // 10
        u32 rts:1;         // 11
        u32 out1:1;        // 12
        u32 out2:1;        // 13
        u32 rtsen:1;       // 14
        u32 ctsen:1;       // 15
        u32 reserved2:16;
    } bits;
};

union uart_ifls {  // 0x034
    u32 all;
    struct {
        u32 txiflsel:3;    // 2:0
        u32 rxiflsel:3;    // 5:3
        u32 reserved:26;
    } bits;
};

union uart_imsc {  // 0x038
    u32 all;
    struct {
        u32 rimim:1;   // 0
        u32 ctsmim:1;  // 1
        u32 dcdmim:1;  // 2
        u32 dsrmim:1;  // 3
        u32 rxim:1;    // 4
        u32 txim:1;    // 5
        u32 rtim:1;    // 6
        u32 feim:1;    // 7
        u32 peim:1;    // 8
        u32 beim:1;    // 9
        u32 oeim:1;    // 10
        u32 reserved;
    } bits;
};

union uart_ris {   // 0x03c
    u32 all;
    struct {
        u32 rirmis:1;  // 0
        u32 ctsrmis:1; // 1
        u32 dcdrmis:1; // 2
        u32 dsrrmis:1; // 3
        u32 rxris:1;   // 4
        u32 txris:1;   // 5
        u32 rtris:1;   // 6
        u32 feris:1;   // 7
        u32 peris:1;   // 8
        u32 beris:1;   // 9
        u32 oeris:1;   // 10
        u32 reserved:21;
    } bits;
};

union uart_mis {   // 0x040
    u32 all;
    struct {
        u32 rimmis:1;  // 0
        u32 ctsmmis:1; // 1
        u32 dcdmmis:1; // 2
        u32 dsrmmis:1; // 3
        u32 rxmis:1;   // 4
        u32 txmis:1;   // 5
        u32 rtmis:1;   // 6
        u32 femis:1;   // 7
        u32 pemis:1;   // 8
        u32 bemis:1;   // 9
        u32 oemis:1;   // 10
        u32 reserved:21;
    } bits;
};

union uart_icr {   // 0x044
    u32 all;
    struct {
        u32 rimic:1;   // 0
        u32 ctsmis:1;  // 1
        u32 dcdmic:1;  // 2
        u32 dsrmic:1;  // 3
        u32 rxic:1;    // 4
        u32 txic:1;    // 5
        u32 rtic:1;    // 6
        u32 feic:1;    // 7
        u32 peic:1;    // 8
        u32 beic:1;    // 9
        u32 oeic:1;    // 10
        u32 reserved:21;
    } bits;
};

union uart_dmacr { // 0x048
    u32 all;
    struct {
        u32 rxdmae:1;      // 0
        u32 txdmae:1;      // 1    
        u32 dmaonerr:1;    // 2
        u32 reserved:29;
    } bits;
};

// register map of an uart
struct pl011 {
    union uart_dr dr;        // 0x000
    union uart_rsr rsr;      // 0x004
    u32 reserved1[4];           // 0x008-0x014
    union uart_fr fr;        // 0x018
    u32 reserved2;              // 0x01c
    union uart_ilpr lpr;     // 0x020
    union uart_ibrd ibrd;    // 0x024
    union uart_fbrd fbrd;    // 0x028
    union uart_lcr_h lcr_h;  // 0x02c
    union uart_cr cr;        // 0x030
    union uart_ifls fls;     // 0x034
    union uart_imsc imsc;    // 0x038
    union uart_ris ris;      // 0x03c
    union uart_mis mis;      // 0x040
    union uart_icr icr;      // 0x044
    union uart_dmacr dmacr;  // 0x048
};

#define UART_SIZE           0x1000
#define UART_BASE_ADDRESS0  0x10009000
#define UART_BASE_ADDRESS1  0x1000A000
#define UART_BASE_ADDRESS2  0x1000B000
#define UART_BASE_ADDRESS3  0x1000C000
#define UART_INTERRUPT0     44
#define UART_INTERRUPT1     45
#define UART_INTERRUPT2     46
#define UART_INTERRUPT3     47

#define UART_CNT 4

#define get_uart(id) ((volatile struct pl011*)__uarts[id])

extern struct pl011* __uarts[];


#endif /* __RVPB_UART_H__ */
