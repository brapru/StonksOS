TARGET=stonksos-kernel8
RASPI=4

SRCDIR=kernel
BUILDDIR=build
INCLUDEDIRS=-Iinclude \
	    -Iinclude/peripherals \
	    -Iinclude/stonksos

CTOOL=aarch64-linux-gnu
CC=$(CTOOL)-gcc
CXX=$(CTOOL)-g++
LD=$(CTOOL)-ld
OBJCOPY=$(CTOOL)-objcopy
GDB=$(CTOOL)-gdb

CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding $(INCLUDEDIRS) -mgeneral-regs-only
CFLAGS += -DRPI_VERSION=$(RASPI)

LIBKFLAGS = -D__is_libk

.PHONY: all clean

all: $(BUILDDIR)/$(TARGET).img

CXXSOURCES=$(notdir $(wildcard $(SRCDIR)/*.cpp))
CXXSOURCES += $(notdir $(wildcard lib/*/*.cpp))
ASMSOURCES=$(notdir $(wildcard $(SRCDIR)/*.S))
ASMSOURCES += $(notdir $(wildcard arch/aarch64/boot/*.S))

OBJECTS = $(addsuffix .o,$(addprefix $(BUILDDIR)/,$(basename $(CXXSOURCES))))
OBJECTS += $(addsuffix .o,$(addprefix $(BUILDDIR)/,$(basename $(ASMSOURCES))))

$(BUILDDIR)/$(TARGET).img: $(SRCDIR)/linker.ld $(OBJECTS)
	$(LD) -T $(SRCDIR)/linker.ld -o $(BUILDDIR)/$(TARGET).elf $(OBJECTS)
	$(OBJCOPY) $(BUILDDIR)/$(TARGET).elf -O binary $(BUILDDIR)/$(TARGET)-$(RASPI).img

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p build
	$(CXX) $(CFLAGS) $(INCLUDEDIRS) -c -MMD $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.S
	@mkdir -p build
	$(CXX) $(INCLUDEDIRS) -MMD -c $< -o $@

$(BUILDDIR)/%.o: arch/aarch64/boot/%.S
	@mkdir -p build
	$(CXX) $(INCLUDEDIRS) -MMD -c $< -o $@

$(BUILDDIR)/%.o: lib/string/%.cpp
	@mkdir -p build
	$(CXX) $(CFLAGS) $(LIBKFLAGS) -MMD -c $< -o $@

$(BUILDDIR)/%.o: lib/stdio/%.cpp
	@mkdir -p build
	$(CXX) $(CFLAGS) $(LIBKFLAGS) -MMD -c $< -o $@

$(BUILDDIR)/%.o: lib/stdlib/%.cpp
	@mkdir -p build
	$(CXX) $(CFLAGS) $(LIBKFLAGS) -MMD -c $< -o $@

rpi3:
	$(MAKE) RASPI=3

rpi4:
	$(MAKE) RASPI=4

qemu:
	$(MAKE) clean
	$(MAKE) RASPI=3
	qemu-system-aarch64 -M raspi3 \
	-nographic -serial null -chardev stdio,id=tty0 \
	-serial chardev:tty0 -monitor none \
	-kernel ./build/stonksos-kernel8-3.img

clean:
	rm -rf $(BUILDDIR) *.img
