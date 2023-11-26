# first_simple_rtos
first simple rtos with qemu vm (realview pb a8)  
Study Book: "도전! 임베디드 OS 만들기"  
(https://github.com/navilera/Navilos)

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
│   ├── Entry.S
│   └── Main.c
├── docs
│   ├── gdb.md
│   └── images
│       └── gdb_with_vim.png
├── hal
│   ├── HalUart.h
│   └── realview_pb
│       ├── Regs.c
│       ├── Uart.c
│       └── Uart.h
├── include
│   ├── ARMv7AR.h
│   ├── MemoryMap.h
│   ├── stdarg.h
│   └── stdint.h
├── lib
│   ├── stdio.c
│   └── stdio.h
├── Makefile
├── navilos.ld
└── README.md
</pre>

## Documents
- RealView Platform Baseboard for Cortex-A8 User Guide
    + https://developer.arm.com/documentation/dui0417/d?lang=en
- PrimeCell UART (PL011) Technical Reference Manual
    + https://developer.arm.com/documentation/ddi0183/g?lang=en
- GCC Link Options
    + https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
