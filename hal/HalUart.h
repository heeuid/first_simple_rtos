#ifndef _HAL_HAL_UART_H_
#define _HAL_HAL_UART_H_

void Hal_uart_init(void);
void Hal_uart_put_char(uint32_t uart_id, uint8_t ch);

#endif /* HAL_HAL_UART_H_ */
