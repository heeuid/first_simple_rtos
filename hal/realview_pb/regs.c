#include <stdint.h>
#include <uart.h>

volatile struct pl011* uarts[] = {
    [0] = (struct pl011*)UART_BASE_ADDRESS0,
    [1] = (struct pl011*)UART_BASE_ADDRESS1,
    [2] = (struct pl011*)UART_BASE_ADDRESS2,
    [3] = (struct pl011*)UART_BASE_ADDRESS3,
};
