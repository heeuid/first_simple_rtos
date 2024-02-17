#include <stdio.h>
#include <stdint.h>
#include <hal/uart.h>

static void hw_init(void);
static void printf_test(void);

int main(void)
{
    u32 i;
    u32 uart_id;

    hw_init();

    uart_id = 0;
    i = 100;
    while (i--) {
        hal_uart_put_char(uart_id, 'N');
    }
	hal_uart_put_char(uart_id, '\n');

    putstr("Hello World!\n");

    printf_test();

    i = 100;
    while (i--) {
        u8 ch = hal_uart_get_char(uart_id);
        hal_uart_put_char(uart_id, ch);
    }

    return 0;
}


static void hw_init(void) 
{
    hal_uart_init();
}

static void printf_test(void)
{
	char *str = "printf pointer test";
	char *nullptr = 0;
	u32 i = 5;

	debug_printf("[%s]\n", "Hello printf");
	debug_printf("output string jpointer: [%s]\n", str);
	debug_printf("[%s] is null pointer, %u number\n", nullptr, 10);
	debug_printf("dec=%u hex=%x\n", 0xfe, 0xfe);
	debug_printf("print zero %u\n", 0);
}