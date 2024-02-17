#include <stdint.h>
#include <mmio.h>
#include <hal/interrupt.h>
#include <realview_pb/interrupt.h>
#include <armcpu.h>

static interrupt_handler_t handlers[INTERRUPT_HANDLER_NUM]; 
static void* handler_args[INTERRUPT_HANDLER_NUM];

void hal_interrupt_init(void) {
    get_gic_cpu()->cpu_control.bits.enable = 1;
    get_gic_cpu()->priority_mask.bits.priority_mask = GIC_PRIORITY_MASK_NONE;
    get_gic_dist()->distributor_ctrl.bits.enable = 1;

    for (u32 i = 0; i < INTERRUPT_HANDLER_NUM; i++) {
        handlers[i] = NULL;
    }

    enable_irq();
}

void hal_interrupt_enable(u32 interrupt_num) {
    if ((interrupt_num < GIC_IRQ_START) || (GIC_IRQ_END < interrupt_num)){
       return; 
    }    

    u32 bit_num = interrupt_num - GIC_IRQ_START;

    if (bit_num < GIC_IRQ_START) {
       set_bit(get_gic_dist()->set_enable1, bit_num);
    } else {
       set_bit(get_gic_dist()->set_enable2, bit_num - GIC_IRQ_START); 
    }
}

void hal_interrupt_disable(u32 interrupt_num) {
    if ((interrupt_num < GIC_IRQ_START) || (GIC_IRQ_END < interrupt_num)) {
       return; 
    }

    u32 bit_num = interrupt_num - GIC_IRQ_START;

    if (bit_num < GIC_IRQ_START) {
       clr_bit(get_gic_dist()->set_enable1, bit_num);
    } else {
       clr_bit(get_gic_dist()->set_enable2, bit_num - GIC_IRQ_START); 
    }
}

void hal_interrupt_register_handler(interrupt_handler_t handler, void* arg,
                                    u32 interrupt_num) {
    handlers[interrupt_num] = handler;
    handler_args[interrupt_num] = arg;
}

void hal_interrupt_run_handler(void) {
    u32 interrupt_num = get_gic_cpu()->interrupt_ack.bits.interrupt_id;

    if (handlers[interrupt_num]) {
        handlers[interrupt_num](handler_args[interrupt_num]); 
    }

    get_gic_cpu()->end_of_interrupt.bits.interrupt_id = interrupt_num;
}
