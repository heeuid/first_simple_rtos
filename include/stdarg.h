#ifndef _STDARG_H_
#define _STDARG_H_

typedef __builtin_va_list va_list;

#define va_start(value,list)    __builtin_va_start(value,list);
#define va_end(value)           __builtin_va_end(value);
#define va_arg(value,type)      __builtin_va_arg(value,type);

#endif /* _STDARG_H_ */

