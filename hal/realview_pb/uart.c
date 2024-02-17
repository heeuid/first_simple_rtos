#include <stdint.h>
#include <realview_pb/uart.h>
#include <hal/interrupt.h>
#include <hal/uart.h>

static void uart_interrupt_handler(void* arg) {
    u32 id = (u32)arg;
    hal_uart_put_char(id, hal_uart_get_char(id));
}

void hal_uart_init(void)
{
    int i;
    volatile struct pl011* uart;

    // enable uarts
    for (i = 0; i < UART_CNT; i++) {
        uart = get_uart(i);

        // enable uart
        uart->cr.bits.en = 0;
        uart->cr.bits.txe = 1;
        uart->cr.bits.rxe = 1;
        uart->cr.bits.en = 1;

        // enable input interrupt
        uart->imsc.bits.rxim = 1;

        // register uart interrupt handler
        hal_interrupt_enable(UART_INTERRUPT0 + i);
        hal_interrupt_register_handler(uart_interrupt_handler, (void*)i,
                                       UART_INTERRUPT0 + i);
    }
}

void hal_uart_put_char(u32 uart_id, u8 ch)
{   
    while(get_uart(uart_id)->fr.bits.txff);
    get_uart(uart_id)->dr.all = ch & 0xff;
}

u8 hal_uart_get_char(u32 uart_id)
{
    u32 data;
    volatile struct pl011* uart = get_uart(uart_id); 

    while (uart->fr.bits.rxfe) {}

    data = uart->dr.all;

    // check for an error flag
    if (data & 0xffffff00) {
        // clear the error
        uart->rsr.all = 0xff;
        return 0;
    }

    return data & 0xff;
}
