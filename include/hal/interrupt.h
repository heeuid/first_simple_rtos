#ifndef __HAL_INTERRUPT_H__
#define __HAL_INTERRUPT_H__

#include <stdint.h>

typedef void (*interrupt_handler_t)(void*);

void hal_interrupt_init(void);
void hal_interrupt_enable(u32 interrupt_num);
void hal_interrupt_disable(u32 interrupt_num);
void hal_interrupt_register_handler(interrupt_handler_t handler, void* arg,
                                    u32 interrupt_num);
void hal_interrupt_run_handler(void);

#endif /* __HAL_HAL_INTERRUPT_H__ */
