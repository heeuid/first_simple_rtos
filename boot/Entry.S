#include "ARMv7AR.h"
#include "MemoryMap.h"

.text
    .code 32                // 32-bit cmd

    .global vector_start
    .global vector_end      // make symbol to be used outside of this file
                            // like extern
    vector_start:
        // EVT: Exception Vector Table
        LDR PC, reset_handler_addr
        LDR PC, undef_handler_addr
        LDR PC, svc_handler_addr
        LDR PC, pftch_abt_handler_addr
        LDR PC, data_abt_handler_addr
        B   .
        LDR PC, irq_handler_addr
        LDR PC, fiq_handler_addr
        
        // Variables having Addresses of handlers for EVT 
        reset_handler_addr: .word reset_handler
        undef_handler_addr: .word dummy_handler
        svc_handler_addr:   .word dummy_handler
        pftch_abt_handler_addr: .word dummy_handler
        data_abt_handler_addr:  .word dummy_handler
        irq_handler_addr:   .word dummy_handler
        fiq_handler_addr:   .word dummy_handler
    vector_end:

    reset_handler:
        /* SVC mode setting */
        MRS r0, cpsr            // copy system reg. into general-purpose reg.
        BIC r1, r0, #0x1F       // clear r0 with #0x1F
        ORR r1, r1, #ARM_MODE_BIT_SVC // write only mode bits
        MSR cpsr, r1            // copy general-purpose reg. into system reg.
        LDR sp, =SVC_STACK_TOP  // load top_address to stack pointer

        /* IRQ mode setting */
        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_IRQ
        MSR cpsr, r1
        LDR sp, =IRQ_STACK_TOP

        /* FIQ mode setting */
        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_FIQ
        MSR cpsr, r1
        LDR sp, =FIQ_STACK_TOP

        /* ABT mode setting */
        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_ABT
        MSR cpsr, r1
        LDR sp, =ABT_STACK_TOP

        /* UND mode setting */
        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_UND
        MSR cpsr, r1
        LDR sp, =UND_STACK_TOP

        /* SYS mode setting */
        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_SYS
        MSR cpsr, r1
        LDR sp, =USRSYS_STACK_TOP

        BL  main

    dummy_handler:
        B   .
.end
