#include <stdint.h>
#include <hal/timer.h>
#include <realview_pb/timer.h>
#include <hal/interrupt.h>
#include <realview_pb/sysctrl.h>
#include <mmio.h>

static u32 internal_ms_counter;

static void timer_interrupt_handler(void* _) {
    internal_ms_counter++;
    get_timer()->intclr = 1;
}

void hal_timer_init(void) {
    u32 sysctrl_val;
    volatile struct sp804_timer* timer = get_timer();

    // interface reset
    timer->control.bits.en = 0;
    timer->control.bits.mode = TIMER_FREERUNNING;
    timer->control.bits.oneshot = 0;
    timer->control.bits.size = 0;
    timer->control.bits.prescale = 0;
    timer->control.bits.int_en = 1;
    timer->load = 0;
    timer->value = 0xffffffff;

    // set periodic mode
    timer->control.bits.mode = TIMER_PERIODIC;
    timer->control.bits.size = TIMER_32BITS_COUNTER;
    timer->control.bits.oneshot = 0; 
    timer->control.bits.prescale = 0;
    timer->control.bits.int_en = 1;

    // select timeclk (1MHz & enable cycle always high)
    sysctrl_val = read32(SYSCTRL_BASE);
    sysctrl_val |= BIT(SYSCTRL_TIMER_CLK_SELECT); 
    sysctrl_val |= BIT(SYSCTRL_TIMER_EN_OUT_SELECT); 
    write32(sysctrl_val, SYSCTRL_BASE);

    timer->load = TIMCLK / 1000;
    timer->control.bits.en = 1;

    internal_ms_counter = 0;

    hal_interrupt_enable(TIMER_INTERRUPT);
    hal_interrupt_register_handler(timer_interrupt_handler, NULL, TIMER_INTERRUPT);
}

u32 hal_timer_get_ms(void) {
    return internal_ms_counter; 
}
