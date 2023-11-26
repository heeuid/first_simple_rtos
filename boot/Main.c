#include <stdio.h>
#include <stdint.h>
#include <HalUart.h>

static void Hw_init(void);
static void printf_test(void);

int main(void)
{
    uint32_t i;
    uint32_t uart_id;

    Hw_init();

    uart_id = 0;
    i = 100;
    while (i--) {
        Hal_uart_put_char(uart_id, 'N');
    }
	Hal_uart_put_char(uart_id, '\n');

    putstr("Hello World!\n");

    printf_test();

    i = 100;
    while (i--) {
        uint8_t ch = Hal_uart_get_char(uart_id);
        Hal_uart_put_char(uart_id, ch);
    }

    return 0;
}


static void Hw_init(void) 
{
    Hal_uart_init();
}

static void printf_test(void)
{
	char *str = "printf pointer test";
	char *nullptr = 0;
	uint32_t i = 5;

	debug_printf("[%s]\n", "Hello printf");
	debug_printf("output string jpointer: [%s]\n", str);
	debug_printf("[%s] is null pointer, %u number\n", nullptr, 10);
	debug_printf("dec=%u hex=%x\n", 0xfe, 0xfe);
	debug_printf("print zero %u\n", 0);
}
