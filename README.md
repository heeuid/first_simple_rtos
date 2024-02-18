# first_simple_rtos
first simple rtos with qemu vm (realview pb a8)  
Study Book: "도전! 임베디드 OS 만들기"  
(https://github.com/navilera/Navilos)

1. booting, exception vector table, reset handler, linker, Makefile, ...
2. uart, console, printf
3. interrupt, gic, uart interrupt
4. timer, delay

## Environments
- Host OS
  + Ubuntu 22.04
- Machine
  + vm: qemu-system-arm / realview-pb-a8
  + `sudo apt install qemu-system-arm`
- Cross platform (toolchain)
  + toolchain: arm-none-eabi-
  + `sudo apt install gcc-arm-none-eabi`
  + gdb: gdb-multiarch
  + `sudo apt install gdb-multiarch`

## Build
- `make`

## Debugging
1. `make debug`
2. `make gdb`
    1. `target remote:1234`
    2. `file build/navilos.axf`

## Run & Quit
- `make run`
- `make kill` (in another terminal)
  
## Directory tree
<pre>
first_simple_rtos/  
├── boot
│   ├── handler.c
│   └── realview_pb
│       ├── entry.S
│       └── main.c
├── docs
│   ├── gdb.md
│   └── images
│       └── gdb_with_vim.png
├── hal
│   └── realview_pb
│       ├── interrupt.c
│       ├── regs.c
│       ├── timer.c
│       └── uart.c
├── include
│   ├── armcpu.h
│   ├── armv7_ar.h
│   ├── hal
│   │   ├── interrupt.h
│   │   ├── timer.h
│   │   └── uart.h
│   ├── mach
│   │   └── realview_pb
│   │       ├── interrupt.h
│   │       ├── memory_map.h
│   │       ├── sysctrl.h
│   │       ├── timer.h
│   │       └── uart.h
│   ├── mmio.h
│   ├── stdarg.h
│   ├── stdint.h
│   ├── stdio.h
│   └── stdlib.h
├── lib
│   ├── armcpu.c
│   ├── stdio.c
│   └── stdlib.c
├── Makefile
├── navilos.ld
└── README.md
</pre>

- All header files are under include/

## Documents
- RealView Platform Baseboard for Cortex-A8
    + [User Guide](https://developer.arm.com/documentation/dui0417/d?lang=en)
        + [Programmer's Reference](https://developer.arm.com/documentation/dui0417/d/programmer-s-reference?lang=en)
- PrimeCell UART (PL011) Technical Reference Manual
    + https://developer.arm.com/documentation/ddi0183/g?lang=en
- ARM Dual-Timer Module (SP804) Technical Reference Manual
    + https://developer.arm.com/documentation/ddi0271/d
- GCC Link Options
    + https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
