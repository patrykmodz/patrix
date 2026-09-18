CXX = g++

CXXFLAGS = -m32 -ffreestanding -fno-exceptions -fno-rtti -fno-pie -I kernel

all: build/patrix.bin iso


# build directory
build:
	mkdir -p build


# architecture
build/boot.o: kernel/arch/x86/boot.s | build
	$(CXX) -m32 -c kernel/arch/x86/boot.s -o build/boot.o

build/io.o: kernel/arch/x86/io.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/arch/x86/io.cpp -o build/io.o

build/halt.o: kernel/arch/x86/halt.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/arch/x86/halt.cpp -o build/halt.o

#gdt
build/gdt.o: kernel/arch/x86/gdt.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/arch/x86/gdt.cpp -o build/gdt.o

build/gdt_flush.o: kernel/arch/x86/gdt_flush.s | build
	$(CXX) -m32 -c kernel/arch/x86/gdt_flush.s -o build/gdt_flush.o

#idt
build/idt.o: kernel/arch/x86/idt.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/arch/x86/idt.cpp -o build/idt.o

build/interrupt_stub.o: kernel/arch/x86/interrupt_stub.s | build
	$(CXX) -m32 -c kernel/arch/x86/interrupt_stub.s -o build/interrupt_stub.o

build/idt_flush.o: kernel/arch/x86/idt_flush.s | build
	$(CXX) -m32 -c kernel/arch/x86/idt_flush.s -o build/idt_flush.o

#pic
build/pic.o: kernel/arch/x86/pic.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/arch/x86/pic.cpp -o build/pic.o



# kernel
build/kernel.o: kernel/main.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/main.cpp -o build/kernel.o

build/boot_init.o: kernel/core/boot_init.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/core/boot_init.cpp -o build/boot_init.o

build/boot_status.o: kernel/core/boot_status.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/core/boot_status.cpp -o build/boot_status.o

build/panic.o: kernel/core/panic.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/core/panic.cpp -o build/panic.o


#drivers
build/vga.o: kernel/drivers/vga.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/drivers/vga.cpp -o build/vga.o

build/keyboard.o: kernel/drivers/keyboard/keyboard.cpp | build
	$(CXX) $(CXXFLAGS) -c kernel/drivers/keyboard/keyboard.cpp -o build/keyboard.o


# kernel binary
OBJS = \
	build/boot.o \
	build/kernel.o \
	build/boot_init.o \
	build/vga.o \
	build/io.o \
	build/gdt.o \
	build/gdt_flush.o \
	build/boot_status.o \
	build/interrupt_stub.o \
	build/idt.o \
	build/idt_flush.o \
	build/halt.o \
	build/panic.o \
	build/pic.o \
	build/keyboard.o \



build/patrix.bin: $(OBJS)
	ld -m elf_i386 -T linker.ld -o build/patrix.bin $(OBJS)


# iso
iso: build/patrix.bin grub.cfg
	mkdir -p build/isodir/boot/grub
	cp build/patrix.bin build/isodir/boot/patrix.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/patrix.iso build/isodir


# cleanup
clean:
	rm -rf build