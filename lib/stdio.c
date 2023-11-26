#include <stdint.h>
#include <HalUart.h>

uint32_t putstr(const char *s)
{
    uint32_t size = 0;
    while (!!*s) {
        Hal_uart_put_char(0, *s++);
        size++;
    }
    return size;
}
