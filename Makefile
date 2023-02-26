MACH = realview-pb-a8
ARCH = armv7-a
MCPU = cortex-a8

TARGET = realview_pb

CROSS_PLATFORM = arm-none-eabi-
CC = $(CROSS_PLATFORM)gcc
AS = $(CROSS_PLATFORM)as
LD = $(CROSS_PLATFORM)ld
OC = $(CROSS_PLATFORM)objcopy

LINKER_SCRIPT = ./navilos.ld
MAP_FILE = build/navilos.map

VPATH = boot \
        hal/$(TARGET)

ASM_SRCS = $(wildcard boot/*.S)
ASM_OBJS = $(patsubst boot/%.S, build/%.os, $(ASM_SRCS))

C_SRCS = $(notdir $(wildcard boot/*.c))
C_SRCS += $(notdir $(wildcard hal/$(TARGET)/*.c))
C_OBJS = $(patsubst %.c, build/%.o, $(C_SRCS))

INC_DIRS = -I include/
INC_DIRS += -I hal/
INC_DIRS += -I hal/$(TARGET)

CFLAGS = -c -g -std=c11

navilos = build/navilos.axf
navilos_bin = build/navilos_bin

.PHONY: all clean run debug gdb arch

all: $(navilos)

clean:
	@rm -rf build tags

run: $(navilos)
	qemu-system-arm -M $(MACH) -kernel $(navilos) -nographic

debug:
	qemu-system-arm -M $(MACH) -kernel $(navilos) -S -gdb tcp::1234,ipv4

gdb:
	gdb-multiarch

arch:
	@echo MACH=$(MACH)
	@echo ARCH=$(ARCH)
	@echo MCPU=$(MCPU)

srcs:
	@echo "asm_srcs: $(ASM_SRCS)"
	@echo "c_srcs: $(C_SRCS)"
	@echo "asm_objs: $(ASM_OBJS)"
	@echo "c_objs: $(C_OBJS)"

$(navilos): $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -nostdlib -o $(navilos) $(ASM_OBJS) $(C_OBJS) -Map=$(MAP_FILE)
	$(OC) -O binary $(navilos) $(navilos_bin)

build/%.os: %.S
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(INC_DIRS) $(CFLAGS) -o $@ $<	
	#$(AS) -march=$(ARCH) -mcpu=$(MCPU) -g -o $@ $<	

build/%.o: %.c
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(INC_DIRS) $(CFLAGS) -o $@ $<
