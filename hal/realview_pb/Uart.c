#include <stdint.h>
#include <Uart.h>
#include <HalUart.h>

#define UART_CNT 4

extern volatile PL011_t* Uart[];

void Hal_uart_init(void)
{
    int i;
//////

    // enable uarts
    for (i = 0; i < UART_CNT; i++) {
        Uart[i]->uartcr.bits.UARTEN = 0;
        Uart[i]->uartcr.bits.TXE = 0;
        Uart[i]->uartcr.bits.RXE = 1;
        Uart[i]->uartcr.bits.UARTEN = 1;
    }
}

void Hal_uart_put_char(uint32_t uart_id, uint8_t ch)
{
    volatile PL011_t* uart = Uart[uart_id];
//////

    while(uart->uartfr.bits.TXFF);
    uart->uartdr.all = ch & 0xff;
}
