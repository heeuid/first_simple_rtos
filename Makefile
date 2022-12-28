MACH = realview-pb-a8
ARCH = armv7-a
MCPU = cortex-a8

CROSS_PLATFORM = arm-none-eabi-
CC = $(CROSS_PLATFORM)gcc
AS = $(CROSS_PLATFORM)as
LD = $(CROSS_PLATFORM)ld
OC = $(CROSS_PLATFORM)objcopy

LINKER_SCRIPT = ./navilos.ld

ASM_SRCS = $(wildcard boot/*.S)
#ASM_OBJS = $(patsubst boot/%.S, build/%.o, $(ASM_SRCS))
ASM_OBJS = $(ASM_SRCS:boot/%.S=build/%.o)

navilos = build/navilos.axf
navilos_bin = build/navilos_bin

.PHONY: all clean run debug gdb arch

all: $(navilos)

clean:
	@rm -rf build

run: $(navilos)
	qemu-system-arm -M $(MACH) -kernel $(navilos)

debug:
	qemu-system-arm -M $(MACH) -kernel $(navilos) -S -gdb tcp::1234,ipv4

gdb:
	gdb-multiarch

arch:
	@echo MACH=$(MACH)
	@echo ARCH=$(ARCH)
	@echo MCPU=$(MCPU)

$(navilos): $(ASM_OBJS) $(LINKER_SCRIPT)
	#@echo $(ASM_OBJS)
	$(LD) -n -T $(LINKER_SCRIPT) -nostdlib -o $(navilos) $(ASM_OBJS)
	$(OC) -O binary $(navilos) $(navilos_bin)

#build/%.o: boot/%.S
$(ASM_OBJS): $(ASM_SRCS)
	mkdir -p $(shell dirname $@)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) -g -o $@ $<	
