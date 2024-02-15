#include <stdint.h>
#include <uart.h>
#include <hal_uart.h>

#define UART_CNT 4

extern volatile struct pl011* uarts[];

void hal_uart_init(void)
{
    int i;

    // enable uarts
    for (i = 0; i < UART_CNT; i++) {
        uarts[i]->uartcr.bits.uarten = 0;
        uarts[i]->uartcr.bits.txe = 1;
        uarts[i]->uartcr.bits.rxe = 1;
        uarts[i]->uartcr.bits.uarten = 1;
    }
}

void hal_uart_put_char(u32 uart_id, u8 ch)
{   
    volatile struct pl011* uart = uarts[uart_id];

    while(uart->uartfr.bits.txff);
    uart->uartdr.all = ch & 0xff;
}

u8 hal_uart_get_char(u32 uart_id)
{
    u32 data;
    volatile struct pl011* uart = uarts[uart_id];

    while (uart->uartfr.bits.rxfe) {}

    data = uart->uartdr.all;

    if (data & 0xf00) {
        uart->uartrsr.all = 0xf;
        return 0;
    }

    return data&0xff;
}
