#include <realview_pb/uart.h>
#include <realview_pb/interrupt.h>
#include <realview_pb/timer.h>

struct pl011* __uarts[] = {
    [0] = (struct pl011*)UART_BASE_ADDRESS0,
    [1] = (struct pl011*)UART_BASE_ADDRESS1,
    [2] = (struct pl011*)UART_BASE_ADDRESS2,
    [3] = (struct pl011*)UART_BASE_ADDRESS3,
};

struct gic_cpu* __gic_cpu = (struct gic_cpu*)GIC_CPU_BASE;
struct gic_dist* __gic_dist = (struct gic_dist*)GIC_DIST_BASE;

struct sp804_timer* __timer = (struct sp804_timer*)TIMER_CPU_BASE;

