#include <stdio.h>
#include <stdint.h>
#include <HalUart.h>

static void Hw_init(void);

void main(void)
{
    uint32_t i;
    uint32_t uart_id;
//////

    Hw_init();

    uart_id = 0;
    i = 100;
    while (i--) {
        Hal_uart_put_char(uart_id, 'N');
    }
	Hal_uart_put_char(uart_id, '\n');

    putstr("Hello World!\n");

    i = 100;
    while (i--) {
        uint8_t ch = Hal_uart_get_char(uart_id);
        Hal_uart_put_char(uart_id, ch);
    }
}


static void Hw_init(void) 
{
    Hal_uart_init();
}
