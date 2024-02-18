MACH = realview-pb-a8
ARCH = armv7-a
MCPU = cortex-a8

TARGET = realview_pb

CROSS_PLATFORM = arm-none-eabi-
CC = $(CROSS_PLATFORM)gcc
AS = $(CROSS_PLATFORM)as
LD = $(CROSS_PLATFORM)gcc
OC = $(CROSS_PLATFORM)objcopy

LINKER_SCRIPT = ./navilos.ld
MAP_FILE = build/navilos.map

VPATH = boot/ \
		boot/$(TARGET) \
		hal/$(TARGET) \
		lib/

ASM_SRCS += $(notdir $(wildcard boot/$(TARGET)/*.S))
ASM_OBJS = $(patsubst %.S, build/%.os, $(ASM_SRCS))

C_SRCS = $(notdir $(wildcard boot/*.c))
C_SRCS += $(notdir $(wildcard boot/$(TARGET)/*.c))
C_SRCS += $(notdir $(wildcard hal/$(TARGET)/*.c))
C_SRCS += $(notdir $(wildcard lib/*.c))
C_OBJS = $(patsubst %.c, build/%.o, $(C_SRCS))

INC_DIRS = -I include/
INC_DIRS += -I include/mach/

CFLAGS = -c -g -std=c11		#-mthumb-interwork
LDFLAGS = -nostdlib -lgcc	#-nostartfiles -nodefaultlibs -static

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

kill:
	kill -9 `ps aux | grep 'qemu' | awk 'NR==1{print $$2}'`    

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
	$(LD) -n -T $(LINKER_SCRIPT) -o $(navilos) $(ASM_OBJS) $(C_OBJS) -Wl,-Map=$(MAP_FILE) $(LDFLAGS)
	$(OC) -O binary $(navilos) $(navilos_bin)

build/%.os: %.S
	mkdir -p $(shell dirname $@)
	$(CC) -mcpu=$(MCPU) $(INC_DIRS) $(CFLAGS) -o $@ $<	
	#$(AS) -march=$(ARCH) -mcpu=$(MCPU) -g -o $@ $<	

build/%.o: %.c
	mkdir -p $(shell dirname $@)
	$(CC) -mcpu=$(MCPU) $(INC_DIRS) $(CFLAGS) -o $@ $<
