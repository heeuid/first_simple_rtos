#include <stdint.h>
#include <hal/timer.h>

void delay(u32 ms) {
    u32 start = hal_timer_get_ms();
    while (hal_timer_get_ms() - start < ms)
        ;
}
