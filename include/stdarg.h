#ifndef __STDARG_H__
#define __STDARG_H__

typedef __builtin_va_list va_list;

#define va_start(value,list)    __builtin_va_start(value,list);
#define va_end(value)           __builtin_va_end(value);
#define va_arg(value,type)      __builtin_va_arg(value,type);

#endif /* __STDARG_H__ */

