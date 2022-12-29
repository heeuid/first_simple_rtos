# first_simple_rtos
first simple rtos with qemu vm (realview pb a8)

## Environments
- Development PC
  + Ubuntu 22.04

- Machine
  + vm: qemu-system-arm / realview-pb-a8
  + `sudo apt install qemu-system-arm`

- Cross platform
  + toolchain: arm-none-eabi-
  + `sudo apt install gcc-arm-none-eabi`
  + gdb: gdb-multiarch
  + `sudo apt install gdb-multiarch`

## Build
- `make`

## Debugging
- `make debug`
- `make gdb`
  1. `target remote:1234`
  2. `ile build/navilos.axf`
  
## Directory tree
<pre>
first_simple_rtos/  
├── boot/  
│   ├── Entry.S  
│   └── Main.c
├── hal/
│   ├── Regs.c  
│   └── Uart.h
├── include/  
│   ├── ARMv7AR.h  
│   ├── MemoryMap.h  
│   └── stdint.h  
├── Makefile  
├── navilos.ld  
└── README.md  
</pre>
