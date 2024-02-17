#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <hal/uart.h>

#define PRINT_BUF_LEN 4096 // 4KB

u32 putstr(const char *s)
{
    u32 size = 0;
    while (!!*s) {
        hal_uart_put_char(0, *s++);
        size++;
    }
    return size;
}

u32 debug_printf(const char *format, ...)
{
    char buf[PRINT_BUF_LEN];
    va_list(args);

    va_start(args, format);
    vsprintf(buf, format, args);
    va_end(args);

    return putstr(buf);
}

// for %c %s %x(==%X) %u
u32 vsprintf(char *buf, const char *format, va_list args)
{
    u32 size;
    u32 i;
    char ch;
    char *str;
    u32 num;

    for (i = 0, size = 0; !!format[i]; i++) {
        if (format[i] == '%') {
            i++;

            if (i >= PRINT_BUF_LEN) {
                buf[0] = '\0';
                return 0;
            }

            switch (format[i]) {
            case 'c':
                ch = (char)va_arg(args, i32);
                buf[size++] = ch;
                break;
            case 's':
                str = (char*)va_arg(args, char*);
                if (!str)
                    str = "";
                while (!!*str)
                    buf[size++] = *str++;
                break;
            case 'X':
            case 'x':
                num = (u32)va_arg(args, u32);
                size += utoa(&buf[size], num, utoa_hex);
                break;
            case 'u':
                num = (u32)va_arg(args, u32);
                size += utoa(&buf[size], num, utoa_dec);
                break;
            }
        }
        else
            buf[size++] = format[i];
    }

    buf[size] = '\0';
    return size;
}

u32 utoa(char *buf, u32 num, enum utoa_base base)
{
    char numstr[10]; //32bits => about 4.3billion => 10 length
    u32 len;
    u32 r;
    char ch;

    len = 0;

    while (num > 0) {
        r = num % base;
        if (r >= 10)
            ch = (r - 10) + 'A';
        else
            ch = r + '0';
        numstr[len++] = ch;
        num /= base;
    }

    r = 0;
    while (r < len) {
        buf[r] = numstr[len - 1 - r];
        r++;
    }

    return len;
}
