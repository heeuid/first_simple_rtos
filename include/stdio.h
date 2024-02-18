#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdint.h>
#include <stdarg.h>

enum utoa_base {
    utoa_dec=10,
    utoa_hex=16,
};

u32 putstr(const char *s);
u32 debug_printf(const char *format, ...);
u32 vsprintf(char *buf, const char *format, va_list args);
u32 utoa(char *buf, u32 num, enum utoa_base base);

#endif /* __STDIO_H__ */

