#include <stdint.h>

#include "Uart.h"

volatile PL011_t* Uart0 = (PL011_t*)UART_BASE_ADDRESS0;
volatile PL011_t* Uart1 = (PL011_t*)UART_BASE_ADDRESS1;
volatile PL011_t* Uart2 = (PL011_t*)UART_BASE_ADDRESS2;
volatile PL011_t* Uart3 = (PL011_t*)UART_BASE_ADDRESS3;
