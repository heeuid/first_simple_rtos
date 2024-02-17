#ifndef __HAL_HAL_UART_H__
#define __HAL_HAL_UART_H__
#include <stdint.h>

void hal_uart_init(void);
void hal_uart_put_char(u32 uart_id, u8 ch);
u8 hal_uart_get_char(u32 uart_id);

#endif /* __HAL_HAL_UART_H__ */
