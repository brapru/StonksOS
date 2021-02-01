TARGET=stonksos-kernel8
RASPI ?= 4

SRCDIR=kernel
BUILDDIR=build
INCLUDEDIR=include

CTOOL=aarch64-linux-gnu
CC=$(CTOOL)-gcc
CXX=$(CTOOL)-cpp
LD=$(CTOOL)-ld
OBJCOPY=$(CTOOL)-objcopy
GDB=$(CTOOL)-gdb

CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -I$(INCLUDEDIR) -mgeneral-regs-only
CFLAGS += -DRASPI=$(RASPI)

all: $(BUILDDIR)/$(TARGET).img

CXXSOURCES=$(notdir $(wildcard $(SRCDIR)/*.cpp))
ASMSOURCES=$(notdir $(wildcard $(SRCDIR)/*.S))
ASMSOURCES += $(notdir $(wildcard arch/aarch64/boot/*.S))

OBJECTS = $(CXXSOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%_cpp.o)
OBJECTS += $(ASMSOURCES:$(SRCDIR)/%.S=$(BUILDDIR)/%_s.o)

DEP_FILES = $(OBJECTS:%o=%.d)
-include $(DEP_FILES)

$(BUILDDIR)/$(TARGET).img: $(SRCDIR)/linker.ld $(OBJECTS)
	$(LD) -T $(SRCDIR)/linker.ld -o $(BUILDDIR)/$(TARGET).elf $(OBJECTS)
	$(OBJCOPY) $(BUILDDIR)/$(TARGET).elf -O binary $(TARGET).img

$(BUILDDIR)/%_cpp.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CFLAGS) -MMD -c $< -o $@

$(BUILDDIR)/%_s.o: $(SRCDIR)/%.S
	mkdir -p $(@D)
	$(CXX) -I$(INCLUDES) -MMD -c $< -o $@

clean:
	rm -rf $(BUILDDIR) *.img
