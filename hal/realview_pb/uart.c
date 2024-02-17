#include <stdint.h>
#include <realview_pb/uart.h>
#include <hal/uart.h>

#define UART_CNT 4

extern struct pl011* uarts[];

void hal_uart_init(void)
{
    int i;
    volatile struct pl011* uart;

    // enable uarts
    for (i = 0; i < UART_CNT; i++) {
        uart = uarts[i];
        uart->cr.bits.en = 0;
        uart->cr.bits.txe = 1;
        uart->cr.bits.rxe = 1;
        uart->cr.bits.en = 1;
    }
}

void hal_uart_put_char(u32 uart_id, u8 ch)
{   
    volatile struct pl011* uart = uarts[uart_id];

    while(uart->fr.bits.txff);
    uart->dr.all = ch & 0xff;
}

u8 hal_uart_get_char(u32 uart_id)
{
    u32 data;
    volatile struct pl011* uart = uarts[uart_id];

    while (uart->fr.bits.rxfe) {}

    data = uart->dr.all;

    if (data & 0xf00) {
        uart->rsr.all = 0xf;
        return 0;
    }

    return data & 0xff;
}
