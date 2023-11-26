#ifndef _LIB_STDIO_H_
#define _LIB_STDIO_H_
#include <stdint.h>
#include <stdarg.h>

enum utoa_base {
    utoa_dec=10,
    utoa_hex=16,
};

uint32_t putstr(const char *s);
uint32_t debug_printf(const char *format, ...);
uint32_t vsprintf(char *buf, const char *format, va_list args);
uint32_t utoa(char *buf, uint32_t num, enum utoa_base base);

#endif /* _LIB_STDIO_H_ */
