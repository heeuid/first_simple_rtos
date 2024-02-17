#ifndef __HAL_HAL_INTERRUPT_H__
#define __HAL_HAL_INTERRUPT_H__

#include <stdint.h>

#define INTERUUPT_HANDLER_NUM	255

typedef void (*interrupt_handler)(void);

void hal_interrupt_init(void);
void hal_interrupt_enable(u32 interrupt_num);
void hal_interrupt_disable(u32 interrupt_num);
void hal_interrupt_register_handler(interrupt_handler handler, u32 irq);
void hal_interrupt_run_handler(void);

#endif /* __HAL_HAL_INTERRUPT_H__ */
