#include <stdint.h>
#include <Uart.h>

volatile PL011_t* Uart[] = {
    [0] = (PL011_t*)UART_BASE_ADDRESS0,
    [1] = (PL011_t*)UART_BASE_ADDRESS1,
    [2] = (PL011_t*)UART_BASE_ADDRESS2,
    [3] = (PL011_t*)UART_BASE_ADDRESS3,
};
