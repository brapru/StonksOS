TARGET=stonksos-kernel8.img
RASPI ?= 4

SRCDIR=src
BUILDDIR=build
INCLUDEDIR=$(SRCDIR)/includes

CC=aarch64-linux-gnu
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only
CFLAGS += -DRASPI=$(RASPI)

CSOURCES=$(notdir $(wildcard $(SRCDIR)/*.c))
ASMSOURCES=$(notdir $(wildcard $(SRCDIR)/*.S))

OBJECTS = $(addsuffix .o,$(addprefix $(BUILDDIR)/,$(basename $(CSOURCES))))
OBJECTS = $(addsuffix .o,$(addprefix $(BUILDDIR)/,$(basename $(ASMSOURCES))))

all: $(BUILDDIR)/$(TARGET).img

$(BUILDDIR)/%_c.o: $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)
	$(CC)-gcc $(CFLAGS) -MMD -c $< -o $@

$(BUILDDIR)/%_c.o: $(SRCDIR)/%.S
	mkdir -p $(BUILDDIR)
	$(CC)-gcc $(CFLAGS) -MMD -c $< -o $@

$(TARGET).img: $(SRCDIR)/linker.ld $(OBJS)
	$(CC)-ld -T $(SRCDIR)/linker.ld -o $(BUILDDIR)/$(TARGET).elf $(OBJS)
	$(CC)-objcopy $(BUILDDIR)/$(TARGET).elf -O binary $(TARGET).img

clean:
	rm -rf $(BUILD_DIR) *.img
